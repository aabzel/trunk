#ifndef __BINARY_TREE_DRAW_H
#define __BINARY_TREE_DRAW_H

#include "arrays.h"
#include "bin_heap_array.h"
#include "bin_tree.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

bool print_tree_to_file(TreeNode_t *root, char *fileName);
bool draw_bin_heap_in_file(BinaryHeap_t *binHeap, char *fileName);

#endif /* __BINARY_TREE_DRAW_H */
