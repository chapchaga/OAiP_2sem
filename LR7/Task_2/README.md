# Lab7_Task2 — Binary Search Tree (Library)

## Variant
20 → 20 − 15 = **Variant 5**  
Individual task: **Determine the number of nodes at each level of the tree.**

Data structure from Lab2 Variant 20: **Library** — key (book code), author, title, year, language.

## Class hierarchy
- `BinarySearchTree` — base class with:
  - `insert`, `remove`, `find`
  - `balanceTree` (DSW / sorted rebuild)
  - `traversePreOrder`, `traverseInOrder`, `traversePostOrder`
  - `clear`
- `LibraryTree : BinarySearchTree` — derived class with:
  - `nodesPerLevel()` — returns count of nodes at each tree level (BFS)

## Build & Run

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt)
cmake --build .
./Lab7_Task2
```

## UI Features
- **Add book** — insert new record by key into the BST
- **Find / Remove** — search or delete by key
- **Balance tree** — rebuild as a balanced BST
- **Pre/In/Post-order** — print traversals to the output log
- **Nodes per level** — variant task: shows node count per level
- **TreeWidget** — visualises tree structure (root → children)
