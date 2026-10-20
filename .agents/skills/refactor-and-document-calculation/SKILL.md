---
name: refactor-and-document-calculation
description: Refactor or split a MEASUR calculation module while keeping C++, tests, WebAssembly bindings, TypeScript declarations, and algorithm documentation synchronized. Use for namespace conversions, binding modernization, or calculation documentation that spans repository layers.
---

# Refactor And Document A Calculation

Preserve calculation behavior and public compatibility unless the user explicitly approves a behavior or breaking API change.

## Ground The Work

1. Read `AGENTS.md`, `ARCHITECTURE.md`, and the applicable style, documentation, TypeScript, and WASM-test guides.
2. Read [the persona workflow](../../README.md) and all five persona files it lists before executing a full cross-layer refactor.
3. Inspect the target across `include/`, `src/`, `bindings-wasm/`, `ts_def/`, `tests/cpp/`, `tests/wasm-mocha/`, legacy `tests/wasm/`, and `docs/dox-content/`.
4. Use the exact canonical example in `AGENTS.md` that matches the binding pattern. Do not infer a pattern from an entire domain directory.
5. Create or update one handoff from [the handoff template](../../templates/refactor-handoff.md). Record lifecycle, GitHub links, compatibility, runtime API contract, formulas, units, package coordination, and validation.

If the public WASM surface, behavior, default data, declarations, or packaging affects AMO-Tools-Desktop, also use `coordinate-suite-desktop-change` and link the Desktop issue.

## Perform The Persona Sequence

Follow the persona responsibilities in this order:

1. Refactor Planner: make the handoff decision-complete before implementation.
2. C++ Namespace Refactorer: update headers, source, Doxygen API comments, and focused C++ tests together.
3. WebAssembly TypeScript Steward: update the binding, declaration, module export, and typed WASM test together.
4. Algorithm Docs Author: document final results first, then supporting formulas, symbols, units, constants, provenance, and assumptions.
5. Verification Reviewer: compare the integrated diff with the handoff and record what actually passed.

Do not change formulas, constants, parameter order, defaults, sentinel handling, or expected results merely to make the refactor cleaner. When source, tests, and prose disagree, record the conflict and use explicit engineering intent or tested behavior; do not guess.

## Compatibility And Cleanup

- Preserve current C++ and runtime names by default.
- A breaking change requires explicit user approval recorded in the handoff.
- For an approved breaking refactor, remove superseded wrappers, headers, runtime constructors, declarations, and compatibility-only tests rather than retaining an unrequested parallel API.
- Record memory ownership for runtime classes, registered vectors, and nested runtime objects.

## Verification And Handoff

Run the narrowest relevant checks first, then the integrated checks required by `AGENTS.md`. For WASM-facing work, use `npm run verify:wasm` so browser tests use newly built artifacts.

Before finishing:

- Mark the handoff lifecycle accurately.
- Keep long investigation history in linked GitHub issues or an appendix.
- Report commands that passed, commands that failed, and commands that could not run.
- Do not describe stale WASM tests as validation of the changed source.
