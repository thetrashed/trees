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
    free_vector(ret_vect);
  }

  return ret_vect;
}

bool vpush(vector *v, void *data) {
  if (v->size == v->capacity) {
    vector *new_data = realloc(v, sizeof(*data) * v->size * 2);
    if (!new_data) {
      return false;
    }
    v->data = new_data;
    v->capacity = v->size * 2;
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
  return v->data;
}

void free_vector(vector *v) {
  if (v) {
    if (v->data) {
      free(v->data);
    }
    free(v);
  }
}
