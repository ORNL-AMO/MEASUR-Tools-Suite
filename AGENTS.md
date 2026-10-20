# Agent Development Guide

This is the canonical repository guidance for AI agents and automation tools. Tool-specific files such as `.claude/CLAUDE.md` and `.github/copilot-instructions.md` should stay thin and point back here instead of duplicating policy.

## Start Here

Before changing code, read the relevant project guidance:

- [ARCHITECTURE.md](ARCHITECTURE.md) for repository layout, module boundaries, and the C++ to WebAssembly to TypeScript flow.
- [BUILD.md](BUILD.md) for build, test, WebAssembly, package, and Docker commands.
- [contributing/style-guide.md](contributing/style-guide.md) for C++ style and naming.
- [contributing/documentation.md](contributing/documentation.md) for Doxygen and `.dox` documentation standards.
- [.agents/README.md](.agents/README.md) when coordinating persona-driven namespace refactors and algorithm documentation.
- [docs/development/suite-desktop-change-workflow.md](docs/development/suite-desktop-change-workflow.md) when a Suite change affects AMO-Tools-Desktop.
- [ts_def/README.md](ts_def/README.md) when adding or correcting TypeScript declarations.
- [tests/wasm-mocha/README.md](tests/wasm-mocha/README.md) when adding or migrating WebAssembly Mocha tests.

If any referenced file is unavailable in context, ask the user for it before proceeding.

## Repository Context

MEASUR Tools Suite is a C++ calculation library with WebAssembly bindings for browser and Node.js use. The project exposes computational engines for the MEASUR / AMO-Tools-Desktop ecosystem.

The core development pattern is:

```text
include/              public C++ headers
src/                  C++ implementations
bindings-wasm/        embind WebAssembly bindings
ts_def/               TypeScript declaration files for the WASM package
tests/cpp/            C++ unit tests
tests/wasm-mocha/     browser-based WebAssembly tests
docs/dox-content/     calculation documentation
```

## Agent Operating Principles

- Prefer small, reviewable changes that preserve existing module boundaries.
- Read nearby implementation, bindings, declarations, and tests before editing.
- Keep source, binding, TypeScript declaration, tests, and documentation in sync.
- Do not invent new abstractions unless they reduce real duplication or match an established local pattern.
- Preserve public API compatibility unless the user explicitly requests a breaking change. When a breaking change is necessary, document the old-to-new migration.
- When a user explicitly approves a breaking namespace/module refactor, remove obsolete compatibility wrappers, legacy headers, legacy runtime constructors, and compatibility-only tests instead of keeping old support code in parallel.
- Do not revert or overwrite unrelated user changes in a dirty worktree.
- Use structured tools and parsers when available. Avoid brittle ad hoc text rewrites for structured data.

## One Module Rule

Maintain one file per logical module whenever refactoring or adding calculations:

- One `.h`/`.cpp` pair for the C++ module.
- One matching binding file in `bindings-wasm/`.
- One C++ test file for each C++ module where applicable.
- One WebAssembly Mocha test file for each binding file.
- One TypeScript declaration file for each public binding surface.
- Documentation organized under `docs/dox-content/` following nearby examples.

Use these current examples instead of inferring a pattern from an entire domain:

| Pattern | Canonical example |
| --- | --- |
| Stateless value-object calculator | `compressedAir/dryer_operating_cost` |
| Runtime class requiring `delete()` | `compressedAir/pipe_data` |
| Registered vector | `compressedAir/assessment/compressor_catalog` |
| Runtime enum | `compressedAir/dryer_operating_cost` |
| Multi-formula algorithm documentation | `docs/dox-content/calculators/compressedAir/assessment/load_unload_cycle_model.dox` |

## Namespace or Module Refactor Phases

When asked to refactor code using namespaces or to split modules, work in this order:

