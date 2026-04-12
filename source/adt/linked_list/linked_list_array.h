#ifndef LINKED_LIST_OF_ARRAY_H
#define LINKED_LIST_OF_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "array_type.h"

typedef struct xList_array_node_t {
  Array_t data;
  struct xList_array_node_t *nextNode;
} list_array_node_t;

#ifdef __cplusplus
}
#endif

#endif /* LINKED_LIST_OF_ARRAY_H */
