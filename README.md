# EE441 Data Structures & OOP – Programming Assignments 

This repository contains the solutions to the three programming assignments for the EE441 – Object Oriented Programming course at METU. All assignments are written in C++ with an emphasis on manual memory management and custom data structures. Standard containers and algorithms like `std::vector`, `std::list`, and `std::sort` were intentionally avoided to reinforce low-level understanding.

## 🧮 Assignment 1 – Sorted List

**Goal:** Implement a class that maintains a dynamically sized sorted list of `float` values.

### Features:
- Insertion while maintaining sorted order
- Manual array shifting for insert/remove
- Exception handling with `std::out_of_range`, `std::length_error`, and `std::domain_error`
- Linear search for insertion, binary search for lookup
- Time complexity analysis included

## 🀄 Assignment 2 – Simplified Mahjong

**Goal:** Design a simplified Mahjong game using object-oriented programming and dynamic memory.

### Components:
- `Tile`: Holds suit and number with overloaded comparison operators
- `Stack`: Custom dynamic array with push/pop/resize logic
- `Hand`: Manages player's 14-tile hand, checks win condition (4 triplets + 1 pair)
- Custom discard heuristic
- No STL containers used; full memory management implemented

## 🔢 Assignment 3 – Sudoku Solver via Graph Coloring

**Goal:** Solve a 9x9 Sudoku puzzle by modeling it as a graph coloring problem.

### Highlights:
- Custom `List` class (doubly linked list) with iterator support
- `Graph` class with recursive brute-force coloring
- Sudoku represented as a graph of 81 vertices with adjacency from rows, columns, and boxes
- Sudoku class inherits the graph and solves the board using coloring constraints
- No standard graph or list libraries used
