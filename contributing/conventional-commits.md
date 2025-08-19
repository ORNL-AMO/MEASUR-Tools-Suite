# Conventional Commits

This project follows the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification for commit messages to ensure clarity, consistency, and automation in version control. This helps in generating changelogs, automating releases, and improving collaboration among contributors.


## Commit Format

Each commit message should follow this format:

```
<type>(<optional scopes>): <description>

<optional body>

<optional footer>
```


## Commit Types

Commit types indicate the nature of the changes made in the commit. They help categorize changes and provide context for reviewers and automated tools. The following types are used:

- **`build`**: Changes that affect the build system or external dependencies.
- **`chore`**: Other changes that don't modify src or tests (e.g., config updates).
- **`ci`**: Changes to our CI configuration files and scripts.
- **`docs`**: Documentation only changes.
- **`feat`**: A new feature.
- **`fix`**: A bug fix.
- **`perf`**: A code change that improves performance.
- **`refactor`**: A code change that neither fixes a bug nor adds a feature.
- **`revert`**: Reverts a previous commit.
- **`style`**: Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc).
- **`test`**: Adding missing tests or correcting existing tests.
- **`wip`**: Work in progress.


## Commit Scopes

Scopes indicate the specific module, component, or area affected by the commit. They help in understanding the reach of changes within the codebase. The following scopes are used:

- **`clang-format`**
- **`cli`**
- **`cmake`**
- **`compressedAir`**
- **`databases`**
- **`docs`**
- **`doxygen`**
- **`git`**
- **`motorDriven`**
- **`other`**
- **`processCooling`**
- **`processHeat`**
- **`readme`**
- **`sqlite`**
- **`steamModeler`**
- **`tests`**
- **`thirdParty`**
- **`treasureHunt`**
- **`util`**
- **`wasteWater`**
- **`vscode`**

When a commit affects multiple areas, you can specify multiple scopes separated by a comma and a space:

```
feat(cli, docs): add new command to generate reports
```


## Breaking Changes

If a commit introduces breaking changes, it must be indicated in the `type/scope` prefix of a commit, or as an entry in the footer.

If included as a footer, a breaking change **MUST** consist of the uppercase text **`BREAKING CHANGE`**, followed by a colon, space, and description:

```
feat: allow provided config object to extend other configs

BREAKING CHANGE: `extends` key in config file is now used for extending other config files
```

If included in the `type/scope` prefix, breaking changes **MUST** be indicated by a **`!`** immediately before the **`:`**. If **`!`** is used, **`BREAKING CHANGE:`** **MAY** be omitted from the footer section, and the commit description **SHALL** be used to describe the breaking change:

```
feat!: send an email to the customer when a product is shipped
```



<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
