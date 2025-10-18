# C++ Module 09 Project Summary

## Project Overview
This final module focuses on advanced practical applications of the Standard Template Library (STL) through three complex real-world problems. The exercises demonstrate sophisticated STL usage patterns, algorithm implementation, and performance analysis while enforcing strict container usage constraints across exercises.

## Key Features and Requirements

### Unique Container Constraint
- **Mandatory STL Usage**: Each exercise must use at least one container
- **No Container Reuse**: Containers used in one exercise cannot be reused in subsequent exercises
- **Exercise 02 Requirement**: Must use two different containers
- **Strategic Planning**: Requires careful container selection across the module

### Performance and Algorithm Focus
- Efficient data processing with large datasets
- Algorithm implementation and optimization
- Performance measurement and comparison
- Real-world problem solving

### Orthodox Canonical Form
- Required for custom classes
- Proper resource management with STL integration

### Compilation and Standards
- Compile with `c++ -Wall -Wextra -Werror -std=c++98`
- C++98 standard compliance
- Complete STL availability

## Exercise Breakdown

### Exercise 00: Bitcoin Exchange
**Objective**: Create a cryptocurrency value calculator using historical data
- **Program**: `btc` - Bitcoin exchange rate calculator
- **Input**: File with 'date | value' format
- **Data Processing**:
  - CSV database of Bitcoin prices over time
  - Date validation (Year-Month-Day format)
  - Value validation (float/integer, 0-1000 range)
  - Closest date lookup for missing dates
- **Key Features**:
  - File I/O and parsing
  - Error handling for invalid inputs
  - Historical data lookup and interpolation
  - Currency value calculation

### Exercise 01: Reverse Polish Notation
**Objective**: Implement RPN calculator using stack-based evaluation
- **Program**: `RPN` - Reverse Polish Notation calculator
- **Input**: Mathematical expression in postfix notation
- **Operations**: Support for `+`, `-`, `*`, `/`
- **Constraints**:
  - Input numbers < 10 (but results can be larger)
  - No bracket handling
  - No decimal number support
- **Algorithm**:
  - Stack-based expression evaluation
  - Operator precedence handling
  - Error detection for invalid expressions

### Exercise 02: PmergeMe
**Objective**: Implement and compare sorting algorithms using different containers
- **Program**: `PmergeMe` - Merge-insertion sort implementation
- **Algorithm**: Ford-Johnson merge-insertion sort
- **Requirements**:
  - Handle at least 3000 different integers
  - Use two different containers
  - Measure and compare performance
  - Separate implementations for each container
- **Output Format**:
  - Unsorted sequence
  - Sorted sequence
  - Timing for first container
  - Timing for second container
- **Performance Analysis**: Clear timing differences between container implementations

## Important Functions and Features

### Data Processing Functions
- **File Parsing**: CSV and custom format reading
- **Data Validation**: Date, number, and format checking
- **Error Handling**: Comprehensive input validation
- **Lookup Operations**: Efficient data retrieval

### Mathematical Functions
- **RPN Evaluation**: Stack-based calculation
- **Currency Conversion**: Value multiplication with exchange rates
- **Sorting Algorithm**: Merge-insertion sort implementation

### Container Operations
- **Sequence Operations**: Insertion, deletion, traversal
- **Associative Operations**: Key-based lookup and retrieval
- **Algorithm Integration**: STL algorithm usage with custom containers
- **Performance Measurement**: Timing and efficiency analysis

### Algorithm Implementation
- **Ford-Johnson Algorithm**: Merge-insertion sort
- **Stack Operations**: RPN expression evaluation
- **Search Algorithms**: Date lookup and interpolation
- **Sorting Techniques**: Container-specific optimizations

## Technical Concepts Emphasized

### STL Container Selection Strategy
```
Exercise 00: map/vector for date-value pairs
Exercise 01: stack for RPN evaluation
Exercise 02: Two different containers for performance comparison
```

### Advanced STL Usage Patterns
- Container-specific performance characteristics
- Algorithm-container compatibility
- Memory management with STL
- Iterator-based operations

### Performance Optimization
- Algorithm efficiency analysis
- Container choice impact on performance
- Large dataset handling (3000+ elements)
- Timing measurement and comparison

### Real-World Application Patterns
- Financial data processing
- Mathematical expression parsing
- Sorting algorithm implementation
- Performance benchmarking

## Learning Outcomes
- Strategic STL container selection for specific use cases
- Implementation of complex algorithms using STL components
- Performance analysis and optimization techniques
- Large-scale data processing with efficiency considerations
- Real-world problem solving with C++ STL
- Algorithm implementation and comparison
- Comprehensive error handling and input validation

This module serves as a capstone project that demonstrates mastery of C++ STL through practical, challenging applications. It requires students to think strategically about container selection, implement sophisticated algorithms, and analyze performance characteristics - skills essential for professional C++ development in real-world scenarios.
