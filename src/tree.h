#ifndef __TREE_H__
#define __TREE_H__

#include <stdbool.h>

typedef struct tree_node tree_node;

// For initialising the root node, or any other node which may then be added to
// the tree using the tree_insert_child function
tree_node *tree_init(char *value);

// Inserts a new node at the same level as the value of level_of, which is found
// using BFS
bool tree_insert_at_level(tree_node *root, char *value, char *level_of);

// Inserts the new value to the child level of the after value. Uses BFS to find
// the after value.
bool tree_insert_after(tree_node *root, char *value, char *after);

// Inserts the child_node after the root that is provided. If a child_node is
// already present for the root, it inserts the new_child before the previous
// the node, and move the previous one to the end of the new_node's level.
void tree_insert_child(tree_node *root, tree_node *insertion_node);

// Searches the tree for the search_value using BFS
bool tree_bfs(tree_node *root, char *search_value);

// Searches the tree for the search_value using DFS
bool tree_dfs(tree_node *root, char *search_value);

// Finds the node with search_value and returns a pointer to that node. Uses DFS
tree_node *tree_find_node(tree_node *root, char *value);

// Checks if a value is present after a certain value in the tree.
bool tree_find_after(tree_node *root, char *initial_value, char *search_value);

// Prints the tree using preorder traversal
void tree_traverse_preorder(tree_node *root);

// Frees the memory allocated by the tree. Ensures that cyclic nodes are not
// doubly free'd by using a queue for the proper freeing
void tree_free(tree_node *root);

#endif
