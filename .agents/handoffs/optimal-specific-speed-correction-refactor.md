# Optimal Specific Speed Correction Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: private implementation preparation; shared branch implementation and validation pending
- Owner: Codex
- Created / last updated: 2026-11-02
- Suite issue: [#229](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/229)
- Epic: [#230](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230), [epic handoff](pump-efficiency-refactor.md)
- Branch / initial PR base: `issue-229` / `issue-228`
- Suite PR: pending
- Fixed legacy capture baseline: `23b58b07e04a16c61d18344a67930ca01d791f7c`
- Desktop issue: [#9059](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059)
- Desktop PR: follow-up after Suite stack integration

## Target Module And Touched Layers

Move `OptimalSpecificSpeedCorrection.h/.cpp` from `motorDriven/pumpFan` to the matching
`motorDriven/pump/optimal_specific_speed_correction.h/.cpp` pair. Migrate the sole production
caller in the still-unmigrated optimal-efficiency implementation. Add one binding, declaration,
native test, typed package-root WASM test and engineering teaching page with that basename.
Update package-root exports and module intersection. Follow `compressedAir/dryer_operating_cost`
for the stateless value-object pattern.

Remove the old mixed-file constructor binding/declaration, legacy header/source and superseded
WASM test. Retain the mixed pump/fan binding/declaration and composite runtime classes until #230.
Move all 626 existing native assertions without changing expected values or Approx tolerances.

## Runtime API Contract And Compatibility

| Surface | Before | After | Embind kind | Units/defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Specific-speed correction | `OptimalSpecificSpeedCorrection(style, specificSpeed).calculate()` in C++ and WASM | `optimal_specific_speed_correction::calculate(const Input&)`; `calculateOptimalSpecificSpeedCorrection({style, specificSpeed})` | Constructor replaced by function + input value object | PumpStyle; rpm*sqrt(US gpm)/ft^(3/4); result fraction decrement; no defaults | Plain input and scalar result; remove calculator delete() | Approved breaking C++/WASM |

The epic records explicit approval of the breaking stateless migration and old-surface removal.
`Input` contains `Pump::Style style` and `double specific_speed`; the TypeScript interface has
required readonly `style` and `specificSpeed`. The module exposes only the runtime function.
No input interface constructor, result type or compatibility wrapper is added. Shared enums and
`Pump.h` remain unchanged. C++ callers replace construction/`calculate()` with one namespace call;
WASM callers pass a plain object and remove calculator cleanup.

Behavior changes approved: **none**. Preserve all 28 coefficients, strict speed comparisons,
weighted-sum evaluation order, powers, fmax NaN handling, lower clamp and division by 100.
Four private named curve records and named thresholds replace indexed tables; no Horner rewrite,
new validation, integer restriction, smoothing, override or upper clamp is introduced.

## Formulas And Units

Engineering question: what efficiency decrement accompanies this pump style and specific speed?
The final correction is a fraction subtracted from viscosity-adjusted efficiency, not a multiplier
or the pump efficiency. Specific speed uses rpm*sqrt(US gpm)/ft^(3/4), not a dimensionless convention.

The selected curve is `max(a0+a1*Ns+a2*pow(Ns,2)+...+a6*pow(Ns,6),0)/100` in the retained
left-to-right sum order. Only vertical turbine uses the vertical curves, splitting at 4550;
all other native styles, including axial flow and unknown values, split at 2530. Equality selects
the upper curve. The source has no supported operating-range or uncertainty metadata.

Example: slurry at Ns=1170 gives approximately `0.018942771852074478`, a decrement of about
1.8943 percentage points. A separately supplied viscosity-adjusted fraction of 0.84 becomes
approximately 0.8211. No new calibration or SME formula decision is implied.

NaN and positive infinity yield zero. Negative infinity yields positive infinity for vertical
turbine and zero for other styles. Signed zeros use the lower curve. Very large finite terms
can overflow to NaN and reach fmax's zero result. These outcomes are preserved arithmetic,
not validation signals. Provenance/calibration gaps remain in the epic; no references are invented.

## Desktop Impact And Package Coordination

Desktop's `PumpsSuiteApiService.achievableEfficiency` must eventually call the new function and
remove calculator cleanup, preserving its app-facing signature, enum mapping and fraction-times-100
conversion; `PsatService` retains two-decimal rounding. Graph/report/saved-data behavior and loading
paths remain unchanged. This child does not edit Desktop or its dependency pins; consolidated
integration under #9059 will use the exact integrated beta and repeat affected production-service
checks. Keep this breaking runtime change linked to that issue.

Classification: breaking C++/WASM API with synchronized declarations, no behavior/default-data or
packaging-path changes. Child beta/final evidence belongs in the PR; no package-version-only pushes.
Release readiness remains pending the integrated Suite/Desktop acceptance gates.

## Validation And Persona Progress

- Planner: API, compatibility, unit conventions, layers, direct consumer and baseline fixed.
- C++ / WASM / Docs: private draft prepared; shared implementation pending.
- Portable fixtures are derived from the immutable 345-case correction matrix in
  `/private/tmp/pump-efficiency-stack-baseline-seajyimb`, covering all 13 styles plus unknown native
  values, both thresholds and adjacent doubles, negative/zero/nonfinite inputs and overflow.
- Retain relative `1e-14` and absolute `1e-15` fraction tolerance for new portable fixtures, compare
  signed zero/nonfinite classes explicitly, and retain the original native/WASM assertion tolerances.
- Required after shared implementation: exact same-platform full-chain comparisons on macOS, Linux
  and WASM; focused/full C++ tests; fresh `npm run verify:wasm`; declarations, links, Doxygen affected-page
  diagnostics/HTML, packed contents and complete-candidate whitespace checks.
- Report every raw numerical difference without replacing goldens or silently loosening tolerances.

## Internal Review

- Intended base: immediate parent `issue-228`; freeze exact parent/head after branch setup.
- Independent review and readiness: pending.
- Record reviewer, findings/dispositions and checks rerun after fixes before opening the child PR.

## Open Questions Or Blockers

No design decisions remain. Shared implementation, validation and independent review are pending.
