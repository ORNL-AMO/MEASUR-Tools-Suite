# Pull Request

<!-- Complete applicable sections and mark others Not applicable.
     Agent-assisted PRs append their separate review records; human-only PRs do not need them. -->

## Purpose

Describe the requested outcome and the calculation or module affected.

## Linked Work

- Suite issue:
- Desktop issue:
- Desktop pull request:

## Change Classification

- [ ] Additive API
- [ ] Breaking API
- [ ] Calculation behavior
- [ ] Default data
- [ ] Declaration-only
- [ ] Packaging or WASM loading
- [ ] Internal-only change
- [ ] Documentation-only

Compatibility decision and approval for any breaking or behavioral change:

## Runtime API Contract

Complete this table for each changed public WASM surface, or write `Not applicable`.

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
|  |  |  |  |  |  |  |

## Desktop Impact

- Affected wrappers, models, reports, saved data, default data, or process-flow consumers:
- Beta package version tested:
- Final package version expected:
- Root/process-flow dependency pins aligned: Yes / No / Not applicable
- Web/Electron WASM loading affected: Yes / No

## Validation

- [ ] Focused C++ tests
- [ ] Native build and `cpp_tests`
- [ ] TypeScript `tsc --noEmit`
- [ ] Fresh WASM build staged into `bin/`
- [ ] WASM browser tests
- [ ] Doxygen generation and documentation links
- [ ] Desktop typecheck/tests/regression coverage
- [ ] Web and Electron loading when applicable
- [ ] `git diff --check`

List exact commands, results, and environmental limits:

## Review Notes

Call out areas for reviewers to inspect and any remaining questions or validation gaps.

## Engineering Or SME Review

Record unresolved formula, units, applicability, terminology, or release decisions.

## Data Safety

- [ ] No customer data, sensitive assessment inputs, credentials, or private operational details are included.
