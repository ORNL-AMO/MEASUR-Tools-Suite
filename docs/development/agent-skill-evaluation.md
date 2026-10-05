# Agent Skill Evaluation Cases

Use these cases after changing a skill name, description, trigger boundary, or major workflow. Record observed activation and output problems in the related pull request rather than turning this file into a permanent run log.

| Skill | Case | Example request | Expected behavior |
| --- | --- | --- | --- |
| `refactor-and-document-calculation` | Direct | Refactor the receiver calculator to the namespace pattern and document its equations. | Activates and uses the persona/handoff workflow. |
| `refactor-and-document-calculation` | Indirect | Split this monolithic calculation so each binding and declaration has one logical module. | Activates after identifying cross-layer refactor scope. |
| `refactor-and-document-calculation` | Incomplete | Modernize this calculator. | Inspects the target and asks only for unresolved product or compatibility decisions. |
| `refactor-and-document-calculation` | Negative | Explain what this existing formula computes. | Does not activate a refactor workflow for an explanation-only request. |
| `coordinate-suite-desktop-change` | Direct | Coordinate this breaking WASM rename with the linked Desktop issue. | Activates and produces the runtime contract, consumer inventory, and release sequence. |
| `coordinate-suite-desktop-change` | Indirect | This output field changed units; find what Desktop must update. | Activates because calculation semantics affect the downstream consumer. |
| `coordinate-suite-desktop-change` | Incomplete | Prepare the Desktop migration, but no issue is linked. | Inspects available repositories and reports the missing durable coordination link. |
| `coordinate-suite-desktop-change` | Negative | Refactor a private C++ helper with no public or behavioral effect. | Does not activate downstream coordination. |
| `measur-code-review` | Direct | Review this pull request for correctness and Desktop impact. | Activates in review-only mode and reports actionable findings. |
| `measur-code-review` | Indirect | Check whether this binding refactor is safe to merge. | Activates and traces the cross-layer runtime contract. |
| `measur-code-review` | Incomplete | Review these changes without a linked issue. | Reviews the diff and reports missing intent/downstream context as an uncertainty, not a defect. |
| `measur-code-review` | Negative | Implement the approved binding refactor. | Does not substitute review-only behavior for an implementation request. |

For Copilot Code Review, also confirm the review-session attribution identifies the skill or relevant GitHub MCP context. Test re-review behavior after a new push when the repository or user rules enable **Review new pushes**.
