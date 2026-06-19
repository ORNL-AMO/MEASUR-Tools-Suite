# Claude Project Guidance

Follow the canonical repository instructions in [../AGENTS.md](../AGENTS.md). Do not duplicate long-form policy here; update `AGENTS.md` when project-wide agent guidance changes.

## Quick Orientation

- Read [../ARCHITECTURE.md](../ARCHITECTURE.md) before broad edits.
- Read [../BUILD.md](../BUILD.md) before changing build, package, WASM, or test workflows.
- Follow [../contributing/style-guide.md](../contributing/style-guide.md) and [../contributing/documentation.md](../contributing/documentation.md).
- For TypeScript WASM tests, follow [../tests/wasm-mocha/README.md](../tests/wasm-mocha/README.md).

## Claude Workflow Notes

- Make a short plan for multi-file or cross-layer changes.
- Inspect related C++ source, WASM bindings, `ts_def` declarations, and tests before editing.
- Keep the one-module rule from `AGENTS.md`: source, binding, declaration, tests, and docs should move together.
- Report exactly which validation commands were run and which were not.
