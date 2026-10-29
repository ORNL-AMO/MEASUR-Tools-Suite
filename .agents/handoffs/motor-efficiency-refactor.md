# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite and Desktop child PRs open; final exact-beta validation and both pre-PR reviews complete
- Owner: Codex
- Created: 2026-10-12
- Last updated: 2026-10-12
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/208
- Suite PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/424
- Desktop issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8961
- Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target Module

- Domain/path: `motorDriven/motor`
- Logical module: motor efficiency
- Current files: legacy `MotorEfficiency.h/.cpp`, the MotorEfficiency sections in the combined motor binding/declaration/test, and the focused native test
- Nearby examples: `compressedAir/dryer_operating_cost`, `motorDriven/pump/pump_result`, and `motorDriven/motor/poles`

## Current Public API

- C++ symbols: global stateful `MotorEfficiency`, `calculate`, `calculate25intervals`, getters/setters, and `getKWloss0`
- Embind runtime names: constructible `MotorEfficiency` class with `calculate(loadFactor, specifiedEfficiency)`
- TypeScript declarations: `MotorEfficiency` runtime class requiring `delete()`
- Test-visible behavior: efficiency is returned as a fraction; specified efficiency is required only for `SPECIFIED`; loads above 1.5 are clamped

## Runtime API Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Motor efficiency | `new MotorEfficiency(lineFrequency, motorRpm, efficiencyClass, motorRatedPower).calculate(loadFactor, specifiedEfficiency)` | `calculateMotorEfficiency(input)` | `class_` to `value_object` + `function` | rpm, hp, dimensionless load/efficiency fractions; `specifiedEfficiency` required and ignored outside `SPECIFIED` | Before: class requires `delete()`; after: plain input and numeric result require no cleanup | Breaking |

## Proposed Namespace API

- Namespace: `motor_efficiency`
- Functions: `Result calculate(const Input&)`
- Structs/value objects: C++ `Input` and `Result`; WASM/TypeScript `MotorEfficiencyInput`
- Enums: reuse `Motor::LineFrequency` and `Motor::EfficiencyClass`
- Runtime names to preserve: `LineFrequency` and `MotorEfficiencyClass`

## Compatibility Decision

- Default: preserve public compatibility.
- Decision: intentionally breaking stateless cleanup approved by the user on 2026-10-12.
- Migration notes needed: replace construction, method call, and `delete()` with one plain-object function call.
- User approval for breaking changes: explicit.
- Removed legacy surfaces: global class, mixed-case header/source, public interval method, getters/setters, embind constructor, TypeScript class, and compatibility-only ownership tests.
- Implementation shape: no calculator class remains; one anonymous namespace contains the source-private coefficient and interval free functions, followed by `motor_efficiency::calculate(const Input&)` as the only calculation entry point.
- Behavior change approved: none.

## Touched Layers

- Headers/source: replace the class with `motor_efficiency.h/.cpp`; migrate all direct native consumers.
- C++ tests: port all 107 focused assertions and add branch/error coverage through the namespace API.
- WebAssembly bindings: add a dedicated binding with one input value object and one numeric function.
- TypeScript declarations: add a dedicated interface/function/module type and remove the legacy class.
- WASM Mocha tests: split MotorEfficiency into a typed dedicated test.
- Algorithm docs: add `motor_efficiency_calculator.dox`.

## Desktop Impact

- Wrapper or helper changes: migrate `PumpsSuiteApiService.nema()` and `.motorEfficiency()` to the plain-object function.
- Enum, unit, percentage, or nullable conversion changes: none; preserve enum mapping and percent/fraction conversions.
- App models, reports, exports, or saved-data changes: none.
- Process-flow package changes: dependency pin only; no direct consumer found.
- Web/Electron WASM loading changes: none.
- Downstream verification: focused wrapper tests, Angular application typecheck, root build, and exact-beta validation.

## Formulas And Units

