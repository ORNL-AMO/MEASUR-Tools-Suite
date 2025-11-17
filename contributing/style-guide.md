# Style Guide <!-- omit in toc -->

Use this guide to ensure your contributions align with the project's coding standards. It is loosely based on the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), with some modifications to suit this project's needs.

## Table of Contents <!-- omit in toc -->

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

## Header Files

Every C++ source file (`.cpp`) should have a corresponding header file (`.h`). The header file contains declarations, while the source file contains definitions and implementations.

> [!NOTE]
> A common exception is unit tests, which may not require a separate header file. Small `.cpp` files containing just a `main()` function may also not have a corresponding header.

**[Table of Contents](#table-of-contents)**

### Include Guards

Every header file must have a `#pragma once` directive to prevent multiple inclusion of header files:

```cpp
#pragma once

// other includes or declarations

// file content
```

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**

### Include Order

Use double quotes (`"header.h"`) for project and third-party headers, and angle brackets (`<vector>`) for standard library headers.

Include project headers relative to the source directory (e.g., `"module/header.h"`).

Clang-Format manages include order via the `.clang-format` file. The typical order is:
1. Related header for the current file
2. Standard library headers
3. Third-party library headers
4. Project-specific headers

List each third-party library as a separate category in `.clang-format`. Update `IncludeCategories` when adding new libraries.

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**

## Scoping

Scoping helps organize code, prevent name collisions, and manage visibility.

**[Table of Contents](#table-of-contents)**

### Namespaces

Place all code in a namespace, named after the project or its path:

```cpp
namespace my_project {
    // Code goes here
}  // namespace my_project
```

> [!NOTE]
> Avoid `using namespace ...;` and inline namespaces.

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**

## Classes

Use `class` for types that encapsulate data and behavior. This section provides guidelines for writing classes in C++.

**[Table of Contents](#table-of-contents)**

### Access Control

Make data members `private` (except for constants) to protect invariants and encapsulation. Use accessor methods as needed.

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**

## Structs

Use `struct` for passive data objects that carry data; use `class` for everything else.

Prefer to use a `struct` instead of a `std::pair` or `std::tuple` whenever the elements can have meaningful names. 

Use pairs and tuples only in generic code where the elements do not have specific meanings, or when required for interoperability with existing code or APIs.

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**

## Naming

Use the following naming conventions for various elements in the codebase to ensure consistency and readability.

**[Table of Contents](#table-of-contents)**

### Files

Use `snake_case` suffixed with the appropriate file extension (`.h`, `.hpp`, or `.cpp`) for file names (e.g., `my_class.h`, `my_class.cpp`).

> [!NOTE]
> This project uses `.h` for header files and `.cpp` for source files.

**[Table of Contents](#table-of-contents)**

### Namespaces

Use `snake_case` for namespace names (e.g., `my_project`, `utils`).

**[Table of Contents](#table-of-contents)**

### Classes and Structs

Use `PascalCase` for class and struct names (e.g., `MyClass`, `MyStruct`).

**[Table of Contents](#table-of-contents)**

### Functions and Methods

Use `camelCase` for function and method names (e.g., `myFunction`, `computeArea`).

Use verbs or verb phrases for function names to indicate actions.

- Accessor methods (getters) should be named after the property they return, without a `get` prefix (e.g., `eyeColor()`).
- Mutator methods (setters) should be named with a `set` prefix followed by the property name (e.g., `setEyeColor()`).

#### Example

```cpp
class Dog {
public:
    std::string eyeColor() const { return eye_color_; } // Accessor for eye_color_

    void setEyeColor(const std::string& color) { eye_color_ = color; } // Mutator for eye_color_

private:
    std::string eye_color_;
};
```

**[Table of Contents](#table-of-contents)**

### Variables

Use `snake_case` for variable names and function parameters.

#### Example

```cpp
void processData(int input_value) {
    int local_variable = input_value * 2;
}
```

**[Table of Contents](#table-of-contents)**

### Member Variables

Use `snake_case` for member variable names, with a trailing underscore (`_`) to distinguish them from local variables and parameters.

#### Example 

```cpp
class Dog {
private:
    std::string name_;
    int age_;
    std::string eye_color_;
};
```

Use `snake_case` for struct member variables without a trailing underscore.

#### Example

```cpp
struct Point2 {
    double x;
    double y;
};
```

**[Table of Contents](#table-of-contents)**

### Constants and Enums

Use `PascalCase` for enum names and `PascalCase` prefixed with `k` for constants and enum values.

#### Example

```cpp
enum class Color {
    kRed,
    kGreen,
    kBlue
};

const int kMaxValue = 100;
constexpr double kPi = 3.14159;
```

**[Table of Contents](#table-of-contents)**

### Aliases

Use `PascalCase` for type aliases.

#### Example

```cpp
using StringList = std::vector<std::string>;
```

**[Table of Contents](#table-of-contents)**

### Templates

Use `PascalCase` for template parameters.

#### Example

```cpp
template <typename InputType>
InputType processInput(InputType input);
```

**[Table of Contents](#table-of-contents)**

### Macros

Use `UPPER_CASE` with a project-specific prefix for macro names.

#### Example

```cpp
#define MYPROJECT_MAX(a, b) ((a) > (b) ? (a) : (b))
```

> [!NOTE]
> Try to avoid using macros whenever possible. Macros can lead to hard-to-debug issues and are generally discouraged in modern C++. Instead, prefer `inline` or `constexpr` functions.

**[Table of Contents](#table-of-contents)**

## Comments

Comments are essential for understanding code. They help explain the intent behind code, document design decisions, and provide context for future maintainers. This section provides guidelines for writing effective comments.

**[Table of Contents](#table-of-contents)**

### When to comment

| Do comment when...                                 | Avoid when...                                 |
| -------------------------------------------------- | --------------------------------------------- |
| A non-obvious **algorithmic trick** needs context. | The code literally states the same thing.     |
| A temporary **work-around or TODO** is present.    | You can instead rename a variable or helper.  |
| There is a subtle **invariant / side-effect**.     | The function already documents the behaviour. |
| You’re **explaining why**, not *what*.             | You’re restating the *what* (“increment i”).  |

**[Table of Contents](#table-of-contents)**

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

**[Table of Contents](#table-of-contents)**
