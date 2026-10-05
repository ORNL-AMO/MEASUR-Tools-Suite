# Copilot Review Evaluation

Use this lightweight log to evaluate the first ten reviews after changing the repository review skill or instructions. Do not copy review comments or issue content that contains sensitive data.

## Repository Settings Checklist

These GitHub settings are not stored in the repository. An administrator should verify them after merging the review skill:

- Copilot Code Review uses repository custom instructions.
- Copilot Code Review may use configured MCP tools.
- Automatic Copilot review is enabled for the intended branches or users.
- **Review new pushes** is enabled so fixes receive a fresh review.
- Human approval requirements remain enabled; Copilot review is advisory.

## Review Rubric

For each review, record:

- Whether Copilot attributed a comment to the `measur-code-review` skill or GitHub MCP context.
- Valid, actionable findings accepted by the author.
- False positives or findings about code not introduced by the PR.
- Duplicate or already-resolved comments.
- Missed cross-layer changes found later by a human reviewer.
- Whether severity matched the actual user or compatibility impact.
- Whether the linked Desktop issue and downstream impact were used correctly.

## Evaluation Log

| Review | PR | Skill/MCP attributed | Valid findings | False positives | Duplicates | Human-found misses | Severity accurate | Desktop context used | Follow-up |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1 |  |  |  |  |  |  |  |  |  |
| 2 |  |  |  |  |  |  |  |  |  |
| 3 |  |  |  |  |  |  |  |  |  |
| 4 |  |  |  |  |  |  |  |  |  |
| 5 |  |  |  |  |  |  |  |  |  |
| 6 |  |  |  |  |  |  |  |  |  |
| 7 |  |  |  |  |  |  |  |  |  |
| 8 |  |  |  |  |  |  |  |  |  |
| 9 |  |  |  |  |  |  |  |  |  |
| 10 |  |  |  |  |  |  |  |  |  |

## Iteration Rule

Change the review instructions only for a recurring, demonstrated failure. Prefer one narrow instruction or example over accumulating broad rules. Remove instructions that consistently create noise or duplicate automated checks.
