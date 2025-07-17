# How to Contribute <!-- omit in toc -->

This guide provides clear standards and best practices for contributing to this project. It covers coding style, documentation, formatting, and workflow expectations to help maintain high code quality, ensure long-term maintainability, and foster smooth collaboration among all contributors.

[<h2> Style Guide </h2>](#style-guide)

Follow this guide to make sure your contributions align with the project's coding standards. This will help ensure that your code is readable, maintainable, and consistent with the rest of the codebase.

[<h2> Formatting </h2>](#formatting)

Follow the formatting standards using clang-format to ensure a consistent code style across all C++ files. This helps maintain readability and reduces merge conflicts.

[<h2> Documentation </h2>](#documentation)

Follow these guidelines to document your code effectively using Doxygen. Proper documentation is crucial for understanding the codebase and facilitating collaboration.

[<h2> Conventional Commits </h2>](#conventional-commits)

Use Conventional Commits to structure your commit messages. This helps maintain a clear project history and makes it easier to understand the purpose of each change.

<!-- START mdsplit-ignore -->
<a id="index"></a>
<details open>
<summary><Strong>Index</Strong></summary>

- [Style Guide](#style-guide)
  - [Header Files](#header-files)
    - [Include Guards](#include-guards)
    - [Include What You Use](#include-what-you-use)
    - [Include Order](#include-order)
    - [Function Definitions in Headers](#function-definitions-in-headers)
  - [Scoping](#scoping)
    - [Namespaces](#namespaces)
    - [Local Variables](#local-variables)
  - [Classes](#classes)
    - [Access Control](#access-control)
    - [Declaration Order](#declaration-order)
  - [Structs](#structs)
  - [Looping and Branching Statements](#looping-and-branching-statements)
  - [Preincrement and Predecrement](#preincrement-and-predecrement)
  - [Use of `const`](#use-of-const)
  - [Naming](#naming)
    - [Files](#files)
    - [Namespaces](#namespaces-1)
    - [Classes and Structs](#classes-and-structs)
    - [Functions and Methods](#functions-and-methods)
    - [Variables](#variables)
    - [Member Variables](#member-variables)
    - [Constants and Enums](#constants-and-enums)
    - [Aliases](#aliases)
    - [Templates](#templates)
    - [Macros](#macros)
  - [Comments](#comments)
    - [When to comment](#when-to-comment)
    - [Comment Style](#comment-style)
- [Formatting](#formatting)
  - [Configuration](#configuration)
  - [How to Format Code](#how-to-format-code)
  - [Best Practices](#best-practices)
- [Documentation](#documentation)
  - [Common Doxygen Tags](#common-doxygen-tags)
  - [How to Generate Doxygen Documentation](#how-to-generate-doxygen-documentation)
  - [Documenting Code](#documenting-code)
    - [Files](#files-1)
    - [Namespaces](#namespaces-2)
    - [Classes \& Structs](#classes--structs)
    - [Functions \& Methods](#functions--methods)
    - [Member Variables](#member-variables-1)
    - [Constants](#constants)
    - [Enums](#enums)
    - [Formulas](#formulas)
    - [Units](#units)
    - [Modules](#modules)
- [Conventional Commits](#conventional-commits)
  - [Commit Format](#commit-format)
  - [Commit Types](#commit-types)
  - [Commit Scopes](#commit-scopes)
  - [Breaking Changes](#breaking-changes)

</details>
<!-- END mdsplit-ignore -->

# Style Guide

Use this guide to ensure your contributions align with the project's coding standards. It is loosely based on the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), with some modifications to suit this project's needs.

<!-- START mdsplit-ignore -->
<a id="style-guide-index"></a>
<details open>
<summary><Strong>Index</Strong></summary>

- [Style Guide](#style-guide)
  - [Header Files](#header-files)
    - [Include Guards](#include-guards)
    - [Include What You Use](#include-what-you-use)
    - [Include Order](#include-order)
    - [Function Definitions in Headers](#function-definitions-in-headers)
  - [Scoping](#scoping)
    - [Namespaces](#namespaces)
    - [Local Variables](#local-variables)
  - [Classes](#classes)
    - [Access Control](#access-control)
    - [Declaration Order](#declaration-order)
  - [Structs](#structs)
  - [Looping and Branching Statements](#looping-and-branching-statements)
  - [Preincrement and Predecrement](#preincrement-and-predecrement)
  - [Use of `const`](#use-of-const)
  - [Naming](#naming)
    - [Files](#files)
    - [Namespaces](#namespaces-1)
    - [Classes and Structs](#classes-and-structs)
    - [Functions and Methods](#functions-and-methods)
    - [Variables](#variables)
    - [Member Variables](#member-variables)
    - [Constants and Enums](#constants-and-enums)
    - [Aliases](#aliases)
    - [Templates](#templates)
    - [Macros](#macros)
  - [Comments](#comments)
    - [When to comment](#when-to-comment)
    - [Comment Style](#comment-style)

</details>
<!-- END mdsplit-ignore -->

## Header Files

Every C++ source file (`.cpp`) should have a corresponding header file (`.h`). The header file contains declarations, while the source file contains definitions and implementations.

> [!NOTE]
> A common exception is unit tests, which may not require a separate header file. Small `.cpp` files containing just a `main()` function may also not have a corresponding header.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Include Guards

Every header file must have a `#pragma once` directive to prevent multiple inclusion of header files:

```cpp
#pragma once

// other includes or declarations

// file content
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Include What You Use

Always include the header file that directly defines any symbol you use. Do not rely on headers being included indirectly through other files. This ensures that removing unnecessary includes will not break your code.

Avoid using forward declarations where possible. Instead, include the headers you need:

- Good:

  ```cpp
  #include "a.h" // Include the header that defines A

  class B {
  public:
      void interactWithA(A* a);
  }
  ```

- Bad:

  ```cpp
  class A; // Forward declaration without full definition
  
  class B {
  public:
      void interactWithA(A* a);
  }
  ```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Include Order

Use double quotes (`"header.h"`) for project and third-party headers, and angle brackets (`<vector>`) for standard library headers.

Include project headers relative to the source directory (e.g., `"module/header.h"`).

Clang-Format manages include order via the `.clang-format` file. The typical order is:
1. Related header for the current file
2. Standard library headers
3. Third-party library headers
4. Project-specific headers

List each third-party library as a separate category in `.clang-format`. Update `IncludeCategories` when adding new libraries.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Function Definitions in Headers

Define functions in header files only if they are short (10 lines or fewer) or are templates. Longer functions should go in `.cpp` files unless required in the header for technical reasons.

If a function must be defined in a header, keep its body out of the public section—use a private section, an `internal` namespace, or place it after a comment like `// Implementation details only below here`.

All header-defined functions must be ODR-safe: use `inline`, make them templates, or define them inside the class body.

Example:

```cpp
template <typename T>
class Foo {
public:
    // Short, ODR-safe function defined in header
    int bar() const { return bar_; }
  
    // Long function declared only; implementation in .cpp or below
    void doSomething();

private:
    int bar_;
};

// Implementation details only below here
template <typename T>
void Foo<T>::doSomething() {
    // ... lengthy implementation ...
}
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Scoping

Scoping helps organize code, prevent name collisions, and manage visibility.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Namespaces

Place all code in a namespace, named after the project or its path:

```cpp
namespace my_project {
    // Code goes here
}  // namespace my_project
```

> [!NOTE]
> Avoid `using namespace ...;` and inline namespaces.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Local Variables

Declare variables in the narrowest scope possible, close to their first use and always initialize them at declaration:

```cpp
void foo() {
    int x = 42; // Declaration and initialization together.
    // Use x...
}
```

For objects used in loops, declare them outside the loop for efficiency:

```cpp
Foo f;
for (int i = 0; i < 1000000; ++i) {
  f.doSomething(i);
}
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Classes

Use `class` for types that encapsulate data and behavior. This section provides guidelines for writing classes in C++.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Access Control

Make data members `private` (except for constants) to protect invariants and encapsulation. Use accessor methods as needed.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Declaration Order

Start with `public:` members, then `protected:`, then `private:`. Omit empty sections.

Within each section, group declarations in this order:

1. Types and aliases (`using`, `enum`, nested structs/classes, friends)
2. (For structs) Non-static data members
3. Static constants
4. Factory functions
5. Constructors and assignment operators
6. Destructor
7. Other functions
8. Other data members

This keeps related items together and improves readability.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Structs

Use `struct` for passive data objects that carry data; use `class` for everything else.

Prefer to use a `struct` instead of a `std::pair` or `std::tuple` whenever the elements can have meaningful names. 

Use pairs and tuples only in generic code where the elements do not have specific meanings, or when required for interoperability with existing code or APIs.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Looping and Branching Statements

Use braces for all control statements (`if`, `else`, `for`, `while`, `do`, `switch`), even for single-line bodies:

```cpp
if (condition) {
    doSomething();
} 
else {
    doSomethingElse();
}

while (condition) {
    doSomething();
}

for (int i = 0; i < 10; ++i) {
    doSomethingWith(i);
}

switch (var) {
    case 0: {
        foo();
        break;
    }
}
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Preincrement and Predecrement

Prefer prefix increment/decrement (`++i`, `--i`) over postfix (`i++`, `i--`) unless you need the value before the change:

```cpp
// Good: preincrement
for (int i = 0; i < n; ++i) {
    std::cout << i << std::endl;
}

// Necessary: postincrement
std::vector<int> vec = {10, 20, 30};
auto it = vec.begin();
while (it != vec.end()) {
    std::cout << *it++ << std::endl; // Value needed before increment
}
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Use of `const`

Use `const` to indicate immutability and improve code safety. `constexpr` is preferred when a value is known at compile time.

```cpp
void processData(const std::vector<int>& data) {
    constexpr int threshold = 10; // Compile-time constant
    
    // Use const to ensure data is not modified
    for (const auto& item : data) {
        if (item > threshold) {
            // Do something with item
        }
    }
}
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Naming

Naming conventions are crucial for maintaining a consistent and readable codebase. This section outlines the naming conventions for various elements in the code.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Files

Use `snake_case` suffixed with the appropriate file extension (`.h`, `.hpp`, or `.cpp`) for file names:

```cpp
my_class.h
my_class.cpp
```

> [!NOTE]
> This project uses `.h` for header files and `.cpp` for source files. 
> File names should be descriptive and reflect the content or purpose of the file.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Namespaces

Namespaces names use `snake_case`:

```cpp
namespace my_project {
namespace utils {

// Utility functions go here.

}  // namespace utils
}  // namespace my_project
```

> [!NOTE]
> All code in the namespace should be under one or more directories with the same name as the namespace.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Classes and Structs

Use `PascalCase` for class and struct names:

```cpp
class MyClass {
    // Class members
};

struct MyStruct {
    // Struct members
};
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Functions and Methods

Use `camelCase` for function and method names:

```cpp
void myFunction();

class MyClass {
public:
    void myMethod();
};
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Variables

Local variables and function parameters use `snake_case`:

```cpp
void processData(int input_value) {
    int local_variable = input_value * 2;
}
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Member Variables

There are two common conventions for member variables:

1. Underscore suffix:

   ```cpp
   class MyClass {
   private:
       int value_;
       std::string name_;
   };
   ```
   
2. `m_` prefix:
   
   ```cpp
   class MyClass {
   private:
       int m_value;
       std::string m_name;
   };
   ```

> [!NOTE]
> This project uses the underscore suffix convention for class member variables. 

Struct member variables are named like ordinary nonmember variables, without the trailing underscore:

```cpp
struct MyStruct {
    int value;
    std::string name;
};
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Constants and Enums

Use `PascalCase` for enum names and `PascalCase` prefixed with `k` for constants and enum values:

```cpp
enum class Color {
    kRed,
    kGreen,
    kBlue
};

const int kMaxValue = 100;
constexpr double kPi = 3.14159;
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Aliases

Use `PascalCase` for type aliases defined with `using`:

```cpp
using StringList = std::vector<std::string>;
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Templates

Use `PascalCase` for template parameters:

```cpp
template <typename InputType>
InputType processInput(InputType input);
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Macros

Use `UPPER_CASE` with a project-specific prefix for macro names:

```cpp
#define MYPROJECT_MAX(a, b) ((a) > (b) ? (a) : (b))
```

> [!NOTE]
> Try to avoid using macros whenever possible. Macros can lead to hard-to-debug issues and are generally discouraged in modern C++. Instead, prefer `inline` or `constexpr` functions.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

## Comments

Comments are essential for understanding code. They help explain the intent behind code, document design decisions, and provide context for future maintainers. This section provides guidelines for writing effective comments.

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### When to comment

| Do comment when...                                 | Avoid when...                                 |
| -------------------------------------------------- | --------------------------------------------- |
| A non-obvious **algorithmic trick** needs context. | The code literally states the same thing.     |
| A temporary **work-around or TODO** is present.    | You can instead rename a variable or helper.  |
| There is a subtle **invariant / side-effect**.     | The function already documents the behaviour. |
| You’re **explaining why**, not *what*.             | You’re restating the *what* (“increment i”).  |

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

### Comment Style

- **Place above** the line or block it explains—never to the right of long code.
- **Start with a capital letter** and **end with a period** if the sentence is complete.
- Use the `TODO(user, yyyy-mm-dd):` format for tasks.
- Keep lines short; wrap with the same `//` prefix.
- Prefer present tense and active voice.
- Be specific and actionable—avoid vague or generic comments.

```cpp
// Compute signed area via Shoelace formula.
double area = polygonSignedArea(verts);

// Guard: polygon must be simple (no self-intersections).
if (hasSelfIntersection(verts)) return Err::kInvalid;

// TODO(alice, 2025-07-01): Replace O(n^2) intersection test with a sweep-line algorithm.
```

<!-- START mdsplit-ignore -->
**[Return to Index](#style-guide-index)**
<!-- END mdsplit-ignore -->

# Formatting

This project uses [clang-format](https://clang.llvm.org/docs/ClangFormat.html) to ensure a consistent code style across all C++ files.

<!-- START mdsplit-ignore -->
<a id="formatting-index"></a>
<details open>
<summary><Strong>Index</Strong></summary>

- [Formatting](#formatting)
  - [Configuration](#configuration)
  - [How to Format Code](#how-to-format-code)
  - [Best Practices](#best-practices)

</details>
<!-- END mdsplit-ignore -->

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

<!-- START mdsplit-ignore -->
**[Return to Index](#formatting-index)**
<!-- END mdsplit-ignore -->

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

<!-- START mdsplit-ignore -->
**[Return to Index](#formatting-index)**
<!-- END mdsplit-ignore -->

## Best Practices

- **Format before committing:** Always run clang-format on your changes before submitting a pull request.
- **Editor integration:** Enable auto-format on save to avoid manual formatting.
- **Consistency:** Do not manually adjust formatting—let clang-format handle it.

If you have questions about the formatting rules or need help configuring your editor, ask in the project discussions or open an issue.

<!-- START mdsplit-ignore -->
**[Return to Index](#formatting-index)**
<!-- END mdsplit-ignore -->

# Documentation

This project uses [Doxygen](https://www.doxygen.nl/) to generate documentation from annotated source code. Doxygen comments are used to describe the purpose, behavior, and usage of classes, functions, and other entities in the codebase. Follow these guidelines to ensure your code is well-documented and easy to understand. Always use `@` for Doxygen commands and tags, as this is the standard convention in this project.

<!-- START mdsplit-ignore -->
<a id="documentation-index"></a>
<details open>
<summary><Strong>Index</Strong></summary>

- [Documentation](#documentation)
  - [Common Doxygen Tags](#common-doxygen-tags)
  - [How to Generate Doxygen Documentation](#how-to-generate-doxygen-documentation)
  - [Documenting Code](#documenting-code)
    - [Files](#files-1)
    - [Namespaces](#namespaces-2)
    - [Classes \& Structs](#classes--structs)
    - [Functions \& Methods](#functions--methods)
    - [Member Variables](#member-variables-1)
    - [Constants](#constants)
    - [Enums](#enums)
    - [Formulas](#formulas)
    - [Units](#units)
    - [Modules](#modules)

</details>
<!-- END mdsplit-ignore -->

## Common Doxygen Tags

| Tag                                           | Applies to            | What it conveys                                                |
| --------------------------------------------- | --------------------- | -------------------------------------------------------------- |
| `@file`                                       | file banner           | Exact file name (with extension).                              |
| `@author`                                     | file banner           | Author list, comma-separated, alphabetical by first name.      |
| `@ingroup`                                    | any entity            | Places the item in a previously defined group/module page.     |
| `@defgroup`                                   | one “module” block    | Declares a new group (module) page.                            |
| `@namespace`                                  | namespace block       | Purpose and scope of the namespace.                            |
| `@class` / `@struct`                          | class or struct block | Identifies the type when the block isn’t immediately adjacent. |
| `@enum`                                       | enumeration block     | Identifies the enum type.                                      |
| `@brief`                                      | all blocks            | One-sentence summary (≤ 80 chars).                             |
| `@details`                                    | any block             | Longer discussion: design notes, examples, algorithms.         |
| `@param[in]`, `@param[out]`, `@param[in,out]` | functions / methods   | Describes parameters and their direction.                      |
| `@tparam`                                     | templates             | Describes a template parameter.                                |
| `@return`                                     | functions / methods   | Meaning of the return value (omit for `void`).                 |
| `@throws`                                     | functions / methods   | Exception types that may be raised.                            |
| `@note`                                       | any block             | Extra caveats, units, thread-safety, side-effects.             |
| `@deprecated`                                 | any block             | Version and replacement when an API is being retired.          |
| `@bug`                                        | any block             | Known issues still present in the code.                        |
| `@see`                                        | any block             | Cross-reference to related symbols, headers, or guides.        |
| `@def`                                        | macro block           | Names the macro when the block is not directly above it.       |
| `@copyright`                                  | file banner           | Legal notice or licence statement.                             |

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

## How to Generate Doxygen Documentation

1. Ensure [Doxygen](https://www.doxygen.nl/) is installed on your system.
2. From the project root, run:
   ```bash
   doxygen Doxyfile
   ```
3. The generated HTML and/or LaTeX documentation will appear in the output directory specified in your `Doxyfile`.

For more details on configuring or customizing Doxygen output, see the official [Doxygen manual](https://www.doxygen.nl/manual/index.html) or review the `Doxyfile` in the project root.

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

## Documenting Code

When documenting code, use Doxygen comments to describe the purpose and behavior of classes, functions, and other entities. Use the following guidelines to ensure clarity and consistency.

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Files

Use a **single Doxygen block** at the very top of every header file.

#### Required tags

| Tag        | Description                                          |
| ---------- | ---------------------------------------------------- |
| `@file`    | Exact file name with extension                       |
| `@authors` | Author(s), comma-separated, alphabetic by first name |
| `@ingroup` | Module or package this file belongs to               |
| `@brief`   | One-sentence purpose                                 |

#### Optional tags

`@details`, `@note`, `@deprecated`, `@bug`, `@see`, `@copyright`

#### Template:

```cpp
/**
 * @file <filename>.h
 * @author <First Last>, <First Last>
 * @ingroup <GroupName>
 * @brief <Short purpose of the file>
 *
 * @details 
 * <Longer explanation—algorithms, design notes...>
 *
 * @note <Optional notes>
 * @deprecated <Version X.Y — replacement API or file>
 * @bug <Known issues>
 * @see <Related header/guide/issue URL>
 * @copyright <Copyright details>
 */
```

#### Example:

```cpp
/**
 * @file polygon_area.h
 * @author Alice Brown, Carlos Diaz
 * @ingroup Geometry
 * @brief Implements Shoelace-based area calculations for simple polygons.
 *
 * @details
 * Implements Shoelace-formula functions to compute signed or absolute area of 2-D polygons supplied as `std::span<const Vec2>` in counter-clockwise order. The Shoelace formula is defined as:
 * @formula{shoelace; A = \frac{1}{2} \sum_{i=1}^{n} (x_i y_{i+1} - x_{i+1} y_i)}
 *
 * @note Assumes polygons are simple (non-self-intersecting).
 * @deprecated Will be superseded by `polygon_metrics.h` in v2.0
 * @see vector2.h
 * @copyright 2025 Geometry Toolkit
 */
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Namespaces

Namespaces are used to organize code into logical groups and prevent name collisions. Each namespace should be documented with a **single Doxygen block** placed at the top of the header file where the namespace is defined. This block describes the purpose, scope, and any relevant notes about the namespace.

#### Required tags

| Tag          | Description          |
| ------------ | -------------------- |
| `@namespace` | Fully-qualified name |
| `@ingroup`   | Module or package    |
| `@brief`     | One-sentence purpose |

#### Optional tags

`@details`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template:

```cpp
/**
 * @namespace <namespace_name>
 * @ingroup <GroupName>
 * @brief <Short purpose of the namespace>
 *
 * @details
 * <Longer explanation—scope, design notes, usage examples.>
 *
 * @note <Caveats / thread safety / units>
 * @deprecated <Version X.Y — replacement namespace>
 * @bug <Known issues>
 * @see <Related namespace or guide>
 */
```

#### Example:

```cpp
/**
 * @namespace geom
 * @ingroup Geometry
 * @brief Core 2-D geometry primitives and algorithms.
 */
namespace geom { /* ... */ }
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Classes & Structs

Use a **Doxygen block** above each public `class` or `struct` declaration in header files and use `///<` for member notes.

#### Required tags

| Tag                       | Description          |
| ------------------------- | -------------------- |
| `@class` **or** `@struct` | Class or struct name |
| `@ingroup`                | Module or package    |
| `@brief`                  | One-sentence purpose |

#### Optional tags

`@details`, `@tparam`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template:

```cpp
/**
 * @class <ClassName>
 * @ingroup <GroupName>
 * @brief <Short description of the class>
 *
 * @details
 * <Longer explanation—design rationale, invariants, usage examples.>
 *
 * @tparam <T>  <Template parameter description> 
 * @note <Thread-safety, units, etc.>
 * @deprecated <Version X.Y — replacement API>
 * @bug <Known issues>
 * @see <Related type or doc link>
 */
```

#### Example:

```cpp
/**
 * @struct Vec2
 * @brief Lightweight 2-D point with double precision.
 */
struct Vec2 {
    double x {0.0}; ///< X coordinate
    double y {0.0}; ///< Y coordinate
};

/**
 * @class Polygon
 * @ingroup Geometry
 * @brief Simple, non-self-intersecting polygon.
 *
 * @details
 * Stores vertices in counter-clockwise order and provides helpers for
 * area, centroid, and point-in-polygon tests. Not thread-safe.
 *
 * @note Capacity is fixed at construction; AddVertex throws when full.
 * @bug AddVertex does not check for self-intersection.
 */
class Polygon {
public:
    explicit Polygon(std::size_t max_vertices);

    /**
     * @brief Adds a new vertex in world coordinates.
     * @param[in] p  Vertex to add.
     * @throws std::length_error  If max_vertices reached.
     */
    void addVertex(const Vec2& p);

    /**
     * @brief Computes the signed area using the Shoelace formula.
     *
     * @return The signed area of the polygon @unit{m^2}.
     *
     * @note The area is positive if vertices are in counter-clockwise order.
     */
    double area() const noexcept; 

private:
    std::vector<Vec2> vertices_; ///< Vertices in CCW order
};
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Functions & Methods

Use a **Doxygen block** above each public function or method declaration in header files. This applies to both free functions and member functions of classes or structs.

#### Required tags

| Tag          | Description                                                  |
| ------------ | ------------------------------------------------------------ |
| `@brief`     | One-sentence purpose                                         |
| `@param[in]` | Input parameter (`@param[out]` / `@param[in,out]` as needed) |
| `@return`    | Meaning of the return value (omit for `void`)                |

#### Optional tags

`@details`, `@tparam`, `@throws`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template:

```cpp
/**
 * @brief <Short description of what the function does>
 *
 * @details 
 * <Longer explanation—algorithm, pre-conditions…>
 *
 * @tparam <T>  <Description of template parameter>
 * @param[in] <name>  <What this parameter represents>
 * @param[out] <name>  <How the caller receives data>
 * @return <Meaningful description of the result>
 *
 * @throws <exception type> <When it is thrown>
 * @note <Caveats / units / thread safety>
 * @deprecated <Version X.Y — replacement API>
 * @bug <Known issues>
 * @see <Related symbol or doc link>
 */
```

#### Example:

```cpp
/**
 * @brief Adds a vertex to the polygon.
 *
 * @tparam Point2D Any 2-D point type convertible to Vec2.
 * @param[in] p  New vertex in world coordinates.
 * @return Index of the inserted vertex.
 *
 * @note Invalidates cached area; recompute via `area()`.
 * @throws std::length_error If vertex count exceeds `kMaxVertices`.
 */
template <typename Point2D>
std::size_t Polygon::addVertex(const Point2D& p);
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Member Variables

Use **inline-after comments with `///<`** for one-line descriptions of data members and individual enum values. This applies to both classes and structs.
 
#### Template:

```cpp
Type name_; ///< <Concise purpose>
```

#### Example:

```cpp
size_t count_ {0};   ///< Current vertex count
std::vector<Vec2> verts_; ///< Vertices in counter-clockwise order
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Constants

Document global constants with an **inline-after** comment.

#### Template:

```cpp
constexpr Type kConstName ///< <Concise purpose>
```

#### Example:

```cpp
constexpr double kPi = 3.141592653589793;    ///< Circle ratio @unit{radians}
inline const Vec2 kOrigin {0.0, 0.0};        ///< Reference point (0,0)
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->


### Enums

Document the **enum type** with a block comment; document each **enumerator** with `///<`. If an enum has only a few obvious values (e.g. `Clockwise`, `CounterClockwise`), the inline docs may be omitted.

#### Required tags

| Tag        | Description          |
| ---------- | -------------------- |
| `@enum`    | Enum name            |
| `@ingroup` | Module or package    |
| `@brief`   | One-sentence purpose |

#### Optional tags

`@details`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template:

```cpp
/**
 * @enum <EnumName>
 * @ingroup <GroupName>
 * @brief <Short description of the enumeration>
 *
 * @details 
 * <Longer explanation—usage rules, algorithms…>
 *
 * @note <Optional notes>
 * @deprecated <Version X.Y — replacement enum>
 * @bug <Known issues>
 * @see <Related enum or doc link>
 */
```

#### Example:

```cpp
/**
 * @enum Axis
 * @ingroup Geometry
 * @brief Principal 3-D axes.
 */
enum class Axis {
    kX, ///< X-axis
    kY, ///< Y-axis
    kZ  ///< Z-axis
};
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->


### Formulas

When documenting functions, algorithms, or concepts that involve mathematical formulas, use the `@formula` command to typeset equations. This command is defined in the Doxyfile under `ALIASES` and uses MathJax for rendering. The `@formula` command allows you to assign a label to each equation, making it easy to reference equations elsewhere in your documentation.

#### Template:

```cpp
/**
 * @formula{<equation_label>; <equation_expression>}
 */
```

> The label entered in `equation_label` will be prefixed with `eq:` automatically. To reference the equation in your documentation, use `\eqref{eq:equation_label}`.

#### Example:

```cpp
/**
 * The shoelace formula is defined as:
 * @formula{shoelace; A = \frac{1}{2} \sum_{i=1}^{n} (x_i y_{i+1} - x_{i+1} y_i)}
 */
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Units

When documenting variables that represent physical quantities, **always specify the unit** in the documentation. Use the `@unit` command, which is defined in the `Doxyfile` under `ALIASES`, to standardize unit notation across the codebase. The `@unit` command utilizes MathJax and the [siunitx](https://ctan.org/pkg/siunitx) library for typesetting units.

#### Template:

```cpp
type variable_name; ///< Brief description @unit{unit}
```

#### Example:

```cpp
double fan_speed; ///< Fan speed @unit{rpm}
double density_corrected; ///< Gas density corrected to reference conditions @unit{lb/ft^3}
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

### Modules

Modules (or groups) are collections of related namespaces, classes, and functions that together provide a high-level overview of a particular area of functionality in the codebase. Modules help organize documentation, making it easier for users and contributors to understand the structure and purpose of different parts of the project.

Each module should be documented with a **single Doxygen block** placed in a central documentation file (such as `mainpage.dox`). This block defines the module and provides an overview of its contents, design philosophy, and any relevant notes or references. All related code elements (namespaces, classes, functions, etc.) should reference the module using the `@ingroup` tag in their own documentation blocks to associate them with the appropriate group.

#### Required tags

| Tag         | Description                    |
| ----------- | ------------------------------ |
| `@defgroup` | `<GroupName>` and display text |
| `@brief`    | One-sentence description       |

#### Optional tags

`@details`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template:

```cpp
/**
 * @defgroup <GroupName> <Display Title>
 * @brief <Short description of the module>
 *
 * @details
 * <Longer overview—contents, design philosophy, links.>
 *
 * @note <Optional notes>
 * @deprecated <Version X.Y — replacement module>
 * @bug <Known issues>
 * @see <Related module or guide>
 */
```

#### Example:

```cpp
/**
 * @defgroup Geometry Geometry
 * @brief 2-D geometry toolkit: vectors, polygons, intersections.
 *
 * @details
 * Includes Vec2, Polygon, area/centroid helpers, and spatial predicates.
 */
```

<!-- START mdsplit-ignore -->
**[Return to Index](#documentation-index)**
<!-- END mdsplit-ignore -->

# Conventional Commits

This project follows the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification for commit messages to ensure clarity, consistency, and automation in version control. This helps in generating changelogs, automating releases, and improving collaboration among contributors.

<!-- START mdsplit-ignore -->
<a id="conventional-commits-index"></a>
<details open>
<summary><Strong>Index</Strong></summary>

- [Conventional Commits](#conventional-commits)
  - [Commit Format](#commit-format)
  - [Commit Types](#commit-types)
  - [Commit Scopes](#commit-scopes)
  - [Breaking Changes](#breaking-changes)

</details>
<!-- END mdsplit-ignore -->

## Commit Format

Each commit message should follow this format:

```
<type>(<optional scopes>): <description>

<optional body>

<optional footer>
```

<!-- START mdsplit-ignore -->
**[Return to Index](#conventional-commits-index)**
<!-- END mdsplit-ignore -->

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

<!-- START mdsplit-ignore -->
**[Return to Index](#conventional-commits-index)**
<!-- END mdsplit-ignore -->

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

<!-- START mdsplit-ignore -->
**[Return to Index](#conventional-commits-index)**
<!-- END mdsplit-ignore -->

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

<!-- START mdsplit-ignore -->
**[Return to Index](#conventional-commits-index)**
<!-- END mdsplit-ignore -->
