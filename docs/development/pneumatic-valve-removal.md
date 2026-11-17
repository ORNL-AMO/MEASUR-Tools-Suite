# Pneumatic Valve Calculator Removal

- Last updated: 2026-11-17
- Status: implementation complete; release evidence is maintained in the pull request
- Branch / PR base: `codex/remove-unused-pneumatic-valve` / `develop`
- Desktop tracking: [issue #8490](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8490)
- Desktop cleanup: [PR #9105](https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/9105)
- Suite tracking: [original refactor issue #194](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/194)
- Original Suite refactor: [PR #341](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/341)
- Suite removal PR and CI/publication evidence:
  [branch pull request](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Acodex%2Fremove-unused-pneumatic-valve)

## Decision And Consumer Audit

Remove the unused pneumatic valve calculator. The user explicitly authorized removal
if neither Suite nor Desktop has another consumer and confirmed that a new Desktop
calculator is unwanted.

Repository searches covered the C++ namespace/header, old `PneumaticValve` class,
new runtime names, declaration types, and pneumatic valve text:

- Suite references were confined to this calculator's own implementation, binding,
  declarations, package exports, tests, and calculation documentation. No other
  calculation, assessment, example, or command-line code calls it.
- Desktop's working tree and `origin/develop` contain only commented-out wrappers
  in `src/app/tools-suite-api/standalone-suite-api.service.ts` and
  `src/app/calculator/standalone.service.ts`, commented-out models in
  `src/app/shared/models/standalone.ts`, and general assessment help text mentioning
  pneumatic valves. No active Angular or process-flow consumer was found.
  GitHub default-branch code search also returned only the commented-out wrappers
  and models. The installed Suite declarations expose the API but do not consume it.
  Inspected Desktop HEAD: `153b777d8a9b04f8d249f26a6138a4fc4e80712d`;
  `origin/develop` and the GitHub code-search snapshot:
  `7bc8e87f3e22c17c965d86f1148edd43a7266307`.
- Desktop PR #9105 removes those commented-out wrappers and models. Its head is
  `dff546f46176fdbda0bf199199d379af6aa00cdb`; a TypeScript token comparison verified
  that executable code is unchanged, and the application typecheck passed against
  the pinned Suite declarations, `1.2.7-rc.434.1`.
- [Desktop PR #5630](https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/5630)
  explicitly recorded that pneumatic valve was unused and left commented out.
- [Desktop PR #8491](https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8491)
  introduced a new calculator UI and active wrappers for issue #8490. It is closed
  and unmerged; those additions are absent from the inspected Desktop source.

## Removed API And Migration

This is an intentional breaking API removal with no replacement. Remove unused
imports/calls rather than migrating to another pneumatic valve API. The separate
pneumatic air requirement calculator remains available.

| Surface | Before | After | Binding kind / units | Ownership |
| --- | --- | --- | --- | --- |
| C++ `pneumatic_valve` | `calculateFlowRate(FlowRateInput)` and `calculateCv(CvInput)`, input/result structs, `kAirFlowFactor`, public header | Removed | Native functions; pressures psia, flow scfm, Cv dimensionless | Plain values |
| `calculatePneumaticValveFlowRate` | Pressure input to flow-rate result | Removed | `function` and `value_object`; psia to scfm | Plain objects; no cleanup |
| `calculatePneumaticValveCv` | Pressure/flow input to flow-coefficient result | Removed | `function` and `value_object`; psia/scfm to dimensionless Cv | Plain objects; no cleanup |
| TypeScript exports | Four input/result interfaces, both functions, `PneumaticValveModule`, and entrypoint/module references | Removed | Type declarations | No runtime ownership |

The matching native and WASM tests and calculator `.dox` page are removed with the
implementation. CMake discovers these files by glob; reconfiguration removes them
from both builds. No formulas in retained modules change.

## Downstream And Delivery

Desktop's commented-out code is removed separately in PR #9105. There is no active
Desktop consumer to migrate. Saved data, dependency pins, and web/Electron asset
paths are unaffected. Future Desktop work should not restore PR #8491's unwanted
calculator.

No manual package version bump is included. The ready Suite PR may publish a beta
through CI; exact package and CI evidence belongs in the linked PR and workflow
comments. No Desktop dependency update is required for this unused API removal.

## Validation

- `cmake -S . -B build-cpp` and `cmake --build build-cpp -j 4` passed.
- `./build-cpp/bin/cpp_tests` passed: 5,830 assertions in 346 test cases.
- `npm run verify:wasm`, with the Emscripten environment activated, rebuilt and
  staged `bin/client.js` and `bin/client.wasm`, passed TypeScript checking, and
  passed all 280 ChromeHeadless browser tests. The first build was blocked by
  compiler-cache permissions; the approved rerun completed successfully.
- A separate initialization check loaded the freshly built WASM and confirmed
  `PneumaticValve`, `calculatePneumaticValveFlowRate`, and
  `calculatePneumaticValveCv` are absent from the initialized module.
- `npm run check:docs` and `git diff --check` passed.
- Final searches found no remaining pneumatic valve references in Suite source,
  public headers, bindings, declarations, tests, or calculation documentation.
- These native/WASM results were obtained before branching from `develop`.
  The starting checkout differs from the PR base only in repository guidance,
  development documentation, and Doxygen CSS; all C++, binding, declaration,
  test, and build inputs are identical on the PR base.
- No Desktop runtime or Electron run was needed for this removal because no
  active consumer or loading path changed. Desktop's comment cleanup was
  separately typechecked as recorded above.

Exact self-review and independent-review execution records are maintained in the
pull request description rather than stamped into this implementation record.
