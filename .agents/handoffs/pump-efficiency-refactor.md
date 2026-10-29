# Pump Efficiency Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: **planned; implementation not started**
- Owner: Codex
- Created: 2026-10-29
- Last updated: 2026-10-29
- Suite coordinating issue: [#230 PumpEfficiency Documentation](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230).
- Suite integration branch / child PR base: `epic-pump-eff-refactor`; inspected head
  `04d91cd6d222f87f8e7cb88e61cf1f9124a98293`.
- Suite PR: not opened for this epic.
- Desktop issue: [#9059 Coordinate pump efficiency calculation namespace refactor](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059).
- Desktop PR: not opened for this epic.
- Precedent: [PumpResult epic handoff](pump-result-refactor.md).
- Workflow: [refactor personas](../README.md), [handoff template](../templates/refactor-handoff.md), and
  [Suite-to-Desktop coordination](../../docs/development/suite-desktop-change-workflow.md).

This pass creates this planning record and one Desktop coordination issue only. It does not implement calculators,
change packages, create branches or PRs, publish packages, or merge work. The Desktop issue is the authoritative
product/coordination record; this handoff owns the Suite implementation plan and evidence.
The issue records this handoff's repository path and future branch link, explicitly marked pending a later
documentation commit/push. This pass leaves the handoff local and uncommitted.

## Target Module And Feature PR Sequence

Move the six pump-only calculators from `motorDriven/pumpFan` to `motorDriven/pump`. Each later child branch starts
from the latest `epic-pump-eff-refactor` head and targets that branch through one reviewed PR per calculator.
Use `codex/` for new child branch names. All rows are planned, with no implementation or validation claimed.

| Order | Suite issue / legacy module | New basename and namespace | Dependencies after migration |
| ---: | --- | --- | --- |
| 1 | [#223 OptimalDeviationFactor](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/223) | `optimal_deviation_factor` | None |
| 2 | [#225 OptimalPrePumpEff](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/225) | `optimal_pre_pump_efficiency` | `Pump::Style` |
| 3 | [#228 OptimalSpecificSpeed](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/228) | `optimal_specific_speed` | None |
| 4 | [#229 OptimalSpecificSpeedCorrection](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/229) | `optimal_specific_speed_correction` | `Pump::Style`; consumes the specific-speed convention established in #228 |
| 5 | [#226 OptimalPumpEfficiency](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/226) | `optimal_pump_efficiency` | #225, #228, #229 |
| 6 | [#230 PumpEfficiency](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230) | `pump_efficiency` | #226, #223 |

Use #230 as the coordinating issue and reference the five supporting issues. All six issues were verified open on
2026-10-29 with existing parent Suite #204; retain that hierarchy. Do not close #230 before integrated acceptance.

Excluded: OptimalFanEfficiency #224, already-implemented OptimalPumpShaftPower #227, the shared `Pump.h` refactor
#202, and unrelated motor/fan public refactors. Positive-displacement feature work in Suite #402 / Desktop #8734
and historical double-entry/stage-count engineering concerns are separate behavior work.

## Current Public API

- Six global C++ calculator classes expose constructor inputs plus `calculate()`. `OptimalPumpEfficiency` also has
  mutable accessors and unused state; `PumpEfficiency::Output` has `average` and `max`.
- Only `OptimalSpecificSpeedCorrection`, `PumpEfficiency`, and `PumpEfficiencyResults` are currently bound runtime
  classes, all in `bindings-wasm/motorDriven/pumpFan/pumpFan.cpp`. Calculators and returned result objects need
  `delete()`; the scalar correction result does not.
- The mixed `pumpFan.d.ts` describes these classes and the runtime `PumpStyle` / `SpecificSpeed` enums.
  Four helpers currently have no standalone WASM API or declaration.
- Existing focused coverage: the large native specific-speed-correction fixture file and two typed WASM tests.
  No dedicated native test files for the other five modules or calculation `.dox` pages were found.

## Runtime API Contract And Proposed Namespace API

Each namespace exposes `calculate(const Input&)`. Use snake_case C++ input members, camelCase WASM/TypeScript
members, and the corresponding `<CalculatorName>Input` interface below. All listed fields are required;
inputs are not modified. The five helper functions return `double` / `number`.

| Surface / TypeScript input | Before | After function and input fields | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| `OptimalDeviationFactorInput` | C++ `OptimalDeviationFactor(flowRate).calculate()`; no runtime export | `calculateOptimalDeviationFactor({flowRate})` | New `function` + input `value_object` | Flow US gpm; output dimensionless multiplier; no defaults | Plain input and scalar; no cleanup | Breaking C++; additive WASM |
| `OptimalPrePumpEfficiencyInput` | C++ `OptimalPrePumpEff(style, flowRate).calculate()`; no runtime export | `calculateOptimalPrePumpEfficiency({style, flowRate})` | New `function` + input `value_object` | `PumpStyle`; US gpm; output percent (0–100 scale); no defaults | Plain input and scalar; no cleanup | Breaking C++; additive WASM |
| `OptimalSpecificSpeedInput` | C++ `OptimalSpecificSpeed(rpm, flowRate, head, stageCount).calculate()`; no runtime export | `calculateOptimalSpecificSpeed({rpm, flowRate, head, stageCount})` | New `function` + input `value_object` | rpm, US gpm, ft, dimensionless stage count; output US customary specific speed; no defaults | Plain input and scalar; no cleanup | Breaking C++; additive WASM |
| `OptimalSpecificSpeedCorrectionInput` | C++ and runtime `OptimalSpecificSpeedCorrection(style, specificSpeed).calculate()` | `calculateOptimalSpecificSpeedCorrection({style, specificSpeed})` | `class_` replaced by `function` + input `value_object` | `PumpStyle`; US customary specific speed; output fractional efficiency decrement; no defaults | Remove calculator cleanup; plain input and scalar | Breaking C++ and WASM |
| `OptimalPumpEfficiencyInput` | C++ `OptimalPumpEfficiency(style, pumpEfficiency, rpm, kinematicViscosity, stageCount, flowRate, head).calculate()` and accessors; no runtime export | `calculateOptimalPumpEfficiency({style, rpm, kinematicViscosity, stageCount, flowRate, head})` | New `function` + input `value_object` | `PumpStyle`, rpm, cSt, dimensionless stage count, US gpm, ft; output efficiency fraction; no defaults | Plain input and scalar; no cleanup | Breaking C++; additive WASM |
| `PumpEfficiencyInput` | C++ / runtime `PumpEfficiency(style, pumpEfficiency, rpm, kinematicViscosity, stageCount, flowRate, head).calculate()` | `calculatePumpEfficiency({style, rpm, kinematicViscosity, stageCount, flowRate, head})` returning `PumpEfficiencyResult` | `class_` calculator/result replaced by `function` + input/result `value_object` | Same duty units as #226; `average`, `max` are fractions; no defaults | Remove calculator and result cleanup; all values plain | Breaking C++ and WASM |
| `PumpStyle`, `SpecificSpeed` | Mixed binding/declaration module | Dedicated pump enum binding/declaration module; same runtime names and enumerator values | Preserve `enum_` | Unitless classifications; no renumbering | Shared runtime enum objects; no per-call cleanup | Runtime preserved; internal/deep import paths migrate |

`pump_efficiency::Result` contains `double average` and `double max`; bind it as `PumpEfficiencyResult` and declare
that name as an interface, not a runtime constructor. The five scalar helpers do not need result structs.
Keep stage count as `double` / `number`, matching current APIs; do not silently restrict it to integers.

## Compatibility Decision

- User explicitly approved the breaking stateless migration, relocation into `motorDriven/pump`, and standalone
  APIs for all six calculators on 2026-10-29, then requested implementation of this documentation plan.
- Remove the six obsolete C++ classes/headers, accessors, compatibility wrappers, and compatibility-only tests
  as each module migrates. Remove the three superseded runtime constructors and declarations when their
  replacements land. Do not retain a second legacy API alongside the approved replacement.
- Omit `pumpEfficiency` from the new #226/#230 inputs: the old member is stored/passed through but never read by
  the calculation. Do not implement a specified-efficiency override as part of removing it. Verify independence
  from several old argument values before deleting the legacy calculation path.
- Behavior changes approved: **none**. Preserve coefficients, arithmetic evaluation order, units, comparisons,
  signed/nonfinite behavior, defaults (including absence of validation), and output values. Do not rewrite
  polynomials with Horner's method or substitute different min/max semantics during this refactor.
- Preserve all `PumpStyle` values 0–12 and `SpecificSpeed` values 0–1. Keep the shared `Pump.h` C++ API unchanged.

## Touched Layers And File Mapping

For every row in the sequence, substitute its exact legacy class name and new basename into this mapping.
This defines one matching file per logical module in each layer.

| Layer | Current | Proposed |
| --- | --- | --- |
| Public C++ | `include/motorDriven/pumpFan/<LegacyClass>.h` | `include/motorDriven/pump/<basename>.h` |
| Implementation | `src/motorDriven/pumpFan/<LegacyClass>.cpp` | `src/motorDriven/pump/<basename>.cpp` |
| Native tests | `tests/cpp/motorDriven/pumpFan/OptimalSpecificSpeedCorrection.unit.cpp` for #229; none dedicated for the other five | `tests/cpp/motorDriven/pump/<basename>.unit.cpp` for each module |
| WASM bindings | Mixed `bindings-wasm/motorDriven/pumpFan/pumpFan.cpp` for #229/#230; none for the four helpers | `bindings-wasm/motorDriven/pump/<basename>.cpp` for each module |
| Declarations | Mixed `ts_def/ts_def_modules/motorDriven/pumpFan/pumpFan.d.ts` for #229/#230 and enums | `ts_def/ts_def_modules/motorDriven/pump/<basename>.d.ts` for each module |
| WASM tests | `tests/wasm-mocha/motorDriven/pumpFan/wasm_achievable_efficiency.test.ts` (#229), `wasm_pump_efficiency.test.ts` (#230); none for the four helpers | `tests/wasm-mocha/motorDriven/pump/wasm_<basename>.test.ts` for each module |
| Algorithm docs | No dedicated pages found | `docs/dox-content/calculators/motorDriven/pump/<basename>_calculator.dox` for each module |
| Child handoff | Not created in the planning pass | `.agents/handoffs/<basename-with-hyphens>-refactor.md`, created when that module begins |

- During #225, extract enums into `bindings-wasm/motorDriven/pump/pump_enums.cpp` and
  `ts_def/ts_def_modules/motorDriven/pump/pump_enums.d.ts`. Add matching
  `tests/wasm-mocha/motorDriven/pump/wasm_pump_enums.test.ts` coverage for preserved runtime values.
  Register enums exactly once; continue including the existing `Pump.h`.
- Update `ts_def/client.d.ts` root exports/module intersections and imports such as `pump_result.d.ts`'s
  `PumpStyle` import. Type-only input/result interfaces must not appear as runtime module properties.
- Keep unmigrated class bindings/declarations in the mixed files until #229/#230 migrate; remove the empty mixed
  files and `PumpFanModule` wiring after #230. Remove superseded test originals when replacements pass.
  No matching active legacy `tests/wasm/` tests were found; recheck at each child start.
- CMake recursively discovers source/header/binding/test files; reconfigure to discover additions/deletions.
  Update direct consumers only as needed for the dependency migration; no unrelated public refactors.
- Each child follows Planner → C++ Namespace Refactorer → WASM TypeScript Steward → Algorithm Docs Author →
  Verification Reviewer, updating its handoff at each phase. These are workflow roles, not a requirement to
  create additional chats. Use `compressedAir/dryer_operating_cost` as the canonical value-object pattern.

## Formulas And Units

Engineering question: estimate achievable average and maximum pump efficiency for a pump style and duty.
Teach the final `average` / `max` interpretation first, then the flow-based estimate, viscosity and speed
corrections, and deviation factor. These are empirical estimates, not a measured pump performance curve.

Let `Q` be US gpm, `H` total head in ft, `n` rpm, `s` dimensionless stage count, and `nu` viscosity in cSt.
Using the coefficient vectors in the appendix, preserve the following source expressions and their order:

```text
Epre = c0 + (c1 * exp(-c2 * Q) + c3 * exp(-c4 * Q))             [percent]
Ns = n * sqrt(Q) / pow(H / s, 0.75)                           [rpm*sqrt(US gpm)/ft^(3/4)]
B = 26.6 * (pow(nu, 0.5) * pow(H, 0.0625)) /
    (pow(Q, 0.375) * pow(n, 0.25))                            [empirical parameter in stated units]
Cnu = fmin(1, pow(B, -(0.0547 * pow(B, 0.69))))                [dimensionless]
Cns = fmax(a0 + a1*Ns + a2*pow(Ns,2) + a3*pow(Ns,3) +
           a4*pow(Ns,4) + a5*pow(Ns,5) + a6*pow(Ns,6), 0)/100 [fractional decrement]
D = 1 + (p0 + p1*exp(-p2*log10(Q)) +
         p3*exp(-p4*log10(Q))) / 100                          [dimensionless multiplier]
average = (Epre / 100) * Cnu - Cns                            [efficiency fraction]
max = average * D                                           [efficiency fraction]
```

Formula/unit conflicts and boundaries to retain explicitly:

- Pre-efficiency really returns percentage points, while optimal efficiency, specific-speed correction, and
  composite results are fractions. Legacy C++/declaration comments claiming percent for the latter are misleading.
- Specific speed uses `rpm*sqrt(US gpm)/ft^(3/4)` with per-stage head. Legacy C++ comments containing `ft/s` are
  inconsistent with the formula. This dimensional US customary convention is not a universal dimensionless speed.
- Only `VERTICAL_TURBINE` uses the vertical-turbine correction table; `AXIAL_FLOW` uses the other table even though
  its pre-efficiency uses the vertical-turbine flow curves. Do not merge these branches.
- `SPECIFIED_OPTIMAL_EFFICIENCY` and `POSITIVE_DISPLACEMENT` return zero pre-efficiency; unknown native enum values
  also reach that fallback. The composite still subtracts the nonvertical speed correction and multiplies by D,
  so results can be negative. Preserve that behavior; do not silently introduce an override, clamp, or PD model.
- No general validation or [0,1] result clamp exists. Preserve `fmin`/`fmax` NaN handling and current behavior for
  zero/negative flow, head, speed, viscosity, or stages; distinguish defined nonfinite arithmetic from undefined
  behavior if found. Do not add new validation or denominator guards without separate approval.
- No double-suction flow-halving is present in the specific-speed formula. Any engineering correction is separate.
- Provenance: inspected source at the Suite commit recorded above and existing fixtures. A source comment refers
  to an Excel sheet, but the original empirical coefficients, calibration ranges, and authoritative references
  remain unverified. Do not invent Hydraulic Institute citations or validated operating ranges.

Existing examples to preserve, not newly executed or newly captured goldens:

- Native nonvertical correction: `END_SUCTION_SEWAGE`, `Ns=680` expects approximately `0.05020039`.
- WASM correction: `END_SUCTION_SLURRY`, `Ns=1170`; current test expects correction times 100 approximately
  `1.8942771852074485`, with tolerance `0.001` in percentage points.
- WASM composite: ANSI/API, Q=2000, n=2000, nu=1.107, s=1, H=137, old unused efficiency=0.90;
  existing assertions are `average≈0.84`, `max≈0.869`, each tolerance `0.001`. The interpreted estimates are
  about 84% average and 86.9% maximum efficiency. Capture full-precision baseline values before implementation;
  do not treat these rounded assertions as complete preservation evidence.
- Each child `.dox` page must explain the engineering question, final result, decision path, formulas, units,
  symbol tables, worked example, provenance, assumptions, and inappropriate uses. Keep API migration history in
  handoffs/issues rather than teaching pages; wire the pages into the relevant Doxygen groups/navigation.
  No SME formula change is required for behavior preservation;
  unresolved engineering corrections require separate acceptance.

## Desktop Impact

- Migrate `PumpsSuiteApiService.pumpEfficiency` to the plain input/result function and
  `achievableEfficiency` to the scalar correction function. Remove only obsolete class/result cleanup.
  Keep their app-facing signatures, including the now-unused `pumpEfficiencyInput` adapter argument, to avoid
  unrelated caller churn; do not pass that argument to the new Suite input.
- Preserve `SuiteApiHelperService` enum mappings. `achievableEfficiency` multiplies the correction fraction by
  100; `PsatService` rounds it to two decimals. `pumpEfficiency` returns fractions; `PsatService` converts flow/head
  to gpm/ft and rounds `average` / `max` to four decimals. UI callers may multiply by 100; preserve those boundaries.
- Trace achievable-efficiency calculators/graphs, specific-speed graphs, PSAT pump-fluid estimates, and
  explore-opportunities pump-data forms through production services. Preserve displayed/report/export values,
  saved-data shapes, nullability, flags, and default database behavior. No new wrappers for unused helper APIs.
- No direct process-flow consumer of the six legacy class names was found in the inspected source; recheck at
  integration. Keep its package pin aligned with the root even if it remains a dependency-only update.
- Local Desktop inspection was on unrelated branch `issue-3493`, pinning `1.2.7-rc.401.1` in both manifests;
  it is not the accepted future integration baseline. The prior PumpResult epic also retains the two legacy
  efficiency wrappers. Reinspect accepted Desktop source and installed declarations when integration begins.
- Reconcile [Suite PR #446](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/446) and
  [Desktop PR #9054](https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/9054), plus
  [Desktop coordination #8957](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957), before final integration.
  Their acceptance/package state must be rechecked; this new epic does not merge or close them.

## Package And Release Coordination

- Classification: breaking C++ and WASM API plus four additive WASM helper APIs; no approved calculation behavior,
  default-data, or WASM filename/location change. Declarations change with the runtime.
- New epic beta/final versions: pending; do not copy package identifiers from the prior epic.
- Finish all six Suite child implementations, fresh cross-layer verification, documentation, and child reviews
  before consolidated Desktop implementation or dependency updates.
- Reconcile current develop and previous PumpResult integration; complete integrated Suite validation and review.
  Open a reviewed integration/readiness PR using the existing CI workflow and keep the Suite PR open during
  Desktop integration. CI currently supports ready same-repository PRs targeting `develop` or `epic-*`.
- Use the exact CI-published integrated beta, not a floating `beta` tag or arbitrary child beta. Record its Suite
  head and publication evidence in the PR and Desktop issue. Do not push evidence-only package-version commits.
- Update both Desktop manifests and both npm-generated lockfiles together, run affected verification, and complete
  Desktop review. Verify browser WASM initialization and representative calls; check Electron loading when
  packaging, asset paths, or `locateFile` changes. No such loading change is planned.
- Select and publish the approved final Suite package only after both implementations are verified; update both
  Desktop pins/lockfiles and repeat affected checks. Record actual versions, PRs, and acceptance before closure.
- Release readiness: not ready. Implementation, baseline capture, Suite/Desktop verification and reviews,
  integrated beta, and final package are all future gates.

## Validation

Planning-pass checks: verify six issue titles/states and retained parents, source/declaration/test mappings,
formula coefficients and thresholds, local links, documentation-only diff, and `git diff --check`.
No calculator tests, builds, Doxygen generation, baseline capture, or package validation are claimed in this pass.

Planning evidence (2026-10-29): six issue titles/open states/unchanged #204 parents verified through GitHub;
read-only documentation audit verified local links, all 113 transcribed coefficient values against source,
six Suite issue references, and every Desktop integration-template section. Desktop issue #9059 was created
from the prepared body and read back through GitHub with an exact body match. `git diff --check` and an explicit
audit of the untracked handoff's whitespace, fences, table widths, and local links passed. Worktree status contains
only this new planning document; no tracked file, calculator, package, or Desktop checkout changes were made.

Later implementation gates:

1. Capture immutable legacy inputs/results before each relevant source change. Record source revision, exact
   package/runtime, units, raw values, signed zero/nonfinite classifications, and existing expected tolerances.
2. Retain every existing correction fixture. Add native and typed package-root WASM coverage for all six modules:
   all pump styles; shared style groups; below/at/above every flow and speed threshold; zero-clamped correction;
   one/multiple/fractional stages; viscosity cases around the correction cap; old ignored-input independence;
   invalid/zero/negative/nonfinite numeric inputs and repeated calls without retained state.
3. Configure/build native C++ and run focused tests, then the full native suite. Run `npm run verify:wasm` for a
   fresh build/stage/typecheck/browser run; `npm run verify:types` for declaration verification. Generate Doxygen,
   inspect affected page diagnostics, and run `git diff --check`. Never claim stale `bin/client.*` validates source.
4. Check all six runtime functions, interfaces, cleanup-free inputs/results, absence of superseded constructors,
   enum values, and package-root exports. Inspect packed artifacts for runtime and declaration completeness.
5. Capture an immutable accepted Desktop baseline before dependency/wrapper changes; separate previous-epic or
   develop reconciliation from this migration. Use synthetic production-service scenarios for all affected
   graphs/forms, PSAT existing/modified paths, unit systems, and displayed/reported values.
6. Report every raw numerical difference, including ones inside tolerances: scenario/input, field/units, before/
   after, absolute/relative delta, source/package versions, verified cause, consumer impact, and disposition.
   Tolerances assess significance, not whether differences are reported. Require zero unexplained differences,
   zero unapproved behavior changes, identical displayed/report-rounded values, and preserved field presence,
   structure, nullability, flags, and nonfinite classifications. Do not overwrite baseline snapshots to pass.
7. Run focused Desktop wrapper/production-service tests, Angular typecheck/build, applicable assessment regressions,
   process-flow tests/typecheck, and browser runtime checks against the exact beta; repeat affected checks for
   the final package. Record actual results and environment limits in the Desktop issue.

## Internal Review

- This is a planning handoff, not implementation readiness or a PR review. No PR is opened in this pass.
- For each later child, follow `.github/skills/measur-code-review/SKILL.md` against its actual epic base; for final
  integration review the full epic-to-intended-base diff. Freeze and record exact base/head commits, reviewer,
  findings/dispositions, checks rerun after fixes, and `ready` / `ready with documented follow-up` outcome.
- No unresolved actionable P0–P2 findings may remain at PR opening. Repeat review after material changes.
  Follow Desktop's own review instructions for its eventual diff. Human approval remains separate.

## Open Questions Or Blockers

- None blocks planning. Original empirical references/ranges remain unverified and must be described honestly.
- Implementation is intentionally deferred; baseline capture and previous PumpResult integration reconciliation
  remain required before their respective implementation/integration gates.

## Appendix: Coefficients And Branches To Preserve

These are transcribed from the inspected legacy source. Tables express coefficient columns as vectors for planning;
they do not authorize changing arithmetic order or storage/evaluation strategies. Verify transcription against source
when creating each module handoff.

Deviation vector `(p0,p1,p2,p3,p4)`:
`(0.10805906, 18.077243, 0.78231304, 30.525232, 0.80684022)`.

Pre-efficiency vector order is `(c0,c1,c2,c3,c4)` in the formula above. Equality selects the upper flow interval.

| Styles / legacy table | Q interval, US gpm | Coefficient vector |
| --- | --- | --- |
| DOUBLE_SUCTION / j | Q < 9000 | `(90.190375, -7.8068742, 0.00033366482, -8.1364684, 0.0026659434)` |
| DOUBLE_SUCTION / j | Q >= 9000 | `(91.0, -3.6664629, 0.0001264433, -14.697275, 0.00072855045)` |
| VERTICAL_TURBINE, AXIAL_FLOW / v | Q < 2550 | `(87.456119, -9.3556039, 0.00067139092, -9.4309496, 0.0039344122)` |
| VERTICAL_TURBINE, AXIAL_FLOW / v | 2550 <= Q < 7220 | `(89.899894, -5.9800814, 0.00019480643, -7.0638099, 0.0010440162)` |
| VERTICAL_TURBINE, AXIAL_FLOW / v | Q >= 7220 | `(90.124016, -1.7332611, 0.00014953651, -3.3197451, 0.00015232542)` |
| LARGE_END_SUCTION / g | All Q | `(90.379274, -3.000737, 0.000034054964, -4.818246, 0.00019083831)` |
| END_SUCTION_ANSI_API / f | Q < 1030 | `(84.655455, -18.706336, 0.0016056629, -20.655962, 0.0081197589)` |
| END_SUCTION_ANSI_API / f | Q >= 1030 | `(87.748473, -7.6842423, 0.0003739105, -17.336122, 0.0024096967)` |
| MULTISTAGE_BOILER_FEED / e | Q < 890 | `(84.286574, -17.836167, 0.0013236525, -26.951966, 0.0068256307)` |
| MULTISTAGE_BOILER_FEED / e | Q >= 890 | `(87.129684, -7.8144274, 0.00034998448, -19.605637, 0.0022387671)` |
| API_DOUBLE_SUCTION, END_SUCTION_STOCK / dh | Q < 4440 | `(87.199887, -10.580842, 0.00027878405, -23.785033, 0.0018831236)` |
| API_DOUBLE_SUCTION, END_SUCTION_STOCK / dh | Q >= 4440 | `(90.158464, -4.8350009, 0.000048652395, -7.2881572, 0.00027630687)` |
| END_SUCTION_SEWAGE, END_SUCTION_SUBMERSIBLE_SEWAGE / bc | Q < 2170 | `(83.528143, -23.543231, 0.00071315587, -37.584938, 0.005809375)` |
| END_SUCTION_SEWAGE, END_SUCTION_SUBMERSIBLE_SEWAGE / bc | Q >= 2170 | `(89.704526, -6.9708815, 0.000057096295, -13.868089, 0.00046766436)` |
| END_SUCTION_SLURRY / a | Q < 1690 | `(79.096487, -32.006283, 0.00084199445, -23.100062, 0.0064912714)` |
| END_SUCTION_SLURRY / a | Q >= 1690 | `(85.957484, -15.256678, 0.00017627657, -24.920847, 0.0012055457)` |

Speed correction vector order is `(a0,a1,a2,a3,a4,a5,a6)` before `fmax(...,0)/100`.
Equality selects the upper speed interval; all nonvertical styles share `notVTP`.

| Styles / legacy table | Ns interval | Coefficient vector |
| --- | --- | --- |
| VERTICAL_TURBINE / VTP | Ns < 4550 | `(14.788539, -0.022490348, 0.000017226359, -0.0000000075690542, 1.8893534E-12, -2.4834106E-16, 1.3345507E-20)` |
| VERTICAL_TURBINE / VTP | Ns >= 4550 | `(4.0559384, -0.0026632249, 0.0000006761157, -0.000000000087766773, 6.5103425E-15, -2.5380141E-19, 4.007753E-24)` |
| All other styles / notVTP | Ns < 2530 | `(14.884085, -0.021342141, 0.0000121172, -0.0000000031885957, 1.4907927E-13, 1.2855352E-16, -2.3798184E-20)` |
| All other styles / notVTP | Ns >= 2530 | `(6.5703317, -0.010048327, 0.0000061475098, -0.0000000019659725, 3.5079978E-13, -3.2272033E-17, 1.1881188E-21)` |
