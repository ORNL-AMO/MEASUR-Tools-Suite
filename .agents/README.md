# Agent Workflows And Personas

This directory defines repo-neutral personas for namespace refactors and algorithm documentation work. These personas are guidance for AI agents and automation tools; they are not tied to any single tool or runtime.

For agent-assisted PR preparation of any change, use the concise [PR workflow](../docs/development/pr-workflow.md), [fresh-review procedure](../docs/development/fresh-pr-review.md), and separate [review records](../docs/development/pr-review-record.md). Human-only PRs keep the general template and existing contributor rules.

Repo-scoped skills in [`skills/`](skills/) provide the task-level entry points:

- `refactor-and-document-calculation` coordinates the persona sequence below.
- `coordinate-suite-desktop-change` handles downstream contracts, linked GitHub work, and release sequencing.

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

The handoff is the shared state for the workflow. It should be short, concrete, and updated after each persona phase. Create one handoff per coordinated refactor, use a lowercase hyphenated filename, and include its lifecycle state and last-updated date.

Every handoff must include:

- Target module and related files across C++, WebAssembly, TypeScript, tests, and docs.
- Current public API and proposed namespace API.
- Compatibility decision: compatible by default, intentionally breaking only with explicit approval.
- For approved breaking changes, the old-to-new migration and removed legacy surfaces.
- Formula and unit notes, including uncertain or unresolved items.
- Validation commands run and remaining validation needed.
- Open questions or blockers.

Keep investigation history and long review matrices in linked GitHub issues or a clearly labeled appendix. When the work is finished, mark the handoff `completed` or `archived`, record unresolved validation accurately, and retain the file only when it provides durable migration or formula provenance.

Record post-push CI and exact package-publication evidence in the linked PR description or CI comments.
Link that evidence location from the handoff before pushing. Do not push follow-up commits whose only purpose
is to record a beta version or its CI result: each push can publish another beta and restart the evidence cycle.

## Pre-PR Internal Review Gate

Complete an internal review after implementation and validation but before opening a pull request:

1. Identify the intended PR base and committed candidate. Review the child branch against the feature branch it will
   merge into rather than assuming `develop`. Preserve unrelated work and use a clean checkout for the final candidate.
2. The context-aware development agent self-reviews with [the MEASUR code-review skill](../.github/skills/measur-code-review/SKILL.md).
   The verification persona can supply this stage if it covers the exact candidate and original requirements.
3. Start the [fresh independent stage](../docs/development/fresh-pr-review.md) with history inheritance explicitly disabled
   and the same model/effort. Pass only neutral requirements, approved contract facts, linked work, validation evidence,
   and the complete comparison; exclude handoff review history and self-review conclusions. For coordinated Desktop
   work, follow each repository's own review instructions.
4. Present findings and resolve or explicitly disposition them; no P0, P1, or P2 finding may remain unresolved when the
   PR opens. Rerun affected checks and both stages after changes, including a moved target.
5. Save complete reports and exact base/head/merge-base metadata in ignored local records, then append both stages to
   the authorized PR description. Keep durable implementation decisions in the handoff before the final candidate is
   committed; do not change a tracked handoff solely to stamp the commit being reviewed or its execution status.
6. Verify live target freshness, both records, readiness, and publication authorization before opening/updating the PR.

This gate improves PR readiness but does not approve the change. Required human review and repository branch
protection still apply after the PR opens.

## Completion Standard

The workflow is complete only when the verification reviewer confirms:

- The C++ API shape matches the namespace/module plan.
- Embind names and TypeScript declarations match the runtime surface.
- Classes, value objects, registered vectors, and enums follow `AGENTS.md` TypeScript rules.
- C++ and WASM tests cover changed public behavior.
- Algorithm documentation is top-down, formula-driven, and includes units and symbol tables.
- Any public compatibility change has migration notes.
- Any affected Desktop work, package version, and release sequencing are recorded or explicitly marked not applicable.
