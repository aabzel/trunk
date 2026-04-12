#include "bin_tree.h"

#include "algorithms.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int g_maxDepthVal = 0;
static void find_max_depth(struct xTreeNode_t *tree, int level);
static int find_size_ll(TreeNode_t *tree);

/* Given a binary tree, print its nodes in inorder*/
void print_inorder(TreeNode_t *node) {
  if (node == NULL) {
    return;
  }

  /* first recur on left child */
  print_inorder(node->left);

  /* then print the data of node */
  printf("%d ", node->val);

  /* now recur on right child */
  print_inorder(node->right);
}

#if 0
void print_pre_order (TreeNode_t* node) {
    if (node == NULL)
        return;

    /* first print data of node */
    printf ("%d ", node->val);

    /* then recur on left sutree */
    printPreorder (node->left);

    /* now recur on right subtree */
    printPreorder (node->right);
}
#endif

#if 0
/* Given a binary tree, print its nodes according to the
 "bottom-up" postorder traversal. */
void print_post_order (TreeNode_t* node) {
    if (node == NULL)
        return;

    // first recur on left subtree
    printPostorder (node->left);

    // then recur on right subtree
    printPostorder (node->right);

    // now deal with the node
    printf ("%d ", node->val);
}
#endif

bool is_node_has_vacant(TreeNode_t *root) {
  bool res = false;
  if (root) {
    if (NULL == root->left) {
      res = true;
    }
    if (NULL == root->right) {
      res = true;
    }
  }
  return res;
}

// get fist node with spare leaf
TreeNode_t *get_first_spare_leaf_node(TreeNode_t *root) {
  TreeNode_t *outNode = NULL;
  TreeNode_t *someSpareNode = get_first_spare_node(root);
  if (someSpareNode) {
    if (root) {
      if (NULL == someSpareNode->left) {
        outNode = someSpareNode->left;
      }
      if (NULL == someSpareNode->right) {
        outNode = someSpareNode->right;
      }
    }
  }
  return outNode;
}

TreeNode_t *get_first_spare_node(TreeNode_t *root) {
  TreeNode_t *outNode = NULL;
  if (root) {
    if (is_node_has_vacant(root)) {
      outNode = root;
    } else {
      outNode = get_first_spare_node(root->left);
      if (NULL == outNode) {
        outNode = get_first_spare_node(root->right);
      }
    }
  }
  return outNode;
}

bool is_balanced(TreeNode_t *root) {
  bool res = false;
  if (root) {
    int lheight; /* for height of left subtree */
    int rheight; /* for height of right subtree */
    /* Get the height of left and right sub trees */
    lheight = height(root->left);
    rheight = height(root->right);
    if ((abs(lheight - rheight) <= 1) && is_balanced(root->left) &&
        is_balanced(root->right)) {
      res = true;
    }
  } else {
    res = true;
  }
  return res;
}

bool is_complete(TreeNode_t *root) {
  bool res = false;
  if (root) {
    int lheight; /* for height of left subtree */
    int rheight; /* for height of right subtree */
    /* Get the height of left and right sub trees */
    lheight = height(root->left);
    rheight = height(root->right);
    if ((0 == abs(lheight - rheight)) && is_complete(root->left) &&
        is_complete(root->right)) {
      res = true;
    }
  } else {
    res = true;
  }
  return res;
}

int height(TreeNode_t *node) {
  /* base case tree is empty */
  if (node == NULL)
    return 0;

  /* If tree is not empty then height = 1 + max of left
   height and right heights */
  return 1 + max(height(node->left), height(node->right));
}

int max_depth(struct xTreeNode_t *root) {
  if (root) {
    g_maxDepthVal = 0;
    find_max_depth(root, 0);
  } else {
    g_maxDepthVal = -1;
  }
  return g_maxDepthVal + 1;
}

// Finds the maximum depth of the binary tree
static void find_max_depth(struct xTreeNode_t *tree, int level) {
  int nextLevel = 0;
  // printf ("\nlevel:%d\n", level);
  if (NULL != tree) {
    if (g_maxDepthVal < level) {
      g_maxDepthVal = level;
    }
    nextLevel = ++level;
    // printf ("\nnextLevel:%d\n", nextLevel);
    if (tree->left) {
      find_max_depth(tree->left, nextLevel);
    }
    if (tree->right) {
      find_max_depth(tree->right, nextLevel);
    }
  } else {
    // printf ("\nlast level:%d\n", level);
  }
  return;
}

// Finds the maximum depth of the binary tree
static void find_max_depth_leavs(struct xTreeNode_t *tree, int curLevel,
                                 int maxdepth) {
  int nextLevel = 0;
  printf("\n curLevel:%d val: %d\n", curLevel, tree->val);
  if (NULL != tree) {
    if (g_maxDepthVal < curLevel) {
      g_maxDepthVal = curLevel;
    }
    if (curLevel == (maxdepth - 1)) {
      g_sum += tree->val;
      printf("\n max level %d val %d\n", curLevel, tree->val);
    }
    nextLevel = ++curLevel;
    // printf ("\nnextLevel:%d\n", nextLevel);
    if (tree->left) {
      find_max_depth_leavs(tree->left, nextLevel, maxdepth);
    }
    if (tree->right) {
      find_max_depth_leavs(tree->right, nextLevel, maxdepth);
    }
  } else {
    // printf ("\nlast level:%d\n", level);
  }
  return;
}

