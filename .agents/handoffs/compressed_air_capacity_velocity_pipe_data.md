# Refactor Handoff

## Target Module

- Domain/path: `compressedAir`
- Logical module: Coordinated refactor of `AirSystemCapacity`, `AirVelocity`, and shared `PipeData`
- Original files:
  - `include/compressedAir/AirSystemCapacity.h`
  - `include/compressedAir/AirVelocity.h`
  - `include/compressedAir/PipeData.h`
  - `bindings-wasm/compressedAir/compressedAir.cpp`
  - `ts_def/ts_def_modules/compressedAir/compressedAir.d.ts`
  - `tests/cpp/compressedAir/CompressedAir.unit.cpp`
  - `tests/wasm-mocha/compressedAir/wasm_air_system_capacity.test.ts`
  - `tests/wasm-mocha/compressedAir/wasm_air_velocity.test.ts`
- Current files after refactor:
  - `include/compressedAir/pipe_data.h`
  - `src/compressedAir/pipe_data.cpp`
  - `include/compressedAir/air_system_capacity.h`
  - `src/compressedAir/air_system_capacity.cpp`
  - `include/compressedAir/air_velocity.h`
  - `src/compressedAir/air_velocity.cpp`
  - `bindings-wasm/compressedAir/pipe_data.cpp`
  - `bindings-wasm/compressedAir/air_system_capacity.cpp`
  - `bindings-wasm/compressedAir/air_velocity.cpp`
  - `ts_def/ts_def_modules/compressedAir/pipe_data.d.ts`
  - `ts_def/ts_def_modules/compressedAir/air_system_capacity.d.ts`
  - `ts_def/ts_def_modules/compressedAir/air_velocity.d.ts`
  - `ts_def/ts_def_modules/compressedAir/compressedAir.d.ts`
  - `tests/cpp/compressedAir/pipe_data.unit.cpp`
  - `tests/cpp/compressedAir/air_system_capacity.unit.cpp`
  - `tests/cpp/compressedAir/air_velocity.unit.cpp`
  - `tests/wasm-mocha/compressedAir/wasm_pipe_data.test.ts`
  - `tests/wasm-mocha/compressedAir/wasm_air_system_capacity.test.ts`
  - `tests/wasm-mocha/compressedAir/wasm_air_velocity.test.ts`
- Nearby examples:
  - `include/compressedAir/pipe_sizing.h`
  - `src/compressedAir/pipe_sizing.cpp`
  - `bindings-wasm/compressedAir/pipe_sizing.cpp`
  - `ts_def/ts_def_modules/compressedAir/pipe_sizing.d.ts`
  - `include/compressedAir/leak_survey/compressed_air_leak_survey.h`
  - `src/compressedAir/leak_survey/compressed_air_leak_survey.cpp`
  - `bindings-wasm/compressedAir/leak_survey/compressed_air_leak_survey.cpp`
  - `docs/dox-content/calculators/compressedAir/pipe_sizing_calculator.dox`

## Current Public API

- Original C++ symbols:
  - Global `struct PipeData`
  - Global `class AirSystemCapacity`
  - Nested `AirSystemCapacity::Output`
  - Global `class AirVelocity`
  - `AirSystemCapacity::calculate()`
  - `AirVelocity::calculate()`
- Original embind runtime names:
  - `PipeData`
  - `AirSystemCapacity`
  - `AirSystemCapacityOutput`
  - `AirVelocity`
  - `calculate` instance method on `AirSystemCapacity` and `AirVelocity`
- Original TypeScript declarations:
  - `PipeData`, `AirSystemCapacity`, `AirSystemCapacityOutput`, and `AirVelocity` runtime classes in `compressedAir.d.ts`
  - `CompressedAirModule` module type exposing those runtime classes
- Test-visible behavior:
  - `PipeData` constructor receives pipe lengths in ft and stores per-size pipe volumes in ft3.
  - `AirSystemCapacity` receives `PipeData` plus receiver capacities in gal, returns total pipe volume, receiver volumes in ft3, total capacity in ft3, and per-size pipe volumes.
  - `AirVelocity` receives airflow in scfm, pipe pressure in psig, and atmospheric pressure in psia, then returns velocities by pipe size in ft/s.

## Proposed Namespace API

- Namespace:
  - `pipe_data`
  - `air_system_capacity`
  - `air_velocity`
- Functions:
  - `air_system_capacity::calculate(const Input&) -> Output`
  - `air_velocity::calculate(const Input&) -> pipe_data::PipeData`
- Structs/value objects:
  - `pipe_data::PipeData`
  - `air_system_capacity::Input`
  - `air_system_capacity::Output`
  - `air_velocity::Input`
