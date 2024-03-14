#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main() {
  tree_node *root = malloc(sizeof(tree_node));
  if (!root) {
    return 1;
  }

  root->node_data = "United States";
  root->level_node = NULL;
  root->child_node = NULL;

  tree_insert_after(root, "USA", "United States");
  tree_insert_after(root, "Canada", "USA");
  tree_insert_after(root, "Toronto", "Canada");
  tree_insert_after(root, "Vancouver", "Toronto");
  tree_insert_after(root, "Montreal", "Toronto");
  tree_insert_after(root, "Paris", "Montreal");
  tree_insert_after(root, "London", "Paris");
  tree_insert_after(root, "Rome", "Paris");

  tree_insert_after(root, "Mexico", "USA");
  tree_insert_after(root, "Mexico City", "Mexico");
  tree_insert_after(root, "Berlin", "Mexico City");

  tree_insert_after(root, "Intermediate Destinations", "United States");
  tree_insert_after(root, "Europe", "Intermediate Destinations");
  tree_insert_after(root, "Germany", "Europe");
  tree_insert_after(root, "Frankfurt", "Germany");
  tree_insert_after(root, "Munich", "Frankfurt");
  tree_insert_after(root, "Vienna", "Munich");

  tree_insert_after(root, "Other Countries", "Intermediate Destinations");
  tree_insert_after(root, "Asia", "Other Countries");
  tree_insert_after(root, "Athens", "Asia");
  tree_insert_after(root, "Budapest", "Athens");

  tree_traverse_preorder(root);

  printf("\nDFS:\n");
  printf("%d\n", tree_dfs(root, "Athens"));
  printf("%d\n", tree_dfs(root, "Germany"));
  printf("%d\n", tree_dfs(root, "Vancouver"));

  printf("\nBFS:\n");
  printf("%d\n", tree_bfs(root, "Berlin"));
  printf("%d\n", tree_bfs(root, "Rome"));
  printf("%d\n", tree_bfs(root, "Vienna"));

  tree_free(root);
  return 0;
}
