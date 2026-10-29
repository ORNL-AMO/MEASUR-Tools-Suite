# Refactor Handoff

## Workflow Metadata

- Lifecycle: complete
- Status: implementation, documentation, validation, and internal review complete
- Owner: Codex
- Created: 2026-10-12
- Last updated: 2026-10-12
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/216
- Suite PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/423
- Desktop issue: not required; this is an internal Suite dependency migration
- Desktop PR: not required

## Target Module

- Domain/path: `motorDriven/motor`
- Logical module: motor pole-count classification
- Pre-refactor files: `include/motorDriven/motor/Poles.h` and `src/motorDriven/motor/Poles.cpp`
- Implemented files: `include/motorDriven/motor/poles.h` and `src/motorDriven/motor/poles.cpp`
- Direct consumers: `src/motorDriven/motor/EstimateFLA.cpp` and `src/motorDriven/motor/MotorEfficiency.cpp`
- Removed incidental reference: `src/motorDriven/motor/OptimalMotorPower.cpp` previously included `Poles.h` without using it
- Nearby examples: `processHeat/energy_equivalency` for a scalar namespace function; `motorDriven/pump/pump_head` for namespace, tests, Doxygen, and handoff structure

## Current Public API

- C++ symbols: global `Poles` class with `Poles(double motorRpm, Motor::LineFrequency lineFreq)` and non-const `int calculate()`
- Embind runtime names: none; `Poles` is not bound in `bindings-wasm/`
- TypeScript declarations: none; the `MotorData.getPoles()` record accessor is unrelated and remains unchanged
- Test-visible behavior: no focused Poles test exists; `EstimateFLA`, `MotorEfficiency`, pump-result, fan-result, and motor WASM tests exercise it indirectly

## Runtime API Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| C++ pole classification | `Poles(motorRpm, lineFreq).calculate()` | `poles::calculate(motor_rpm, line_frequency)` | none | input speed rpm; line frequency 50 or 60 Hz; return value is a pole count | Value parameters and integer result; no owned runtime object | Intentionally breaking C++ source change; numerical behavior preserved |
| WebAssembly package | No direct Poles export | No direct Poles export | none | not applicable | not applicable | Unchanged |
| `MotorData` pole field | `getPoles()` / `setPoles()` | unchanged | `class_` property methods | pole count | `MotorData` remains an embind class requiring `delete()` | Unchanged |

## Implemented Namespace API

- Namespace: `poles`
- Functions: `int calculate(double motor_rpm, Motor::LineFrequency line_frequency)`
- Structs/value objects: none
- Enums: reuse `Motor::LineFrequency`; do not introduce a duplicate enum
- Runtime names to preserve: all existing motor bindings; do not add a new WebAssembly export

## Compatibility Decision

- Default: preserve public compatibility.
- Decision: the requested namespace refactor intentionally replaces the C++ `Poles` constructor/method API with a free function. No compatibility wrapper will be retained.
- Migration notes needed: replace `Poles(rpm, frequency).calculate()` with `poles::calculate(rpm, frequency)` and update the include to `motorDriven/motor/poles.h`.
- User approval for breaking changes: the 2026-10-12 request explicitly identifies this work as the Poles namespace refactor.
- Removed legacy surfaces: `Poles.h`, `Poles.cpp`, and global `Poles` class; remove the unused Poles include from `OptimalMotorPower.cpp`.
- Behavior change approved: none. Preserve thresholds, fallback behavior, maximum pole count, parameter meaning, and integer results exactly.

## Touched Layers

- Headers/source: replaced `Poles.h/.cpp` with `poles.h/.cpp`; implemented the same logic in namespace `poles`; migrated both direct consumers and removed the unused include.
- C++ tests: added `tests/cpp/motorDriven/motor/poles.unit.cpp` with table-driven coverage for both frequencies, range endpoints, gaps handled by the fallback, speeds above 3600 rpm, and the 12-pole cap. Existing consumer goldens remain passing.
- WebAssembly bindings: no source change; confirm the refactor compiles into the existing motor, pump-result, and fan-result bindings.
- TypeScript declarations: no source change; `motor.d.ts`, `motorEnum.d.ts`, and `client.d.ts` remain unchanged.
- WASM Mocha tests: no new Poles API test because no runtime surface is added. Re-run existing typed motor, pump-result, and fan-result tests through a fresh WASM build.
- Algorithm docs: added `docs/dox-content/calculators/motorDriven/motor/poles_calculator.dox` under `equipment_and_property_calculators`; linked the public C++ header to the group, exposed that parent group from `docs/mainpage.dox`, and wrote an engineering teaching narrative covering the engineering question, final result, classification workflow, physical basis, fully worked primary and fallback examples, units, assumptions, and compatibility caveat.