int g_sum = 0;
int calc_leaves_sum(TreeNode_t *root, int maxDepth) {
  g_sum = 0;
  if (root) {
    g_maxDepthVal = 0;
    find_max_depth_leavs(root, 0, maxDepth);
  } else {
    g_maxDepthVal = -1;
  }
  return g_sum;
}

int find_size(TreeNode_t *tree) {
  int numOfNodes = 0;
  numOfNodes = find_size_ll(tree);
  return numOfNodes;
}

// In Order traversal
void print_inorder_traversal(TreeNode_t *tree) {
  if (tree->left) {
    print_inorder_traversal(tree->left);
  }
  printf("%d\n", tree->val);
  if (tree->right) {
    print_inorder_traversal(tree->right);
  }
}

int get_parent_index(int nodeIndex, int size) {
  double paretnt = ceil(((double)nodeIndex / 2.0f) - 1.0f);
  int outParent = (int)paretnt;
  if (size < outParent) {
    printf("\nError out of array %d\n", outParent);
    outParent = 0;
  }
  return outParent;
}

#if 0
static int get_left_child_index (int perent, int sizeOfArr) {
    int leftChild = perent * 2 + 1;
    if (sizeOfArr < leftChild) {
        printf ("\nError out of array %d\n", leftChild);
        leftChild = 0;
    }
    return leftChild;
}

static bool is_left_son_exist (int patentIndex, int *arr, int size) {
    bool res = false;
    int leftSonIndex = get_left_child_index (patentIndex, size);
    if (NOT_NUM != arr [leftSonIndex]) {
        res = true;
    }
    return res;
}
static int get_right_child_index (int parentIndex, int sizeOfArr) {
    int rightChild = parentIndex * 2 + 2;
    if (sizeOfArr < rightChild) {
        printf ("\nError out of array %d\n", rightChild);
        rightChild = 0;
    }
    return rightChild;
}

static bool is_right_son_exist (int parentIndex, int *arr, int size) {
    bool res = false;
    int rightSonIndex = get_right_child_index (parentIndex, size);
    if (NOT_NUM != arr [rightSonIndex]) {
        res = true;
    }
    return res;
}

void parse_bin_tree (int *arr, int size) {
    bool res = false;
    for (int i = 0; i < size; i++) {
        printf ("\narr[%d] %d", i, arr [i]);
        if (NOT_NUM != arr [i]) {
            res = is_left_son_exist (i, arr, size);
            if (false == res) {
                printf ("\nlack of L son for %d", i);
            }
            res = is_right_son_exist (i, arr, size);
            if (false == res) {
                printf ("\nlack of R son for %d", i);
            }
        }
        //printf ("\n index %d expLindex %d expRindex %d", i, get_left_child_index (i, 1000), get_right_child_index (i, 1000));

        //int patentVal = arr [get_parent_index (i, size)];
        //if (NOT_NUM == patentVal) {
        //    printf ("\ni does not have parent %d\n", i);
        //}
        //if (NOT_NUM != arr [i]) {
        //    printf ("\n%d L(%d) R(%d)", arr [i], arr [get_left_child (i, size)], arr [get_right_child (i, size)]);
        //}
    }
}
#endif

int deepestLeavesSum(TreeNode_t *root) {
  int sum = 0;
  int maxDepth = 0;
  maxDepth = max_depth(root);
  sum = calc_leaves_sum(root, maxDepth);
  return sum;
}

bool init_tree_node(TreeNode_t *NodePar, int val, TreeNode_t *NodeLeftChild,
                    TreeNode_t *NodeRightChild) {
  bool res = false;
  if (NodePar) {
    NodePar->val = val;
    NodePar->left = NodeLeftChild;
    NodePar->right = NodeRightChild;
    res = true;
  }
  return res;
}

void init_node(TreeNode_t *Node, int val) {
  Node->left = NULL;
  Node->right = NULL;
  Node->val = val;
}

// Set new val to NodePtr
bool binary_tree_add_node(TreeNode_t **NodePtr, int val) {
  bool res = false;
  TreeNode_t *newNode = NULL;
  newNode = (TreeNode_t *)malloc(sizeof(TreeNode_t));
  if (NULL != newNode) {
    init_node(newNode, val);
    *NodePtr = newNode;
    res = true;
  }
  return res;
}

bool binary_tree_attace_node(TreeNode_t *NodePtr, int val, bool isleft) {
  bool res = false;
  if (NodePtr) {
    TreeNode_t *newNode = NULL;
    newNode = (TreeNode_t *)malloc(sizeof(TreeNode_t));
    if (NULL != newNode) {
      init_node(newNode, val);
      if (isleft) {
        NodePtr->left = newNode;
      } else {
        NodePtr->right = newNode;
      }
      res = true;
    }
  }

  return res;
}

// Finds the size of the binary tree
static int find_size_ll(TreeNode_t *tree) {
  int amountOfElements = 0;
  if (tree) {
    amountOfElements++;
    if (tree->left) {
      amountOfElements += find_size_ll(tree->left);
    }
    if (tree->right) {
      amountOfElements += find_size_ll(tree->right);
    }
  } else {
    amountOfElements = 0;
  }

  return amountOfElements;
}
