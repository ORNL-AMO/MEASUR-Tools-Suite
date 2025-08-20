# Documentation

This project uses [Doxygen](https://www.doxygen.nl/) to generate documentation from annotated source code. Doxygen comments are used to describe the purpose, behavior, and usage of classes, functions, and other entities in the codebase. Follow these guidelines to ensure your code is well-documented and easy to understand. Always use `@` for Doxygen commands and tags, as this is the standard convention in this project.


## Doxygen Commands

All commands start with `@`. 

Some commands have one or more arguments. Each argument has a certain range:
- If `<sharp>` braces are used the argument is a single word.
- If `(round)` braces are used the argument extends until the end of the line on which the command was found.
- If `{curly}` braces are used the argument extends until the next paragraph. Paragraphs are delimited by a blank line or by a section indicator.

Commands:
- `@file <name>`
- `@authors { list of authors }`
- `@ingroup (<group-name>)`
- `@defgroup <name> (group title)`
- `@namespace <name>`
- `@class <name>`
- `@struct <name>`
- `@enum <name>`
- `@brief { brief description }`
- `@details { detailed description }`
- `@param[<dir>] <parameter-name> { parameter description }`
- `@tparam <template-parameter-name> { description }`
- `@return { description of the return value }`
- `@throws <exception-object> { exception description }`
- `@note { text }`
- `@bug { bug description }`
- `@see { references }`                                       
- `@def <name>`                                      
- `@copyright { copyright description }`


## Custom Commands

- `@math{<math expression>}`
- `@unit{<unit expression>}`
- `@formula{<label>; <equation>}`
- `symbol{<symbol>; <description>}`


## Generating Doxygen Documentation

1. Ensure [Doxygen](https://www.doxygen.nl/) is installed on your system.
2. From the project root, run:
   ```bash
   doxygen Doxyfile
   ```
3. The generated HTML and/or LaTeX documentation will appear in the output directory specified in your `Doxyfile`.

For more details on configuring or customizing Doxygen output, see the official [Doxygen manual](https://www.doxygen.nl/manual/index.html) or review the `Doxyfile` in the project root.


## Documenting Code

When documenting code, use Doxygen comments to describe the purpose and behavior of classes, functions, and other entities. Follow these guidelines to ensure your documentation is clear, consistent, and useful.


### Math

Use the `@math{<math expression>}` command to to write LaTeX-style mathematical expressions in your documentation.

#### Example

```cpp
/**
 * The speed of light in water is often denoted as @math{C_w}.
 */
```


### Units

Use the `@unit{<unit expression>}` command to document units. The `@unit{}` command uses the siunitx package to format units in LaTeX.

#### Example

```cpp
/**
 * The speed of light in water is often denoted as @math{C_w} and is approximately 2.25 @unit{\meter\per\second}.
 */
```


### Formulas

Use the `@formula{<label>; <equation>}` command to document formulas. The command takes 2 arguments, separated by `;`:
1. A label for the formula, which can be used to reference the formula in the documentation by using `\eqref{eq:formula-label}`.
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


### Symbols

Use the `symbol{<symbol>; <description>}` command to document mathematical symbols. This command takes two arguments, separated by `;`:
1. The symbol itself, written in LaTeX syntax.
2. A description of the symbol.

#### Example

```cpp
/**
 * The area of a circle can be computed using the formula:
 * @formula{circle-area; A = \pi r^2}
 * where:
 * - @symbol{A; is the area of the circle}
 * - @symbol{\pi; is the mathematical constant pi}
 * - @symbol{r; is the radius of the circle}
 */
```


### Files

Use a **Doxygen block** at the very top of each header file to document the file's purpose, authors, and any relevant notes.

#### Required tags

`@file`, `@authors`, `@ingroup`, `@brief`

#### Optional tags

`@details`, `@note`, `@bug`, `@see`, `@copyright`

#### Example

```cpp
/**
 * @file polygon.h
 * @authors Alice Brown, Carlos Diaz
 * @ingroup geometry
 * @brief Defines the Polygon class for representing simple 2-D polygons.
 * @details This file contains the Polygon class, which provides methods for adding vertices, computing area, and checking point containment.
 * @note The Polygon class assumes vertices are provided in counter-clockwise order.
 * @bug Self-intersection checks are not implemented.
 * @see https://en.wikipedia.org/wiki/Polygon
 * @copyright 2025 Geometry Toolkit
 */
```


### Namespaces

Use a **Doxygen block** above each namespace declaration in header files to document the namespace's purpose and contents.

#### Required tags

`@namespace`, `@ingroup`, `@brief`

#### Optional tags

`@details`, `@note`, `@see`

#### Example

```cpp
/**
 * @namespace constants
 * @ingroup math
 * @brief Defines mathematical constants used throughout the project.
 */
namespace constants {}
```


### Classes & Structs

Use a **Doxygen block** above each class or struct declaration in header files to document its purpose, behavior, and any important details. This applies to both classes and structs.

#### Required tags

`@class` **or** `@struct`, `@ingroup`, `@brief`

#### Optional tags

`@details`, `@tparam`, `@note`, `@bug`, `@see`

#### Example

```cpp
/**
 * @struct Point2
 * @ingroup geometry
 * @brief Lightweight 2-D point with double precision.
 */
struct Point2 {
    double x {0.0}; ///< X coordinate
    double y {0.0}; ///< Y coordinate
};

/**
 * @class Polygon
 * @ingroup geometry
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
     * - @symbol{A; is the signed area}
     * - @symbol{x_i \& y_i; are the coordinates of the i-th vertex}
     * - @symbol{n; is the number of vertices}
     * @note The area is positive if vertices are in counter-clockwise order. 
     * @return The signed area of the polygon.
     */
    double area() const;

private:
    std::vector<Point2> vertices_; ///< Vertices in counter-clockwise order.
};
```


### Functions & Methods

Use a **Doxygen block** above each public function or method declaration in header files. This applies to both free functions and member functions of classes or structs.

#### Required tags

`@brief`, `@param[in]` **or** `param[out]` **or** `param[in,out]`, `@return` (if applicable)

#### Optional tags

`@details`, `@tparam`, `@throws`, `@note`, `@bug`, `@see`

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


### Member Variables

Use inline comments with `///<` for one-line descriptions of data members. This applies to both classes and structs.

#### Example

```cpp
std::vector<Point2> vertices_; ///< Vertices in counter-clockwise order.
```


### Constants

Use inline comments with `///<` to document constants and their purpose.

#### Example

```cpp
constexpr double kPi = 3.141592653589793;    ///< Circle ratio @unit{radians}.
inline constexpr Point2 kOrigin {0.0, 0.0};  ///< Reference point (0,0).
```


### Enums

Use a **Doxygen block** above each enum declaration in header files to document the enum type and its enumerators. Each enumerator should have an inline comment describing its purpose.

#### Required tags

`@enum`, `@ingroup`, `@brief`

#### Optional tags

`@details`, `@note`, `@bug`, `@see`

#### Example

```cpp
/**
 * @enum Axis
 * @ingroup geometry
 * @brief Principal 3-D axes.
 */
enum class Axis {
    kX, ///< X-axis
    kY, ///< Y-axis
    kZ  ///< Z-axis
};
```


### Groups

Use **Doxygen groups** to organize related namespaces, classes, and functions into logical modules.

Place a **Doxygen block** in a central location (e.g., `mainpage.dox`) to define the group and provide an overview. Each related code element should reference the group using the `@ingroup` command in its own documentation block.

#### Required tags

`@defgroup`, `@brief`

#### Optional tags

`@details`, `@note`, `@see`

#### Example

```cpp
/**
 * @defgroup geometry Geometry
 * @brief Geometry module for 2D and 3D shapes.
 */
```




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
