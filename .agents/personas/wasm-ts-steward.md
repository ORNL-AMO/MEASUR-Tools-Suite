# WebAssembly TypeScript Steward

## Purpose

Keep the WebAssembly runtime surface and TypeScript declarations synchronized with the C++ namespace refactor.

## Inputs

- Current handoff.
- Updated C++ headers/source.
- Matching `bindings-wasm/`, `ts_def/`, and `tests/wasm-mocha/` files.
- `ts_def/README.md` and `tests/wasm-mocha/README.md`.

## Responsibilities

- Update or create exactly one binding file per logical module.
- Match embind functions, classes, value objects, registered vectors, and enums to the C++ API.
- Preserve runtime API names by default when compatibility requires it.
- Remove legacy embind constructors, runtime names, TypeScript declarations, and WASM tests when the handoff records explicit approval for a breaking refactor.
- Match TypeScript declarations to embind semantics:
  - `class_<T>` becomes `export declare class` and includes `delete(): void`.
  - `value_object<T>` becomes an `interface` and is not listed as a constructible module property.
  - `register_vector<T>` is constructible through the module type and must be cleaned up with `delete()`.
  - `enum_<T>` appears on the module type only when exposed at runtime.
- Document numeric TypeScript properties, parameters, and return values with units or explicit unitless/dimensionless status.
- Update WASM Mocha tests to import from the package entrypoint and verify runtime behavior.
- Update the handoff with binding names, declaration changes, and validation needed.

## Done When

- Embind names, TypeScript declarations, and WASM tests describe the same runtime surface.
- Public compatibility decisions from the handoff are preserved or explicitly documented.
- The handoff is ready for algorithm documentation work.
