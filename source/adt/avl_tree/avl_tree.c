#include "avl_tree.h"

#ifdef MATH
#include "algorithms.h"
#endif

#include <stdlib.h>

static TreeNode_t *_avl_subtree_insert(TreeNode_t *n, int val);
static TreeNode_t *_avl_node_create(int val);
static int _avl_get_height(TreeNode_t *n);
static int _avl_balance_factor(TreeNode_t *n);
static int _avl_subtree_min_val(TreeNode_t *n);
static TreeNode_t *_avl_rotate_left(TreeNode_t *n);
static TreeNode_t *_avl_rotate_right(TreeNode_t *n);
static void _avl_update_height(TreeNode_t *n);
static TreeNode_t *_avl_subtree_remove(TreeNode_t *n, int oldVal);
static TreeNode_t *_avl_balance(TreeNode_t *n);

TreeNode_t *avl_insert(TreeNode_t *root, int newVal) {
  TreeNode_t *node;
  /*
   * We insert val by using our subtree insertion function starting with the
   * subtree rooted at t->root (i.e. the whole tree).
   */
  node = _avl_subtree_insert(root, newVal);
  return node;
}

bool avl_is_empty(TreeNode_t *rootNode) {
  bool res = false;
  if (NULL == rootNode) {
    res = true;
  }
  return res;
}

TreeNode_t *avl_delete(TreeNode_t *rootNode, int oldVal) {
  TreeNode_t *newRoot = NULL;
  if (rootNode) {
    newRoot = _avl_subtree_remove(rootNode, oldVal);
  }
  return newRoot;
}

/*
 * Helper function to remove a given value from a subtree of a AVL rooted at
 * a specified node.  Operates recursively by figuring out whether val is in
 * the left or the right subtree of the specified node and performing the
 * remove operation on that subtree.
 *
 * Returns the potentially new root of the given subtree, modified to have
 * the specified value removed.
 */
static TreeNode_t *_avl_subtree_remove(TreeNode_t *n, int oldVal) {
  if (n == NULL) {
    /*
     * If n is NULL, that means we've reached a leaf node without finding
     * the value we wanted to remove.  The tree won't be modified.
     */
    return NULL;

  } else if (oldVal < n->val) {

    /*
     * If val is less than n, remove val from n's left subtree and update
     * n->left to point to the modified subtree (with val removed).  Return
     * n, whose subtree itself has now been modified, after balancing that
     * subtree.
     */
    n->left = _avl_subtree_remove(n->left, oldVal);
    return _avl_balance(n);

  } else if (oldVal > n->val) {

    /*
     * If val is greater than n, remove val from n's right subtree and update
     * n->right to point to the modified subtree (with val removed).  Return
     * n, whose subtree itself has now been modified, after balancing that
     * subtree.
     */
    n->right = _avl_subtree_remove(n->right, oldVal);
    return _avl_balance(n);

  } else {

    /*
     * If we've reached this point, we've found a node with value val.  We
     * need to remove this node from the tree, and the way we do that will
     * differ based on whether the node has 0, 1, or 2 children.
     */
    if (n->left != NULL && n->right != NULL) {

      /*
       * If n has 2 children, we replace the value at n with the value at n's
       * in-order successor node, which is the minimum value in n's right
       * subtree.  Then we recursively remove n's in-order successor node from
       * the tree (specifically from n's right subtree).  Balance n before
       * returning it
       */
      n->val = _avl_subtree_min_val(n->right);
      n->right = _avl_subtree_remove(n->right, n->val);
      return _avl_balance(n);

    } else if (n->left != NULL) {

      /*
       * If n has only a left child, we simply delete n by freeing it and
       * returning the left child node so that it becomes the new child of
       * n's parent via the recursion.  We don't need to balance the left
       * child before returning, since it should already be balanced.
       */
      TreeNode_t *left_child = n->left;
      free(n);
      return left_child;

    } else if (n->right != NULL) {

      /*
       * If n has only a right child, we simply delete n by freeing it and
       * returning the right child node so that it becomes the new child of
       * n's parent via the recursion.  We don't need to balance the right
       * child before returning, since it should already be balanced.
       */
      TreeNode_t *right_child = n->right;
      free(n);
      return right_child;
    } else {
      /*
       * Otherwise, n has no children, and we can simply free it and return
       * NULL so that n's parent will lose n as a child via the recursion.
       */
      free(n);
      return NULL;
    }
  }
}

