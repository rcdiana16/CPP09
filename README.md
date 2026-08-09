# CPP Module 09 - Standard Template Library (STL)

A C++ Module focused on mastering C++ Standard Template Library (STL) containers, algorithms, and data manipulation rules under the C++98 standard.

---

## Table of Contents

- [Overview](#overview)
- [Module Constraints](#module-constraints)
- [Exercises Breakdown](#exercises-breakdown)
  - [Exercise 00: Bitcoin Exchange](#exercise-00-bitcoin-exchange)
  - [Exercise 01: Reverse Polish Notation](#exercise-01-reverse-polish-notation)
  - [Exercise 02: PmergeMe](#exercise-02-pmergeme)
- [Installation & Compilation](#installation--compilation)
- [Test Suite & Examples](#test-suite--examples)
- [Author](#author)

---

## Overview

CPP Module 09 is designed to test container selection and algorithm efficiency in C++98. Each exercise requires choosing the optimal STL container based on performance, iterators, and architectural constraints, strictly prohibiting the reuse of containers across different exercises where applicable.

---

## Module Constraints

- Language Standard: C++98 (`-std=c++98` flag mandatory).
- Compilation Flags: `-Wall -Wextra -Werror`.
- Container Restriction: Each exercise must use different STL containers where specified.
- No external libraries allowed beyond standard C++ headers.

---

## Exercises Breakdown

### Exercise 00: Bitcoin Exchange
- **Target:** Evaluate the value of a bitcoin amount on a specific date based on a historical database (`data.csv`).
- **Container Chosen:** `std::map<std::string, float>`
- **Justification:** `std::map` automatically sorts keys (dates in `YYYY-MM-DD` format) and provides `lower_bound()` / `upper_bound()`, enabling $O(\log N)$ lookup to fetch the exact date or the closest previous date available in history.

### Exercise 01: Reverse Polish Notation
- **Target:** Evaluate mathematical expressions provided in Reverse Polish Notation (Postfix) passed as a single string argument.
- **Container Chosen:** `std::stack<int>`
- **Justification:** RPN evaluation follows a Last-In, First-Out (LIFO) pattern. Operands are pushed onto the stack, and operators consume the top two elements, making `std::stack` the natural data structure.

### Exercise 02: PmergeMe
- **Target:** Sort a sequence of positive integers using the Ford-Johnson algorithm (merge-insert sort) and compare performance between two distinct STL containers.
- **Containers Chosen:** `std::vector<int>` and `std::deque<int>`
- **Justification:**
  - `std::vector`: Provides contiguous memory storage and fast random access, optimal for cache locality during pair comparisons.
  - `std::deque`: Allows efficient insertion/deletion at both ends without full reallocation overhead, serving as a comparison benchmark for non-contiguous storage.

---

## Installation & Compilation

### Clone the repository
```bash
git clone https://github.com/rcdiana16/CPP09
cd CPP09

### Clone the repository
Each exercise contains its own Makefile. Navigate to the respective directory and build:

Bash
# Build Exercise 00
cd ex00 && make

# Build Exercise 01
cd ../ex01 && make

# Build Exercise 02
cd ../ex02 && make
Test Suite & Examples
Exercise 00: Bitcoin Exchange (btc)
Database Format (data.csv)
Fragmento de código
date,exchange_rate
2011-01-03,0.3
2011-01-04,0.3
2012-01-11,7.1
Input File (input.txt)
Plaintext
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42 | 10000
Test Execution & Expected Output
Bash
$ ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-09 => 1 = 0.3
Error: not a positive number.
Error: bad input => 2001-42-42
Exercise 01: Reverse Polish Notation (RPN)
Valid Calculations
Bash
$ ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42

$ ./RPN "7 7 * 7 -"
42

$ ./RPN "1 2 + 3 4 + *"
21
Edge Cases & Error Handling
Bash
# Error: Division by zero
$ ./RPN "5 0 /"
Error

# Error: Invalid token
$ ./RPN "1 2 + a"
Error

# Error: Insufficient operands
$ ./RPN "1 +"
Error
Exercise 02: PmergeMe (PmergeMe)
Sorting Test
Bash
$ ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque  : 0.00048 us
Large Dataset Benchmark Test
Bash
# Generate 3000 random integers and run PmergeMe
$./PmergeMe$(shuf -i 1-100000 -n 3000 | tr '\n' ' ')
Before: 421 8901 12 9481 ...
After:  12 421 8901 9481 ...
Time to process a range of 3000 elements with std::vector : 1.24012 us
Time to process a range of 3000 elements with std::deque  : 2.10841 us
Error Handling Tests
Bash
# Error: Negative numbers
$ ./PmergeMe "-5" "3" "9"
Error

# Error: Non-numeric arguments
$ ./PmergeMe "3" "five" "9"
Error
Author
rcdiana16 - GitHub Profile
