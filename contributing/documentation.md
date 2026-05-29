# Documentation

This project uses [Doxygen](https://www.doxygen.nl/) to generate documentation from annotated source code. Doxygen comments are used to describe the purpose, behavior, and usage of classes, functions, and other entities in the codebase. Follow these guidelines to ensure your code is well-documented and easy to understand. Always use `@` for Doxygen commands.

.dox files are used to describe calculations with the audience of non-developers in mind. It is used to provide algorithm documentation for system engineering end users. In general we want to use a top down approace in the algorithm documentation. Starting with the final result and breaking down the equations and formulas from there.

## Table of Contents

- [Doxygen Commands](#doxygen-commands)
- [Doxygen Aliases](#doxygen-aliases)
- [Documenting Code](#documenting-code)
  - [Math](#math)
  - [Units](#units)
  - [Formulas](#formulas)
  - [Symbols](#symbols)
  - [Files](#files)
  - [Namespaces](#namespaces)
  - [Classes \& Structs](#classes--structs)
  - [Functions \& Methods](#functions--methods)
  - [Member Variables](#member-variables)
  - [Constants](#constants)
  - [Enums](#enums)
  - [Groups](#groups)
- [Generating Doxygen Documentation](#generating-doxygen-documentation)

## Doxygen Commands

All commands must start with `@`. 

Useful Commands:
- `@file <name>`
- `@authors <authors>`
- `@ingroup <group-name>`
- `@defgroup <name> <group-title>`
- `@namespace <name>`
- `@class <name>`
- `@struct <name>`
- `@enum <name>`
- `@brief <brief description>`
- `@details <detailed description>`
- `@param[<direction>] <parameter-name> <parameter-description>`
- `@tparam <template-parameter-name> <description>`
- `@return <description>`
- `@throws <exception-object> <description>`
- `@note <text>`
- `@bug <description>`
- `@see <reference>`
- `@copyright <text>`
- `@cite <reference>`
- `@ref <reference> <display-text>`

**[Table of Contents](#table-of-contents)**

## Doxygen Aliases

The following Doxygen aliases are defined in the `Doxyfile` to simplify common documentation tasks:
- `@math{<math expression>}`
- `@unitr{<unit expression>}`
- `@unitb{<unit expression>}`
- `@unitp{<unit expression>}`
- `@formula{<label>; <equation>}`
- `@symtable`
- `@symrow{<symbol>; <description>; <unit expression>}`
- `@endsymtable`

**[Table of Contents](#table-of-contents)**

## Documenting Code

When documenting code, use Doxygen comments to describe the purpose and behavior of classes, functions, and other entities. Follow these guidelines to ensure your documentation is clear, consistent, and useful.

**[Table of Contents](#table-of-contents)**

### Math

Use the `@math{<math expression>}` command to to write LaTeX-style mathematical expressions in your documentation.

#### Example

```cpp
/**
 * The speed of light in water is often denoted as @math{C_w}.
 */
```

**[Table of Contents](#table-of-contents)**

### Units

Use the `@unitb{<unit expression>}` command to document units. The `@unitb{}` command uses the siunitx package to format units in LaTeX style and encloses them in brackets.

#### Example

```cpp
/**
 * The speed of light in water is often denoted as @math{C_w} and is approximately 2.25 @unitb{\meter\per\second}.
 */
```

**[Table of Contents](#table-of-contents)**

### Formulas

Use the `@formula{<label>; <equation>}` command to document formulas. The command takes 2 arguments, separated by `;`:
1. A label for the formula, which can be used to reference the formula in the documentation by using `\eqref{eq:<formula-label>}`.
   - All labels are automatically prefixed with `eq:` to avoid conflicts.
2. The formula itself, written in LaTeX syntax.

#### Example

```cpp
/**
 * The area of a circle can be computed using the formula:
 * @formula{circle-area; A = \pi r^2}
 */

/**
 * Remember to use \eqref{eq:circle-area} to calculate the area of a circle.
 */
```

**[Table of Contents](#table-of-contents)**

### Symbols

Use the `@symtable` and `@endsymtable` commands to create a table of symbols used in formulas. Each symbol is documented using the `@symrow{<symbol>; <description>; <unit expression>}` command, which takes three arguments, separated by `;`:
1. The symbol itself, written in LaTeX syntax.
2. A description of the symbol.
3. The unit of the symbol, written in LaTeX syntax and formatted using the siunitx package.

#### Example

```cpp
/**
 * The area of a circle can be computed using the formula:
 * @formula{circle-area; A = \pi r^2}
 * where:
 * @symtable
 * @symrow{A; is the area of the circle; \meter\squared}
 * @symrow{\pi; is the mathematical constant pi; 1}
 * @symrow{r; is the radius of the circle; \meter}
 * @endsymtable
 */
```

**[Table of Contents](#table-of-contents)**

### Files

Use a **Doxygen block** at the very top of each header file to document the file's purpose, authors, and any relevant notes.

#### Relevant commands

- `@ingroup`
- `@file`
- `@authors`
- `@brief`
- `@details`
- `@note`
- `@see`
- `@copyright`

#### Example

```cpp
/**
 * @ingroup geometry
 * @file polygon.h
 * @authors Alice Brown, Carlos Diaz
 * @brief Defines the Polygon class for representing simple 2-D polygons.
 * @details This file contains the Polygon class, which provides methods for adding vertices, computing area, and checking point containment.
 * @note The Polygon class assumes vertices are provided in counter-clockwise order.
 * @see https://en.wikipedia.org/wiki/Polygon
 * @copyright 2025 Geometry Toolkit
 */
```

**[Table of Contents](#table-of-contents)**

### Namespaces

Use a **Doxygen block** above each namespace declaration in header files to document the namespace's purpose and contents.

#### Relevant commands

- `@ingroup`
- `@namespace`
- `@brief`
- `@details`
- `@note`
- `@see`

#### Example

```cpp
/**
 * @ingroup math
 * @namespace constants
 * @brief Defines mathematical constants used throughout the project.
 */
namespace constants {}
```

**[Table of Contents](#table-of-contents)**

### Classes & Structs

Use a **Doxygen block** above each class or struct declaration in header files to document its purpose, behavior, and any important details. This applies to both classes and structs.

#### Relevant commands

- `@ingroup`
- `@class`
- `@struct`
- `@brief`
- `@details`
- `@tparam`
- `@note`
- `@bug`
- `@see`

#### Example

```cpp
/**
 * @ingroup geometry
 * @struct Point2
 * @brief Lightweight 2-D point with double precision.
 */
struct Point2 {
    double x {0.0}; ///< X coordinate
    double y {0.0}; ///< Y coordinate
};

/**
 * @ingroup geometry
 * @class Polygon
 * @brief Simple 2-D polygon representation.
 * @details Stores vertices in counter-clockwise order.
 * @note Capacity is fixed at construction.
 * @bug AddVertex does not check for self-intersection.
 */
class Polygon {
public:
    /**
     * @brief Constructs a Polygon with a maximum number of vertices.
     * @param[in] max_vertices  Maximum number of vertices allowed.
     * @throws std::length_error  If max_vertices is zero.
     */
    Polygon(std::size_t max_vertices);

    /**
     * @brief Adds a vertex to the polygon.
     * @param[in] p  New vertex in world coordinates.
     * @return Index of the inserted vertex.
     * @throws std::length_error If max_vertices reached.
     */
    std::size_t Polygon::addVertex(const Point2& p);

    /**
     * @brief Computes the signed area of the polygon.
     * @details Uses the Shoelace formula to compute the area:
     * @formula{polygon-area; A = \frac{1}{2} \sum_{i=1}^{n} (x_i y_{i+1} - x_{i+1} y_i)}
     * where:
     * @symtable
     * @symrow{A; is the signed area of the polygon; \meter\squared}
     * @symrow{n; is the number of vertices; 1}
     * @symrow{x_i, y_i; are the coordinates of vertex i; \meter}
     * @symrow{x_{n+1}, y_{n+1}; are the coordinates of vertex 1 (wrap-around); \meter}
     * @endsymtable
     * @note The area is positive if vertices are in counter-clockwise order. 
     * @return The signed area of the polygon.
     */
    double area() const;

private:
    std::vector<Point2> vertices_; ///< Vertices in counter-clockwise order.
};
```

**[Table of Contents](#table-of-contents)**

### Functions & Methods

Use a **Doxygen block** above each public function or method declaration in header files. This applies to both free functions and member functions of classes or structs.

#### Relevant commands

- `@brief`
- `@param[in]` **or** `param[out]` **or** `param[in,out]`
- `@return`
- `@details`
- `@tparam`
- `@throws`
- `@note`
- `@bug`
- `@see`

#### Example

```cpp
/**
 * @brief Adds a vertex to the polygon.
 * @param[in] p  New vertex in world coordinates.
 * @return Index of the inserted vertex.
 * @throws std::length_error If max_vertices reached.
 */
std::size_t Polygon::addVertex(const Point2& p);
```

**[Table of Contents](#table-of-contents)**

### Member Variables

Use inline comments with `///<` for one-line descriptions of data members. This applies to both classes and structs.

#### Example

```cpp
std::vector<Point2> vertices_; ///< Vertices in counter-clockwise order.
```

**[Table of Contents](#table-of-contents)**

### Constants

Use inline comments with `///<` to document constants and their purpose.

#### Example

```cpp
constexpr double kPi = 3.141592653589793;    ///< Circle ratio @unitb{radians}.
inline constexpr Point2 kOrigin {0.0, 0.0};  ///< Reference point (0,0).
```

**[Table of Contents](#table-of-contents)**

### Enums

Use a **Doxygen block** above each enum declaration in header files to document the enum type and its enumerators. Each enumerator should have an inline comment describing its purpose.

#### Relevant commands

- `@ingroup`
- `@enum`
- `@brief`
- `@details`
- `@note`
- `@bug`
- `@see`

#### Example

```cpp
/**
 * @ingroup geometry
 * @enum Axis
 * @brief Principal 3-D axes.
 */
enum class Axis {
    kX, ///< X-axis
    kY, ///< Y-axis
    kZ  ///< Z-axis
};
```

**[Table of Contents](#table-of-contents)**

### Groups

Use **Doxygen groups** to organize related namespaces, classes, and functions into logical modules.

Large groups must be defined in their own file (e.g., `math.dox`, `geometry.dox`) to avoid cluttering header files. These files should be placed in the `docs/` directory or one of its subdirectories.

#### Relevant commands

- `@defgroup`
- `ingroup`
- `@brief`
- `@details`
- `@copydoc`
- `@see`

#### Example

```cpp
/**
 * @defgroup geometry Geometry
 * @ingroup math
 * @brief Geometry module for 2D and 3D shapes.
 */
```

**[Table of Contents](#table-of-contents)**

## Generating Doxygen Documentation

Use the `Doxyfile` to configure Doxygen settings like input/output directories, file patterns, and more.

Use the `DoxygenLayout.xml` file to customize the layout of the generated documentation.

To generate the documentation, follow these steps:
1. Ensure [Doxygen](https://www.doxygen.nl/) is installed.
2. From the project root, run:
   ```bash
   doxygen Doxyfile
   ```
3. The generated HTML and/or LaTeX documentation will appear in the output directory specified in the `Doxyfile`.

**[Table of Contents](#table-of-contents)**
