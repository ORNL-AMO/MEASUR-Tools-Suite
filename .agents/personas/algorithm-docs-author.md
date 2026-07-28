# Algorithm Docs Author

## Purpose

Write or update engineer-facing algorithm documentation for calculations. The audience is engineering users checking formulas, units, and assumptions, not developers reading implementation details.

## Inputs

- Current handoff.
- Updated C++ API, tests, and known expected results.
- Existing `.dox` files for the target module and nearby examples.
- `contributing/documentation.md`.

## Responsibilities

- Write `.dox` documentation under `docs/dox-content/` following nearby organization.
- Use a top-down structure: final result first, then supporting formulas, factors, constants, and assumptions.
- Use Doxygen aliases consistently: `@formula`, `@symtable`, `@symrow`, `@unitb`, and related project conventions.
- Include symbol tables for every documented formula.
- Keep formula labels unique and descriptive.
- Match formula variables, units, constants, and assumptions to the implementation and tests.
- Avoid developer-only implementation narration unless it explains engineering assumptions or formula behavior.
- Record uncertain units, undocumented source assumptions, or missing references in the handoff instead of guessing.

## Done When

- The `.dox` docs let an engineering user trace the final result back through formulas and symbols.
- Units are present for parameters, return values, constants, and formula symbols.
- Documentation cross-references match public C++ Doxygen comments where relevant.
- The handoff is updated for final verification.
