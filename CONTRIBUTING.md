# How to Contribute

This guide provides clear standards and best practices for contributing to this project. It covers coding style, documentation, formatting, and workflow expectations to help maintain high code quality, ensure long-term maintainability, and foster smooth collaboration among all contributors.

## [Style Guide](#style-guide)

Follow this guide to make sure your contributions align with the project's coding standards. This will help ensure that your code is readable, maintainable, and consistent with the rest of the codebase.

## [Clang-Format](#clang-format)

Use Clang-Format to automatically format your code according to the project's style guide. This ensures consistent formatting across the codebase and reduces manual formatting effort.

## [Doxygen Documentation](#doxygen-documentation)

Follow these guidelines to document your code effectively using Doxygen. Proper documentation is crucial for understanding the codebase and facilitating collaboration.

## [Conventional Commits](#conventional-commits)

Use Conventional Commits to structure your commit messages. This helps maintain a clear project history and makes it easier to understand the purpose of each change. 

<br>

# Style Guide

This section describes the coding style for this project. It is based on the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), with some modifications to suit this project's needs.

## Header Files

Every `.cpp` file should have an associated `.h` file. There are some common exceptions, such as unit tests and small `.cpp` files containing just a `main()` function.

### The #define Guard

---

All header files should have `#define` guards to prevent multiple inclusion.

#### Format

```cpp
#ifndef <PROJECT>_<PATH>_<FILE>_H_
#define <PROJECT>_<PATH>_<FILE>_H_

...

#endif  // <PROJECT>_<PATH>_<FILE>_H_
```

#### Example

```cpp
#ifndef GEOMETRY_POLYGON_AREA_H_
#define GEOMETRY_POLYGON_AREA_H_

...

#endif  // GEOMETRY_POLYGON_AREA_H_
```

### Include What You Use

---

If a source or header file refers to a symbol defined elsewhere, it must directly include the header that provides the declaration or definition of that symbol. Do not include headers for any other reason.

Do **not** rely on transitive inclusions (i.e., do not assume that a header is included indirectly via another header). This practice allows unnecessary `#include` statements to be safely removed from headers without breaking dependent code.

This rule also applies to related headers: for example, if `foo.cpp` uses a symbol from `bar.h`, it should include `bar.h` directly, even if `foo.h` already includes `bar.h`.

### Forward Declarations

---

Avoid using forward declarations where possible. Instead, include the headers you need.

#### Good

```cpp
#include "b.h"
void f(B*);
void f(void*);
void test(D* x) { f(x); }  // Calls f(B*)
```

#### Bad

```cpp
class B;  // Forward declaration without definition.
void FuncInB();
extern int variable_in_b;
```

### Defining Functions in Header Files

---

Only define a function at its public declaration if it is short (10 lines or fewer) or if it is a template function. Place longer function bodies in the `.cpp` file unless they must be in the header for performance or technical reasons.

If a definition must be in the header, avoid placing it in the public section. Instead, put it in a private section, an `internal` namespace, or below a comment like `// Implementation details only below here`.

All function definitions in header files must be ODR-safe by using the `inline` specifier, being a function template, or being defined in a class body at first declaration.

#### Example

```cpp
template <typename T>
class Foo {
 public:
  int bar() { return bar_; }

  void MethodWithHugeBody();

 private:
  int bar_;
};

// Implementation details only below here

template <typename T>
void Foo<T>::MethodWithHugeBody() {
  ...
}
```

### Names and Order of Includes

---

Project-specific and third-party library headers should be included using double quotes (`"myheader.h"`), while standard library headers should use angle brackets (`<vector>`).

All of a project's header files should be listed as descendants of the project's source directory. For example, `myproject/include/module/header.h` should be included as `"module/header.h"`.

The order of includes is handled automatically by Clang-Format using the `IncludeCategories` setting in the `.clang-format`. The general order is:
1. Related header file for the current source file (e.g., `"foo.h"`).
2. Standard library headers (e.g., `<string>` and `<vector>`).
3. Third-party library headers (e.g., `<boost/some_header.h>`).
4. Project-specific headers (e.g., `"project/some_header.h"`).

