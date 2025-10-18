# C++ Module 05 Project Summary

## Project Overview
This module focuses on exception handling and class hierarchy design through a bureaucratic system simulation. The exercises progress from basic exception handling to complex form processing systems, emphasizing proper error management, abstract class design, and factory patterns. The project demonstrates robust C++ programming practices with comprehensive exception safety.

## Key Features and Requirements

### Exception Handling Focus
- Custom exception classes for different error scenarios
- Try-catch block implementation
- Exception safety and proper error propagation
- Grade validation with specific exception types

### Class Hierarchy and Design
- Orthodox Canonical Form for all main classes
- Abstract base class implementation
- Concrete class specialization
- Factory pattern for object creation

### Compilation and Standards
- Compile with `c++ -Wall -Wextra -Werror -std=c++98`
- C++98 standard compliance
- Modern C++ features forbidden

### Restrictions
- `using namespace` and `friend` keywords forbidden
- STL containers and algorithms prohibited until Modules 08-09
- External libraries including Boost forbidden
- Memory leak prevention required

## Exercise Breakdown

### Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!
**Objective**: Implement Bureaucrat class with exception handling
- **Key Class**: `Bureaucrat`
- **Attributes**:
  - Constant name
  - Grade (1-150 range)
- **Exception Classes**:
  - `Bureaucrat::GradeTooHighException`
  - `Bureaucrat::GradeTooLowException`
- **Key Functions**:
  - `incrementGrade()` - Increase grade (lower number)
  - `decrementGrade()` - Decrease grade (higher number)
  - `getName()`, `getGrade()` - Accessors
  - Operator `<<` overload for output

### Exercise 01: Form up, maggots!
**Objective**: Implement Form class with signing mechanism
- **Key Class**: `Form`
- **Attributes**:
  - Constant name
  - Boolean signed status
  - Constant grade required to sign
  - Constant grade required to execute
- **Exception Classes**:
  - `Form::GradeTooHighException`
  - `Form::GradeTooLowException`
- **Key Functions**:
  - `beSigned(Bureaucrat&)` - Attempt to sign form
  - `isSigned()`, `getGradeToSign()`, `getGradeToExecute()` - Accessors
  - Bureaucrat::`signForm(Form&)` - Form signing interface

### Exercise 02: No, you need form 28B, not 28C...
**Objective**: Create form hierarchy with specific behaviors
- **Abstract Class**: `AForm` (renamed from Form)
- **Concrete Form Classes**:
  - `ShrubberyCreationForm`: File creation with ASCII trees
  - `RobotomyRequestForm`: 50% success rate robotomy
  - `PresidentialPardonForm`: Presidential pardon notification
- **Key Functions**:
  - `execute(Bureaucrat const& executor)` - Form execution with validation
  - Bureaucrat::`executeForm(AForm const& form)` - Execution interface
- **Grade Requirements**:
  - Shrubbery: sign 145, exec 137
  - Robotomy: sign 72, exec 45
  - Presidential: sign 25, exec 5

### Exercise 03: At least this beats coffee-making
**Objective**: Implement Intern class with form creation factory
- **Key Class**: `Intern`
- **Factory Method**: `makeForm(string formName, string target)`
- **Functionality**: Creates appropriate form based on name
- **Design Constraint**: Avoid excessive if/else chains
- **Output**: Creation messages and error handling

## Important Functions and Features

### Exception Handling Functions
- Custom exception constructors and what() methods
- Grade validation in constructors and modifier methods
- Try-catch blocks for exception safety

### Form Processing Functions
- `beSigned()` - Form signing with grade validation
- `execute()` - Form execution with status and grade checks
- `signForm()` - Bureaucrat-level signing interface
- `executeForm()` - Bureaucrat-level execution interface

### Factory Pattern Functions
- `makeForm()` - Dynamic form creation based on string input
- Target initialization for created forms
- Error handling for invalid form names

### Accessor and Utility Functions
- Getters for all class attributes
- Operator `<<` overloads for consistent output formatting
- Status checking methods

## Technical Concepts Emphasized

### Exception Safety
- Resource management during exceptions
- Proper exception propagation
- Custom exception hierarchy
- Graceful error recovery

### Class Hierarchy Design
```
AForm (Abstract)
├── ShrubberyCreationForm (Concrete)
├── RobotomyRequestForm (Concrete)
└── PresidentialPardonForm (Concrete)
```

### Factory Pattern Implementation
- String-based object creation
- Avoidance of complex conditional logic
- Extensible design for new form types

### Const Correctness
- Constant attributes for immutability
- Const member functions
- Reference parameters for efficiency

### Validation Systems
- Grade range validation (1-150)
- Signing privilege checks
- Execution privilege verification
- Form status validation

## Learning Outcomes
- Comprehensive exception handling implementation
- Abstract class design and concrete class specialization
- Factory pattern application for object creation
- Complex validation systems with multiple constraints
- Robust error handling and user feedback
- Hierarchical class design with proper encapsulation
- Memory management in exception-prone environments

This module provides essential skills in building robust, exception-safe C++ applications with complex business logic and validation requirements, preparing students for real-world software development scenarios.
