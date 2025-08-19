# Documentation

This project uses [Doxygen](https://www.doxygen.nl/) to generate documentation from annotated source code. Doxygen comments are used to describe the purpose, behavior, and usage of classes, functions, and other entities in the codebase. Follow these guidelines to ensure your code is well-documented and easy to understand. Always use `@` for Doxygen commands and tags, as this is the standard convention in this project.


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




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
