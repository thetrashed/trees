#ifndef __TREE_H__
#define __TREE_H__

#include <stdbool.h>

typedef struct tree_node {
  char *node_data;
  struct tree_node *child_node;
  struct tree_node *level_node;
} tree_node;

bool tree_insert_at_level(tree_node *root, char *value, char *level_of);
bool tree_insert_after(tree_node *root, char *value, char *after);
tree_node *tree_find_node(tree_node *root, char *value);
bool tree_bfs(tree_node *root, char *search_value);
bool tree_dfs(tree_node *root, char *search_value);
void tree_traverse_preorder(tree_node *root);
void tree_free(tree_node *root);

#endif