All third-party libraries should be defined as separate categories in the `.clang-format` file. When adding a new third-party library, update the `IncludeCategories` section in the `.clang-format` file to include it.

## Scoping

### Namespaces

---

With few exceptions, place all code in a namespace. Namespaces should have unique names based on the project name and, if appropriate, its path.

- **Do not** use using-directives (e.g., `using namespace foo;`).
- **Do not** use inline namespaces.

Namespaces subdivide the global scope into distinct, named scopes, preventing name collisions in large programs and allowing most code to use reasonably short names. For example, if two projects both define a class `Foo` in the global scope, these symbols may collide. By placing code in namespaces, `project1::Foo` and `project2::Foo` are distinct and do not conflict, while code within each namespace can refer to `Foo` without qualification.

**Inline namespaces** automatically place their names in the enclosing scope. For example:

```cpp
namespace outer {
inline namespace inner {
  void foo();
}  // namespace inner
}  // namespace outer

// Both of these are valid:
outer::inner::foo();
outer::foo();
```

### Local Variables

---

Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.
- Declare variables as close as possible to their first use, and within the smallest scope needed.
- Always initialize variables at the point of declaration, rather than declaring and assigning separately.

#### Good

```cpp
int i = f();  // Declaration and initialization together.
int jobs = NumJobs();
f(jobs);      // Declaration closely followed by use.
std::vector<int> v = {1, 2};  // Prefer brace initialization.
```

#### Bad

```cpp
int i;
i = f();      // Initialization separate from declaration.
int jobs;
jobs = NumJobs();
// ... more code ...
f(jobs);      // Declaration far from use.
std::vector<int> v;
v.push_back(1);
v.push_back(2);  // Prefer initializing with braces.
```

Variables needed for if, while, and for statements should normally be declared within those statements to confine their scope:

```cpp
while (const char* p = strchr(str, '/')) str = p + 1;
```

#### Caveat

If a variable is an object, its constructor and destructor are called each time it enters and leaves scope. For objects used in a loop, it may be more efficient to declare the variable outside the loop:

```cpp
// Inefficient: constructor/destructor called every iteration
for (int i = 0; i < 1000000; ++i) {
  Foo f;
  f.DoSomething(i);
}

// Efficient: constructor/destructor called once
Foo f;
for (int i = 0; i < 1000000; ++i) {
  f.DoSomething(i);
}
```

## Classes

Classes are the fundamental unit of code in C++. Naturally, we use them extensively. This section lists the main dos and don'ts you should follow when writing a class.

### Structs vs. Classes

---

Use a `struct` only for passive objects that carry data; use a `class` for everything else.

- The `struct` and `class` keywords behave almost identically in C++, but we assign different semantic meanings:
  - **struct:** Use for passive data objects with all fields public. Structs may have associated constants, constructors, destructors, and helper methods, but these methods must not require or enforce invariants between fields. There should be no invariants that could be broken by direct field access.
  - **class:** Use when functionality, invariants, encapsulation, or future evolution is needed. If in doubt, prefer `class`.

For consistency with the STL, you may use `struct` for stateless types such as traits, template metafunctions, and

### Structs vs. Pairs and Tuples

---

Prefer to use a `struct` instead of a `std::pair` or `std::tuple` whenever the elements can have meaningful names.

While pairs and tuples can save time by avoiding the need to define a custom type, meaningful field names are almost always clearer than using `.first`, `.second`, or `std::get<X>`.

Use pairs and tuples only in generic code where the elements do not have specific meanings, or when required for interoperability with existing code

### Access Control

---

Make class data members `private`, unless they are constants. This helps maintain class invariants and encapsulation, even if it requires writing simple accessor methods (usually `const`).

### Declaration Order

---

Group similar declarations together, placing public parts earlier.

A class definition must start with a `public:` section, followed by `protected:`, then `private:`. Omit any section that would be empty.

Within each section, group similar kinds of declarations together, in this preferred order:

1. Types and type aliases (`typedef`, `using`, `enum`, nested structs/classes, friend types)
2. (For structs only) Non-static data members
3. Static constants
4. Factory functions
5. Constructors and assignment operators
6. Destructor
7. All other functions (static and non-static member functions, friend functions)
8. All other data members (static and non-static)

This order improves readability and makes it easier to find related declarations.

## Other C++ Features

### Preincrement and Predecrement

---

Use the prefix form (`++i`, `--i`) of the increment and decrement operators unless you specifically need the value before the increment or decrement (postfix semantics).

- The prefix form is generally more readable and can be more efficient, as it does not require making a copy of the original value.
- The postfix form (`i++`, `i--`) should only be used when the previous value is required in the same expression.

#### Good

```cpp
for (int i = 0; i < n; ++i) {
    // Use ++i unless you need the previous value
}
```

#### Bad

```cpp
for (int i = 0; i < n; i++) {
    // Avoid i++ unless you need the previous value
}
```

### Use of `const`

---

Use `const` in APIs wherever it is meaningful and accurate. This includes function parameters, methods, and non-local variables. `constexpr` is preferred when a value is known at compile time.

- **Function parameters:**  
  If a function does not modify an argument passed by reference or pointer, declare the parameter as `const T&` or `const T*`.  
  For parameters passed by value, `const` has no effect on the caller and is not recommended.
- **Member functions:**  
  Declare methods as `const` unless they alter the logical state of the object or allow the user to do so (e.g., by returning a non-const reference). All `const` operations of a class should be safe to invoke concurrently; if not, document the class as "thread-unsafe".
- **Benefits:**  
  Using `const` makes code easier to understand, enables better compiler checks, and helps document which objects can be mutated. This is especially important for thread safety and API clarity.
- **Local variables:**  
  Using `const` on local variables is optional; use your judgment.
- **Placement:**  
  Prefer placing `const` before the type (e.g., `const int* foo`), but consistency with surrounding code is more important than style.

**Summary:**  
Use `const` consistently in APIs to clearly communicate immutability and enable safer, more maintainable code.

## Naming

Give things names that make their purpose or intent understandable to a new reader, even someone on a different team than the owners. Do not worry about saving horizontal space as it is far more important to make your code immediately understandable by a new reader.

Minimize the use of abbreviations that would likely be unknown to someone outside your project (especially acronyms and initialisms). Do not abbreviate by deleting letters within a word. When an abbreviation is used, prefer to capitalize it as a single "word", e.g., StartRpc() rather than StartRPC(). As a rule of thumb, an abbreviation is probably OK if it's listed in Wikipedia. Note that certain universally-known abbreviations are OK, such as i for a loop index and T for a template parameter.

### File Names

---

Filenames are `snake_case` (all lowercase, with underscores between words). For instance: `my_class.cpp`, `polygon.cpp`.

C++ files have a `.cpp` extension, and header files have a `.h` extension.

### Type Names

---

Type names start with a capital letter and have a capital letter for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.

The names of all types — classes, structs, type aliases, enums, and type template parameters — have the same naming convention. Type names should start with a capital letter and have a capital letter for each new word. No underscores. For example:

```cpp
// classes and structs
class MyClass { ...
class MyClassTester { ...
struct MyClassProperties { ...

// typedefs
typedef hash_map<MyClassProperties *, std::string> PropertiesMap;

// using aliases
using PropertiesMap = hash_map<MyClassProperties *, std::string>;

// enums
enum class MyClassError { ...
```

### Concept Names

---

Concept names follow the same rules as type names.

### Variable Names

---

The names of variables (including function parameters) and data members are `snake_case` (all lowercase, with underscores between words). Data members of classes (but not structs) additionally have trailing underscores. For instance: `a_local_variable`, `a_struct_data_member`, `a_class_data_member_`.

#### Common Variable Names

```cpp
std::string table_name;
```

#### Class Data Members