- Enums: none
- Runtime names to preserve:
  - `PipeData`
  - `AirSystemCapacityInput`
  - `AirSystemCapacityOutput`
  - `AirVelocityInput`
  - `calculateAirSystemCapacity`
  - `calculateAirVelocity`

## Compatibility Decision

- Default: preserve public compatibility.
- Decision: Intentionally breaking after user approval. Do not retain wrapper classes, legacy PascalCase headers, legacy runtime constructors, or compatibility-only tests.
- Migration notes needed:
  - C++ callers that included `compressedAir/AirSystemCapacity.h`, `compressedAir/AirVelocity.h`, or `compressedAir/PipeData.h` must switch to `compressedAir/air_system_capacity.h`, `compressedAir/air_velocity.h`, or `compressedAir/pipe_data.h`.
  - C++ callers should use `air_system_capacity::calculate({pipe_lengths, receivers})` and `air_velocity::calculate({airflow, pipe_pressure, atmospheric_pressure})`.
  - WASM/TypeScript callers should replace `new AirSystemCapacity(pipeData, receivers).calculate()` with `calculateAirSystemCapacity({ pipeLengths: pipeData, receivers })`.
  - WASM/TypeScript callers should replace `new AirVelocity(airFlow, pipePressure, atmosphericPressure).calculate()` with `calculateAirVelocity({ airFlow, pipePressure, atmosphericPressure })`.
  - `AirSystemCapacityOutput` is now an embind `value_object` interface rather than a runtime class. Do not call `delete()` on the output object itself; clean up nested `receiverCapacities` and `pipeLengths` runtime objects when finished.
- User approval for breaking changes: Approved by follow-up requests to remove old implementation files and then remove legacy support methods/wrapper code altogether.
- Removed legacy surfaces:
  - `include/compressedAir/AirSystemCapacity.h`
  - `include/compressedAir/AirVelocity.h`
  - `include/compressedAir/PipeData.h`
  - C++ wrapper classes `air_system_capacity::AirSystemCapacity` and `air_velocity::AirVelocity`
  - Embind runtime classes `AirSystemCapacity` and `AirVelocity`
  - Embind constructor/class binding for `AirSystemCapacityOutput`
  - TypeScript class declarations for `AirSystemCapacity`, `AirVelocity`, and class-shaped `AirSystemCapacityOutput`
  - Compatibility-only C++ and WASM tests for the deleted constructor-and-instance-method path

## Touched Layers

- Headers/source:
  - Added `include/compressedAir/pipe_data.h`, `src/compressedAir/pipe_data.cpp`
  - Added `include/compressedAir/air_system_capacity.h`, `src/compressedAir/air_system_capacity.cpp`
  - Added `include/compressedAir/air_velocity.h`, `src/compressedAir/air_velocity.cpp`
  - Removed legacy `AirSystemCapacity.h`, `AirVelocity.h`, and `PipeData.h` after user approval.
  - Removed compatibility wrapper classes from the new snake_case modules after explicit user approval.
  - Made `pipe_data::PipeData` default-constructible and assignable so embind value-object inputs/results can carry it.
- C++ tests:
  - Replaced combined `CompressedAir.unit.cpp` coverage with namespace-focused module tests:
    - `tests/cpp/compressedAir/pipe_data.unit.cpp`
    - `tests/cpp/compressedAir/air_system_capacity.unit.cpp`
    - `tests/cpp/compressedAir/air_velocity.unit.cpp`
- WebAssembly bindings:
  - Split old `compressedAir.cpp` into one binding file each for `pipe_data`, `air_system_capacity`, and `air_velocity`.
  - Kept `PipeData` as the shared runtime class.
  - Replaced `AirSystemCapacity` and `AirVelocity` runtime classes with `calculateAirSystemCapacity` and `calculateAirVelocity` module functions.
  - Replaced class-shaped `AirSystemCapacityOutput` with an embind `value_object`.
  - Added `AirSystemCapacityInput`, `AirSystemCapacityOutput`, and `AirVelocityInput` value objects.
- TypeScript declarations:
  - Added one declaration file per binding surface:
    - `ts_def/ts_def_modules/compressedAir/pipe_data.d.ts`
    - `ts_def/ts_def_modules/compressedAir/air_system_capacity.d.ts`
    - `ts_def/ts_def_modules/compressedAir/air_velocity.d.ts`
  - Kept `compressedAir.d.ts` as a barrel and module type aggregator.
  - Removed old calculator class declarations and represented value objects as interfaces.
- WASM Mocha tests:
  - Updated runtime tests to call `calculateAirSystemCapacity` and `calculateAirVelocity`.
  - Added `tests/wasm-mocha/compressedAir/wasm_pipe_data.test.ts`.