- Engineering question and why the result matters: estimate a motor's electrical efficiency at a requested load from its line frequency, speed, efficiency class, and rated horsepower.
- Teaching sequence or decision path: select pole/coefficient family, calculate 25/50/75/100/125-percent points, adjust a specified-efficiency curve, then evaluate the low-, normal-, or overload region.
- Final result formula: efficiency is shaft power divided by electrical input power for the low-load region and an interpolated efficiency fraction for higher loads.
- Supporting formulas: double-exponential interval curves; 125-percent efficiency equals 0.99 times full-load efficiency; zero-load loss equals 0.8 times 25-percent loss; fourth-order and quadratic curve fits.
- Constants: 0.746 kW/hp, 0.8 no-load loss ratio, 0.99 overload efficiency factor, 1.5 maximum evaluated load.
- Units: speed rpm; rated power hp; power loss kW; load and efficiency dimensionless fractions.
- Formula provenance: DOE motor sourcebook for general motor-efficiency context; empirical coefficients and legacy thresholds are retained from the implementation with unverified historical provenance.
- Golden inputs and expected results: retain the 107 existing assertions, including 200 hp at 1785 rpm and full-load energy-efficient result 0.956259245.
- Worked example and interpretation: 200 hp, 1785 rpm, 60 Hz energy-efficient motor evaluated at full load.
- Valid ranges, boundaries, fallbacks, and inappropriate uses: preserve `<0.251`, `<1.251`, and 1.5 clamp behavior; specified class without a nonnegative efficiency throws; the empirical model is not a substitute for measured efficiency outside its retained coefficient domain.
- SME decisions required: none for behavior preservation.
- Unclear or unverified items: original coefficient source and the legacy standard-curve specified-efficiency indexing behavior.

## Package And Release Coordination

- Change classification: breaking API
- Beta package version: `1.2.6-beta.363.1` from the final class-free Suite head
- Final package version: handled by the integrated feature sequence
- Desktop root dependency: update to exact beta
- Desktop process-flow dependency: keep aligned with root
- Release readiness: Suite PR #424 is green and published `1.2.6-beta.363.1`; Desktop PR #8964 is open with both manifests and lockfiles pinned to that exact beta.
- Release blockers: required human approval and merge sequencing for the Suite and Desktop child PRs

## Validation

- Commands run: baseline `./build-cpp/bin/cpp_tests '[MotorEfficiency],[MotorEfficiency25]' --reporter compact` passed 107 assertions in 5 test cases; after removing the internal calculator class, the focused MotorEfficiency filters passed 124 assertions in 7 cases and focused EstimateFLA passed 64 assertions in 1 case; the full native suite passed 4,196 assertions in 321 cases; `npm run verify:types` passed; `npm run verify:wasm` rebuilt and staged the current class-free module and passed all 253 browser tests; `npm run check:docs` passed; Doxygen generated the Motor Efficiency page and linked it into the equipment/property calculator group; `git diff --check` passed.
- Commands still needed: CI completion on the final Desktop PR head.
- Known environment limits: Doxygen reports pre-existing repository warnings and cannot run BibTeX in this environment. The local Emscripten SDK must be activated explicitly before running `npm run verify:wasm`.

## Internal Review

- Intended PR base and reviewed base commit: `epic-pump-result-refactor` at `90b00dc68894c7e39d5afb4ced8cf3193e59bfc3`.
- Reviewed head commit: `8b323f810fc3678f0859e4c2f99a4c86f48e2ada`
- Reviewer or review task: Codex review-only pass using `.github/skills/measur-code-review/`
- Readiness result: **Ready**
- Findings and dispositions: no actionable findings
- Checks rerun after review fixes: focused MotorEfficiency filters passed 124 assertions in 7 cases; focused EstimateFLA passed 64 assertions; the full native suite and freshly rebuilt WASM package passed. The review confirmed that no production `Calculator` or `MotorEfficiency` class remains and the source uses one private anonymous namespace.
- Remaining P3 findings, questions, or validation gaps: none for the Suite surface.

### Desktop Review

- Reviewed base commit: `epic-pump-result-refactor` at `32c870936a3fd07c1ad35b64f43999fbb5c866d2`
- Reviewed head commit: `8dfded443561991a55fed2b7986bc55be1deb01f`
- Reviewer or review task: Codex review-only pass using the Desktop `suite-coordination` workflow
- Readiness result: **Ready**
- Findings and dispositions: no actionable findings
- Validation: against `measur-tools-suite@1.2.6-beta.363.1`, the focused wrapper spec passed 7 tests; application typecheck passed; root build passed; full compressed-air regression passed 49 fixtures; `git diff --check` passed.
- Non-blocking environment note: the pre-existing process-flow `npm run test:typecheck` script treats `typecheck` as a Vitest filter and finds no test files. Process-flow source is unchanged and its bundle compiled in the passing root build.

## Open Questions Or Blockers

- Required human approval and merge sequencing remain external to this implementation.
