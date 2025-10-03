# 📘 Set Implementation in C++

This project contains an **object-oriented implementation of a Set container in C++**, similar in functionality to `std::set`.  
It is implemented as a **balanced binary search tree (AVL Tree)** with full iterator support.

---

## ✨ Features

- **Balanced Binary Search Tree (AVL)**
  - Automatic balancing with rotations.
  - Ensures logarithmic complexity for insert, erase, and search.

- **Iterators**
  - `iterator`, `const_iterator`
  - `reverse_iterator`, `const_reverse_iterator`
  - Full support for increment (`++`) and decrement (`--`).

- **Element Operations**
  - `insert(const T&)`
  - `erase(iterator)`
  - `erase(const key_type&)`
  - `find(const key_type&)`
  - `count(const key_type&)`
  - `lower_bound(const key_type&)`
  - `upper_bound(const key_type&)`
  - `equal_range(const key_type&)`

- **Traversal Methods**
  - Recursive: `inOrder`, `preOrder`, `postOrder`, `levelOrder`
  - Iterative: `inOrderIterative`, `preOrderIterative`, `postOrderIterative`

- **Utility Functions**
  - `clear()`
  - `empty()`
  - `size()`
  - `max_size()`
  - `swap(Set&)`
  - Output operator `operator<<` to print the tree structure.

- **Comparison Operators**
  - `==`, `!=`, `<`, `<=`, `>`, `>=`

---

## 📂 Project Structure
