# K-Dimensional Tree (K-D Tree) Implementation

This repository contains an implementation of a **K-Dimensional Tree (K-D Tree)** data structure. A K-D Tree is a space-partitioning binary search tree designed to store and efficiently query \(K\)-dimensional vectors (points in a \(K\)-dimensional space).

---

##  Theoretical Overview

### What is a K-D Tree?
Standard Binary Search Trees (BSTs) use single values as keys. A **K-D Tree** extends this concept by using **vectors** as keys instead of individual numbers. 

### Core Parameters
* **\(K\) (or \(N\)):** A constant value representing the fixed number of dimensions for every vector in the tree.
* **Vector Notation:** A random vector \(d\) within the tree is represented by its specific coordinate values across all dimensions:
  \[d = [d_0, d_1, d_2, \dots, d_{N-1}]\]
* **Component Notation:** The specific value of a vector \(d\) at a given dimension \(i\) is denoted as \(d_i\).
* **Dataset \(D\):** The tree stores a collection of \(Z\) random multi-dimensional vectors:
  \[D = \{d_1, d_2, d_3, \dots, d_Z\}\]

---

## Tree Properties & Operations

### 1. Node Structure
Every node in the tree stores:
* A \(K\)-dimensional data vector (\(d\)).
* An **axis** (or split dimension) \(i\), where \(0 \le i < N\).
* References to its **Left Child** and **Right Child**.

### 2. Splitting Rule
Unlike regular BSTs, the dimension used to split the data changes at each level of the tree. 
* At the **Root level (Level 0)**, vectors are split based on their first dimension (\(d_0\)).
* At **Level 1**, vectors are split based on their second dimension (\(d_1\)).
* At **Level \(m\)**, the split dimension is calculated cyclically: 
  \[\text{Split Dimension } i = m \pmod N\]

### 3. Insertion & Search Mechanics
When comparing a target vector \(x\) against a node's vector \(d\) at tree level \(m\) (with split dimension \(i\)):
* If \(x_i < d_i\), the search or insertion proceeds to the **Left Subtree**.
* If \(x_i \ge d_i\), the search or insertion proceeds to the **Right Subtree**.

---

##  Project Structure

```text
├── src/
│   ├── Main.ext          # Entry point of the program
│   ├── KDTree.ext        # Core K-D Tree logic (Insert, Search)
│   └── Node.ext          # Node structure definitions
├── README.md             # Project documentation
└── assignment_specs.pdf  # Original assignment requirements
```
*(Note: Replace `.ext` with your actual programming language extension like `.cpp`, `.java`, or `.py`)*

---

##  Getting Started

### Prerequisites
List any compilers, interpreters, or dependencies needed to run the application here.
* Example: `GCC Compiler` (for C++) or `Python 3.x`.

### Execution
Provide clear commands on how to compile and run your implementation.

```bash
# Compilation Example (if using C++)
g++ -O3 src/main.cpp -o kdtree

# Running the program
./kdtree
```

---

##  Features To Implement
- [ ] Dynamic initialization of a tree with a custom dimension size $K$.
- [ ] **Insertion (`insert`)** of new $K$-dimensional vectors into the tree.
- [ ] **Exact Search (`search`)** to check if a specific vector exists.
- [ ] *Optional/Bonus:* **Nearest Neighbor Search (NNS)** or Range Queries.
