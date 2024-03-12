#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define MIN_VECT_CAPACITY 10

vector *init_vector(size_t data_size, ssize_t capacity) {
  if (capacity <= 0) {
    capacity = MIN_VECT_CAPACITY;
  }
  vector *ret_vect = calloc(1, sizeof(vector));
  if (!ret_vect) {
    return NULL;
  }

  ret_vect->data = calloc(1, data_size * capacity);
  if (!ret_vect->data) {
    free(ret_vect);
    return NULL;
  }
  ret_vect->capacity = capacity;
  ret_vect->size = 0;

  return ret_vect;
}

bool vpush(vector *v, void *data) {
  if (v->size == v->capacity) {
    vector *new_data = realloc(v->data, sizeof(*data) * v->capacity * 2);
    if (!new_data) {
      return false;
    }
    v->data = new_data;
    v->capacity = v->capacity * 2;
  }

  memcpy(&v->data[v->size], data, sizeof(*data));
  v->size++;

  return true;
}

void *vpop(vector *v) {
  if (v->size == 0) {
    return NULL;
  }

  void *ret_val = &v->data[v->size];

  v->size--;
  return ret_val;
}

void free_vector(vector *v, void (*free_fn)(void *)) {
  if (v) {
    if (v->data) {
      for (size_t i = 0; i < v->size; i++) {
        free_fn(&v->data[i]);
      }
    }
    free(v);
  }
}
