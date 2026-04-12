#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H


// https://en.wikipedia.org/wiki/Binary_tree

#include "bin_heap_types.h"

bool swap_i32(int32_t* const a, int32_t* const b) ;
bool bin_heap_init_common(const BinHeapConfig_t* const Config, BinHeapHandle_t* const Node);
bool BinHeapIsValidConfig(const BinHeapConfig_t* const Config) ;

#if 0
int bin_heap_pop_max(TreeNode_t* Root);
int bin_heap_get_max(TreeNode_t** Root);
bool bin_heap_swift_up(TreeNode_t* Root);
bool bin_heap_is_max_heap(TreeNode_t* Root);

// TOTO
TreeNode_t* bin_heap_get_last(TreeNode_t* Root);
void bin_heap_make_max_heap(TreeNode_t* root);
bool bin_heap_max_heap_insert(TreeNode_t** Root, int newVal);
void bin_heap_init_node(TreeNode_t* Node, int val);
bool bin_heap_delet_node_with(TreeNode_t** root, int val);
bool bin_heap_delete_node_with_val(TreeNode_t* perent, TreeNode_t* child, int val, bool isLeft);
#endif

#endif /* BINARY_HEAP_H */
