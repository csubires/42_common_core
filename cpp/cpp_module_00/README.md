# C++ Module 00 Project Summary

## Project Overview
This module serves as an introduction to fundamental C++ concepts and Object-Oriented Programming principles. It consists of three progressively challenging exercises designed to transition students from C to C++ programming paradigms while enforcing specific coding standards and restrictions.

## Key Features and Requirements

### Compilation and Standards
- Must compile with `c++ -Wall -Wextra -Werror -std=c++98`
- Compliance with C++98 standard required
- Modern C++ features (C++11 and beyond) are forbidden

### Code Structure and Style
- Exercise directories follow `ex00`, `ex01`, `exn` naming convention
- Class names use UpperCamelCase format
- File naming corresponds to class names (e.g., `ClassName.hpp`, `ClassName.cpp`)
- No enforced coding style, but clean, readable code is expected
- Header files must include necessary dependencies and implement include guards

### Restrictions
- `using namespace` and `friend` keywords are forbidden
- STL containers and algorithms are prohibited until Modules 08-09
- External libraries (including Boost) are forbidden
- Specific forbidden functions: `sprintf()`, `*alloc()`, `free()`
- Dynamic allocation is restricted in certain exercises
- Function implementations in header files result in zero points

### Design Requirements
- Memory leaks must be avoided when using `new`
- Orthodox Canonical Form required for classes from Module 02 onward
- Each header file must be independently usable

## Exercise Breakdown

### Exercise 00: Megaphone
- **Objective**: Create a program that converts input text to uppercase
- **Key Features**:
  - Handles command-line arguments
  - Outputs uppercase text
  - Provides default feedback noise when no arguments given
- **Technical Focus**: Basic C++ I/O, string manipulation

### Exercise 01: My Awesome PhoneBook
- **Objective**: Implement a simple phonebook management system
- **Key Classes**:
  - `PhoneBook`: Manages up to 8 contacts using an array
  - `Contact`: Stores individual contact information
- **Functionality**:
  - ADD: Save new contacts with validation (no empty fields)
  - SEARCH: Display contacts in formatted columns with truncation
  - EXIT: Terminate program
- **Technical Focus**: Classes, member functions, formatted output, input validation

### Exercise 02: The Job Of Your Dreams
- **Objective**: Recreate a missing implementation file (`Account.cpp`) based on existing header and log files
- **Key Challenge**: Reverse engineering class implementation from behavior patterns
- **Technical Focus**: Class implementation, static members, const correctness, debugging techniques

## Learning Outcomes
- Transition from C to C++ programming mindset
- Understanding of basic OOP concepts (classes, encapsulation)
- Proper use of namespaces, member functions, and initialization lists
- Formatted I/O operations using C++ streams
- Memory management principles in C++
- Code organization and header file management

This module establishes the foundation for C++ development while enforcing good programming practices and preparing students for more advanced Object-Oriented Programming concepts in subsequent modules.
