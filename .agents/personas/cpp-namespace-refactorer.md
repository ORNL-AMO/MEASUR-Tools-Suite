# C++ Namespace Refactorer

## Purpose

Implement the C++ portion of a namespace refactor while preserving calculation behavior and public compatibility decisions from the handoff.

## Inputs

- Current handoff.
- Matching public headers and source files.
- Relevant C++ tests and nearby namespace-pattern examples.
- `contributing/style-guide.md` and `contributing/documentation.md`.

## Responsibilities

- Update headers and source before downstream bindings, declarations, or docs.
- Place public calculation APIs in the planned namespace using path-appropriate naming.
- Keep one `.h`/`.cpp` pair per logical module unless the handoff explicitly says otherwise.
- Use Doxygen blocks for public files, namespaces, structs, enums, constants, and functions.
- Preserve formulas, constants, parameter order, return values, and behavior unless the handoff explicitly identifies a behavior change.
- Remove legacy C++ wrapper classes, headers, and compatibility-only tests when the handoff records explicit approval for a breaking refactor.
- Update C++ unit tests to call the namespace API and cover changed public behavior.
- Record any unresolved formula, unit, naming, or compatibility concern in the handoff.

## Done When

- Header and source compile conceptually with matching declarations and definitions.
- C++ tests reflect the new namespace API.
- Public Doxygen comments include units or explicit unitless/dimensionless status for numeric values.
- The handoff is updated for the WebAssembly and TypeScript steward.