## Implementation Plan

1. Record a baseline from the focused `EstimateFLA` and `MotorEfficiency` native tests before changing the API.
2. Rename the header/source to lowercase snake case, introduce `poles::calculate`, and add file, namespace, parameter, return-unit, and documentation cross-reference comments.
3. Preserve the current decision order exactly: explicit 60 Hz bands, explicit 50 Hz bands, the `motor_rpm > 3600` result, then the legacy 60 Hz fallback and 12-pole cap.
4. Update `EstimateFLA.cpp` and `MotorEfficiency.cpp` to call the namespace function. Remove the unused include from `OptimalMotorPower.cpp`; do not refactor those consumers' public APIs.
5. Add focused table-driven native tests that lock every explicit pole class and the non-obvious fallback behavior, including a 50 Hz gap case.
6. Write the algorithm page top-down: returned pole count, synchronous-speed relationship, slip-based lookup bands, legacy fallback, worked examples, and interpretation limits. Every formula receives a symbol table and units.
7. Run focused native checks, the full native suite, a fresh WASM verification, documentation checks, and whitespace checks.
8. Run the pre-PR internal review against `epic-pump-result-refactor` rather than `develop`; resolve or disposition every finding and record the final base/head commits here before opening the child PR.

## Desktop Impact

- Wrapper or helper changes: none. GitHub code search found no Desktop `calculatePoles` call, and Suite exposes no direct Poles runtime constructor or function.
- Enum, unit, percentage, or nullable conversion changes: none; `LineFrequency` and all existing runtime enum names remain unchanged.
- App models, reports, exports, or saved-data changes: none. Desktop uses pole values in its own models and `MotorData.getPoles()`, neither of which changes.
- Process-flow package changes: none for this child refactor.
- Web/Electron WASM loading changes: none.
- Downstream verification: no separate Desktop PR or package-pin change. Preserve indirect Suite behavior through native consumer goldens and fresh motor, pump-result, and fan-result WASM tests; repeat broader Desktop validation later for the integrated feature package.

## Formulas And Units

- Engineering question and why the result matters: classify a measured motor speed into the supported even pole count used to select downstream motor-performance coefficients; the calculation does not predict motor speed or redesign the motor.
- Teaching sequence or decision path: validate the positive speed and nominal frequency, check the frequency-specific inclusive bands, apply the above-range or legacy fallback only when no band matches, and interpret the result as a downstream coefficient class.
- Final result formula: for synchronous speed, `P = 120 f / N_s`, where `P` is pole count, `f` is line frequency in Hz, and `N_s` is synchronous speed in rpm.
- Supporting formulas: the explicit tables classify measured full-load speed from `0.9 N_s` through `N_s` for even pole counts 2, 4, 6, 8, 10, and 12. Outside those bands, preserve `P_fallback = 2 floor(floor(7200 / N) / 2)`, capped at 12; speeds above 3600 rpm return 2.
- Constants: 120 in the synchronous-speed relationship; 7200 = 120 x 60 in the retained fallback; 0.9 band lower bound; maximum 12 poles.
- Units: motor speed rpm; line frequency Hz; returned pole count is a count.
- Formula provenance: the synchronous-speed relationship and explanation of induction-motor slip are supported by the U.S. Department of Energy's 2008 *Improving Motor and Drive System Performance* sourcebook, recorded as `doe2008motorSourcebook` in `docs/references.bib`. The classification boundaries and fallback are traced to the existing implementation and consumer regression fixtures.
- Golden inputs and expected results: 60 Hz synchronous endpoints 3600/1800/1200/900/720/600 rpm map to 2/4/6/8/10/12 poles; 50 Hz endpoints 3000/1500/1000/750/600/500 rpm map to the same counts. Add exact lower-bound cases, representative in-band cases, a 60 Hz fallback such as 2400 rpm -> 2, a 50 Hz gap such as 800 rpm -> 8, above-range speed -> 2, and a low positive speed -> 12.
- Worked example and interpretation: the page derives the 60 Hz four-pole band and 1.11-percent implied slip for 1780 rpm, then demonstrates the compatibility fallback for a 50 Hz input at 800 rpm. It explains that the returned pole count selects coefficient data and is not a speed or slip result.
- Valid ranges, boundaries, fallbacks, and inappropriate uses: positive motor speed and nominal 50 Hz or 60 Hz inputs only; band endpoints are inclusive; speeds above 3600 rpm return two poles; remaining gaps use the retained 60 Hz fallback capped at 12; the calculator is not an arbitrary-frequency VFD estimator.
- SME decisions required: none for behavior preservation.
- Unclear or unverified items: the historical source for the 90-percent lower bounds and the 60 Hz fallback used even for 50 Hz inputs is not recorded. Document these as retained compatibility behavior, not as a newly validated universal selection method.

