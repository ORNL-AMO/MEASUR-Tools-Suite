# Optimal Pre-Pump Efficiency Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: implemented, verified and independently reviewed; publication tracked in the linked child PR
- Owner: Codex
- Created / last updated: 2026-11-02
- Suite issue: [#225](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/225)
- Epic: [#230](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230),
  [epic handoff](pump-efficiency-refactor.md)
- Suite PR: delivery requested on 2026-11-02; branch `issue-225`, intended base `epic-pump-eff-refactor`.
  [Child PR and CI/publication record](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Aissue-225+base%3Aepic-pump-eff-refactor)
  owns post-push evidence; do not make evidence-only follow-up pushes.
- Starting base/head: `666f224605365c95aaf70220ea04f6a7c4b7cc57`, merged
  [#448](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/448)
- Desktop issue: [#9059](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059)
- Desktop PR: deferred to consolidated epic integration

## Target Module And Touched Layers

Move `OptimalPrePumpEff.h/.cpp` from `motorDriven/pumpFan` to
`include/motorDriven/pump/optimal_pre_pump_efficiency.h` and the matching `src/` path.
Delete the old class/files and migrate its sole direct caller, `OptimalPumpEfficiency.cpp`.
Add matching binding, declaration, native test, typed WASM test and calculator `.dox` page:

- `bindings-wasm/motorDriven/pump/optimal_pre_pump_efficiency.cpp`
- `ts_def/ts_def_modules/motorDriven/pump/optimal_pre_pump_efficiency.d.ts`
- `tests/cpp/motorDriven/pump/optimal_pre_pump_efficiency.unit.cpp`
- `tests/wasm-mocha/motorDriven/pump/wasm_optimal_pre_pump_efficiency.test.ts`
- `docs/dox-content/calculators/motorDriven/pump/optimal_pre_pump_efficiency_calculator.dox`

Extract the shared runtime enums from the mixed `pumpFan` binding/declaration into
`motorDriven/pump/pump_enums` files, with matching WASM coverage. Update package-root exports,
module intersections and `pump_result.d.ts` imports. Leave `Pump.h` and remaining class APIs unchanged.
Canonical pattern: `compressedAir/dryer_operating_cost`.

## Current Public API And Runtime Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Calculator | `OptimalPrePumpEff(style, flowRate).calculate()`; no WASM export | `optimal_pre_pump_efficiency::calculate(const Input&)`; `calculateOptimalPrePumpEfficiency({style, flowRate})` | function + input value object | Pump style; flow US gpm; result percent; no defaults | Plain input, numeric result; no cleanup | Approved breaking C++, additive WASM |
| Pump enums | Mixed `pumpFan` module | Dedicated `pump_enums` module | Same `enum_` registrations, once each | Unitless classifications, unchanged values | Shared runtime objects; no per-call cleanup | Runtime/root exports preserved; deep imports move |

`Input` contains `Pump::Style style` and `double flow_rate`. The corresponding type-only
`OptimalPrePumpEfficiencyInput` contains `style: PumpStyle` and `flowRate: number`.
`OptimalPrePumpEfficiencyModule` contains only the runtime function. No input/result constructor or `delete()`.
`PumpEnumsModule` exposes the runtime `PumpStyle` (0–12) and `SpecificSpeed` (0–1).

## Compatibility Decision

The user explicitly approved the breaking namespace relocation and deletion of the class, with no compatibility
wrapper. Behavior changes approved: **none**. Preserve all 80 coefficient values, strict `<` range selection,
formula grouping, special-style/unknown-enum fallback, and nonfinite arithmetic. Retain the direct caller's
percent-to-fraction conversion, subsequent corrections, and ownership contract. Private descriptive `constexpr`
curve records, named thresholds, one evaluator and readable decay intermediates replace indexed arrays.
At the user's readability request, private `select_curve` uses explicit threshold branches, with no ternaries
inside evaluator arguments. Public `calculate` selects a curve, returns the zero fallback if none applies,
then evaluates it once. The pointer refers only to immutable static records; no allocation or ownership changes.
Keep source files free of file/brief/author banners; document the public header.

## Formulas And Units

Estimate efficiency before viscosity and specific-speed corrections, in percent:
`baseline + (first_amplitude * exp(-first_decay * Q) + second_amplitude * exp(-second_decay * Q))`.
Amplitudes/baseline are percentage points; decay coefficients are inverse US gpm. All signed coefficients and
addition/multiplication grouping are retained. The source referred to an Excel sheet; original coefficient
provenance and calibration ranges remain unverified. No new physical interpretation is assigned to coefficients.

Thresholds (US gpm): double suction 9000; vertical turbine/axial 2550 and 7220; ANSI/API 1030;
boiler feed 890; API double suction/stock 4440; sewage/submersible 2170; slurry 1690. Large end suction has
one curve. Equality chooses the upper interval. Specified-optimal, positive-displacement and unknown native
styles return zero even for nonfinite flow. No validation, interpolation, conversion or clamp is introduced.
ANSI/API at 2000 US gpm selects the upper curve: approximately 83.97084437955112% (not 0.8397%).
The teaching page records all curves, units, boundaries and limitations; API migration belongs here.

## Desktop Impact And Package Coordination

Desktop has no standalone legacy pre-efficiency wrapper to migrate. Preserve root enum runtime names and
values, unit mapping, existing `PumpEfficiency`/correction classes and their `delete()` contracts. No Desktop
implementation, package version or dependency update belongs to this child. Exact integrated beta, aligned
root/process-flow pins and npm lockfiles, wrapper migration, immutable raw/rounded baselines and final-package
verification remain under #9059 after all six modules. Reconcile Suite #446 / Desktop #9054 at epic integration.

## Legacy Capture

Captured **before replacement** at `666f224605365c95aaf70220ea04f6a7c4b7cc57`, Apple clang 21.0.0,
arm64 macOS, `-O3 -DNDEBUG -std=gnu++20`. Temporary archive:
`/private/tmp/optimal-pre-pump-efficiency-whf960m7` (source copies, harness, command metadata and
full-precision decimal/hex results). 660 scalar results cover 13 styles plus two unknown native values,
positive/negative/extreme/nonfinite flows and adjacent doubles at all thresholds; 39 composite results cover
all 13 styles at 100, 2000 and 10000 US gpm with n=2000 rpm, nu=1.107 cSt, one stage, H=137 ft.
Portable fixture subsets will be retained in native/WASM tests independently of exact same-platform comparisons.

## Validation

- Planner, C++ Namespace Refactorer, WASM TypeScript Steward and Algorithm Docs Author phases complete.
  Verification Reviewer confirmed matching source, bindings, declarations, units, ownership and teaching page.
- macOS: `cmake -S . -B build-cpp`, `cmake --build build-cpp -j 8`, focused native tests:
  **692 assertions / 4 cases**; full native suite: **6558 assertions / 355 cases**.
- Ubuntu 24.04 amd64 container (emulated on arm64 host), GCC 13.3.0, CMake Release:
  focused and full native counts match macOS. Full suite under Valgrind 3.22.0 with
  `--error-exitcode=99 --leak-check=full`: **zero errors, no leaks, zero bytes at exit**.
- Same-platform full-precision comparisons: **zero raw differences across all 699 rows on macOS,
  Ubuntu/GCC and Emscripten/WASM**. Legacy and current builds used the same flags on each platform.
  Emscripten capture flags: `-O3 -DNDEBUG -std=gnu++20 -fexceptions -sENVIRONMENT=node`.
- Cross-platform comparison against the unchanged macOS captures is reported separately: both GCC and WASM
  differ in 6 scalar and 44 composite numeric fields (50 each). Maximum differences: `1.4210854715202004e-14`
  percentage points and `4.440892098500626e-16` efficiency fraction. All are within the approved bounds.
  These differences also occur in the archived legacy calculation, consistent with compiler/libm rounding;
  no legacy/current differences or classification changes occurred on any platform. Every differing field,
  its raw values and tolerance are listed in the archive's `gcc-cross-platform-differences.json` and
  `wasm-cross-platform-differences.json`. Captured goldens were not replaced or loosened.
- Fresh `npm run verify:wasm` after activating `/Users/txr/dev/emsdk/emsdk_env.sh`:
  build/stage/typecheck and **295 ChromeHeadless browser tests passed**; existing pump-efficiency assertions
  and class cleanup tests retained. Separate `tsc --noEmit` passed.
- `npm run check:docs`: all local Markdown targets exist. `npm pack --dry-run --json` confirmed both runtime
  artifacts, root declarations and both new declaration modules; no version/dependency changes.
- Doxygen generation exited zero and emitted the new page, group navigation, all three formula anchors,
  symbol tables and coefficient table, with no warnings naming the affected page/header. Generated HTML
  inspected; interactive browser/MathJax rendering was not verified. Repository-wide missing BibTeX executable
  still reports `Problems running bibtex` / missing `.bbl`, alongside unrelated legacy warnings.
- `git diff --check` and explicit changed/untracked-file trailing-whitespace audit passed. Independent review
  identified an extra EOF blank line in the initially untracked enum binding; removed it and confirmed the
  complete frozen-candidate `base...head` diff passes `git diff --check`.
- Percentage fixtures: relative `1e-14`, absolute `1e-12` percentage points; composite fixtures:
  relative `1e-14`, absolute `1e-15` in efficiency fractions. Do not replace captured goldens to pass tests.
- An initial new-test build failed because `nan` conflicted with the system function; renamed the private
  test constant `quiet_nan`. All reported passing checks above ran after that correction. Subsequent test-only
  formatting did not change fixtures or semantics.
- After the user's readability request, reran same-platform captures on all three platforms (zero differences),
  focused/full native suites on macOS and Ubuntu (same counts), fresh WASM verification (295 passed),
  documentation checks and full Ubuntu Valgrind (zero errors/leaks). Final local variable naming is descriptive.

### Validation Evidence Locations

Temporary evidence root: `/private/tmp/optimal-pre-pump-efficiency-whf960m7`, including compiler/command
metadata, archived sources, capture harness, legacy/current decimal and hexadecimal results, cross-platform
reports and `linux-evidence/` (configure/build/focused/full/Valgrind logs).
Original logs: `/private/tmp/oppe-{native-focused,native-full,wasm,wasm-comparison,doxygen,doc-links,types}.log`;
readability-change reruns use the corresponding `-final.log` files
and `/private/tmp/oppe-pack.json`. These local files are supporting evidence; portable baseline fixtures
are retained in the native and WASM test files. Post-push CI/package publication evidence belongs in the
eventual child PR targeting `epic-pump-eff-refactor`, without evidence-only follow-up pushes.

## Internal Review

### Stack CI Amendment (2026-11-02)

- The user approved exact `issue-225/228/229/226/230` PR-base support and base-retarget handling in #449.
- Reviewed amendment: `23b58b07e04a16c61d18344a67930ca01d791f7c...3c9156905af676c120fa361856bb9f25f32784c5`.
- Independent reviewer: `desktop_impact`, using the repository review skill; 88 actual-YAML trigger/job scenarios
  passed, including exact branch allowlisting, metadata-only skips, retargeting, draft/fork restrictions and
  unchanged push/manual release paths. Scoped whitespace passed; live Actions results belong in #449.
- One P3 metadata finding resolved: distinguish initial epic inspection from #449's actual base commit.
- Readiness: ready; no unresolved actionable findings. Report/matrix:
  `/private/tmp/pump-stack-ci-review-KdaWVY`. This amendment does not change calculator source or fixtures.

- Intended base: `epic-pump-eff-refactor` at `666f224605365c95aaf70220ea04f6a7c4b7cc57`.
- Reviewed head: final isolated review snapshot `11bba6c998dbe311c964e116954c32f467ee5ac4`.
  This records the complete candidate without moving `issue-225` or changing the user's staging area.
- Reviewer: independent `review_optimal_pre_pump_efficiency` agent using the review-only repository skill.
- Readiness: **ready with documented follow-up**; no unresolved actionable P0–P3 findings.
- Initial review snapshot `1829df2219ad9a520da0ee18c2cb9818327d15e3` exposed an extra EOF blank line in
  the new enum binding. Removed it; full-candidate whitespace check passed at `a8e89298913e5ef7277fc8570e6accf2c12ce15f`.
- User subsequently requested clearer curve selection. Replaced nested ternary arguments with explicit
  selection branches; reran affected validation and independent review against the final snapshot above.
  Reviewer independently reconfirmed all coefficients, preservation files, focused native assertions, types,
  full-diff whitespace and the final 295-test fresh WASM run. No calculation/API/ownership defects found.
- Remaining documented follow-up: historical coefficient provenance/calibration gaps, repository-wide missing
  BibTeX and unverified visual MathJax rendering. Generated affected-page HTML, formulas, tables and links pass.
- After the calculation review at `31636f8d33ad5f224f55ac5161f6b7bdff3ff75a`, updated handoff metadata. At the user's subsequent
  request, removed the developer-facing Calculation Provenance section from the engineering page and changed
  the header's documentation cross-reference to applicability limits. Formulae, coefficients and engineering
  assumptions remain unchanged; provenance history stays in this handoff. Implementation, tests, bindings and
  declarations remain identical to the calculation review snapshot. Independent final review of the complete
  candidate and prose changes at `11bba6c998dbe311c964e116954c32f467ee5ac4` found no actionable findings,
  confirmed full-diff whitespace, and retained the documented non-blocking limits above. Only publication and
  review-evidence metadata changed after that final review.

## Open Questions Or Blockers

Coefficient provenance and calibration range are historical gaps, not authorization for engineering changes.
Record any continuing repository-wide BibTeX or browser-rendering limitations separately from affected-page checks.
