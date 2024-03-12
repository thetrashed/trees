#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct vector {
  size_t capacity;
  size_t size;
  void *data;
} vector;

vector *init_vector(size_t data_size, ssize_t capacity);
bool vpush(vector *v, void *data);
void *vpop(vector *v);
void free_vector(vector *v, void (*free_fn)(void *));

#endif
