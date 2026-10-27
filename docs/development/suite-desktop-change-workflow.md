# Suite To Desktop Change Workflow

Use this workflow when a MEASUR-Tools-Suite change can affect AMO-Tools-Desktop. The Desktop issue is the authoritative product and coordination record. The Suite handoff records implementation evidence and links back to that issue; it should not duplicate a long issue history.

## Required Links

Record durable GitHub URLs for every artifact that exists:

- Desktop issue: product intent, acceptance criteria, SME decisions, and delivery status.
- Suite issue: implementation scope when separate tracking is useful.
- Suite pull request: calculation, binding, declaration, test, and documentation changes.
- Desktop pull request: wrapper migration, dependency update, and application verification.

Every Suite PR with downstream impact must link the Desktop issue. Every Desktop PR consuming an unreleased or newly released Suite package must link the Suite PR and record the exact package version tested.

Do not put customer data, sensitive assessment inputs, credentials, or private operational details in public issues or pull requests.

## Classify The Change

Choose every applicable classification:

| Classification | Meaning | Required downstream action |
| --- | --- | --- |
| Additive API | New runtime name or optional capability without removing an existing surface | Confirm declarations, wrapper adoption, and package compatibility. |
| Breaking API | Removed or changed runtime name, signature, enum, object shape, or cleanup contract | Record explicit approval and an old-to-new migration. |
| Behavioral | Existing inputs can produce different outputs | Record golden before/after results, engineering rationale, and affected UI/reporting behavior. |
| Default data | Suite-provided catalog or material data changes | Review Desktop initialization, IndexedDB/reset behavior, and existing-user impact. |
| Declaration-only | TypeScript declarations change without an intended runtime change | Confirm the declaration now matches the binding and migrate narrow Desktop workarounds. |
| Packaging | WASM filenames, locations, exports, or npm contents change | Verify web and Electron asset copying and `locateFile` behavior. |

## Runtime API Contract

Use this table in the handoff, issue, or PR description. Add one row per changed public surface.

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Example runtime name | Constructor/function/object shape | Constructor/function/object shape | `class_`, `value_object`, `register_vector`, `enum_`, or `function` | Numeric units, ranges, defaults, sentinel values | Who creates it and which objects require `delete()` | Additive, preserved, deprecated, or breaking |

Treat the binding as the runtime source of truth and the declaration as its public TypeScript description. Document nested runtime objects separately when a plain value object contains a class or registered vector that still requires cleanup.

## Desktop Consumer Review

Inspect the installed declarations and search AMO-Tools-Desktop for affected runtime names. Review every applicable consumer:

- `src/app/tools-suite-api/` wrapper and helper services.
- Enum mappings, percentage/fraction conversions, units, nullable values, and vector construction.
- App-facing models, result displays, reports, exports, and saved assessment data.
- Suite-backed default database initialization and reset behavior.
- `process-flow-diagram-component/` dependency and direct consumers.
- Root and process-flow `measur-tools-suite` dependency pins.
- `angular.json` WASM assets, `locateFile`, web builds, and Electron path handling.

When the Desktop repository or linked issue cannot be inspected, state that downstream impact is unverified. Do not infer that no consumer exists.

## Release And Verification Order

1. Implement and verify the Suite change across C++, bindings, declarations, tests, and documentation.
2. Open or ready the Suite PR. The current GitHub workflow publishes a beta package for ready, same-repository PRs targeting `develop`.
3. Record the exact beta version in the Desktop issue and update both Desktop dependency pins when the process-flow package consumes the Suite.
4. Update Desktop wrappers and other consumers, then run the relevant typecheck, application tests, regression tests, and web/Electron checks.
5. Record Desktop validation results and remaining SME or release decisions in the Desktop issue.
6. Merge and publish the appropriate Suite RC or final package.
7. Replace the beta pin with the approved final version in Desktop and repeat the affected verification.

Do not describe a stale `bin/client.js` or `bin/client.wasm` test run as WASM verification. In the Suite repository, use `npm run verify:wasm` to rebuild, stage, typecheck, and test the current source.

## Completion

The coordinated change is complete when:

- Runtime bindings, declarations, tests, and documentation agree.
- Compatibility and behavioral decisions are explicit.
- The Desktop issue contains acceptance and SME decisions.
- Desktop consumers and both dependency pins are updated or marked not applicable.
- The exact beta/final package versions and validation results are recorded.
- Web and Electron WASM loading are verified when packaging or asset resolution changed.
- All linked issues and PRs point to one another.
