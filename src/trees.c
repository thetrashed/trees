#include <stdlib.h>

#include "trees.h"
#include "vector.h"

tree_node *init_tree() {
  tree_node *ret_tree = calloc(1, sizeof(tree_node));
  if (!ret_tree) {
    return NULL;
  }

  ret_tree->nodes = NULL;

  return ret_tree;
}

bool insert_into_tree(tree_node *root, char *value) {
  if (!root->nodes) {
    root->nodes = init_vector(sizeof(tree_node), -1);
  }

  return vpush(root->nodes, value);
}
bool insert_after(tree_node *root, char **to_be_inserted, char *previous);
tree_node *delete_node(tree_node *root, char *value);
bool bfs(tree_node *root, char *value);
bool dfs(tree_node *root, char *value);
void traverse_tree(tree_node *root);
void free_tree(void *root) {
  if (root) {
    free_vector(((tree_node *)root)->nodes, free_tree);

    free((tree_node *)root);
  };
}
