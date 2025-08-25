# Formatting

This project uses [clang-format](https://clang.llvm.org/docs/ClangFormat.html) to ensure a consistent code style across all C++ files.


## Configuration

The formatting style is defined in the `.clang-format` file at the root of the repository. This file specifies rules for indentation, spacing, brace placement, include ordering, and more. The style is based on Google's C++ style guide with some customizations to fit the project's needs. To modify the formatting style, follow these steps:

1. **Open** the `.clang-format` file in the root directory.
2. **Experiment** with different settings using the [Clang-Format Configurator tool](https://clang-format-configurator.site/) or by editing the file directly.
3. **Apply changes** by copying your updated configuration into the `.clang-format` file.
4. **Reformat all code** to apply the new style. Use the following command to format every C++ source and header file in the project:
   ```bash
   find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i --style=file
   ```
5. **Commit and review:** Commit only the style changes and immediately open a pull request. This keeps formatting changes separate from functional code changes, making reviews easier and reducing merge conflicts.


## How to Format Code

To format your code using clang-format, run the following command from the root directory of the project:

```bash
clang-format -i --style=file <file1> <file2> ...
```

- Replace `<file1> <file2> ...` with the files you want to format (e.g., `src/main.cpp include/util.h`).
- The `-i` flag edits files in-place.
- The `--style=file` flag tells clang-format to use the `.clang-format` configuration in the project root.

To format **all** C++ source and header files in the project, you can use:
```bash
find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i --style=file
```

You can also configure your editor (such as VS Code, CLion, or Vim) to automatically format code on save using clang-format. Refer to your editor’s documentation or extensions/plugins for setup instructions.


## Best Practices

- **Format before committing:** Always run clang-format on your changes before submitting a pull request.
- **Editor integration:** Enable auto-format on save to avoid manual formatting.
- **Consistency:** Do not manually adjust formatting—let clang-format handle it.

If you have questions about the formatting rules or need help configuring your editor, ask in the project discussions or open an issue.




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
