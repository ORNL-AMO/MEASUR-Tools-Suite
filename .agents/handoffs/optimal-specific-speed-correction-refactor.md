# Optimal Specific Speed Correction Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: implemented, verified and independently reviewed; CI/publication tracked in child PR
- Owner: Codex
- Created / last updated: 2026-11-02
- Suite issue: [#229](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/229)
- Epic: [#230](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230), [epic handoff](pump-efficiency-refactor.md)
- Branch / initial PR base: `issue-229` / `issue-228`
- Suite PR: [child PR and CI/publication record](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Aissue-229+base%3Aissue-228)
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
- C++ / WASM / Docs / Verification Reviewer: complete across all layers and migrated consumers.
- Portable fixtures are derived from the immutable 345-case correction matrix in
  `/private/tmp/pump-efficiency-stack-baseline-seajyimb`, covering all 13 styles plus unknown native
  values, both thresholds and adjacent doubles, negative/zero/nonfinite inputs and overflow.
- Retain relative `1e-14` and absolute `1e-15` fraction tolerance for new portable fixtures, compare
  signed zero/nonfinite classes explicitly, and retain the original native/WASM assertion tolerances.
- macOS/Apple clang and Ubuntu 24.04 amd64/GCC Release: focused **1557 assertions / 4 cases**, full
  **7534 assertions / 360 cases**. Full Linux Valgrind: **zero errors, no leaks**.
- Fresh `npm run verify:wasm`: **300 browser tests passed**, rebuilt/staged runtime and types verified.
- Complete immutable legacy matrix: **5254 fields exactly preserved** on each of macOS, GCC and WASM,
  with **zero numerical differences or classification changes**. Same-platform reports are
  `/private/tmp/pump-229-{macos,wasm}-comparison/comparison.json` and archive `gcc-stage-2/comparison.json`.
- Types, links, generated Doxygen formulas/tables, package runtime/declaration contents and complete
  diff whitespace passed. No affected-page warnings; existing repository BibTeX/unrelated warnings remain,
  and interactive MathJax rendering is unverified. Logs: `/private/tmp/pump-229-*.log` and archive `linux-229-*.log`.
- All 626 original native expected assertions and their tolerances are retained. Cross-platform legacy-only
  differences are recorded separately in the archive; no fixture or tolerance was replaced to pass.
- Report every raw numerical difference without replacing goldens or silently loosening tolerances.

## Internal Review

- Intended base: `issue-228` at `f99de8d4d60840288b84ff19bc46fa82f4ec2115`.
- Reviewed source head: `2d2d6bb830437037b98a0fd3f5c887eb2a847052`.
- Independent reviewer: `legacy_capture`, using `.github/skills/measur-code-review/`; **no actionable findings**.
- Readiness: ready with documented existing BibTeX/visual-MathJax follow-up. Reviewer independently verified
  all 626 legacy expected tuples, all 28 coefficients, focused native/types/whitespace, cross-layer contracts,
  Desktop conversion and all 5254 exact frozen-head macOS fields; inspected full Linux/Valgrind evidence.
- Report: archive `review-229/review.md`. Only handoff/epic metadata follows the reviewed source head.
- Record reviewer, findings/dispositions and checks rerun after fixes before opening the child PR.

## Open Questions Or Blockers

No design decisions remain. Live CI/publication evidence belongs in the linked child PR; Desktop
adoption and final release remain follow-up gates.
