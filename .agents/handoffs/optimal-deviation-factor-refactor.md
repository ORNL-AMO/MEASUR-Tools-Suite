# OptimalDeviationFactor Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: implemented, verified and independently reviewed; ready with documented follow-up for the
  pre-existing BibTeX and browser-rendering limitations. User requested commit, push and child PR delivery
  into the epic on 2026-10-29.
- Owner: Codex
- Created / last updated: 2026-10-29.
- Suite issue: [#223](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/223).
- Epic: [pump efficiency handoff](pump-efficiency-refactor.md), Suite [#230](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230).
- Branch / intended PR base: `codex/issue-223-optimal-deviation-factor` / `epic-pump-eff-refactor`.
- Verified local/remote epic base: `892065db8442d2472d7cbba44cf003e16f54a179`.
- Suite PR / CI and publication evidence: [child branch PR](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Acodex%2Fissue-223-optimal-deviation-factor+base%3Aepic-pump-eff-refactor).
  Post-push checks and exact beta publication belong in the PR; do not push package-version-only evidence commits.
- Desktop coordination: [#9059](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059); no Desktop PR for this child.

## Target Module And Touched Layers

- Move `include/` and `src/motorDriven/pumpFan/OptimalDeviationFactor.h/.cpp` to the matching
  `motorDriven/pump/optimal_deviation_factor.h/.cpp` pair.
- Add matching `bindings-wasm/motorDriven/pump/optimal_deviation_factor.cpp`,
  `ts_def/ts_def_modules/motorDriven/pump/optimal_deviation_factor.d.ts`, native
  `tests/cpp/motorDriven/pump/optimal_deviation_factor.unit.cpp`, typed WASM
  `tests/wasm-mocha/motorDriven/pump/wasm_optimal_deviation_factor.test.ts`, and teaching
  `docs/dox-content/calculators/motorDriven/pump/optimal_deviation_factor_calculator.dox`.
- Update `ts_def/client.d.ts` exports/module intersection, private call in `PumpEfficiency.cpp`, and unused
  include in `OptimalPumpEfficiency.cpp`. No dedicated legacy binding/declaration/test/page exists to migrate.
- Patterns: `compressedAir/dryer_operating_cost` for cross-layer consistency; scalar input explicitly chosen by user.

## Current Public API And Runtime API Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| C++ factor | `OptimalDeviationFactor(flowRate).calculate()` | `optimal_deviation_factor::calculate(double flow_rate)` | Native scalar function | US gpm input; dimensionless multiplier; no default/validation | Values only | Breaking, explicitly approved |
| Standalone WASM | No export | `calculateOptimalDeviationFactor(flowRate: number): number` | `function` only | Same units/behavior | No constructor, input struct/interface, result object or cleanup | Additive |
| Composite consumer | Legacy construction in `PumpEfficiency::calculate()` | Namespace call | Existing class binding remains | Same input/output conventions | Existing composite ownership remains | Public contract preserved |

## Compatibility Decision And Proposed API

- User approved the breaking class removal, pump-domain relocation, additive standalone WASM API, and scalar input
  on 2026-10-29. The namespace has only `double calculate(double flow_rate)`; TypeScript contributes
  `OptimalDeviationFactorModule` with that one runtime function. No compatibility wrappers or runtime constructors.
- Name all seven constants exactly as approved: `base_multiplier`, `baseline_deviation_percent`,
  `first_exponential_amplitude_percent`, `first_log_flow_decay_coefficient`,
  `second_exponential_amplitude_percent`, `second_log_flow_decay_coefficient`,
  `percentage_points_per_fraction`. Private `constexpr double` values use the user's naming despite the generic
  style guide's `kPascalCase` constant convention.
- Behavior changes approved: none. Preserve weighted-sum grouping, signed/nonfinite outputs, and absence of
  validation/clamping. Remove both obsolete files, not only the public declaration.
- User readability follow-up: remove the new `.cpp` file/brief/authors banner, use named intermediate values
  for the logarithmic flow, two exponential decays, total deviation percentage and deviation fraction, and use
  descriptive composite-consumer variable names. Compute the common `log10(flow_rate)` once; both exponential
  calls and weighted-sum order remain. This supersedes the initial duplicate-log-call constraint, not the
  requirement to preserve numerical results. API Doxygen documentation remains in the header.

## Formulas And Units

- Question: what multiplier converts the composite's estimated average efficiency to its maximum estimate?
- Final interpretation: `maximum = average * deviation_factor`; efficiencies remain fractions.
- Numerical Q is flow expressed in US gpm. Retain
  `1 + (0.10805906 + (18.077243 * exp(-0.78231304 * log10(Q))) + 30.525232 * exp(-0.80684022 * log10(Q))) / 100`.
- Coefficients describe empirical mathematical roles, not independently established physical properties.
  The 100 divisor converts the deviation percentage into a fraction; 1 is the baseline multiplier.
- Worked example: Q=2000 US gpm gives factor `1.0360243794198285`, about a 3.6024% relative increase.
  A supplied average of 0.84 would give about 0.8703 maximum; this example is not an equipment guarantee.
- Finite positive flow gives a multiplier above 1, not an efficiency bounded by 1. There are no branch thresholds.
  Both signed zeros give positive infinity; negative flow/negative infinity/NaN give NaN; positive infinity gives
  `1.0010805906`. Invalid-domain arithmetic is retained, not endorsed as an engineering operating range.
- Provenance: unchanged source at the base commit. Original empirical references/calibration range are unverified;
  no SME formula decision is needed for this behavior-preserving migration.
- Teaching page: final result, flow/unit choice, empirical equation and coefficient/symbol tables, worked example,
  limits and provenance; no API migration narrative in `.dox`.

## Desktop Impact And Package Coordination

- No direct legacy/new factor usage found in Desktop application/process-flow sources or installed declarations;
  composite `PumpEfficiency` is the indirect consumer. Preserve existing wrapper units/percentages/ownership.
- Classification: breaking C++ API and additive WASM API; no behavior/default-data/packaging changes.
- No Desktop code/tests, wrapper additions, app models, reports, saved-data migrations, dependency pins or loading
  paths change in this child. All Desktop implementation and root/process-flow package adoption remain deferred
  to final epic integration under #9059. No package version bump or publication performed here.
- Beta/final package: pending publication evidence in the future PR; no version-only evidence commits.

## Validation

- Before source changes, archived all six legacy efficiency-chain headers/sources at
  `/private/tmp/optimal-deviation-factor-b3gx75zb`; `capture-metadata.json` records base SHA, compiler and command.
- Legacy harness compiled with Apple clang 21.0.0, arm64, `-O3 -DNDEBUG -std=gnu++20`.
  `legacy-results.txt` holds decimal/hex captures for 17 scalar and five composite cases.
- Scalar flows: 0.001, 1, 100, 1000, 2000, 10000, 100000, 1e-300, minimum normal, minimum subnormal,
  maximum finite, both signed zeros, -1, both infinities and NaN.
- Composite captures include ANSI/API, vertical turbine with viscous multistage duty, slurry,
  specified-optimal and positive-displacement styles. Preserve every raw value, including negative outputs.
- Native baseline configure/build passed; existing PumpResult coverage passed 129 assertions in 11 cases.
- Refactored C++ configure/build passed. Native captures are byte-for-byte identical for all 17 scalar and
  five composite cases, including hexadecimal values. A temporary differential harness compared 100,000
  deterministic random double inputs: zero bit/classification differences (NaN payloads not compared).
- Archived and refactored sources were also compiled with Emscripten at `-O3 -fexceptions -DNDEBUG -std=gnu++20`
  and exercised in Node's WASM runtime: all 17 scalar and five composite captures match byte-for-byte, and
  100,000 deterministic scalar comparisons have zero bit/classification differences. Commands/compiler metadata
  and result files are retained in the same temporary archive. All 12 archived source/header files were checked
  byte-for-byte against the epic base. No numerical preservation differences were observed in either runtime.
- Focused factor/PumpResult tests passed 159 assertions in 14 cases; full native suite passed 5,866 assertions
  in 351 cases. `npm run verify:types` passed. The initial WASM link hit restricted Emscripten-cache writes;
  the approved `npm run verify:wasm` rerun rebuilt/staged both assets, typechecked and passed all 290 browser tests.
  This includes three new scalar/consumer tests and the unchanged existing composite assertions.
- `npm run check:docs` and `git diff --check` passed. Package dry run contains 103 files, including both runtime
  assets, the entrypoint and new declaration; no legacy header is packaged.
- Explicit whitespace audit covered all 14 changed/new/deleted paths, including untracked additions.
- Doxygen generated the new page with all four formulas/symbol tables, worked example and provenance sections;
  generated HTML local links resolve and no module-specific diagnostics were emitted. Full generation exits zero
  but logs the existing missing-BibTeX failure and unrelated warnings. Do not call that a clean documentation build.
- Browser local-file navigation was rejected by URL policy. Generated markup was inspected statically;
  rendered MathJax/visual browser verification was not performed, and no browser workaround was attempted.
- Still required for this implementation: none. Desktop integration and package publication remain epic-level work.

Readability follow-up verification (2026-10-29): native rebuild and focused tests again passed 159 assertions
in 14 cases; the full native suite passed 5,866 assertions in 351 cases. Fresh `npm run verify:wasm` rebuilt/staged
the readability revision and passed all 290 browser tests. Native and WASM comparisons each preserved all
17 scalar/five composite captures exactly, with zero bit/classification differences in 100,000 additional
scalar comparisons per runtime. Follow-up outputs are archived as `readability-*-results.txt` alongside the
original captures. `git diff --check` passed. No public interfaces or algorithm teaching documentation changed.

## Persona Progress

- Refactor Planner: complete; scalar API, affected layers, compatibility, constants and legacy captures established.
- C++ Namespace Refactorer: complete; source/header, named constants, direct consumers and focused tests migrated.
- WebAssembly TypeScript Steward: complete; scalar binding, declarations, module exports and three typed browser
  tests added; fresh runtime verification passed.
- Algorithm Docs Author: complete; engineering question/result first, four formulas with symbol/unit tables,
  coefficient roles, worked example, percentage interpretation, bounds and honest provenance.
- Verification Reviewer: complete; integrated source/binding/declaration/test/doc consistency verified.
- Independent review-only readiness pass: complete; no actionable findings.

## Internal Review

- Intended base / reviewed base: `epic-pump-eff-refactor` at `892065db8442d2472d7cbba44cf003e16f54a179`.
- Reviewed head: isolated snapshot `718fb83ec1140a6bf9314c8b0d1cc2dab18e0e4a`, tree
  `142f325658600b9cfc5fb4bedaf46262c963218f`. The snapshot freezes the entire candidate without committing the
  working branch or staging its files. The later user-requested readability edit to the two implementation files
  is covered by a supplemental review of the uncommitted file contents, recorded below.
- Reviewer: independent `review_optimal_deviation_factor` agent, following `.github/skills/measur-code-review/`.
- Readiness: **ready with documented follow-up**. No actionable findings or unresolved P0-P2 findings.
- Independent checks: focused factor tests passed 30 assertions in three cases; TypeScript and Markdown links
  passed; all candidate paths matched the frozen snapshot; legacy source provenance and exact native/WASM
  captures verified. Full native/WASM execution evidence was reviewed rather than redundantly rerun.
- Fixes / affected checks rerun: no review fixes required; final handoff-only link/whitespace checks passed.
- Remaining non-blocking validation gaps: pre-existing BibTeX failure; browser-rendered MathJax/visual QA not
  performed because local-file navigation was blocked. No numerical preservation differences observed.
- User requested reviewed child PR delivery on 2026-10-29. Final package selection and Desktop mutations remain
  outside this child; post-push CI/publication evidence belongs in the linked PR.
- Supplemental readability review: independent `review_optimal_deviation_factor` agent found no actionable
  findings and rated the follow-up **ready**. Reviewed uncommitted SHA-256 values:
  - `src/motorDriven/pump/optimal_deviation_factor.cpp`:
    `92a34924f9500a073f45108ffaa48033557731d496c827f1026c7796066a4abc`.
  - `src/motorDriven/pumpFan/PumpEfficiency.cpp`:
    `f559ba7220ed84526d4f9280466762ca995e17b7e31aaf9af47aca4ce731ceee`.
  The prior snapshot review anchors the remaining files. Existing documentation limitations are unchanged;
  final Markdown-link/whitespace checks passed after recording the follow-up.

## Open Questions Or Blockers

- No implementation policy questions remain. Doxygen BibTeX and browser-rendering limitations are recorded above.