Data members of classes, both static and non-static, are named like ordinary nonmember variables, but with a trailing underscore. The exception to this is static constant class members, which should follow the rules for [naming constants](#constant-names). For example:

```cpp
class TableInfo {
 public:
  ...
  static const int kTableVersion = 3;  // OK - constant naming.
  ...

 private:
  std::string table_name_;             // OK - underscore at end.
  static Pool<TableInfo>* pool_;       // OK.
};
```

#### Struct Data Members

Data members of structs, both static and non-static, are named like ordinary nonmember variables. They do not have the trailing underscores that data members in classes have. For example:

```cpp
struct TableProperties {
  std::string name;
  int num_entries;
  static Pool<TableProperties>* pool;
};
```

### Constant Names

---

Variables declared `constexpr` or `const`, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case. Underscores can be used as separators in the rare cases where capitalization cannot be used for separation. For example:

```cpp
constexpr int kDaysInWeek = 7;
const int kAndroid8_0_0 - 24; // Android 8.0.0
```

### Function Names

---

Regular functions have mixed case; accessors and mutators are named like variables. Regular functions should be named with a verb or verb phrase, and should be descriptive of the action they perform. For example:

```cpp
AddTableEntry()
DeleteTableEntry()
OpenFile()
```

Accessors and mutators (get and set functions) may be named like variables. These often correspond to actual member variables, but this is not required. For example, `int count()` and `void set_count(int count)`.

### Namespace Names

---

Namespace names are `snake_case` (all lowercase, with underscores between words).

When choosing names for namespaces, note that names must be fully qualified when used in a header outside the namespace, because unqualified Aliases are generally banned.

Top-level namespaces must be globally unique and recognizable, so each one should be owned by a single project or team, with a name based on the name of that project or team. Usually, all code in the namespace should be under one or more directories with the same name as the namespace.

Nested namespaces should avoid the names of well-known top-level namespaces, especially `std` and `absl`, because in C++, nested namespaces do not protect from collisions with names in other namespaces.

### Enumerator Names

---

Enumerators (for both scoped and unscoped enums) should be named like constants with a leading "k" followed by mixed case. For example:

```cpp
enum class TableError {
  kOk = 0,
  kOutOfMemory,
  kMalformedInput,
};
```

### Template Parameter Names

---

Template parameters should follow the naming style for their category: type template parameters should follow the rules for [naming types](#type-names), and non-type template parameters should follow the rules for [naming variables](#variable-names) or [constants](#constant-names).

### Macro Names

---

In general macros should not be used. However, if they are absolutely needed, then they should be named with all capitals and underscores, and with a project-specific prefix. For example:

```cpp
#define MYPROJECT_ROUND(x) ...
```

### Aliases

---

The name for an alias follows the same principles as any other new name, applied in the context where the alias is defined rather than where the original name appears. For example:

```cpp
using Bar = Foo;
```

## Comments

Clear, concise comments are essential for maintainable code. Use comments to clarify *why* code exists, explain non-obvious logic, and provide context for future maintainers. Avoid restating what the code does—focus on intent, rationale, and caveats.

### When to comment

---

| Do comment when...                                 | Avoid when...                                 |
| -------------------------------------------------- | --------------------------------------------- |
| A non-obvious **algorithmic trick** needs context. | The code literally states the same thing.     |
| A temporary **work-around or TODO** is present.    | You can instead rename a variable or helper.  |
| There is a subtle **invariant / side-effect**.     | The function already documents the behaviour. |
| You’re **explaining why**, not *what*.             | You’re restating the *what* (“increment i”).  |

### Comment Style

---

1. **Place above** the line or block it explains—never to the right of long code.
2. **Start with a capital letter** and **end with a period** if the sentence is complete.
3. Use the `TODO(user, yyyy-mm-dd):` format for tasks.
4. Keep lines short; wrap with the same `//` prefix.
5. Prefer present tense and active voice.
6. Be specific and actionable—avoid vague or generic comments.

#### Good

```cpp
// Compute signed area via Shoelace formula.
double area = PolygonSignedArea(verts);

// Guard: polygon must be simple (no self-intersections).
if (HasSelfIntersection(verts)) return Err::kInvalid;

// TODO(alice, 2025-07-01): Replace O(n^2) intersection test with a sweep-line algorithm.
```

#### Bad

```cpp
// Increment i.           // (What, not why)
i++; 

// Set area.              // Redundant with code
area = PolygonSignedArea(verts);
```

## Formatting

### Looping and Branching Statements

---

**Always use braces** for all control statements (`if`, `else`, `for`, `while`, `do`, `switch`), even for single-line bodies. This prevents bugs and improves readability.

#### Good

```cpp
if (condition) {
    DoSomething();
} 
else {
    DoSomethingElse();
}

for (int i = 0; i < 10; ++i) {
    LoopBody();
}
```

#### Bad

```cpp
if (condition)
    DoSomething(); // Missing braces
```

#### Exceptions

Braces may be omitted only if the entire statement fits on one line and there is no `else` or `do ... while` part:

```cpp
if (x == kFoo) return new Foo(); // OK
```

#### Switch/case

Braces in `case` blocks are optional, but if used, indent as shown:

```cpp
switch (var) {
    case 0: {
        Foo();
        break;
    }
}
```

#### Empty loops

Use `{}` or `continue`; for empty bodies, not a lone semicolon:

```cpp
while (condition) {}
while (condition) continue;
```

<br>

# Clang-Format

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

<br>

# Doxygen Documentation

Effective documentation makes code **readable, maintainable, and teachable**. Strive for *self-documenting* design—use clear names and small, focused functions—then use comments and documentation to fill in any remaining gaps.

- **Contributors** need to understand design intent, constraints, and rationale to safely extend or modify the code.
- **API users** need clear guidance on usage, contracts, and limitations without reading the implementation.

Write documentation that serves **both** audiences.

> **Note:** This project uses `@` (not `\`) for all Doxygen commands and tags.

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

## How to Generate Doxygen Documentation

1. Ensure [Doxygen](https://www.doxygen.nl/) is installed on your system.
2. From the project root, run:
   ```bash
   doxygen Doxyfile
   ```
3. The generated HTML and/or LaTeX documentation will appear in the output directory specified in your `Doxyfile`.

For more details on configuring or customizing Doxygen output, see the official [Doxygen manual](https://www.doxygen.nl/manual/index.html) or review the `Doxyfile` in the project root.

## Documenting Code

When documenting code, use Doxygen comments to describe the purpose and behavior of classes, functions, and other entities. Use the following guidelines to ensure clarity and consistency.

### Documenting Units for Physical Quantities

---

When documenting variables that represent physical quantities, **always specify the unit** in the documentation. Use the `@unit` command, which is defined in the `Doxyfile` under `ALIASES`, to standardize unit notation across the codebase. The `@unit` command utilizes MathJax and the [siunitx](https://ctan.org/pkg/siunitx) library for typesetting units.

#### Template

```cpp
type variable_name; ///< Brief description @unit{unit}
```

#### Example

```cpp
double fan_speed; ///< Fan speed @unit{rpm}
double density_corrected; ///< Gas density corrected to reference conditions @unit{lb/ft^3}
```

### Documenting Formulas

---

When documenting functions, algorithms, or concepts that involve mathematical formulas, use the `@formula` command to typeset equations. This command is defined in the Doxyfile under `ALIASES` and uses MathJax for rendering. The `@formula` command allows you to assign a label to each equation, making it easy to reference equations elsewhere in your documentation.

#### Template

```cpp
/**
 * @formula{<equation_label>; <equation_expression>}
 */
```

> The label entered in `equation_label` will be prefixed with `eq:` automatically. To reference the equation in your documentation, use `\eqref{eq:equation_label}`.

#### Example

```cpp
/**
 * The shoelace formula is defined as:
 * @formula{shoelace; A = \frac{1}{2} \sum_{i=1}^{n} (x_i y_{i+1} - x_{i+1} y_i)}
 */
```

### File Documentation

---

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

#### Template

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

#### Example

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

### Function & Method Documentation

---

Use a **Doxygen block** above each public function or method declaration in header files. This applies to both free functions and member functions of classes or structs.

#### Required tags

| Tag          | Description                                                  |
| ------------ | ------------------------------------------------------------ |
| `@brief`     | One-sentence purpose                                         |
| `@param[in]` | Input parameter (`@param[out]` / `@param[in,out]` as needed) |
| `@return`    | Meaning of the return value (omit for `void`)                |

#### Optional tags

`@details`, `@tparam`, `@throws`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template

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

#### Example

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
std::size_t Polygon::AddVertex(const Point2D& p);
```

### Class & Struct Documentation

---

Use a **Doxygen block** above each public `class` or `struct` declaration in header files and use `///<` for member notes.

#### Required tags

| Tag                       | Description          |
| ------------------------- | -------------------- |
| `@class` **or** `@struct` | Class or struct name |
| `@ingroup`                | Module or package    |
| `@brief`                  | One-sentence purpose |

#### Optional tags

`@details`, `@tparam`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template

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

#### Example

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
    void AddVertex(const Vec2& p);

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

### Data-Member Documentation

---

Use **inline-after comments with `///<`** for one-line descriptions of data members and individual enum values. This applies to both classes and structs.
 
#### Template

```cpp
Type name_; ///< <Concise purpose>
```

#### Example

```cpp
size_t count_ {0};   ///< Current vertex count
std::vector<Vec2> verts_; ///< Vertices in counter-clockwise order
```

### Enumeration Documentation

---

Document the **enum type** with a block comment; document each **enumerator** with `///<`. If an enum has only a few obvious values (e.g. `Clockwise`, `CounterClockwise`), the inline docs may be omitted.

#### Required tags

| Tag        | Description          |
| ---------- | -------------------- |
| `@enum`    | Enum name            |
| `@ingroup` | Module or package    |
| `@brief`   | One-sentence purpose |

#### Optional tags

`@details`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template

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

#### Example

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

### Constant Documentation

---

Document global constants with an **inline-after** comment.

#### Template

```cpp
constexpr Type kConstName ///< <Concise purpose>
```

#### Example

```cpp
constexpr double kPi = 3.141592653589793;    ///< Circle ratio @unit{radians}
inline const Vec2 kOrigin {0.0, 0.0};        ///< Reference point (0,0)
```

### Namespace Documentation

---

Namespaces are used to organize code into logical groups and prevent name collisions. Each namespace should be documented with a **single Doxygen block** placed at the top of the header file where the namespace is defined. This block describes the purpose, scope, and any relevant notes about the namespace.

#### Required tags

| Tag          | Description          |
| ------------ | -------------------- |
| `@namespace` | Fully-qualified name |
| `@ingroup`   | Module or package    |
| `@brief`     | One-sentence purpose |

#### Optional tags

`@details`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template

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

#### Example

```cpp
/**
 * @namespace geom
 * @ingroup Geometry
 * @brief Core 2-D geometry primitives and algorithms.
 */
namespace geom { /* ... */ }
```

### Module (Group) Documentation

---

Modules (or groups) are collections of related namespaces, classes, and functions that together provide a high-level overview of a particular area of functionality in the codebase. Modules help organize documentation, making it easier for users and contributors to understand the structure and purpose of different parts of the project.

Each module should be documented with a **single Doxygen block** placed in a central documentation file (such as `mainpage.dox`). This block defines the module and provides an overview of its contents, design philosophy, and any relevant notes or references. All related code elements (namespaces, classes, functions, etc.) should reference the module using the `@ingroup` tag in their own documentation blocks to associate them with the appropriate group.

#### Required tags

| Tag         | Description                    |
| ----------- | ------------------------------ |
| `@defgroup` | `<GroupName>` and display text |
| `@brief`    | One-sentence description       |

#### Optional tags

`@details`, `@note`, `@deprecated`, `@bug`, `@see`

#### Template

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

#### Example

```cpp
/**
 * @defgroup Geometry Geometry
 * @brief 2-D geometry toolkit: vectors, polygons, intersections.
 *
 * @details
 * Includes Vec2, Polygon, area/centroid helpers, and spatial predicates.
 */
```

<br>

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
