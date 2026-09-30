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
- Documentation/trust pass decision (2026-09-22): preserve every current assessment name. Add
  `fullLoadBrakeHorsepower` while retaining deprecated `fullLoadBhpPowerKw` with the same BHP value;
  add an explicit-compressor-type `StartStopCompressor` overload while retaining the four-argument
  screw-default constructor.

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
- Catalog decisions verified against source rows: `fullLoadBrakeHorsepower` is bhp,
  `specificPackagePower` is kW/100 acfm, no-load power fields are percentages, and `-9999` is
  unavailable/not applicable rather than a physical value.
- Electrical power factor is a dimensionless 0-to-1 fraction. Test fixtures now use realistic
  current and power-factor pairs while preserving the tested kW.
- The load/unload inverse remains a sixth-order fit constructed from 76 equal airflow intervals and
  77 evaluated points. The zero-flow endpoint is represented as 0.0001 acfm to avoid division by zero.
- The receiver pump-up formula's 200 psig value is named
  `kLegacyReceiverPumpupReferencePressurePsig`; its physical origin remains unverified.

## SME Review Matrix (2026-09-22)

| Review comment or trust gap | Source/implementation finding | Resolution in this pass | Follow-up |
|---|---|---|---|
| Show performance curves | No engineer-facing figures existed | Added seven normalized SVG curves using the same anchors as the assessment tests | SME to confirm curve labeling and intended audience terminology |
| Explain where inputs come from | Pages mixed API details with sparse formulas | Added measurement/catalog/default/derived origin tables and a repeated profile-point workflow | None |
| Load/unload energy terms are unexplained | All five energy terms existed only in source | Documented every runtime, average power, energy, total time, and cycle average; consolidated source into one cycle-state calculation | SME to confirm storage applicability |
| Explain the unload pressure band | Runtime uses calculated unload pressure minus full-load pressure | Documented `Q_UL`, `P_UL`, and the origin of `P_UL,g-P_FL,g` | None |
| Replace “helper” terminology | It described an internal branch above unload | Replaced with “the modulation submodel used above the unload point” | None |
| Explain BHP and 0.746 | Catalog/API text incorrectly called BHP kW | Added corrected property and plain-language shaft/electrical distinction; shared the existing 0.746 constant | None |
| Remove coding/WebAssembly language from teaching pages | Overview/catalog discussed value objects and bindings | Reframed pages as process-engineering instructions | API reference remains separate by design |
| Blow-off is not a normal user output | Library still computes it for balance | Retained code/API fields and documented blow-off as a bypass-flow intermediate | SME to approve “bypass flow” wording |
| Catalog metadata is misleading | bhp, specific power, and percentage fields were mislabeled | Corrected C++, bindings, TypeScript, Doxygen, and consistency tests | None |
| Centrifugal transition behavior is suspect | Capacity path compared airflow fraction to unload power fraction | Corrected comparison to unload airflow fraction; added below/at/above tests | None |
| Short load/unload constructor factor is ignored | Eight-input call resolved to a defaulted long constructor | Added an exact eight-input constructor that derives no-load kW from the 0-to-1 factor | Longer forms intentionally use explicit no-load kW |
| Start/stop correction assumes screw | Implementation hard-coded screw construction | Added explicit type overload and tests for screw/reciprocating; legacy form remains screw | SME to confirm start/stop applicability |
| Electrical examples obscure PF convention | Tests used PF=50 with artificially small current | Replaced with equivalent realistic PF=0.50 fixtures and centralized the conversion | None |
| Explain repeated profile processing | Pages did not say calculations are interval independent | Overview now states and sequences the per-interval process | None |

## Formula Provenance and Behavior Reconciliation

| Formula family | Verification basis | Executable authority and reconciliation |
|---|---|---|
| Centrifugal piecewise curves and three-point pressure fit | Historical implementation and regression fixtures | C++ model plus boundary/golden tests; transition comparison corrected where dimensions were inconsistent |
| Positive-displacement load/unload cycle | Historical implementation and regression fixtures | Named `CycleState` implementation is shared by direct and sampled inverse paths; all five stage energies documented |
| Modulation, start/stop, and VFD | Historical implementation and regression fixtures | Existing equations retained, dimensional reconstruction and worked examples added |
| Pressure/inlet and electrical correction | Historical implementation and regression fixtures | Shared implementation; 0.746 constant and three-phase conversion centralized for assessment models |
| EEM calculations | Historical implementation and regression fixtures | Formulas retained; input provenance, gauge/absolute pressure, and per-interval application clarified |
| Catalog interpretation | Embedded default-data tables and reviewed catalog documentation | Values cross-checked using BHP conversion and kW/100 acfm relationships |

When historical prose conflicts with executable behavior, the tested implementation is documented
unless engineering intent is clear enough to correct safely. The principal example is polynomial
order: an earlier description mentions a fourth-order inverse, while the implementation and
historical behavior use a sixth-order fit; the public documentation states sixth order and discloses
the sampling method.

## Validation

- Commands run for the documentation/trust pass:
  - `cmake -S . -B build-cpp`
  - `cmake --build build-cpp -j4`
  - `./build-cpp/bin/cpp_tests` passed: 4138 assertions in 315 test cases.
  - `./node_modules/.bin/tsc --noEmit` passed.
  - `xmllint --noout docs/assets/ca-*.svg` passed for all seven figures.
  - `doxygen Doxyfile` exited 0. It emitted the repository's existing missing-BibTeX message,
    disabled-clang-option notices, and unrelated parameter warnings; it emitted no new compressed-air warnings.
  - Generated HTML was inspected for equation blocks, symbol tables, captions, cross-links, the
    seven SVG object references, the worked examples, and responsive SVG CSS.
  - `git diff --check` passed.
  - `npm run tests` completed 246 tests successfully and failed 3 tests that require the new WASM
    artifact: the catalog alias was undefined, the five-argument start/stop constructor was absent,
    and the old eight-argument load/unload constructor behavior remained. These failures match the
    stale `bin/client.js`/`bin/client.wasm`, not the passing C++ implementation.
- Commands still needed in an Emscripten-enabled environment:
  - `emcmake cmake -S . -B build-wasm -DBUILD_WASM=ON`
  - `emmake make -C build-wasm`
  - Stage the rebuilt `client.js` and `client.wasm`, then rerun `npm run tests`.
- Known environment limits:
  - `emcmake`, `emmake`, and `emcc` are not installed or on PATH. Docker is installed but no local
    MEASUR/Emscripten image is available, so rebuilding would require a network-dependent image build.
  - The in-app browser blocks local `file://` Doxygen pages. Generated HTML structure was inspected
    directly; the browser was not routed through a temporary server or another browser surface.

## Open Questions Or Blockers

- WASM binding compile and runtime browser tests remain blocked on Emscripten availability.
- Confirm whether effective storage volume should apply to every current load/unload calculation or
  only selected configurations.
- Confirm the physical rationale and units for the 200 psig receiver pump-up reference constant.
- Confirm the inherited 0.92 modulation-floor fraction for lubricant-injected load/unload control.
- Confirm start/stop applicability by compressor construction and operating size.
- Confirm that “bypass-flow intermediate” is the preferred user-facing description of blow-off.