- Algorithm docs:
  - Added `.dox` docs under `docs/dox-content/calculators/compressedAir/`.

## Formulas And Units

- Final result formula:
  - Air system capacity: `V_system = V_pipe,total + V_receiver,total`, units ft3.
  - Air velocity by pipe size: `v_i = Q * P_atm / (P_line + P_atm) * 144 / A_i / 60`, units ft/s.
- Supporting formulas:
  - Pipe volume by size: `V_i = L_i * c_i`, where `L_i` is pipe length in ft and `c_i` is per-foot pipe volume in ft3/ft.
  - Total pipe volume: `V_pipe,total = sum(V_i)`, units ft3.
  - Receiver capacity conversion: `V_receiver,j = G_j / 7.480515625`, with gallons converted to ft3.
  - Total receiver volume: `V_receiver,total = sum(V_receiver,j)`, units ft3.
- Constants:
  - Receiver conversion: `7.480515625 gal/ft3` from existing implementation.
  - Area conversion: `144 in2/ft2`.
  - Time conversion: `60 s/min`.
  - Pipe volume coefficients by nominal size: `0.0021`, `0.0037`, `0.006`, `0.0104`, `0.0141`, `0.0233`, `0.0333`, `0.0513`, `0.0687`, `0.0884`, `0.1389`, `0.2006`, `0.3442`, `0.5476`, `0.7763`, `0.9354`, `1.223`, `1.555`, `1.926`, `2.793` ft3/ft.
  - Pipe internal areas by nominal size: `0.3`, `0.53`, `0.86`, `1.5`, `2.04`, `3.36`, `4.79`, `7.39`, `9.89`, `12.73`, `20`, `28.89`, `50.02`, `78.85`, `111.9`, `135.3`, `176.7`, `224`, `278`, `402.10` in2.
- Units:
  - Pipe lengths: ft.
  - Stored `PipeData` values: context-specific, ft3 for capacity volume data or ft/s for velocity results.
  - `totalPipeVolume`, `totalReceiverVolume`, and total system capacity: ft3.
  - Receiver inputs: gal; converted receiver outputs: ft3.
  - Airflow: scfm.
  - Pipe pressure: psig.
  - Atmospheric pressure: psia.
  - Velocity results: ft/s.
- Unclear or unverified items:
  - Existing `PipeData` helper comment said velocity pipe area was square feet, but the formula and constants require square inches. Document as square inches.
  - Source of pipe volume coefficients and internal area table is not cited in existing code; docs should present them as implementation tables, not external standard references.

## Validation

- Commands run:
  - `cmake -S . -B build-cpp` passed after removing the legacy wrappers.
  - `cmake --build build-cpp` passed after removing the legacy wrappers.
  - `./build-cpp/bin/cpp_tests` passed: 4029 assertions in 296 test cases.
  - `./node_modules/.bin/tsc --noEmit` passed after the TypeScript declaration changes.
  - `emcmake cmake -S . -B build-wasm -DBUILD_WASM=ON` failed because `emcmake` is not installed in this shell.
  - `npm run tests` failed with 4 compressed-air failures because the existing `bin/client.*` artifact does not expose the newly bound `calculateAirSystemCapacity` or `calculateAirVelocity` functions. The command reported 226 passing tests and 4 failing tests.
  - `git diff --check` passed after the final edits.
  - `rg -n "[ \t]+$" ...` over new files found no trailing whitespace.
  - `rg -n "new moduleInstance\\.(AirSystemCapacity|AirVelocity)|moduleInstance\\.(AirSystemCapacity|AirVelocity)\\b|export declare class (AirSystemCapacity|AirVelocity)|class_<.*(AirSystemCapacity|AirVelocity)|air_system_capacity::AirSystemCapacity|air_velocity::AirVelocity" include src bindings-wasm ts_def tests AGENTS.md .agents` found no live legacy API references outside this handoff.
- Commands still needed:
  - Install or source Emscripten, then run `emcmake cmake -S . -B build-wasm -DBUILD_WASM=ON`.
  - Run `emmake make -C build-wasm`.
  - Rerun `npm run tests` after rebuilding `bin/client.js` and `bin/client.wasm`.
- Known environment limits:
  - WASM build requires Emscripten tools to be installed; `emcmake` is not available in this shell.
  - `clang-format` is not available in this shell, so C++ formatting was manually reviewed instead of auto-formatted.
  - Karma can run in this shell, but it currently exercises stale `bin/client.*` artifacts because the WASM rebuild is blocked.

## Open Questions Or Blockers

- No source-level blockers remain.
- Remaining validation risk: the split embind files could not be compiled into a fresh WASM artifact here because Emscripten is unavailable.
