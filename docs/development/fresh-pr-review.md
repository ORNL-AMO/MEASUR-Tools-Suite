# Fresh Independent PR Review

This is the second stage of the [agent-assisted PR workflow](pr-workflow.md), after context-aware self-review. It also supports an explicitly requested standalone fresh review of an existing PR. Use the existing [MEASUR review skill](../../.github/skills/measur-code-review/SKILL.md) as the domain rubric.

## 1. Pin The Candidate

Resolve the intended base and fetch its remote ref. For an existing PR, capture its current configured base/head commits. Use a clean checkout containing only the intended committed candidate; do not stash or commit unrelated work automatically. Record repository/checkout, branch, target ref/commit, HEAD, and merge base. Review the complete merge-base-to-HEAD comparison GitHub will display.

Agent commands, substituting the resolved `<remote>/<base>` (for example `origin/develop`, `upstream/develop`, or the intended feature branch):

```bash
git status --porcelain --untracked-files=all --ignore-submodules=none
git rev-parse --abbrev-ref HEAD
git rev-parse --verify <remote>/<base>
git rev-parse --verify HEAD
git merge-base <remote>/<base> HEAD
git diff <remote>/<base>...HEAD
```

## 2. Start Without History

With the current collaboration tool, use `spawn_agent` with `fork_turns: "none"`; omitting it inherits history and does not satisfy this workflow. Leave model/effort overrides unset to inherit the development agent's settings with this tool. For another interface, use its documented no-history equivalent and verify the same model/effort. Asking the development agent to forget its reasoning is insufficient. If the capability is unavailable, report the readiness gap instead of falling back silently.

Pass only pinned comparison facts, neutral requirements, approved compatibility/behavior decisions, applicable runtime contract and linked work, factual validation evidence, and instructions to read repository guidance and the review skill. Extract these facts from a module handoff rather than passing a full handoff containing prior findings, verification conclusions, or development history. Do not supply self-review reports, reasoning summaries, suspected bugs, proposed fixes, or previous review conclusions. Treat author-reported checks as unverified until independently run.

Repository/global instructions still apply. No-history delegation does not independently disable host memory; disable per-agent memory if supported and do not retrieve saved memories or other chats. Subagents inherit execution permissions; read-only review is a task constraint, not a separate filesystem sandbox.

## 3. Review And Retain Evidence

The already-delegated reviewer performs the review skill directly; it must not delegate recursively, edit implementation, publish GitHub actions, or read other chats, session logs, memories, or review reports. Trace affected C++, bindings, declarations, ownership, tests, formulas/units, documentation, and Desktop consumers when relevant. Run focused checks needed to substantiate findings; do not repeat unrelated builds/tests by habit.

Keep the candidate unchanged while review runs. Wait for a complete report with prioritized findings, exact comparison, independently performed checks, gaps, and the skill's readiness result. Save complete self-review and fresh-review reports as `.txt`, plus comparison metadata/identifiers/timestamps, under ignored `tmp/pr-reviews/<head>/`. Plain-text reports avoid being scanned as repository Markdown by `npm run check:docs`. Failed/interrupted reviews or missing reports leave the gate incomplete.

Keep mutable execution evidence and exact reviewed-head stamps in local reports and the PR description, not in tracked handoff updates that would change the commit being reviewed. Put durable implementation decisions and fixes into the handoff before the final candidate is committed. Preserve the complete findings when presenting them; explicitly report when none remain.

## 4. Evaluate And Verify Freshness

Resolve or explicitly disposition findings under the existing readiness rules; no unresolved P0–P2 finding may remain when opening the PR. Apply only authorized fixes, rerun affected validation, commit, and repeat both stages for PR preparation. A standalone fresh review of an existing PR need not invent an author-context stage.

Before publication, fetch the target again and verify repository/checkout, branch, target commit, head, merge base, and clean state still match both records. Any change invalidates the review, even when a moved target retains the same merge base. For existing PRs, also verify live GitHub base/head commits. Refresh reviews before publishing changed comparisons.

Agents compose the general [PR template](../../.github/pull_request_template.md) with the separate [agent review records](pr-review-record.md). Human-only PRs do not need the agent sections. Review execution is not merge approval, comment-posting permission, or a GitHub-required status check.
