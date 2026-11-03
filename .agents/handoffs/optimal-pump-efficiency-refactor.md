# Optimal Pump Efficiency Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: implemented, verified and independently reviewed; CI/publication tracked in child PR
- Owner: Codex
- Created / last updated: 2026-11-02
- Suite issue: [#226](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/226)
- Epic: [#230](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230),
  [epic handoff](pump-efficiency-refactor.md)
- Suite branch: `issue-226`; initial PR base: `issue-229`;
  [child PR and CI/publication record](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Aissue-226+base%3Aissue-229)
- Fixed legacy baseline: `23b58b07e04a16c61d18344a67930ca01d791f7c`
- Desktop issue: [#9059](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059)
- Desktop PR: follow-up after Suite stack integration

## Target Module And Touched Layers

Move `OptimalPumpEfficiency.h/.cpp` from `motorDriven/pumpFan` into the
`motorDriven/pump/optimal_pump_efficiency` namespace module. Delete the old class, unused state and
mutable accessors. Migrate the still-legacy `PumpEfficiency.cpp` caller to the six-field namespace input.
Add matching binding, declaration/root export and module intersection, native test, typed WASM test
and calculator `.dox` page. Each layer uses the `optimal_pump_efficiency` basename, matching the
canonical `compressedAir/dryer_operating_cost` value-object pattern.

Planner, C++ Namespace Refactorer, WASM TypeScript Steward and Algorithm Docs Author responsibilities
are complete, together with Verification Reviewer checks and independent pre-PR review.

## Public API And Runtime Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Corrected efficiency | `OptimalPumpEfficiency(style, pumpEfficiency, rpm, kinematicViscosity, stageCount, flowRate, head).calculate()` and mutable accessors; no standalone WASM export | `optimal_pump_efficiency::calculate(const Input&)`; `calculateOptimalPumpEfficiency({style, rpm, kinematicViscosity, stageCount, flowRate, head})` | New function + input value object | Pump style, rpm, cSt, dimensionless stages, US gpm, ft total head; result is efficiency fraction; no defaults | Plain input/scalar result, no `delete()` | Approved breaking C++; additive WASM |

C++ `Input` members are `Pump::Style style` and `double rpm`, `kinematic_viscosity`, `stage_count`,
`flow_rate`, `head`. The matching TypeScript interface has six required readonly camelCase fields.
`OptimalPumpEfficiencyModule` exposes only the runtime function. The input/result names are not
runtime constructors. Shared enums and `Pump.h` stay unchanged.

## Compatibility Decision

The epic records the user's approved breaking stateless migration without compatibility wrappers.
Behavior changes approved: **none**. Preserve all arithmetic grouping, coefficients, percent-to-fraction
conversion, helper curve selection and fmin/fmax nonfinite behavior. No validation, conversion,
stage-count integer restriction, flow-halving, specified-efficiency override or final clamp is added.

The old `pumpEfficiency` argument is stored but never used; omit it from the new input. Immutable
pre-change `ignored-efficiency-independence.json` records 360 exact comparisons across all styles and
old arguments 0, -0, -1, 1, 90, positive/negative infinity and NaN. The caller stops forwarding it, but its
own legacy constructor remains until #230. Remove the old header/source, accessors and unused members.

## Formulas And Units

The result answers which corrected efficiency follows from the pump-style/flow estimate, viscosity
and specific-speed decrement. Preserve this evaluation sequence:

```text
Epre = optimal_pre_pump_efficiency::calculate({style, flow_rate})
B = 26.6 * (pow(kinematic_viscosity, 0.5) * pow(head, 0.0625)) /
    (pow(flow_rate, 0.375) * pow(rpm, 0.25))
Cnu = fmin(1, pow(B, -(0.0547 * pow(B, 0.69))))
Ns = optimal_specific_speed::calculate({rpm, flow_rate, head, stage_count})
Cns = optimal_specific_speed_correction::calculate({style, Ns})
Epre = Epre / 100
result = Epre * Cnu - Cns
```

Pre-efficiency is percent; result and speed decrement are fractions. Viscosity is cSt; rotational
speed is rpm; flow is US gpm; head is total ft; stages are dimensionless doubles. Viscosity uses total
head, whereas specific speed divides it by stage count. Only vertical turbines use the vertical speed
correction. Unsupported styles retain zero pre-efficiency and can return negative corrected values.
The teaching page explains the final result, each correction, the stated numerical unit convention,
formula symbol tables, an example and applicability/nonfinite boundaries. No source provenance or
migration-history section is added to the engineer-facing page; historical provenance stays here.

Representative immutable ANSI/API legacy outputs at n=2000 rpm, Q=2000 US gpm, H=137 ft, one stage:

- nu=1.107 cSt: `0.83933686357794668`.
- nu=100 cSt: `0.73181046586426868` (B about 3.12811654, Cnu about 0.871947938).

The relationships are retained from the fixed source. Original empirical calibration ranges and
prediction uncertainty remain unverified; no SME behavior change is required or inferred.

## Desktop Impact And Package Coordination

No standalone legacy optimal-efficiency WASM wrapper is removed. This helper export is additive;
the legacy composite remains and speed correction already uses the stateless API from #229. Desktop code,
package pins, app signatures, saved data, reports and WASM loading are outside this child. Consolidated
consumer verification and exact integrated beta/final decisions remain under #9059 after the Suite
stack. No child version-only commit or arbitrary beta acceptance is planned. Release readiness remains
pending integrated verification, review and downstream acceptance.

## Legacy Captures And Validation

Fixed evidence root: `/private/tmp/pump-efficiency-stack-baseline-seajyimb`, archived at the source
revision above before replacement. Inputs are immutable, with hexadecimal C++ literals and tagged JSON.
All 1575 duty scenarios retain optimal/average/max raw decimal/hex results and classifications on
macOS/Apple clang 21, Ubuntu/GCC 13.3 and Emscripten 4.0.12. Exact platform comparisons assess preservation
independently from compiler/libm cross-platform differences.

The native test retains 197 selected macOS legacy optimal values; the WASM test retains 191
`wasm-legacy-verified` values, excluding unsupported numeric enum inputs not accepted by embind.
Rows preserve their original duty indices. Coverage includes all 13 styles, two unknown native styles,
applicable flow thresholds, both speed thresholds, one/multiple/fractional stages, viscosity-cap
neighbors, signed/zero/nonfinite values, extreme values and repeated independent calls.
Unchanged fixture bounds are absolute `1e-15` plus relative `1e-14` in efficiency-fraction units;
zero signs and nonfinite classes are compared separately. No existing fixture or tolerance is changed.

The full pre-refactor ledgers already contain 12 unsupported-style five-stage fields outside earlier
cross-platform diagnostic bounds, reproduced entirely by legacy sources. They remain in the exact
same-platform matrix. Do not loosen tolerances or replace goldens to hide them. Every selected native
fixture was checked against the captured other-platform legacy result and meets the unchanged bounds.

- Run in a private snapshot before shared application: fixture-provenance/cross-platform subset audit;
  stage-3 macOS capture exactly matched all 5254 fixed legacy fields with zero numeric/classification
  differences; focused native tests passed **204 assertions / 2 cases**; private declaration/test typecheck
  passed. The first ad hoc native link omitted Catch.cpp; adding its separate implementation resolved that
  harness-only failure. These private checks do not replace integrated shared-tree validation.
- Shared-tree macOS/Clang and Ubuntu 24.04 amd64/GCC Release: focused **204 assertions / 2 cases**,
  full **7738 assertions / 362 cases**. Full Linux Valgrind: **zero errors, no leaks**.
- Fresh `npm run verify:wasm`: rebuild/stage/types and **302 browser tests passed**.
- Stack-stage-3 captures: **5254 fields exactly preserved** against fixed legacy on each of macOS,
  GCC and WASM, with **zero numerical differences or classification changes**. Reports:
  `/private/tmp/pump-226-{macos,wasm}-comparison/comparison.json` and archive `gcc-stage-3/comparison.json`.
- Types, links, generated Doxygen page/formulas/tables, packed runtime/declaration contents and whitespace
  checks passed. Existing repository BibTeX/unrelated warnings remain; interactive MathJax rendering is
  unverified. Logs: `/private/tmp/pump-226-*.log` and archive `linux-226-*.log`.
- Preserve all earlier child/composite fixtures. Report every raw before/after difference with cause;
  identical same-platform values and classifications are required, not only tolerance acceptance.

## Internal Review

- Intended base: `issue-229` at `c0fc35a3318361673193ee04852c75041e2eeabc`.
- Reviewed source head: `364f535d112511d95edccd49e044c7a9ea396808`.
- Independent reviewer: `desktop_impact`, using `.github/skills/measur-code-review/`;
  **no actionable P0-P3 findings**. Readiness: ready with documented existing BibTeX/visual-MathJax follow-up.
- Reviewer independently ran focused native/types/links/whitespace, verified all 197 native and 191 WASM
  fixture provenance rows, ignored-input independence, generated formulas/helper links and worked-example math.
- Report: `/private/tmp/optimal-pump-efficiency-review-svmp2bea/review.md`.
- Only handoff/epic metadata follows the reviewed source head; source and fixtures are unchanged.
- Review each current parent diff and repeat after material changes; the final epic requires integrated review.

## Open Questions Or Blockers

No API/formula design questions remain. Shared-tree verification, publication evidence and review are pending.
