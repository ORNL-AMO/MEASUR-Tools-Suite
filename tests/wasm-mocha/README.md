# WASM Mocha TypeScript Test Guide

This folder contains browser-based Mocha tests for the WebAssembly bindings. New
tests should be written in TypeScript, and existing `.js` tests should be
migrated to `.ts` when the corresponding typings are available.

Use the database tests and compressed air tests as the current examples:

- `tests/wasm-mocha/databases/*.test.ts`
- `tests/wasm-mocha/compressedAir/**/*.test.ts`

## Standard Test Shape

Import the module factory and the types from the package entrypoint. The Karma
webpack config aliases this entrypoint to `bin/client.js` at runtime and
TypeScript resolves it to `ts_def/client.d.ts`.

```ts
import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type PipeSizingInput,
    type PipeSizingResult,
} from 'measur-tools-suite';

describe('Example WASM Test', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('calculates a typed result', function () {
        const input: PipeSizingInput = {
            airflow: 1000,
            airlinePressure: 90,
            designVelocity: 25,
            atmosphericPressure: 14.5
        };
        const result: PipeSizingResult = moduleInstance.calculatePipeSize(input);

        assert.approximately(result.crossSectionalArea, 13.3205741627, 0.01);
    });
});
```

Prefer this import pattern over dynamic imports from `bin/client.js`. It keeps
the test exercising the same public TypeScript surface users consume.

## Embind Typing Rules

When a test migration exposes incorrect typings, update the `.d.ts` files to
match the bindings in `bindings-wasm/`.

Use these rules when comparing a declaration to an embind binding:

- `class_<T>("Name")` is a runtime class. Declare it as `export declare class`
  and include `delete(): void` on instances returned to JavaScript.
- `value_object<T>("Name")` is converted from plain JavaScript objects. Declare
  it as an `interface` and do not require `delete(): void`.
- `register_vector<T>("Name")` is a constructible runtime vector. The module
  type should expose a constructor, for example `DoubleVector:
  RegisteredVectorConstructor<DoubleVector>`.
- `enum_<T>("Name")` is a runtime enum only when it appears in the binding file.
  If C++ uses numeric enum fields but no `enum_` binding exists, use
  `declare const enum` or a numeric union type and do not add it to the
  `MeasurToolsSuite` module type.
- Module type intersections should only include runtime properties that actually
  exist on the initialized WASM module. Type-only interfaces should be exported
  from their `.d.ts` file, but should not be listed as module properties.

## Object Cleanup

Clean up embind class instances that the test creates or receives:

```ts
const calculator = new moduleInstance.AirVelocity(1800, 100, 14.7);
const result = calculator.calculate();

try {
    assert.approximately(result.oneHalf, 1845.510026, 0.01);
} finally {
    result.delete();
    calculator.delete();
}
```

Do not call `delete()` on plain value-object inputs or value-object results.

## Migration Checklist

1. Rename the test from `.test.js` to `.test.ts`.
2. Replace dynamic `bin/client.js` imports with `createModule` from
   `measur-tools-suite`.
3. Type the module as `MeasurToolsSuite`.
4. Type inputs and results with exported interfaces/classes from `ts_def`.
5. Check the matching `bindings-wasm/` file if a type does not match runtime
   behavior.
6. Keep assertions and expected values unchanged unless the old test was
   incorrect.
7. Delete the old `.js` test once the `.ts` replacement passes.
8. Run:

```bash
./node_modules/.bin/tsc --noEmit
npm run tests
```

`npm run tests` starts Karma on a local port. In restricted environments it may
need permission to bind that port.

## Agent Notes

For future agent work, read the relevant existing `.test.ts` examples first,
then inspect the matching `bindings-wasm/` and `ts_def/` files before editing.
If a test only passes by adding casts such as `as any`, the declaration probably
needs to be corrected instead.
