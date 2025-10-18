# C++ Module 07 Project Summary

## Project Overview
This module introduces C++ templates, focusing on generic programming and template metaprogramming. The exercises progress from basic function templates to more complex class templates, demonstrating how to write type-agnostic code that works with any data type while maintaining type safety and performance. The module emphasizes template syntax, generic algorithms, and custom container implementation.

## Key Features and Requirements

### Template Programming Focus
- Function templates for generic algorithms
- Class templates for generic data structures
- Template specialization and instantiation
- Generic programming principles

### Orthodox Canonical Form
- Required for class templates (Exercise 02)
- Default constructor, copy constructor, copy assignment operator, destructor
- Proper resource management in template classes

### Compilation and Standards
- Compile with `c++ -Wall -Wextra -Werror -std=c++98`
- C++98 standard compliance
- Template definitions in header files

### Restrictions
- `using namespace` and `friend` keywords forbidden
- STL containers and algorithms prohibited until Modules 08-09
- External libraries including Boost forbidden
- Preventive allocation forbidden (must use `new[]`)

## Exercise Breakdown

### Exercise 00: Start with a few functions
**Objective**: Implement basic function templates
- **Template Functions**:
  - `swap(T& a, T& b)` - Swaps two values of any type
  - `min(const T& a, const T& b)` - Returns the smaller value (returns second if equal)
  - `max(const T& a, const T& b)` - Returns the larger value (returns second if equal)
- **Requirements**:
  - Both parameters must be of the same type
  - Types must support comparison operators
  - Templates defined in header files
  - No return for swap, appropriate returns for min/max

### Exercise 01: Iter
**Objective**: Implement function template for array iteration
- **Template Function**: `iter(T* array, size_t length, void (*func)(T&))`
- **Parameters**:
  - Array address (pointer to first element)
  - Array length
  - Function pointer to apply to each element
- **Features**:
  - Works with any array type
  - Applies function to each element
  - Third parameter can be instantiated function template
  - Comprehensive testing required

### Exercise 02: Array
**Objective**: Implement generic array class template
- **Class Template**: `Array<T>`
- **Constructors**:
  - Default: Creates empty array
  - Parameterized: Creates array of n default-initialized elements
  - Copy constructor and assignment operator (deep copy required)
- **Key Features**:
  - Subscript operator `[]` with bounds checking
  - `size()` member function returning element count
  - Exception throwing for out-of-bounds access
  - Proper memory management with `new[]` and `delete[]`
- **Memory Management**:
  - No preventive allocation allowed
  - Never access non-allocated memory
  - Copy operations must maintain separate memory

## Important Functions and Features

### Function Templates (Exercise 00)
- **swap**: In-place value exchange using references
- **min**: Comparative function with tie-breaking to second parameter
- **max**: Comparative function with tie-breaking to second parameter

### Iteration Template (Exercise 01)
- **iter**: Generic array processor applying functions element-wise
- **Function Pointer Parameter**: Flexible operation application
- **Type Agnostic**: Works with any data type

### Array Class Template (Exercise 02)
- **Element Access**: `operator[]` with bounds validation
- **Capacity Management**: `size()` method for element count
- **Memory Operations**: Proper allocation/deallocation with `new[]/delete[]`
- **Copy Semantics**: Deep copy implementation
- **Exception Safety**: std::exception for invalid access

## Technical Concepts Emphasized

### Template Syntax and Semantics
- Template parameter declaration
- Template function definition
- Template class implementation
- Template instantiation

### Generic Programming Principles
- Type-independent algorithms
- Compile-time polymorphism
- Code reusability across types
- Performance optimization through templates

### Memory Management in Templates
- Resource allocation in class templates
- Deep copy implementation for template classes
- Exception safety in template code
- Bounds checking and validation

### Operator Overloading in Templates
- Subscript operator for array access
- Comparison operators for min/max functions
- Assignment operator for template classes

## Learning Outcomes
- Mastery of C++ template syntax and semantics
- Implementation of generic algorithms and data structures
- Understanding of template instantiation and specialization
- Development of type-safe generic code
- Memory management in template classes
- Exception handling in generic programming
- Compile-time polymorphism techniques

This module provides essential skills in generic programming, teaching students how to write flexible, reusable code that works with any data type while maintaining C++'s performance and type safety benefits. The template knowledge gained here forms the foundation for understanding and effectively using the Standard Template Library in subsequent modules.
