# C++ Module 04 Project Summary

## Project Overview
This module focuses on advanced object-oriented programming concepts, specifically subtype polymorphism, abstract classes, and interface implementation. The exercises progress from basic polymorphism to complex interface-based systems, emphasizing proper memory management, deep copying, and abstract class design patterns in C++98.

## Key Features and Requirements

### Core Concepts
- **Subtype Polymorphism**: Virtual functions and dynamic binding
- **Abstract Classes**: Pure virtual functions and non-instantiable classes
- **Interfaces**: Implementation through pure abstract classes
- **Memory Management**: Deep copying, proper resource cleanup

### Orthodox Canonical Form
- Required for all concrete classes
- Default constructor, copy constructor, copy assignment operator, destructor
- Deep copy implementation for classes with pointer members

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

### Exercise 00: Polymorphism
**Objective**: Implement basic polymorphism with virtual functions
- **Key Classes**:
  - `Animal` (base class with virtual functions)
  - `Dog` and `Cat` (derived classes)
  - `WrongAnimal` and `WrongCat` (non-virtual demonstration)
- **Key Functions**:
  - `makeSound()` - Virtual function demonstrating polymorphism
  - `getType()` - Accessor for type information
- **Technical Focus**: Virtual function tables, dynamic binding, proper inheritance

### Exercise 01: I don't want to set the world on fire
**Objective**: Implement deep copying and complex memory management
- **New Class**: `Brain` with array of 100 strings
- **Enhanced Classes**: `Dog` and `Cat` with Brain* attributes
- **Key Features**:
  - Dynamic Brain allocation in constructors
  - Proper cleanup in destructors
  - Deep copy implementation
  - Array of Animal pointers with polymorphic deletion
- **Technical Focus**: Deep vs shallow copying, memory leak prevention, polymorphic arrays

### Exercise 02: Abstract class
**Objective**: Convert Animal class to abstract base class
- **Modification**: Make Animal non-instantiable using pure virtual functions
- **Key Change**: `makeSound()` becomes pure virtual (= 0)
- **Technical Focus**: Abstract class design, interface enforcement, pure virtual functions

### Exercise 03: Interface & recap
**Objective**: Implement complex interface-based system with multiple classes
- **Abstract Classes**:
  - `AMateria` (abstract materia base)
  - `ICharacter` (character interface)
  - `IMateriaSource` (materia source interface)
- **Concrete Classes**:
  - `Ice` and `Cure` (materia implementations)
  - `Character` (implements ICharacter)
  - `MateriaSource` (implements IMateriaSource)
- **Key Functions**:
  - `clone()` - Virtual copy constructor pattern
  - `use(ICharacter&)` - Materia effect application
  - `equip()`, `unequip()`, `use()` - Inventory management
  - `learnMateria()`, `createMateria()` - Materia factory pattern

## Important Functions and Features

### Polymorphic Functions
- `makeSound()` - Virtual function demonstrating runtime polymorphism
- `clone()` - Virtual copy constructor for polymorphic copying
- `use()` - Virtual function for behavior application

### Memory Management Functions
- Constructors with dynamic allocation
- Destructors with proper cleanup
- Deep copy implementations in copy constructors and assignment operators
- Inventory management with leak prevention

### Interface Functions
- `equip(AMateria* m)` - Add materia to inventory
- `unequip(int idx)` - Remove materia without deletion
- `use(int idx, ICharacter& target)` - Use specific materia
- `learnMateria(AMateria*)` - Learn materia template
- `createMateria(string const& type)` - Create materia from learned template

### Accessor Functions
- `getType()` - Type information retrieval
- `getName()` - Character name access

## Technical Concepts Emphasized

### Polymorphism Mechanisms
- Virtual function tables and dynamic dispatch
- Pure virtual functions for interface definition
- Abstract base class design
- Runtime type behavior

### Memory Management Patterns
- RAII (Resource Acquisition Is Initialization)
- Deep copy implementation
- Polymorphic object arrays
- Proper deletion through base class pointers

### Design Patterns
- **Factory Pattern**: MateriaSource creating materials
- **Prototype Pattern**: clone() method for polymorphic copying
- **Interface Pattern**: Pure abstract classes as interfaces
- **Inventory Pattern**: Limited slot management system

### Class Relationships
```
AMateria (Abstract)
├── Ice (Concrete)
└── Cure (Concrete)

ICharacter (Interface)
└── Character (Implementation)

IMateriaSource (Interface)
└── MateriaSource (Implementation)
```

## Learning Outcomes
- Mastery of subtype polymorphism and virtual functions
- Implementation of abstract classes and interfaces
- Advanced memory management with polymorphic objects
- Deep copy implementation for complex class hierarchies
- Interface-based design patterns
- Factory and prototype pattern implementation
- Comprehensive resource management in polymorphic systems

This module provides essential skills in advanced C++ object-oriented programming, focusing on the powerful combination of polymorphism, abstract classes, and proper resource management that forms the foundation for complex software systems.
