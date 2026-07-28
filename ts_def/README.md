# TypeScript Declaration Authoring Guide

This directory contains the public TypeScript declarations for the WebAssembly package. Declarations are part of the user-facing API and should be maintained with the same care as C++ headers and embind bindings.

## Source of Truth

Use the matching `bindings-wasm/` file as the runtime source of truth, then use C++ headers, implementations, tests, and docs to fill in semantics and units.

```text
bindings-wasm/<domain>/<module>.cpp     runtime names and embind kind
include/<domain>/<module>.h             public C++ inputs, outputs, and units
src/<domain>/<module>.cpp               formulas and default behavior
tests/wasm-mocha/<domain>/              expected JavaScript usage
docs/dox-content/                       calculation intent, equations, and units
```

Do not add a type because it seems useful downstream unless the initialized WebAssembly module actually exposes that runtime property.

## Required Documentation

Every public declaration file should include:

- A top-level module summary describing the calculator or data group.
- JSDoc/TSDoc comments for every exported enum, interface, class, and function.
- Per-member comments for every public property.
- Constructor parameter comments for every public class constructor.
- Function `@param` and `@returns` comments for every exported function.
- Cleanup guidance on embind classes and vectors that require `delete()`.

Comments should explain user-facing meaning, not just restate the property name.

## Units Requirement

At minimum, every numeric property, constructor parameter, function parameter, and numeric return value must document units.

Use one of these forms consistently:

- `units kWh/year`
- `units degF`
- `units scfm`
- `units $/kWh`
- `dimensionless`
- `dimensionless, 0-1`
- `unitless enum`
- `count`

For booleans, strings, enums, and nested objects, document meaning instead of units. For example, `true when using nameplate data` or `enum selecting the measurement method`.

Do not guess units. If bindings and C++ sources do not make units clear, inspect tests, documentation, and downstream usage. If units still cannot be established, call this out in the PR or handoff and avoid presenting a guessed unit as fact.

## Embind Mapping Rules

Match declarations to embind exactly:

- `class_<T>("Name")`: declare `export declare class Name`. Include constructors, methods, public properties, and `delete(): void`.
- `value_object<T>("Name")`: declare an `interface`. Use plain object shapes. Do not include `delete(): void`.
- `register_vector<T>("Name")`: declare an interface extending `RegisteredVector<T>` and expose a constructor in `RegisteredVectorsModule`.
- `enum_<T>("Name")`: declare an enum and expose it on the module type.
- `function("name", ...)`: declare an exported function and expose it on the matching module type.

Module type aliases should include only runtime properties that exist on the initialized module: classes, functions, enums, and registered vector constructors. Type-only interfaces should be exported, but should not appear as module properties.

## File Structure

Use this order unless a nearby module has a stronger established pattern:

1. File-level summary.
2. Imports, using `import type` for type-only imports.
3. Enums.
4. Input and output interfaces or classes.
5. Calculator functions.
6. Module type alias.

Keep names aligned with embind runtime names. Do not rename declaration symbols independently of the binding surface.

## Example Value Object

```ts
/**
 * Input data for pipe sizing.
 *
 * @property airflow Airflow through the pipe, units scfm
 * @property airlinePressure Airline pressure, units psig
 * @property designVelocity Target design velocity, units ft/s
 * @property atmosphericPressure Atmospheric pressure, units psia
 */
export interface PipeSizingInput {
    /** Airflow through the pipe, units scfm */
    airflow: number;
    /** Airline pressure, units psig */
    airlinePressure: number;
    /** Target design velocity, units ft/s */
    designVelocity: number;
    /** Atmospheric pressure, units psia */
    atmosphericPressure: number;
}
```

Because this is a `value_object`, callers pass a plain object and do not call `delete()`.

## Example Runtime Class

```ts
/**
 * Dryer operating cost calculator.
 */
export declare class DryerOperatingCost {
    /**
     * @param airflow Dryer airflow, units scfm
     * @param inletPressure Inlet pressure, units psig
     * @param averageSystemDemand Average system demand, units %
     */
    constructor(airflow: number, inletPressure: number, averageSystemDemand: number);

    /**
     * Calculate dryer operating cost for the selected dryer type.
     * @param dryerType Dryer type enum.
     * @returns Annual dryer operating cost results.
     */
    calculate(dryerType: DryerType): DryerOperatingCostOutput;

    /** Frees the underlying embind resource. Call when finished with the instance. */
    delete(): void;
}
```

Because this is a `class_`, callers must clean up instances and class outputs with `delete()`.

## Validation Checklist

Before finishing declaration work:

- [ ] The matching `bindings-wasm/` file was inspected.
- [ ] Each runtime class, function, enum, and vector is present in the module type.
- [ ] Type-only interfaces are not listed as runtime module properties.
- [ ] Every numeric public field, parameter, and return documents units or dimensionless status.
- [ ] Cleanup requirements match embind semantics.
- [ ] `ts_def/client.d.ts` exports the new declaration file and includes its module type in `MeasurToolsSuite`.
- [ ] A typed WASM Mocha test exercises the declaration through `createModule`.
- [ ] `./node_modules/.bin/tsc --noEmit` passes.