## Package And Release Coordination

- Change classification: breaking C++ source API; WebAssembly runtime and TypeScript package API unchanged
- Beta package version: not required for this internal-only child refactor
- Final package version: handled by the integrated pump-result dependency sequence
- Desktop root dependency: no change for this child refactor
- Desktop process-flow dependency: no change for this child refactor
- Release readiness: ready for the Suite pull request; no package release is required for this internal-only child refactor
- Release blockers: none identified

## Validation

- Baseline before the API change: `./build-cpp/bin/cpp_tests "[EstimateFLA],[MotorEfficiency]"` passed with 121 assertions in 5 test cases.
- Native build: `cmake -S . -B build-cpp` and `cmake --build build-cpp` passed.
- Focused namespace tests: `./build-cpp/bin/cpp_tests "[poles]"` passed with 31 assertions in 2 test cases.
- Dependent native tests: `./build-cpp/bin/cpp_tests "[EstimateFLA],[MotorEfficiency]"` passed with 121 assertions in 5 test cases after migration.
- Full native suite: `./build-cpp/bin/cpp_tests` passed with 4,179 assertions in 319 test cases.
- Fresh WebAssembly verification: after loading `/Users/txr/dev/emsdk/emsdk_env.sh`, `npm run verify:wasm` rebuilt and staged the module, typechecked declarations/tests, and passed all 251 browser tests.
- Documentation and cleanliness: `npm run check:docs`, `doxygen Doxyfile`, `git diff --check`, and `git diff --cached --check` completed. The generated Poles group and header pages contain the engineering question, decision workflow, namespace API, tables, formulas, worked examples, interpretation, and limits. Rendered HTML inspection also confirmed the fallback equation's punctuation and spacing.
- Known environment limits: `emcmake` was not initially on `PATH`, and the sandboxed Emscripten cache was not writable; loading the local SDK and rerunning with the required filesystem access resolved both. Local Doxygen lacks BibTeX and clang-assisted parsing, so the bibliography could not be rendered locally; Doxygen otherwise completed with existing unrelated undocumented-parameter warnings. `clang-format` is not installed locally.

## Internal Review

- Intended PR base and reviewed base commit: `epic-pump-result-refactor` at `91593869534eb0ba5657af9031fe50744650bce8`
- Reviewed head commit: `3daec6eeee471d887e20dd92d43843de9a7550dc`
- Reviewer or review task: Codex review-only pass using `.github/skills/measur-code-review/`
- Readiness result: **Ready**
- Findings and dispositions: no actionable P0-P3 findings in the original pass or the documentation-focused rerun after formalizing the engineering teaching standard
- Checks rerun after review fixes: no code fixes were required; documentation generation, rendered-HTML inspection, link checking, and whitespace checks were rerun after the teaching-narrative and homepage updates
- Post-review metadata: the follow-up handoff-only commit records the pull request URL and reviewed commit; it does not change the reviewed implementation or documentation.
- Remaining P3 findings, questions, or validation gaps: no code finding remains. Before opening a PR from a future commit, record the resulting head commit and rerun review if the candidate diff changes materially.

## Open Questions Or Blockers

- No blocker. Preserve the legacy 50 Hz fallback as implemented; changing it would be a separate behavior-fix decision with new expected results and downstream analysis.
