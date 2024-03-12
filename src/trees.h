#ifndef __TREES_H__
#define __TREES_H__

#include "vector.h"

typedef struct tree_node {
  char *data;
  vector *nodes;
} tree_node;

tree_node *init_tree();
bool insert_after(tree_node *root, char **to_be_inserted, char *previous);
tree_node *delete_node(tree_node *root, char *value);
bool bfs(tree_node *root, char *value);
bool dfs(tree_node *root, char *value);
void traverse_tree(tree_node *root);
void free_tree(tree_node *root);

#endif
