#include "bin_tree_draw.h"

#include "bin_tree.h"

#include "algorithms.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void bst_print_dot_null(unsigned long long int nodeAdddr, FILE *stream);
static void bst_print_dot_aux(TreeNode_t *node, FILE *stream);

static bool draw_bin_heap_in_file_ll(BinaryHeap_t *binHeap, FILE *stream);
static void bst_print_dot(TreeNode_t *tree, FILE *stream);

int gNullCnt = 0;
static void bst_print_dot_null(unsigned long long int nodeAdddr, FILE *stream) {
  gNullCnt++;
  fprintf(stream, "    null%d [shape=point];\n", gNullCnt);
  fprintf(stream, "    node%llu -> null%d;\n", nodeAdddr, gNullCnt);
}

static void bst_print_dot_aux(TreeNode_t *node, FILE *stream) {
  unsigned long long int nodeAddr = (unsigned long long int)node;
  if (node) {
    fprintf(stream, "    node%llu[ label = \"%d\"]; \n",
            (unsigned long long int)node, node->val);
  }

  if (NULL != node->left) {
    unsigned long long int leftNodeAddr = (unsigned long long int)(node->left);
    fprintf(stream, "   node%llu -> node%llu ; \n", nodeAddr, leftNodeAddr);
    bst_print_dot_aux(node->left, stream);
  } else {
    bst_print_dot_null(nodeAddr, stream);
  }
  if (NULL != node->right) {
    unsigned long long int rightNodeAddr = (uint64_t)(node->right);
    fprintf(stream, "   node%llu -> node%llu ; \n", nodeAddr, rightNodeAddr);
    bst_print_dot_aux(node->right, stream);
  } else {
    bst_print_dot_null(nodeAddr, stream);
  }
}

// use Graphviz Online
// https://dreampuf.github.io/GraphvizOnline

bool print_tree_to_file(TreeNode_t *root, char *fileName) {
  bool res = false;
  FILE *fp = NULL;
  fp = fopen(fileName, "w");
  if (fp) {
    bst_print_dot(root, fp);
    res = true;
    fclose(fp);
  } else {
    printf("\n Unable to open file!");
  }
  return res;
}

static void bst_print_dot(TreeNode_t *tree, FILE *stream) {
  fprintf(stream, "digraph BST {\n");
  fprintf(stream, "    node [fontname=\"Arial\"];\n");
  if (NULL == tree) {
    fprintf(stream, "\n");
  } else if (NULL == tree->right && NULL == tree->left) {
    fprintf(stream, "    node%llu[ label = \"%d\"]; \n",
            (unsigned long long int)tree, tree->val);
  } else {
    bst_print_dot_aux(tree, stream);
  }
  fprintf(stream, "}\n");
}

bool draw_bin_heap_in_file(BinaryHeap_t *binHeap, char *fileName) {
  bool res = false;
  FILE *fp = NULL;
  fp = fopen(fileName, "w");
  if (fp) {
    draw_bin_heap_in_file_ll(binHeap, fp);
    res = true;
    fclose(fp);
  } else {
    printf("\n Unable to open file!");
  }
  return res;
}

static bool draw_bin_heap_in_file_ll(BinaryHeap_t *binHeap, FILE *stream) {
  bool res = true;
  if (stream) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");
    if (binHeap) {
      gNullCnt = 0;
      for (int node = 0; node < binHeap->length; node++) {
        fprintf(stream, "    node%u[ label = \"%d\"]; \n", (unsigned int)node,
                binHeap->array[node]);
        if (is_right_ch_exist(binHeap, node)) {
          int childIndex = get_right_child_index(node);
          fprintf(stream, "   node%u -> node%u ; \n", node, childIndex);
        } else {
          gNullCnt++;
          fprintf(stream, "    null%d [shape=point];\n", gNullCnt);
          fprintf(stream, "    node%u -> null%d;\n", node, gNullCnt);
        }
        if (is_left_ch_exist(binHeap, node)) {
          int childIndex = get_left_child_index(node);
          fprintf(stream, "   node%u -> node%u ; \n", node, childIndex);
        } else {
          gNullCnt++;
          fprintf(stream, "    null%d [shape=point];\n", gNullCnt);
          fprintf(stream, "    node%u -> null%d;\n", node, gNullCnt);
        }
      }
    } else {
      fprintf(stream, "\n");
    }
    fprintf(stream, "}\n");
  }
  return res;
}
