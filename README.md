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
git clone [https://github.com/rcdiana16/CPP09.git](https://github.com/rcdiana16/CPP09.git)
cd CPP09
