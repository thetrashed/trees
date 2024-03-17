# N-ary Trees Implementation
This repository contains an implementation of n-ary trees in C. A visual representation of the trees generated is as follows:
```
 A
 |
 B -- C -- D -- E
 |    |
 |    H -- I
 F -- G
```
 
- A -> the root node
- B, C, D, E -> children of the root node, all at the same level
- F, G -> children of the B node, at the same level

Both BFS and DFS have been implemented for searching for a specific value within the tree. BFS uses a *queue* to implement the searching while DFS is implemented in a recursive manner. A function for *preorder traversal* of the tree has also been implemented using a recursive approach. Details of other functions available are mentioned in the comments in the `tree.c` and `tree.h` files.
