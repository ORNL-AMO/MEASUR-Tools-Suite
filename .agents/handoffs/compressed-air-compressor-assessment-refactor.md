# Refactor Handoff

## Target Module

- Domain/path: `compressedAir/assessment`
- Logical module: compressor assessment performance models, EEM calculations, and compressor catalog records
- Original files: `include/compressedAir/Compressors.h`, `src/compressedAir/Compressors.cpp`, `include/compressedAir/compressors_data.h`, `bindings-wasm/compressedAir/compressorsCalc.cpp`, `ts_def/ts_def_modules/compressedAir/compressorsCalc.d.ts`, `tests/cpp/compressedAir/Compressors.unit.cpp`, `tests/wasm/compressedAir/wasm-compressorsCalc-test.js`, `tests/wasm/compressedAir/wasm-compressorCalc-reciprocatingScrew-test.js`, `tests/wasm/compressedAir/wasm-compressorCalc-helpers.js`
- New files: `include/compressedAir/assessment/*`, `src/compressedAir/assessment/*`, `bindings-wasm/compressedAir/assessment/*`, `ts_def/ts_def_modules/compressedAir/assessment/*`, `tests/cpp/compressedAir/assessment/*`, `tests/wasm-mocha/compressedAir/assessment/*`, `docs/dox-content/calculators/compressedAir/assessment/*`
- Nearby examples: namespace-based `compressedAir` one-off calculators and `compressedAir/leak_survey`

## Current Public API

- C++ symbols: global `CompressorsBase`, `Compressors_*`, `Compressor_VFD`, `CompressorEEMs`, and `CompressorsData`
- Embind runtime names: legacy `Compressors_*`, `Compressor_VFD`, `CompressorsOutput`, `CompressorsOutputBlowOff`, `CompressorsData`, `CompressorsDataV`, and EEM function names
- TypeScript declarations: `compressedAir/compressorsCalc.d.ts`
- Test-visible behavior: C++ compressor unit tests plus legacy JS WASM tests

## Proposed Namespace API

- Namespace: `compressed_air::assessment`
- Functions: EEM free functions under `compressor_eem`
- Structs/value objects: compressor performance/blow-off results, EEM results, `CompressorCatalogRecord`
- Enums: `CompressorType`, `CompressorControl`, `CompressorStage`, `CompressorLubricant`, `CompressorInputBasis`
- Runtime names to preserve: none; this is an approved breaking cleanup

## Compatibility Decision

- Default: preserve public compatibility.
- Decision: breaking cleanup approved by user.
- Migration notes needed: old class/function/type names are removed and replaced by new assessment names.
- User approval for breaking changes: yes.
- Removed legacy surfaces: old C++ headers/source, old embind names, old TS `compressorsCalc`, and legacy JS WASM tests.

## Touched Layers

- Headers/source: split into `include/compressedAir/assessment` and `src/compressedAir/assessment`; legacy compressor headers/source removed.
- C++ tests: split under `tests/cpp/compressedAir/assessment`; legacy monolithic test removed.
- WebAssembly bindings: split under `bindings-wasm/compressedAir/assessment`; legacy `compressorsCalc.cpp` removed.
- TypeScript declarations: split under `ts_def/ts_def_modules/compressedAir/assessment`; legacy `compressorsCalc.d.ts` removed; client and registered vector declarations updated.
- WASM Mocha tests: typed tests under `tests/wasm-mocha/compressedAir/assessment`; legacy JS tests removed.
- Algorithm docs: new `.dox` files under `docs/dox-content/calculators/compressedAir/assessment`.

## Formulas And Units

- Final result formula: preserve current formulas and expected numeric outputs exactly.
- Supporting formulas: pressure/inlet correction, compressor control curves, load/unload cycle timing, VFD interpolation, EEM pressure reduction.
- Constants: existing 1.732 three-phase conversion, 0.746 hp-to-kW conversion, pressure correction coefficients, and existing time constants.
- Units: kW, acfm, psig, psia, hp, seconds, hours/year, $/kWh, kWh/year, dimensionless fractions.
- Unclear or unverified items: legacy catalog comments contain some inconsistent units and should be documented according to field usage/tests.

## Validation

- Commands run:
  - `cmake -S . -B build-cpp`
  - `cmake --build build-cpp`
  - `./build-cpp/bin/cpp_tests` passed: 4033 assertions in 301 test cases.
  - `./node_modules/.bin/tsc --noEmit` passed.
  - `doxygen Doxyfile` exited 0, but printed the repo's existing BibTeX failure and unrelated documentation warnings.
  - `npm run tests` ran against stale `bin/client.*`; 230 existing tests passed and 10 new assessment tests failed because the new WASM constructors/functions were not present.
  - `git diff --check` passed.
- Commands still needed:
  - Re-run `emcmake cmake -S . -B build-wasm -DBUILD_WASM=ON`.
  - Re-run `emmake make -C build-wasm`.
  - Re-run `npm run tests` after `bin/client.js` and `bin/client.wasm` are rebuilt.
- Known environment limits:
  - `emcmake`, `emmake`, and `emcc` were not installed or not on PATH in this environment, so the WASM artifact could not be rebuilt.

## Open Questions Or Blockers

- WASM binding compile and runtime browser tests remain blocked on Emscripten availability.