1. **C++ API and Tests**: Update headers, source, and focused C++ tests together.
2. **WebAssembly Surface and Tests**: Update the binding, TypeScript declaration, module export, and WASM Mocha test together. Move migrated tests from `tests/wasm/` and delete obsolete originals.
3. **Algorithm Documentation**: Update `docs/dox-content/` and related examples when public behavior, formulas, usage, or module organization changed.
4. **Integrated and Downstream Verification**: Rebuild and stage WASM, run the affected validation, and verify AMO-Tools-Desktop impact when applicable.

For namespace refactors that include algorithm documentation, use the repo-neutral persona workflow in [.agents/README.md](.agents/README.md). The default sequence is:

1. **Refactor Planner**: Map the target module across all layers and classify public API compatibility.
2. **C++ Namespace Refactorer**: Update headers, source, namespace shape, Doxygen API comments, and C++ tests.
3. **WebAssembly TypeScript Steward**: Update embind bindings, TypeScript declarations, module exports, and WASM Mocha tests.
4. **Algorithm Docs Author**: Write or update engineer-facing `.dox` documentation with formulas, units, and symbol tables.
5. **Verification Reviewer**: Check cross-layer consistency, public compatibility, documentation math, tests, and validation notes.

Each persona must consume and update the shared handoff template in [.agents/templates/refactor-handoff.md](.agents/templates/refactor-handoff.md). Preserve public API compatibility by default unless the user explicitly approves a breaking change.
When a breaking change is approved, the handoff must record the old-to-new migration and downstream layers should remove the superseded API surface rather than adding wrapper code for the deleted shape.

Repo-scoped skills under `.agents/skills/` package the recurring workflows:

- `refactor-and-document-calculation` for cross-layer calculation refactors and algorithm documentation.
- `coordinate-suite-desktop-change` for changes that affect the Desktop consumer, release order, or GitHub coordination.

GitHub Copilot PR review uses `.github/skills/measur-code-review/`. AI review is advisory and does not replace required human approval.

## WebAssembly and TypeScript Rules

Match declarations to embind bindings:

- `class_<T>("Name")` is a runtime class. Declare it as `export declare class Name` and include `delete(): void`.
- `value_object<T>("Name")` is passed as a plain object. Declare it as an `interface`; do not require `delete()`.
- `register_vector<T>("Name")` is a constructible runtime vector. Expose a constructor through the module type and clean instances up with `delete()`.
- `enum_<T>("Name")` is a runtime enum. Add it to the module type only when the binding file exposes it.
- Module types should include runtime properties only. Export type-only interfaces, but do not list them as module properties.
- Document all public declarations. At minimum, every numeric property, parameter, and return value needs units or explicit dimensionless/unitless status.
- Prefer importing from the package entrypoint in TypeScript tests:

```ts
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';
```

## Testing Expectations

Choose verification based on the changed surface:

- C++ source or headers: build and run relevant C++ tests.
- WASM bindings or TypeScript declarations: run `npm run verify:wasm` so tests use a newly built and staged module.
- Browser-facing changes: verify `bin/client.js` and `bin/client.wasm` are built and served correctly.
- Documentation-only changes: run markdown or whitespace checks when available, and ensure links are correct.

Common commands:

```bash
cmake -S . -B build-cpp
cmake --build build-cpp
./build-cpp/bin/cpp_tests
npm run build:wasm
./node_modules/.bin/tsc --noEmit
npm run tests
git diff --check
```

Do not claim tests passed unless you ran them. If a command cannot run in the environment, report that plainly with the reason.

## Documentation Expectations

- Use Doxygen comments for public C++ classes, structs, functions, enums, and files.
- Use `.dox` files for calculation-level documentation aimed at engineering users.
- Keep formulas, units, and symbol tables consistent with [contributing/documentation.md](contributing/documentation.md).
- Update examples when public WebAssembly or TypeScript usage changes.

## Completion Checklist

Before handing work back, verify:

- [ ] Source changes match the existing module pattern.
- [ ] Bindings match headers and runtime names exactly.
- [ ] TypeScript declarations match embind semantics.
- [ ] C++ and WASM tests cover the changed public behavior.
- [ ] Documentation and examples are updated for public changes.
- [ ] Formatting, whitespace, and generated artifacts are intentional.
