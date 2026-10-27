# Copilot Instructions

Use [../AGENTS.md](../AGENTS.md) as the source of truth for repository-wide agent behavior.

## Repository Rules

- Follow [../ARCHITECTURE.md](../ARCHITECTURE.md) for module boundaries and repository layout.
- Follow [../contributing/style-guide.md](../contributing/style-guide.md) for C++ implementation style.
- Follow [../contributing/documentation.md](../contributing/documentation.md) for Doxygen and `.dox` documentation.
- For persona-driven namespace refactors and algorithm docs, follow [../.agents/README.md](../.agents/README.md).
- Keep C++ source, WebAssembly bindings, TypeScript declarations, and tests synchronized.
- Use the exact canonical example matrix in `AGENTS.md`; do not infer a pattern from an entire domain.

## Pull Request Review

- When reviewing a pull request, use the `measur-code-review` skill in `.github/skills/measur-code-review/`.
- Use linked Suite and Desktop issues or pull requests through available GitHub MCP context.
- AI review is advisory and does not replace required human approval.

## Common Review Focus

- Public API compatibility and old-to-new migration notes.
- Correct embind semantics in `ts_def/`: `class_` versus `value_object` versus `register_vector`.
- One binding file and one WASM test file per logical module.
- Tests that exercise changed public behavior instead of only compile-time shape.
