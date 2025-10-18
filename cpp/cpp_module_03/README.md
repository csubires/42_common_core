# C++ Module 03 Project Summary

## Project Overview
This module introduces inheritance in C++ through the implementation of a robot hierarchy. The project progresses from a base class to multiple derived classes, demonstrating fundamental object-oriented programming concepts including inheritance, constructor/destructor chaining, and multiple inheritance with virtual base classes. The exercises build upon each other to create a comprehensive class hierarchy.

## Key Features and Requirements

### Inheritance Concepts
- Single inheritance from base to derived classes
- Multiple inheritance with virtual base classes
- Constructor and destructor chaining
- Attribute and method inheritance
- Function overriding and specialization

### Orthodox Canonical Form
- Required for all classes as established in Module 02
- Default constructor, copy constructor, copy assignment operator, destructor
- Proper construction/destruction chaining in inheritance hierarchy

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

### Exercise 00: Aaaaand... OPEN!
**Objective**: Implement base ClapTrap class
- **Key Class**: `ClapTrap`
- **Attributes**:
  - Name (constructor parameter)
  - Hit points (10)
  - Energy points (10)
  - Attack damage (0)
- **Member Functions**:
  - `attack(const std::string& target)`
  - `takeDamage(unsigned int amount)`
  - `beRepaired(unsigned int amount)`
- **Behavior**: Actions cost energy points, health management, descriptive messages

### Exercise 01: Serena, my love!
**Objective**: Create ScavTrap derived from ClapTrap
- **Key Class**: `ScavTrap` inherits from `ClapTrap`
- **Modified Attributes**:
  - Hit points (100)
  - Energy points (50)
  - Attack damage (20)
- **Special Function**: `guardGate()` - Gate keeper mode
- **Focus**: Constructor/destructor chaining, function overriding

### Exercise 02: Repetitive work
**Objective**: Create FragTrap derived from ClapTrap
- **Key Class**: `FragTrap` inherits from `ClapTrap`
- **Modified Attributes**:
  - Hit points (100)
  - Energy points (100)
  - Attack damage (30)
- **Special Function**: `highFivesGuys()` - Positive high fives request
- **Focus**: Alternative derived class with different characteristics

### Exercise 03: Now it's weird!
**Objective**: Implement DiamondTrap using multiple inheritance
- **Key Class**: `DiamondTrap` inherits from both `FragTrap` and `ScavTrap`
- **Complex Inheritance**: Virtual base class to avoid duplicate ClapTrap subobjects
- **Attribute Composition**:
  - Hit points (from FragTrap: 100)
  - Energy points (from ScavTrap: 50)
  - Attack damage (from FragTrap: 30)
  - `attack()` method (from ScavTrap)
- **Special Function**: `whoAmI()` - Display both DiamondTrap name and ClapTrap name
- **Technical Challenge**: Diamond problem resolution, virtual inheritance

## Important Functions and Features

### Core Member Functions (All Classes)
- Constructors and destructors with descriptive messages
- Orthodox Canonical Form compliance
- Resource management and memory leak prevention

### Action Methods
- `attack()`: Target-based attack with energy cost
- `takeDamage()`: Health reduction mechanism
- `beRepaired()`: Health restoration with energy cost

### Specialized Functions
- `guardGate()`: ScavTrap's unique capability
- `highFivesGuys()`: FragTrap's positive interaction
- `whoAmI()`: DiamondTrap's identity display

### Inheritance Mechanics
- Proper construction chain: Base → Derived
- Proper destruction chain: Derived → Base
- Function overriding with different behaviors
- Attribute inheritance and modification

## Technical Concepts Emphasized

### Inheritance Hierarchy
```
ClapTrap (Base)
    │
    ├── ScavTrap (Derived)
    │
    └── FragTrap (Derived)
            │
            ScavTrap (Virtual)
            │
DiamondTrap (Multiple Inheritance)
```

### Virtual Inheritance
- Resolution of diamond problem
- Single instance of base class in multiple inheritance
- Proper initialization of virtual base classes

### Constructor/Destructor Chaining
- Automatic base class construction before derived class
- Reverse order destruction
- Debug messages to demonstrate chaining

### Attribute and Method Selection
- Mixed inheritance from multiple parents
- Explicit scope resolution for method selection
- Attribute shadowing and name conflicts

## Learning Outcomes
- Understanding of single and multiple inheritance
- Mastery of constructor/destructor chaining
- Virtual inheritance and diamond problem resolution
- Function overriding and polymorphism foundations
- Complex class hierarchy design
- Proper resource management in inheritance contexts

This module provides essential object-oriented programming skills focused on inheritance mechanisms, preparing students for advanced polymorphism concepts in subsequent modules.
