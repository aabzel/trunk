#include "linked_list_array.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#if 0
static void reverse_util (ListNode* curr, ListNode* prev, ListNode** head);

list_node_t *pHead;

list_node_t Node1;
list_node_t Node2;
list_node_t Node3;
list_node_t Node4;
list_node_t Node5;

#endif

#if 0

/* Function to insert a node at the beginging of the linked list */
bool push_val (list_node_t **pInHead, int newVal) {
    bool res = false;
    /* allocate node */
    list_node_t *newNodePtr = (list_node_t *)malloc (sizeof (list_node_t));
    if (newNodePtr) {
        newNodePtr->data = newVal;
        newNodePtr->nextNode = (*pInHead);
        (*pInHead) = newNodePtr;
        res = true;
    }
    return res;
}

void list_print_reverse (void) {
    list_print_rev (&Node1);
    printf ("\n");
}
#endif

#if 0

void list_print_rev (list_node_t *pHead) {
    if (pHead) {
        list_print_rev (pHead->nextNode);
        printf (" %d", pHead->val);
    }
}
#endif
#if 0
void list_print_fwd (void) {
    list_node_t *curNode = &Node1;
    while (NULL != curNode->nextNode) {
        printf (" %d", curNode->val);
        curNode = curNode->nextNode;
    }
    printf (" %d", curNode->val);
    printf ("\n");
}

/* Function to insert a node at the beginging of the linked list */
bool push_val (list_node_t **pInHead, int newVal) {
    bool res = false;
    /* allocate node */
    list_node_t *newNodePtr = (list_node_t *)malloc (sizeof (list_node_t));
    if (newNodePtr) {
        newNodePtr->data = newVal;
        newNodePtr->nextNode = (*pInHead);
        (*pInHead) = newNodePtr;
        res = true;
    }
    return res;
}

#endif

#if 0
void save_list_to_file (list_node_t *pInHead, char *filename) {
    FILE * fp;
    printf ("\nSave to file: %s\n", filename);
    fp = fopen (filename, "a");
    if (fp) {
        list_node_t *curNode = pInHead;
        while (curNode) {
            print_array_to_file_pointer (fp, curNode->data.pArr, curNode->data.arrSize);
            curNode = curNode->nextNode;
        }
        /* write 10 lines of text into the file stream*/
        //for (i = 0; i < numItem; i++) {
        //    fprintf (fp, "%d ", array [i]);
        //}
        //fprintf (fp, "\n");
        fclose (fp);
    } else {
        printf ("\n Unable to open file %s", filename);
    }

}

bool linked_list_deinit (list_node_t *pInHead) {
    list_node_t *curNode = pInHead;
    list_node_t *prevNode = pInHead;
    bool res = false;
    if (pInHead) {
        if (NULL == curNode->nextNode) {
            free (curNode->data.pArr);
            free (curNode);
            res = true;
        } else {
            free (curNode->data.pArr);
            while (NULL != curNode->nextNode) {
                prevNode = curNode;
                curNode = curNode->nextNode;
                free (curNode->data.pArr);
                free (prevNode);
            }
            res = true;
        }
    }
    return res;
}

bool linked_list_add_array (list_node_t **pInHead, int *inArr, int arrSize) {
    /*Find the end of Linked List*/
    bool res = false;
    if (0 < arrSize) {
        list_node_t *newNode = NULL;
        int amountOfElem = list_num_of_elements (*pInHead);
        if (0 < amountOfElem) {
            list_node_t *pCurNode = *pInHead;
            list_node_t *pEndNode = NULL;
            while (NULL != pCurNode->nextNode) {
                pCurNode = pCurNode->nextNode;
            }
            pEndNode = pCurNode;
            newNode = malloc (sizeof(list_node_t));
            if (newNode) {
                newNode->nextNode = NULL;
                newNode->data.arrSize = arrSize;
                newNode->data.pArr = memdup (inArr, sizeof(int) * arrSize);
                pEndNode->nextNode = newNode;
                res = true;
            } else {
                printf ("\nUnable to malloc new node!\n");
            }
        }
        if (0 == amountOfElem) {
            newNode = malloc (sizeof(list_node_t));
            if (newNode) {
                newNode->nextNode = NULL;
                newNode->data.arrSize = arrSize;
                newNode->data.pArr = memdup (inArr, sizeof(int) * arrSize);

                *pInHead = newNode;
                res = true;
            } else {
                printf ("\nUnable to malloc new node!\n");
            }
        }
    } else {
        printf ("\nArray is 0\n");
    }
    return res;

}

int list_num_of_data_byte (list_node_t *pHead) {
    int amountOfByte = 0;
    if (pHead) {
        list_node_t *pCurNode = pHead;
        if (pCurNode) {
            while (pCurNode) {
                amountOfByte += (pCurNode->data.arrSize) * (sizeof(int));
                pCurNode = pCurNode->nextNode;
            }
        }
    }
    return amountOfByte;
}

list_node_t *get_node_by_index (list_node_t *pHead, int desInd) {
    list_node_t *pCurNode = pHead;
    list_node_t *pRetNode = NULL;
    int curIndex = 0;
    if (pCurNode) {
        while (pCurNode) {
            if (desInd == curIndex) {
                pRetNode = pCurNode;
                break;
            }
            curIndex++;
            pCurNode = pCurNode->nextNode;
        }
    }

    return pRetNode;
}

int list_num_of_elements (list_node_t *pHead) {
    int amountOfElem = 0;
    if (pHead) {
        list_node_t *pCurNode = pHead;
        if (pCurNode) {
            while (pCurNode) {
                amountOfElem++;
                pCurNode = pCurNode->nextNode;
            }
        }
    }

    return amountOfElem;
}

void print_list1 (list_node_t *pHead) {
    int numElem = list_num_of_elements (pHead);
    printf ("\nList content: amount of item: [%d]\n", numElem);
    if (pHead) {
        list_node_t *pCurNode = pHead;
        while (pCurNode) {
            print_curr_array (pCurNode->data.pArr, pCurNode->data.arrSize);
            pCurNode = pCurNode->nextNode;
        }
    }
}

#endif