static TreeNode_t *_avl_balance(TreeNode_t *n) {
  if (n) {
    int bf = _avl_balance_factor(n);
    if (bf < -1) {
      /*
       * Here, n is height-imbalanced on the left.  We need a double rotation if
       * n’s left child is right-heavy.
       */
      if (_avl_balance_factor(n->left) > 0) {
        n->left = _avl_rotate_left(n->left);
      }
      return _avl_rotate_right(n);
    } else if (bf > 1) {
      /*
       * Here, n is height-imbalanced on the right.  We need a double rotation
       * if n’s right child is left-heavy.
       */
      if (_avl_balance_factor(n->right) < 0) {
        n->right = _avl_rotate_right(n->right);
      }
      return _avl_rotate_left(n);
    } else {
      // Just update the height if we didn’t rotate.
      _avl_update_height(n);
      return n;
    }
  } else {
    return NULL;
  }
}

/*
 * This function performs a right rotation on the subtree rooted at a given
 * node.  The rotation is centered around the node's right child.  The new
 * subtree root (the rotation's center) is returned.
 */
static TreeNode_t *_avl_rotate_right(TreeNode_t *n) {
  TreeNode_t *center = n->left;

  // The center's right child and n "trade places" in the tree.
  n->left = center->right;
  center->right = n;

  _avl_update_height(n);
  _avl_update_height(center);

  return center;
}

/*
 * This function performs a left rotation on the subtree rooted at a given
 * node.  The rotation is centered around the node's right child.  The new
 * subtree root (the rotation's center) is returned.
 */
static TreeNode_t *_avl_rotate_left(TreeNode_t *n) {
  TreeNode_t *center = n->right;

  // The center's left child and n "trade places" in the tree.
  n->right = center->left;
  center->left = n;

  _avl_update_height(n);
  _avl_update_height(center);

  return center;
}

/*
 * Helper function to get a node's height, even if the node is NULL (in which
 * case the height is -1).
 */
static int _avl_get_height(TreeNode_t *n) {
  if (n == NULL) {
    return -1;
  }
  return n->height;
}

static void _avl_update_height(TreeNode_t *n) {
  int lh = _avl_get_height(n->left);
  int rh = _avl_get_height(n->right);

  // Height is 1 more than the maximum child height.
  if (lh > rh) {
    n->height = lh + 1;
  } else {
    n->height = rh + 1;
  }
}

static int _avl_balance_factor(TreeNode_t *n) {
  int balFac = 0;
  if (n) {
    balFac = _avl_get_height(n->right) - _avl_get_height(n->left);
  } else {
    printf(" Error ");
  }
  return balFac;
}

static int _avl_subtree_min_val(TreeNode_t *n) {
  /*
   * The minimum value in any subtree is just the leftmost value.  Keep going
   * left till we get there.
   */
  while (n->left != NULL) {
    n = n->left;
  }
  return n->val;
}

/*
 * Helper function to generate a single AVL node containing a given value.
 */
static TreeNode_t *_avl_node_create(int val) {
  TreeNode_t *n = malloc(sizeof(TreeNode_t));
  if (n) {
    n->val = val;
    n->left = n->right = NULL;
    n->height = 0;
  }
  return n;
}

/*
 * Helper function to insert a given value into a subtree of a AVL rooted at
 * a given node.  Operates recursively by determining into which subtree (left
 * or right) under the given node the value should be inserted and performing
 * the insertion on that subtree.
 *
 * Returns the root of the given subtree, modified to contain a new node with
 * the specified value.
 */
static TreeNode_t *_avl_subtree_insert(TreeNode_t *n, int val) {
  if (n == NULL) {
    /*
     * If n is NULL, we know we've reached a place to insert val, so we
     * create a new node holding val and return it.
     */
    return _avl_node_create(val);
  } else if (val < n->val) {
    /*
     * If val is less than the value at n, we insert val in n's left subtree
     * (somewhere) and update n->left to point to the modified subtree (with
     * val inserted).
     */
    n->left = _avl_subtree_insert(n->left, val);
  } else {
    /*
     * If val is greater than or equal to the value at n, we insert val in n's
     * right subtree (somewhere) and update n->right to point to the modified
     * subtree (with val inserted).
     */
    n->right = _avl_subtree_insert(n->right, val);
  }

  /*
   * For the else if and else conditions, the subtree rooted at n has already
   * been modified (by setting n->left or n->right above), so we can just
   * return n here, after balancing n's subtree.
   */
  return _avl_balance(n);
}
