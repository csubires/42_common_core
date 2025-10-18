# C++ Module 01 Project Summary

## Project Overview
This module focuses on fundamental C++ memory management concepts, pointer/reference mechanics, and advanced function handling. It consists of six exercises that progressively introduce critical C++ features including dynamic memory allocation, references, pointers to member functions, and switch statements while building on the OOP foundation from Module 00.

## Key Features and Requirements

### Compilation and Standards
- Must compile with `c++ -Wall -Wextra -Werror -std=c++98`
- C++98 standard compliance required
- Modern C++ features (C++11+) remain forbidden

### Memory Management Focus
- Explicit focus on stack vs heap allocation decisions
- Memory leak prevention when using `new` keyword
- Proper cleanup of dynamically allocated objects
- Array allocation and deallocation practices

### Restrictions
- `using namespace` and `friend` keywords remain forbidden
- STL containers and algorithms still prohibited until Modules 08-09
- External libraries including Boost forbidden
- Specific forbidden functions: `sprintf()`, `*alloc()`, `free()`
- In Exercise 04: `std::string::replace` is explicitly forbidden

### Code Structure
- Orthodox Canonical Form required from Module 02 onward
- Header files must include necessary dependencies with include guards
- Function implementations in header files result in zero points
- Clean, readable code expected despite no enforced style guide

## Exercise Breakdown

### Exercise 00: BraiiiiinnnzzzZ
- **Objective**: Implement Zombie class with stack vs heap allocation understanding
- **Key Concepts**:
  - Class implementation with private attributes and member functions
  - Stack allocation (`randomChump`) vs heap allocation (`newZombie`)
  - Destructor implementation for resource cleanup
  - Memory management principles

### Exercise 01: Moar brainz!
- **Objective**: Create zombie horde with single allocation
- **Key Concepts**:
  - Array allocation with `new Zombie[N]`
  - Object initialization in allocated arrays
  - Memory leak detection and prevention
  - Bulk object management

### Exercise 02: HI THIS IS BRAIN
- **Objective**: Demonstrate pointer and reference mechanics
- **Key Concepts**:
  - Pointer declaration and usage
  - Reference declaration and usage
  - Memory address comparison
  - Value access through different mechanisms

### Exercise 03: Unnecessary violence
- **Objective**: Implement weapon system with reference vs pointer usage
- **Key Concepts**:
  - Class composition and aggregation
  - Reference members (HumanA) vs pointer members (HumanB)
  - Const member functions and return by const reference
  - Object lifetime considerations

### Exercise 04: Sed is for losers
- **Objective**: Create file search and replace utility
- **Key Concepts**:
  - File I/O using C++ streams
  - String manipulation without `replace()` function
  - Error handling for file operations
  - C++ standard library usage for file management

### Exercise 05: Harl 2.0
- **Objective**: Implement complaint system using pointers to member functions
- **Key Concepts**:
  - Pointers to member functions syntax and usage
  - Function pointer arrays/maps
  - Avoiding conditional chains with function pointers
  - Class method organization

### Exercise 06: Harl filter
- **Objective**: Create log level filtering system
- **Key Concepts**:
  - Switch statement implementation
  - Log level hierarchies and filtering
  - Command-line argument processing
  - Program behavior based on input parameters

## Technical Skills Developed
- Memory allocation strategies (stack vs heap)
- Pointer and reference mechanics and differences
- Dynamic array allocation and management
- File I/O operations using C++ streams
- Pointers to member functions for dynamic dispatch
- Switch statement control flow
- Object composition and aggregation patterns
- Const correctness in member functions
- Memory leak prevention and detection

## Learning Outcomes
- Deep understanding of C++ memory management model
- Proficiency with pointers, references, and their appropriate use cases
- Ability to implement complex class relationships
- Skills in file manipulation using C++ standard library
- Advanced function handling techniques
- Practical application of control flow statements
- Foundation for more advanced C++ concepts in subsequent modules

This module provides essential skills for effective C++ programming with particular emphasis on memory management and advanced language features that distinguish C++ from C programming paradigms.
