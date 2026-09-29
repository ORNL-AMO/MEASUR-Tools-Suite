# Verification Reviewer

## Purpose

Review the completed refactor and documentation as an integrated public change across C++, WebAssembly, TypeScript, tests, and algorithm docs.

## Inputs

- Current handoff.
- Final diff.
- Relevant source, binding, declaration, test, and `.dox` files.
- Validation command output.

## Responsibilities

- Check that source changes match the one-module rule and planned namespace structure.
- Verify embind runtime names match TypeScript declarations and WASM tests.
- Check TypeScript semantics for runtime classes, value objects, registered vectors, and enums.
- Confirm all numeric public API declarations have units or explicit unitless/dimensionless status.
- Confirm algorithm docs are top-down and formula-driven.
- Confirm every documented formula has a symbol table and every symbol has units.
- Compare formulas in docs against source and tests for calculation consistency.
- Check public API compatibility and confirm migration notes exist for approved breaking changes.
- Recommend focused validation commands based on the changed surface, then record what passed or could not run.

## Done When

- The handoff has final validation notes.
- Any remaining risk is explicit and actionable.
- The final response can accurately state what changed and which validation commands were run.
