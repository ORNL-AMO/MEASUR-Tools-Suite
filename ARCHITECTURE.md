# Architecture Overview

MEASUR Tools Suite is a layered calculation library. The authoritative calculations are implemented in C++, exposed to browser and Node.js consumers through Emscripten WebAssembly bindings, and described for TypeScript consumers through declaration files.

## Layers

```text
Engineering formulas and data
        |
        v
Public C++ headers          include/<domain>/
C++ implementations         src/<domain>/
C++ tests                   tests/cpp/
        |
        v
WebAssembly bindings        bindings-wasm/<domain>/
Browser WASM tests          tests/wasm-mocha/<domain>/
TypeScript declarations     ts_def/ts_def_modules/<domain>/
        |
        v
Package entrypoint          bin/client.js + bin/client.wasm
TypeScript entrypoint       ts_def/client.d.ts
```

Consumers import the public npm package root. Its `package.json` resolves the
WebAssembly module factory to `bin/client.js` and TypeScript declarations to
`ts_def/client.d.ts`; `bin/client.wasm` is the accompanying runtime asset.

## Repository Map

| Path | Purpose |
| --- | --- |
| `include/` | Public C++ headers and module contracts. |
| `src/` | C++ implementations. |
| `bindings-wasm/` | Emscripten embind bindings that define the JavaScript/WASM runtime API. |
| `ts_def/` | TypeScript declarations mirroring the runtime API. See [ts_def/README.md](ts_def/README.md). |
| `tests/cpp/` | Catch2 C++ unit tests. |
| `tests/wasm-mocha/` | Browser-based Mocha tests for the WebAssembly package. |
| `tests/wasm/` | Legacy WASM tests; migrate active tests to `tests/wasm-mocha/`. |
| `docs/dox-content/` | Doxygen calculation documentation for engineering users. |
| `contributing/` | Style, documentation, formatting, and commit guidance. |
| `BUILD.md` | Build, test, packaging, WebAssembly, and Docker workflows. |
| `AGENTS.md` | Canonical guidance for AI agents and automation. |

## Domain Modules

Top-level domains are mirrored across `include/`, `src/`, `bindings-wasm/`, `ts_def/`, and tests where applicable:

- `compressedAir`
- `databases`
- `motorDriven`
- `other`
- `physics`
- `processCooling`
- `processHeat`
- `steam`
- `steamModeler`
- `treasureHunt`
- `wasteWater`
- `water`

When adding or refactoring a calculation, keep the same logical module name across layers. For example, a new `src/processHeat/foo.cpp` should have a matching public header, binding file, declaration file, tests, and documentation where appropriate.

## C++ Layer

The C++ layer owns calculation behavior. Headers in `include/` define public data structures and calculator APIs. Implementations in `src/` should follow the project style guide:

- Prefer explicit, named structs for passive data.
- Use namespaces that match the module path.
- Keep declarations and implementations paired.
- Use `const` and references intentionally to avoid unnecessary copies.
- Include what you use.

Unit tests should exercise formulas and edge cases at the C++ layer when behavior changes independent of WebAssembly.

## WebAssembly Binding Layer

Bindings in `bindings-wasm/` define the JavaScript runtime surface. Treat binding names as public API:

- `class_<T>("Name")` exposes a runtime constructor and embind instance methods.
- `value_object<T>("Name")` accepts and returns plain JavaScript objects.
- `register_vector<T>("Name")` exposes a runtime vector with `size()`, `get()`, `push_back()`, and `delete()`.
- `enum_<T>("Name")` exposes a runtime enum object.

Keep one binding file per logical C++ module. Avoid grouping unrelated modules into one binding file because it makes tests, declarations, and downstream migration harder.

## TypeScript Declaration Layer

Declarations in `ts_def/` describe the WebAssembly runtime API. They should match embind semantics exactly:

- Runtime classes are `export declare class` declarations with `delete(): void`.
- Value objects are `interface` declarations and should not require cleanup.
- Registered vectors extend the shared `RegisteredVector<T>` type and are exposed through `RegisteredVectorsModule`.
- Module type aliases should include only properties that exist on the initialized WebAssembly module.
- `ts_def/client.d.ts` re-exports all module declarations and defines `MeasurToolsSuite`, the typed initialized module instance.

Declaration comments are part of the public developer experience. Every numeric public property, constructor parameter, function parameter, and numeric return value should document units or explicitly say `dimensionless`, `unitless`, or `count`. Follow [ts_def/README.md](ts_def/README.md) for the full typing documentation checklist.

When a TypeScript test needs casts such as `as any`, check the binding and declaration first; the declaration is often wrong or incomplete.

## WebAssembly Test Layer

`tests/wasm-mocha/` tests run in Karma/Chrome against `bin/client.js` and `bin/client.wasm`. New tests should use the typed package entrypoint:

```ts
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';
```

Follow [tests/wasm-mocha/README.md](tests/wasm-mocha/README.md) for migration details. Clean up embind classes and vectors with `delete()`. Do not call `delete()` on value-object results.

## Documentation Layer

Use Doxygen comments for public C++ APIs and `.dox` files for calculation narratives. Documentation should explain engineering intent, units, formulas, and assumptions, not just repeat code structure.

Follow [contributing/documentation.md](contributing/documentation.md) for Doxygen commands, formula syntax, and symbol tables.

## Build and Packaging

Common build products:

- Native C++ build: `build-cpp/`
- WebAssembly build: `build-wasm/`
- Runtime package artifacts: `bin/client.js` and `bin/client.wasm`

Use separate build directories for native and WebAssembly builds to avoid stale CMake cache state. See [BUILD.md](BUILD.md) for full commands.

## Development Workflow

For calculation changes, work from the core outward:

1. Update C++ headers and source.
2. Update or add C++ tests.
3. Update WebAssembly bindings.
4. Update TypeScript declarations.
5. Update WASM Mocha tests.
6. Update documentation and examples.
7. Run the narrowest useful validation first, then broader tests before handoff.

For declaration-only or test migration work, still inspect the matching binding file before changing types. The binding file is the runtime source of truth for TypeScript declarations.

## Validation Matrix

| Change | Minimum validation |
| --- | --- |
| C++ formula or data model | Build C++; run relevant `tests/cpp` or `cpp_tests`. |
| WASM binding | Rebuild WASM; run affected `tests/wasm-mocha` tests. |
| TypeScript declarations | `./node_modules/.bin/tsc --noEmit`; run affected WASM tests. |
| Packaging | Build package or inspect packed contents for `client.js`, `client.wasm`, and declarations. |
| Documentation | Check links, Doxygen syntax, and `git diff --check`. |

Prefer adding focused tests near the changed module instead of relying only on large integration coverage.
