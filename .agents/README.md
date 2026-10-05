# Agent Personas

This directory defines repo-neutral personas for namespace refactors and algorithm documentation work. These personas are guidance for AI agents and automation tools; they are not tied to any single tool or runtime.

Use this workflow when a task asks to refactor a calculation module into a namespace pattern, split a module, or write/update algorithm documentation alongside source, WebAssembly, TypeScript, or test changes.

## Required Sequence

Work through the personas in this order:

1. [`refactor-planner`](personas/refactor-planner.md)
2. [`cpp-namespace-refactorer`](personas/cpp-namespace-refactorer.md)
3. [`wasm-ts-steward`](personas/wasm-ts-steward.md)
4. [`algorithm-docs-author`](personas/algorithm-docs-author.md)
5. [`verification-reviewer`](personas/verification-reviewer.md)

Each persona must read the current handoff, perform its phase, and update the handoff before the next persona starts. Use [`templates/refactor-handoff.md`](templates/refactor-handoff.md) for the handoff.

## Defaults

- Preserve public API compatibility unless the user explicitly approves a breaking change.
- If the user explicitly approves a breaking namespace/module refactor, remove obsolete compatibility wrappers and legacy runtime surfaces instead of keeping old support code in parallel.
- Keep source, bindings, TypeScript declarations, tests, and documentation in sync.
- Prefer established module patterns, especially the `processHeat/` namespace examples.
- Treat `.dox` files as algorithm documentation for engineering users who need to check formulas, units, and assumptions.
- Do not guess units or formula meaning. Inspect source, tests, docs, and downstream usage first; if still unclear, record the uncertainty in the handoff.

## Handoff Rules

The handoff is the shared state for the workflow. It should be short, concrete, and updated after each persona phase.

Every handoff must include:

- Target module and related files across C++, WebAssembly, TypeScript, tests, and docs.
- Current public API and proposed namespace API.
- Compatibility decision: compatible by default, intentionally breaking only with explicit approval.
- For approved breaking changes, the old-to-new migration and removed legacy surfaces.
- Formula and unit notes, including uncertain or unresolved items.
- Validation commands run and remaining validation needed.
- Open questions or blockers.

## Completion Standard

The workflow is complete only when the verification reviewer confirms:

- The C++ API shape matches the namespace/module plan.
- Embind names and TypeScript declarations match the runtime surface.
- Classes, value objects, registered vectors, and enums follow `AGENTS.md` TypeScript rules.
- C++ and WASM tests cover changed public behavior.
- Algorithm documentation is top-down, formula-driven, and includes units and symbol tables.
- Any public compatibility change has migration notes.
