# Fan Affinity Laws Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite implementation complete; Desktop integration and package publication remain separate delivery steps.
- Created: 2026-11-10
- Last updated: 2026-11-10
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/324
- Suite PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/461; publication evidence belongs in the PR description and CI comments.
- Desktop issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/7129
- Desktop PR: not identified.

## Target Module and Compatibility

- Logical module: `motorDriven/fans/fan_affinity_laws`.
- One public header/source pair, binding, declaration, C++ test, WASM test, and engineering teaching page.
- Canonical stateless value-object pattern: `compressedAir/dryer_operating_cost`.
- User approved the breaking namespace replacement and S1-S4 behavioral corrections. The later instruction places all input validation in Desktop/callers, superseding the earlier minimum Suite guards. No compatibility class or constructor overloads remain.
- C++ namespace: `fan_affinity_laws`; passive `Input`, `Result`, `TimeFactorResult`; scoped `MotorControlType` and `FlowMode` retain the existing values.
- C++ fields use snake_case. Runtime and TypeScript fields remain camelCase. The existing public header path now contains the namespace API.

## Runtime API Contract and Migration

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Annual calculation | `new FanAffinityLaws(...).calculate()` | `calculateFanAffinityLaws(input)` | function + value objects | complete input; kW, percentages 0-100, hours/year, $/kWh | plain values; no delete | breaking API and S1 behavior |
| Resized calculation | class method `changeFanSize(current, next)` | `calculateFanAffinityLawsWithFanSize(input, current, next)` | function + value objects | diameters in inches; consistent flow units | plain values; no delete | breaking API and S1/S2 behavior |
| Two-speed helper | private scalar helper | `get50PercentTimeFactor(flowFraction)` | function + value object | caller-validated fraction 0-1; factor and three time fractions; no runtime checks | plain values; no delete | additive |
| Enums | `MotorControlType`, `FlowMode` | same runtime names and numeric values | enum | OnOff=0, TwoSpeed=1, VSD=2, None=3; Percent=0, Volume=1 | runtime enums; no delete | preserved |

- C++ callers use `fan_affinity_laws::calculate(input)`, `fan_affinity_laws::changeFanSize(input, current, next)`, and `fan_affinity_laws::get50PercentTimeFactor(fraction)`.
- Replace positional constructors with complete input objects. Remove calculator/output `delete()` calls; new `FanAffinityLawsResult` and `FanAffinityLawsTimeFactorResult` are plain interfaces.
- Existing package-entrypoint exports and module composition already include the declaration file; no extra entrypoint edit is needed.

## Formulas, Units, and Provenance

- Source: supplied `Fan_Affinity_Law_Fixes_7129_11042026_clean_version.docx`, formal Part B S1-S4 and regression table. Annotated draft code is supporting feedback only.
- Motor power is delivered fan power at the baseline operating point in kW, not electrical input or full-speed rated power.
- Current electrical power = delivered power / (motor efficiency * drive efficiency), with percentage inputs converted to fractions internally.
- Full-speed reference = current electrical power / baseline control factor.
- Modified power = full-speed reference * modified control factor * diameter ratio^5.
- Factors: VSD = flow fraction^3; Two-Speed = full-speed time + 0.125 * half-speed time; OnOff/None = 1.
- Modified flow fraction = desired volume / (original rated flow * diameter ratio^3). Without resizing, diameter ratio is one.
- Energy results are kWh/year and signed annual savings are dollars/year. No intermediate rounding or savings clamping.
- Desktop/callers own all input validation. The Suite performs arithmetic without range/finite/diameter checks, input-validation exceptions, default substitution, or clamping. The helper's max terms remain part of the time-split formula. Invalid inputs can produce nonphysical time shares, infinity, or NaN; these results are returned unchanged.

### Golden Before and After Results

Triples below are baseline kWh/year / modified kWh/year / savings dollars/year.

| Original Suite case | Before | After |
| --- | --- | --- |
| #5, Two-Speed plus resizing | 94072.16 / 51363.60 / 3416.69 | 94072.16 / 29829.67 / 5139.40 |
| #6, VSD baseline | 9626.23 / 3448.64 / 432.43 | 14125.64 / 5060.58 / 634.55 |
| #7, Two-Speed baseline | 55283.50 / 14239.70 / 2873.07 | 67010.31 / 17260.23 / 3482.51 |
| #12/#13, Two-Speed plus resizing | 247877.76 / 236128.03 / 822.48 | 247877.76 / 86816.41 / 11274.29 |

- Other original outputs are unchanged to the supplied precision. Case #4's ignored OnOff baseline placeholder is now 100 instead of 91. Duplicate constructor case #13 is consolidated into #12.
- VSD worked example: delivered 11.22 kW, drive/motor 97%/96%, baseline 7040/30000, desired 5000 -> 12.04896907 / 4.31660118 kW electrical.
- Resized Two-Speed example: flow fraction 0.5668464790785829, factor 0.24198133838752003, time split 0.13369295815716575 / 0.8663070418428342 / 0.
- The engineering page teaches final results, normalization, control/time factors, diameter scaling, worked examples, symbol units, and ideal-model applicability limits. API migration history stays in this handoff.

## Desktop and Release Contract

- Classification: breaking API, calculation behavior, additive helper.
- Desktop UI implementation is separate. The inspected local Desktop source did not contain this calculator consumer; installed Suite 1.2.6 declarations still expose the old class. Downstream runtime verification is outstanding.
- Migrate adapter calls and cleanup, pass delivered baseline power, and adopt the helper for nameplate estimates and time rows. Desktop must validate all inputs, including positive baseline flow for variable controls, efficiencies, diameters, and the requested fraction of the resized fan's rated flow. Inspect saved-data semantics before reinterpreting old full-speed power.
- Root/process-flow Suite pins were both 1.2.6 at inspection; update them together during separate Desktop integration.
- WASM filenames and loading contract remain unchanged. Validate Desktop against the exact CI-published beta, then the approved final package before release.
- The initial unpublished integration archive `1.2.7-beta.fan-affinity-laws.1` predates removal of Suite validation; do not use it to validate the current contract. Repository package version and Desktop pins were not changed.
- Published beta/final versions and Desktop results remain pending. Keep post-push CI/publication evidence in the PR description or CI comments, without evidence-only follow-up commits.

## Verification and Review Contract

- Required checks: focused/full C++ tests, freshly built/staged `npm run verify:wasm`, TypeScript, documentation/link generation, package contents, and whitespace.
- Full Doxygen reports a missing BibTeX dependency for repository bibliography generation. Scoped module generation covers the new header and engineering page independently; no universal clean documentation build is claimed.
- Record exact execution results, reviewed base/head/merge-base, and both self-review/fresh-review reports in ignored local review records and the PR description under the current PR workflow.
- Remaining delivery gaps: Desktop validation, publication, and human/SME release approval.
