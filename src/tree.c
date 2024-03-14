#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_node {
  char *node_data;
  struct tree_node *child_node;
  struct tree_node *level_node;
} tree_node;

/***********************Queue Implementation for BFS***************************/
typedef struct queue_node {
  tree_node *tdata;
  struct queue_node *next;
} queue_node;

typedef struct queue_header {
  queue_node *start;
  queue_node *end;
} queue_header;

queue_header *queue_init() {
  queue_header *ret_val = malloc(sizeof(queue_header));
  if (!ret_val) {
    return NULL;
  }

  ret_val->start = NULL;
  ret_val->end = NULL;
  return ret_val;
}

bool enqueue(queue_header *queue, tree_node **new) {
  if (!queue->start) {
    queue->start = malloc(sizeof(queue_node));
    if (!queue->start) {
      return false;
    }

    queue->start->next = NULL;
    queue->start->tdata = *new;
    queue->end = queue->start;
    return true;
  }

  queue->end->next = malloc(sizeof(queue_node));
  if (!queue->end->next) {
    return false;
  }

  queue->end->next->tdata = *new;
  queue->end->next->next = NULL;

  queue->end = queue->end->next;
  return true;
}

queue_node *dequeue(queue_header *queue) {
  if (!queue->start) {
    return NULL;
  }

  queue_node *ret_node = queue->start;
  queue->start = queue->start->next;

  return ret_node;
}

void queue_free(queue_header *queue) {
  if (queue) {
    queue_node *tmp = queue->start;
    while (tmp) {
      queue->start = queue->start->next;
      free(tmp);
      tmp = queue->start;
    }
    free(queue);
  }
}

void queue_print(queue_header *queue) {
  queue_node *tmp = queue->start;
  while (tmp) {
    printf("%s\t", tmp->tdata->node_data);
    tmp = tmp->next;
  }
  printf("\n");
}
/******************************************************************************/

tree_node *tree_init_node(char **value) {
  tree_node *new_node = malloc(sizeof(tree_node));
  if (!new_node) {
    return NULL;
  }
  new_node->child_node = NULL;
  new_node->level_node = NULL;

  new_node->node_data = *value;
  return new_node;
}

bool tree_insert_at_level(tree_node *root, char *value, char *level_of) {
  if (!root->node_data) {
    root->node_data = value;
    return true;
  }

  tree_node *new_node = tree_init_node(&value);
  if (!new_node) {
    return false;
  }

  queue_header *queue = queue_init();
  tree_node *tmp;
  if (!enqueue(queue, &root)) {
    queue_free(queue);
    return false;
  }

  while (queue->start) {
    tmp = queue->start->tdata;

    do {
      if (strcmp(tmp->node_data, level_of) == 0) {
        while (tmp->level_node) {
          tmp = tmp->level_node;
        }
        tmp->level_node = new_node;

        queue_free(queue);
        return true;
      }

      if (tmp->child_node) {
        if (!enqueue(queue, &tmp->child_node)) {
          queue_free(queue);
          return false;
        }
      }
      tmp = tmp->level_node;
    } while (tmp);

    free(dequeue(queue));
  }

  queue_free(queue);
  return false;
}

bool tree_insert_after(tree_node *root, char *value, char *after) {
  if (!root->node_data) {
    root->node_data = value;
    return true;
  }

  tree_node *new_node = tree_init_node(&value);
  if (!new_node) {
    return false;
  }

  queue_header *queue = queue_init();
  tree_node *tmp;
  if (!enqueue(queue, &root)) {
    queue_free(queue);
    return false;
  }

  while (queue->start) {
    tmp = queue->start->tdata;
    do {
      if (strcmp(tmp->node_data, after) == 0) {
        if (!tmp->child_node) {
          tmp->child_node = new_node;
          goto cleanup_and_return;
        }

        tmp = tmp->child_node;
        while (tmp->level_node) {
          tmp = tmp->level_node;
        }
        tmp->level_node = new_node;

      cleanup_and_return:
        queue_free(queue);
        return true;
      }

      if (tmp->child_node) {
        if (!enqueue(queue, &tmp->child_node)) {
          queue_free(queue);
          return false;
        }
      }
      tmp = tmp->level_node;
    } while (tmp);

    free(dequeue(queue));
  }

  queue_free(queue);
  return false;
}

bool tree_bfs(tree_node *root, char *search_value) {
  if (!root) {
    return false;
  }

  queue_header *queue = queue_init();
  tree_node *tmp;
  if (!enqueue(queue, &root)) {
    queue_free(queue);
    return false;
  }

  while (queue->start) {
    tmp = queue->start->tdata;
    do {
      if (strcmp(tmp->node_data, search_value) == 0) {
        queue_free(queue);
        return true;
      }

      if (tmp->child_node) {
        if (!enqueue(queue, &tmp->child_node)) {
          queue_free(queue);
          return false;
        }
      }
      tmp = tmp->level_node;
    } while (tmp);

    free(dequeue(queue));
  }

  queue_free(queue);
  return false;
}

bool tree_dfs(tree_node *root, char *search_value) {
  if (!root) {
    return false;
  }

  if (strcmp(root->node_data, search_value) == 0) {
    return true;
  }

  bool search_result = tree_dfs(root->child_node, search_value);
  if (!search_result) {
    search_result = tree_dfs(root->level_node, search_value);
  }

  return search_result;
}

void tree_free(tree_node *root) {
  if (root) {
    if (root->child_node) {
      tree_free(root->child_node);
    }
    if (root->level_node) {
      tree_free(root->level_node);
    }
    free(root);
  }
}

int main() {
  tree_node *root = malloc(sizeof(tree_node));
  if (!root) {
    return 1;
  }

  root->node_data = "int";
  root->level_node = NULL;
  root->child_node = NULL;

  tree_insert_at_level(root, "hello", "int");
  tree_insert_at_level(root, "world", "int");
  tree_insert_at_level(root, "bye", "int");
  tree_insert_at_level(root, "int2", "int");
  tree_insert_at_level(root, "10000088888888", "int");
  tree_insert_at_level(root, "1", "int");
  tree_insert_at_level(root, "100", "int");
  tree_insert_at_level(root, "in312", "int");
  tree_insert_after(root, "secondary", "int");

  printf("\nDFS:\n");
  printf("%d\n", tree_dfs(root, "hello"));
  printf("%d\n", tree_dfs(root, "hellow"));
  printf("%d\n", tree_dfs(root, "secondary"));

  printf("\nBFS:\n");
  printf("%d\n", tree_bfs(root, "hello"));
  printf("%d\n", tree_bfs(root, "hellow"));
  printf("%d\n", tree_bfs(root, "secondary"));

  tree_free(root);
  return 0;
}
