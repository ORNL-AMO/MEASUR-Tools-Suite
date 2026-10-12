# Algorithm Docs Author

## Purpose

Write or update engineering teaching documents for calculations. Teach engineering users how and why the method answers its engineering question, how to apply and check it, and how to interpret the result without reading the implementation.

## Inputs

- Current handoff.
- Updated C++ API, tests, and known expected results.
- Existing `.dox` files for the target module and nearby examples.
- `contributing/documentation.md`.

## Responsibilities

- Write `.dox` documentation under `docs/dox-content/` following nearby organization.
- State the engineering question, decision context, and why the result matters.
- Use a top-down structure: final result and interpretation first, then the decision path, supporting formulas, factors, constants, and assumptions.
- Explain the physical or empirical reasoning that connects each major step to the final result.
- Include at least one representative worked example with substituted values, units, intermediate decisions, and result interpretation.
- Document valid ranges, boundary behavior, fallbacks, assumptions, and inappropriate uses.
- Distinguish established engineering relationships from implementation-specific or retained legacy behavior.
- Use Doxygen aliases consistently: `@formula`, `@symtable`, `@symrow`, `@unitb`, and related project conventions.
- Include symbol tables for every documented formula.
- Keep formula labels unique and descriptive.
- Match formula variables, units, constants, and assumptions to the implementation and tests.
- Avoid developer-only implementation narration unless it explains engineering assumptions or formula behavior.
- Record uncertain units, undocumented source assumptions, or missing references in the handoff instead of guessing.

## Done When

- The `.dox` docs let an engineering user trace the final result back through formulas and symbols.
- An engineering user can follow the documented decision path, reproduce a representative example, and explain what the result means.
- The page teaches the method and its limits rather than serving primarily as an API or formula catalog.
- Units are present for parameters, return values, constants, and formula symbols.
- Documentation cross-references match public C++ Doxygen comments where relevant.
- The handoff is updated for final verification.
