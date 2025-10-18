# C++ Module 02 Project Summary

## Project Overview
This module focuses on ad-hoc polymorphism, operator overloading, and the Orthodox Canonical Form for C++ classes. The central theme is implementing a fixed-point number class that demonstrates advanced C++ features while maintaining strict canonical form requirements. The module progresses from basic class structure to complex mathematical operations and practical geometric applications.

## Key Features and Requirements

### Orthodox Canonical Form Mandatory
- **Required for all classes from Module 02 onward**
- Must implement four essential member functions:
  - Default constructor
  - Copy constructor
  - Copy assignment operator
  - Destructor
- Class code must be split between header (.hpp) and implementation (.cpp) files

### Compilation and Standards
- Compile with `c++ -Wall -Wextra -Werror -std=c++98`
- C++98 standard compliance required
- Modern C++ features (C++11+) forbidden

### Restrictions
- `using namespace` and `friend` keywords forbidden
- STL containers and algorithms prohibited until Modules 08-09
- External libraries including Boost forbidden
- Specific forbidden functions: `*printf()`, `*alloc()`, `free()`

### Technical Requirements
- Memory leak prevention with proper `new`/`delete` usage
- Header files must include dependencies with include guards
- No function implementations in header files (except templates)
- Clean, readable code expected

## Exercise Breakdown

### Exercise 00: My First Class in Orthodox Canonical Form
- **Objective**: Implement basic Fixed-point number class in Orthodox Canonical Form
- **Key Features**:
  - Private integer to store fixed-point value
  - Static constant integer for fractional bits (value: 8)
  - Basic accessor methods: `getRawBits()` and `setRawBits()`
- **Technical Focus**: Orthodox Canonical Form implementation, basic class structure

### Exercise 01: Towards a more useful fixed-point number class
- **Objective**: Enhance Fixed class with conversion capabilities and output streaming
- **Key Features**:
  - Constructors from integer and floating-point types
  - Conversion methods: `toFloat()` and `toInt()`
  - Operator overloading: insertion operator (`<<`) for output streaming
- **Allowed Function**: `roundf` from `<cmath>`
- **Technical Focus**: Type conversion, operator overloading, stream manipulation

### Exercise 02: Now we're talking
- **Objective**: Implement comprehensive operator overloading for Fixed class
- **Key Features**:
  - **Comparison operators**: `>`, `<`, `>=`, `<=`, `==`, `!=`
  - **Arithmetic operators**: `+`, `-`, `*`, `/`
  - **Increment/Decrement operators**: pre/post `++`, pre/post `--`
  - **Static utility functions**: `min()` and `max()` with const and non-const variants
- **Technical Focus**: Complete operator overloading, static member functions, epsilon precision handling

### Exercise 03: BSP (Binary Space Partitioning)
- **Objective**: Implement point-in-triangle detection using Fixed class
- **Key Features**:
  - `Point` class in Orthodox Canonical Form with Fixed const attributes
  - `bsp()` function to determine if point is inside triangle
  - Geometric algorithm implementation
- **Technical Focus**: Practical application of Fixed class, geometric algorithms, const correctness

## Important Functions and Operations

### Fixed Class Core Functions
- Constructors: default, from int, from float, copy
- Conversion methods: `toInt()`, `toFloat()`
- Accessors: `getRawBits()`, `setRawBits()`
- Operator overloads: arithmetic, comparison, increment/decrement
- Static functions: `min()`, `max()`

### Point Class Functions
- Constructors for 2D point creation
- Coordinate access methods
- Orthodox Canonical Form compliance

### Utility Functions
- `bsp()` - Binary Space Partitioning for point-in-triangle test
- Operator `<<` overload for Fixed class output

## Technical Concepts Emphasized

### Fixed-Point Arithmetic
- Representation of fractional numbers using integer storage
- Balance between performance, accuracy, and precision
- Applications in graphics, sound processing, scientific computing

### Operator Overloading
- Comprehensive mathematical operator implementation
- Pre and post increment/decrement semantics
- Comparison operators for relational operations
- Stream insertion for output formatting

### Const Correctness
- Const member functions and parameters
- Const and non-const overloaded functions
- Immutable attributes in Point class

### Geometric Algorithms
- Point-in-triangle testing using BSP
- Coordinate system manipulation
- Fixed-point precision in geometric calculations

## Learning Outcomes
- Mastery of Orthodox Canonical Form for C++ classes
- Comprehensive understanding of operator overloading
- Implementation of fixed-point arithmetic systems
- Application of mathematical classes to practical problems
- Advanced const correctness and function overloading techniques
- Geometric algorithm implementation using custom number types

This module provides essential skills in class design, operator overloading, and mathematical abstraction that form the foundation for advanced C++ development in subsequent modules.
