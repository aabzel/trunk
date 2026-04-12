#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

/* Function to push a node */
bool list_add_node_front(ListNode_t **head_node, int new_data) {
  bool res = false;
  ListNode_t *new_node = NULL;
  new_node = (ListNode_t *)malloc(sizeof(ListNode_t));
  if (NULL != new_node) {
    (new_node)->val = new_data;
    (new_node)->next = (*head_node);
    *head_node = new_node;
    res = true;
  }
  return res;
}
#if 0
ListNode_t** reverseList (ListNode_t** head) {
    ListNode_t** prevNode = NULL;
    ListNode_t** currentNode = head;
    ListNode_t** nextNode = NULL;
    while (currentNode != NULL) {
        // Store next
        nextNode = currentNode->next;

        // Reverse current node's pointer
        currentNode->next = prevNode;

        // Move pointers one position ahead.
        prevNode = currentNode;
        currentNode = nextNode;
    }
    head = prevNode;
    return head;
}

// This function mainly calls reverseUtil()
// with prev as NULL
void reverse_rec (ListNode_t*** head) {
    if (!head)
        return;
    reverse_util (*head, NULL, head);
}
#endif

// A simple and tail recursive function to reverse
// a linked list.  prev is passed as NULL initially.
static void reverse_util(ListNode_t *curr, ListNode_t *prev,
                         ListNode_t **head) {
  /* If last node mark it head*/
  if (!curr->next) {
    *head = curr;

    /* Update next to prev node */
    curr->next = prev;
    return;
  }

  /* Save curr->next node for recursive call */
  ListNode_t *next = curr->next;

  /* and update next ..*/
  curr->next = prev;

  reverse_util(next, curr, head);
}

#if 0
struct xListNode_t *middle_node (struct xListNode_t *head) {
    struct xListNode_t *slow = head;
    struct xListNode_t *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
#endif

int linked_list_counts(ListNode_t *head_node) {
  int cnt = 0;
  if (head_node) {
    ListNode_t *cur_node = head_node;
    while (NULL != cur_node) {
      cnt++;
      cur_node = cur_node->next;
    }
  }
  return cnt;
}

ListNode_t *is_data_exist_linked_list(ListNode_t *head_node, int data) {
#ifdef DEBUG_LINKED_LIST
  printf("\n[d] %s() %p", __FUNCTION__, head_node);
#endif
  ListNode_t *cur_node = NULL;
  int cnt = 0;
  int num = linked_list_counts(head_node);
  if (head_node) {
    cur_node = head_node;
    while (NULL != cur_node) {
      printf(",");
      cnt++;
#ifdef DEBUG_LINKED_LIST
      printf("\n[d] %s() iter cnt %d", __FUNCTION__, cnt);
#endif
      if (num < cnt) {
        printf("\n[d] num < cnt");
        cur_node = NULL;
        break;
      }
      if (data == cur_node->val) {
        printf("\n[d] cur_node: %p %d", cur_node, cur_node->val);
        break;
      }
      if (cur_node->next) {
        cur_node = cur_node->next;
      } else {
        cur_node = NULL;
      }
    }
  } else {
    printf("\n[d] error node");
  }
#ifdef DEBUG_LINKED_LIST
  printf("\n[d] %s() node [%p] data end", __FUNCTION__, cur_node);
#endif
  return cur_node;
}

#if 0
bool delete_node (ListNode_t **node) {
#if 1
    printf ("\n[d] %s() node=%p val=%d", __FUNCTION__, *node, (*node)->val);
#endif
    if (NULL == (*node)) {
#if 0
        printf ("\n[d] empty list\n");
#endif
        return false;
    } else {
#if 0
        printf ("\n[d] %s() node=%p val=%d", __FUNCTION__, *node, (*node)->val);
        printf ("\n[d] valid node %p\n", *node);
#endif
        if ((*node)->next == NULL) {
#if 0
            printf ("\n[d] This is last node\n");
#endif
            (*node)->val = 0;
            // free((*node)); //crash ?
            (*node) = NULL; // crash ?
#if 0
            printf ("\n[d] Empty list\n");
#endif
            return true;
        } else {
            ListNode_t *temp = (*node)->next;
            // Copy data of the next node to current node
            (*node)->val = (*node)->next->val;
            (*node)->next = (*node)->next->next;
            free (temp);
            return true;
        }
    }
    return false;
}

bool linked_list_deinit (ListNode_t **head) {
#if 0
    printf ("\n[d] %s()", __FUNCTION__);
#endif
    if (NULL == head) {
        return true;
    }
    if (NULL == *head) {
        return true;
    }
    bool res = false;
    int del_cnt = 0;
    int num_el = linked_list_counts (*head);
    printf ("\n[d] elements in the list %d", num_el);

    for (int i = 0; i < num_el; i++) {
        res = delete_node (head);
        if (true == res) {
            del_cnt++;
        } else {
            break;
        }
    }

    printf ("\n[d] del node done %d", del_cnt);
    if (num_el == del_cnt) {
        printf ("\n[d] del fine ");
        res = true;
        (*head) = NULL;
    } else {
        printf ("\n[d] cnt!=del %d!=%d", num_el, del_cnt);
    }

    printf ("\n[d] %s() done", __FUNCTION__);
    return res;
}

#endif

int val_by_index(ListNode_t *head_node, int des_index) {
  ListNode_t *ret_node = NULL;
  int val = -1;
  ret_node = node_by_index(head_node, des_index);
  if (NULL != ret_node) {
    val = ret_node->val;
  }
  return val;
}

bool swap_node_ll(ListNode_t *node_a, ListNode_t *node_b) {
  bool res = false;
  if (node_a && node_b) {
    int temp_a = node_a->val;
    int temp_b = node_b->val;
    node_a->val = temp_b;
    node_b->val = temp_a;
    res = true;
  }
  return res;
}

ListNode_t *node_by_index(ListNode_t *head_node, int des_index) {
  int cur_index = 0;
  ListNode_t *ret_node = NULL;
  ListNode_t *cur_node = head_node;
  while (cur_node != NULL) {
    if (des_index == cur_index) {
      ret_node = cur_node;
      break;
    }
    cur_index++;
    cur_node = cur_node->next;
  }
  return ret_node;
}

/* Function to print linked list */
void print_linked_list(ListNode_t *head_node) {
  if (head_node) {

    ListNode_t *cur_node = head_node;
    printf("\n Start of list\n");
    while (cur_node != NULL) {
      printf("%d  ", cur_node->val);
      cur_node = cur_node->next;
    }
    printf("\n End of list\n");
  } else {
    printf("\n ptr error\n");
  }
}
