#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

/********************** Queue Implementation for BFS **************************/
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
/******************************************************************************
 ******************************************************************************
 ************************** Helper Functions **********************************/
void insert_after_helper(tree_node *old_node, tree_node *new_node) {
  if (!old_node->child_node) {
    old_node->child_node = new_node;
    return;
  }
  old_node = old_node->child_node;
  while (old_node->level_node) {
    old_node = old_node->level_node;
  }
  old_node->level_node = new_node;
}

void insert_at_helper(tree_node *old_node, tree_node *new_node) {
  while (old_node->level_node) {
    old_node = old_node->level_node;
  }
  old_node->level_node = new_node;
}

bool bfs_helper(queue_header **queue, char **comp_val,
                tree_node **insertion_val,
                void (*fn)(tree_node *, tree_node *)) {
  tree_node *tmp;
  while ((*queue)->start) {
    tmp = (*queue)->start->tdata;

    do {
      if (strcmp(tmp->node_data, *comp_val) == 0) {
        if (fn) {
          fn(tmp, *insertion_val);
        }
        return true;
      }

      if (tmp->child_node) {
        if (!enqueue(*queue, &tmp->child_node)) {
          queue_free(*queue);
          return false;
        }
      }
      tmp = tmp->level_node;
    } while (tmp);

    free(dequeue(*queue));
  }
  return false;
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
  if (!enqueue(queue, &root)) {
    queue_free(queue);
    return false;
  }

  if (bfs_helper(&queue, &level_of, &new_node, insert_at_helper)) {
    queue_free(queue);
    return true;
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
  if (!enqueue(queue, &root)) {
    queue_free(queue);
    return false;
  }

  if (bfs_helper(&queue, &after, &new_node, insert_after_helper)) {
    queue_free(queue);
    return true;
  }

  queue_free(queue);
  return false;
}

bool tree_bfs(tree_node *root, char *search_value) {
  if (!root) {
    return false;
  }

  queue_header *queue = queue_init();
  if (!enqueue(queue, &root)) {
    queue_free(queue);
    return false;
  }

  if (bfs_helper(&queue, &search_value, NULL, NULL)) {
    queue_free(queue);
    return true;
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

tree_node *tree_find_node(tree_node *root, char *search_value) {
  if (!root) {
    return NULL;
  }

  if (strcmp(root->node_data, search_value) == 0) {
    return root;
  }

  tree_node *ret_value = tree_find_node(root->child_node, search_value);
  if (!ret_value) {
    ret_value = tree_find_node(root->level_node, search_value);
  }
  return ret_value;
}

void tree_traverse_preorder(tree_node *root) {
  if (!root) {
    return;
  }

  printf("%s  ", root->node_data);
  if (root->child_node) {
    tree_traverse_preorder(root->child_node);
  }
  if (root->level_node) {
    tree_traverse_preorder(root->level_node);
  }
}

bool in_queue(queue_header *queue, tree_node *node) {
  queue_node *tmp = queue->start;
  while (tmp) {
    if (tmp->tdata == node) {
      return true;
    }
    tmp = tmp->next;
  }
  return false;
}

void tree_free(tree_node *root) {
  if (root) {
    queue_header *queue = queue_init();
    if (!queue)
      return;

    if (!enqueue(queue, &root)) {
      goto cleanup;
    }
    tree_node *tmp1, *tmp2;
    while (queue->start) {
      tmp1 = queue->start->tdata;
      do {
        if (tmp1->child_node && !in_queue(queue, tmp1->child_node)) {
          if (!enqueue(queue, &tmp1->child_node)) {
            goto cleanup;
          }
        }

        if (!in_queue(queue, tmp1)) {
          tmp2 = tmp1;
          tmp1 = tmp1->level_node;
          free(tmp2);
          continue;
        }
        tmp1 = tmp1->level_node;
      } while (tmp1);
      queue_node *queue_tmp = dequeue(queue);
      free(queue_tmp->tdata);
      free(queue_tmp);
    }
  cleanup:
    queue_free(queue);
  }
}
