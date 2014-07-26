/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.80.307 (20140726)                       **
**                                                                            **
**                    File: internal/singly_linked_list.c                     **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

/* TODO: consider to implement SinglyLinkedList.reserved_head and reserved_tail
         members as SLLNode* which will hold the deleted nodes, and whenever a
         new node has to be inserted, it will insert from reserved_head, and
         replace its data -- super fast; less allocations (less fragmented
         memory blocks); takes way more space. Also: resize() will add empty
         nodes to reserved_tail (or removed from there) and size() will return
         the total number of nodes (length + reserved_length) */

#include <stdio.h>   /* FILE, snprintf() */
#include <stdlib.h>  /* size_t, malloc(), free(), labs() */
#include <string.h>  /* memcpy() */
#include "cutils/cexc.h"

#include "cutils/cbug.h"
#include "cutils/capi.h"

/*----------------------------------------------------------------------------*/
/* Exception messages */
#undef  CEXC_MSG_TYPE
#define CEXC_MSG_TYPE "SinglyLinkedList"

#undef  CEXC_MSG_ARGUMENT_NULL
#define CEXC_MSG_ARGUMENT_NULL(func, idx, arg) \
        CEXC_MSG_TYPE ", " func ": " idx " argument '" #arg "' is NULL"

#undef  CEXC_MSG_ARGUMENT_OUTOF
#define CEXC_MSG_ARGUMENT_OUTOF(func, idx, arg) \
        CEXC_MSG_TYPE ", " func ": " idx " argument '" #arg "' is out of range"

/* TODO: change this exception to:
         CEXC_MSG_NULL_POINTER passed pointer to NULL
         in DynamicArray and doumentation as well */
#undef  CEXC_MSG_NOT_INIT
#define CEXC_MSG_NOT_INIT(func) \
        CEXC_MSG_TYPE ", " func ": array is not initialised"

#undef  CEXC_MSG_EMPTY
#define CEXC_MSG_EMPTY(func) \
        CEXC_MSG_TYPE ", " func ": array is empty"

#undef  CEXC_MSG_ALLOC_FAIL
#define CEXC_MSG_ALLOC_FAIL(func) \
        CEXC_MSG_TYPE ", " func ": internal allocation failed"

#undef  CEXC_MSG_OVERLAP
#define CEXC_MSG_OVERLAP(func) \
        CEXC_MSG_TYPE ", " func ": blocks are overlapping"

/* A variable to construct the exception message in */
#undef EXCEPTION_MSG


/*----------------------------------------------------------------------------*/
/* Item type */
typedef struct sll_node
{
    struct sll_node *next;  /* Pointer to next node (link) */
    char data[];            /* Internally stored data */

} SLLNode;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Iterator type (node alias) */
typedef SLLNode cutils_csll_SinglyLinkedList_void_ptr_iterator;


/*----------------------------------------------------------------------------*/
/* Base type */
typedef struct
{
    size_t size;    /* Size of an item */
    size_t length;  /* Number of items in the list */
    SLLNode *head;  /* Pointer to first node */
    SLLNode *tail;  /* Pointer to last node */

} cutils_csll_SinglyLinkedList_void_ptr;


/*----------------------------------------------------------------------------*/
static inline void
__csll_node_ins(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                SLLNode *node_prev,  /* node before sub-sequence */
                SLLNode *node_head,  /* sub-sequence start */
                SLLNode *node_tail,  /* sub-sequence end */
                SLLNode *node_next)  /* node after sub-sequence */
{
    /* If head will be nth item */
    if (node_prev)
        node_prev->next = node_head;
    /* If head will be the first item */
    else
        linlist->head = node_head;
    /* If tail will be nth item */
    if (node_next)
        node_tail->next = node_next;
    /* If tail will be the last item */
    else
    {
        linlist->tail = node_tail;
        node_tail->next = NULL;
    }
}


/*----------------------------------------------------------------------------*/
static inline void
__csll_node_pop(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                SLLNode *node_prev,  /* node before sub-sequence */
                SLLNode *node_next)  /* node after sub-sequence */
{
    /* If node is nth item */
    if (node_prev)
        node_prev->next = node_next;
    /* If node is first item */
    else
        linlist->head = node_next;
}


/*----------------------------------------------------------------------------*/
static inline bool
__csll_node_new(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                const char *exception_msg,
                size_t exception_msg_size,
                SLLNode *node_prev,
                SLLNode *node_next,
                size_t item_count,
                char *items)
{
    /* Get item individual item size */
    size_t item_size = linlist->size;
    /* Node pointers */
    SLLNode *node_head, *node_tail, *node_temp;
    /* Allocate space for the first new node */
    node_tail = node_head = malloc(sizeof(SLLNode) + item_size);
    if (!node_head)
    {
        cutils_cexc_raise(exception_msg, exception_msg_size);
        return false; /* Internal allocation failed */
    }
    /* Store item in first node */
    memcpy(node_head->data, items, item_size);
    /* Allocate space for each of the remaining nodes */
    for (size_t i=1; i<item_count; i++)
    {
        /* Allocate space for a new node */
        node_temp = malloc(sizeof(SLLNode) + item_size);
        if (!node_temp)
        {
            cutils_cexc_raise(exception_msg, exception_msg_size);
            return false; /* Internal allocation failed */
        }
        node_tail->next = node_temp;
        memcpy(node_temp->data, items + i*item_size, item_size);
        node_tail = node_temp;
    }
    /* Insert new nodes */
    __csll_node_ins(linlist, node_prev, node_head, node_tail, node_next);
    /* Update item counter */
    linlist->length += item_count;
    return true; /* Items successfully added */
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_new(cutils_csll_SinglyLinkedList_void_ptr **linlist,
                                          size_t item_size,
                                          size_t count,
                                          void *source)
{
    /* Allocate space for list */
    cutils_csll_SinglyLinkedList_void_ptr *_linlist =
        malloc(sizeof(cutils_csll_SinglyLinkedList_void_ptr));
    if (!_linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("new")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #ifndef CSLL_OPT
        /* Set pointer to list to NULL so all other methods of
           DynamicArray won't break the code, just raise exceptions */
        *linlist = NULL;
        #endif
        return false; /* Internal allocation failed */
    }
    /* Set list to empty */
    _linlist->head = NULL;
    _linlist->tail = NULL;
    _linlist->length = 0;
    _linlist->size = item_size;
    /* Assign newly created list to passed pointer */
    *linlist = _linlist;

#ifndef CSLL_OPT
    if (count && source)
    {
#endif
        if (!__csll_node_new(_linlist,
                /* message */EXCEPTION_MSG,
         /* message length */sizeof EXCEPTION_MSG,
          /* previous node */NULL,
              /* next node */NULL,
             /* item count */count,
          /* data if items */(char *)source))
            return false; /* Internal allocation failed */
        #undef EXCEPTION_MSG
#ifndef CSLL_OPT
    }
#endif
    return true; /* The list have been successfully allocated */
}


/*----------------------------------------------------------------------------*/
void
cutils_csll_SinglyLinkedList_void_ptr_del(cutils_csll_SinglyLinkedList_void_ptr *linlist)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
#endif
        /* Remove all items */
        SLLNode *next,
                *node = linlist->head;
        while (node)
        {
            next = node->next;
            free(node);
            node = next;
        }
#ifndef CSLL_OPT
    }
#endif
    /* Delete base itself */
    free(linlist);
}


/*----------------------------------------------------------------------------*/
size_t
cutils_csll_SinglyLinkedList_void_ptr_len(cutils_csll_SinglyLinkedList_void_ptr *linlist)
{
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("len")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
#endif
    return linlist->length;
}


/*----------------------------------------------------------------------------*/
void
cutils_csll_SinglyLinkedList_void_ptr_clear(cutils_csll_SinglyLinkedList_void_ptr *linlist)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
#endif
        /* Remove all items */
        SLLNode *next,
                *node = linlist->head;
        while (node)
        {
            next = node->next;
            free(node);
            node = next;
        }
#ifndef CSLL_OPT
    }
#endif
    /* Set list empty */
    linlist->length = 0;
    linlist->head = NULL;
    linlist->tail = NULL;
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_swap(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           size_t index1,
                                           size_t index2,
                                           size_t count)
{
    size_t length;
#ifndef CSLL_OPT
    /* If pointer to list is pointing to NULL */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
#endif /* CSLL_OPT */
    /* No swapping needed */
    if ((index1 == index2) || !count)
    {
        return true; /* Successfully did nothing */
    }
    /* If list empty */
    else if (!(length = linlist->length))
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }
#ifndef CSLL_OPT
    /* If index1 or index2 out of range */
    else if (index1 >= length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("swap", "2nd", index1)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Not valid index */
    }
    else if (index2 >= length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("swap", "3rd", index2)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Not valid index */
    }
    /* If blocks are overlapping */
    if (labs(index1 - index2) < count)
    {
        #define EXCEPTION_MSG CEXC_MSG_OVERLAP("swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Not valid count */
    }
    /* If blocks are out of bounds */
    if ((index1 + count) > length || (index2 + count) > length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("swap", "4th", count)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Not valid count */
    }
#endif /* CSLL_OPT */

    SLLNode *node1_prev,  /* node before node at index1 */
            *node1_head,  /* node at index1 */
            *node1_tail,  /* node at index1 + (count - 1) */
            *node1_next,  /* node after node at index1 + (count - 1) */

            *node2_prev,  /* node before node at index2 */
            *node2_head,  /* node at index2 */
            *node2_tail,  /* node at index2 + (count - 1) */
            *node2_next,  /* node after node at index2 + (count - 1) */

            *temp1 = linlist->head,
            *temp2;
    size_t counter = 0;
    bool found_head = false,
         found_tail = false;

    /* CORE FUNCTIONALITY
       If one of the indices is 0 */
    if (!index1 || !index2)
    {
        /* Start counter */
        counter = count;
        /* Ste the first node */
        node1_prev = NULL;
        node1_head = temp1;
        found_head = true;
    }
    /* Start iterate through the list */
    for (size_t i=1;; i++)
    {
        /* Get next node too if current node is not NULL */
        if (temp1)
            temp2 = temp1->next;
        else
            temp2 = NULL;

        /* If looking for the end of the sub-sequence */
        if (counter && !--counter)
        {
            /* If already found one */
            if (found_tail)
            {
                node2_tail = temp1;
                node2_next = temp2;
                break;
            }
            /* If this is the first match */
            node1_tail = temp1;
            node1_next = temp2;
            found_tail = true;
        }
        /* If one of the indices is a match */
        if (index1 == i || index2 == i)
        {
            /* Start counter */
            counter = count;
            /* If already found one */
            if (found_head)
            {
                node2_prev = temp1;
                node2_head = temp2;
            }
            else
            /* If this is the first match */
            {
                node1_prev = temp1;
                node1_head = temp2;
                found_head = true;
            }
        }
        /* Set next node */
        temp1 = temp2;
    }

    /* If sequences are direct neighbours */
    if (node1_tail == node2_prev || node2_tail == node1_prev)
    {
        __csll_node_pop(linlist, node1_prev, node1_next);
        __csll_node_ins(linlist, node2_tail, node1_head, node1_tail, node2_next);
    }
    /* If at least there is one node between sequences */
    else
    {
        __csll_node_ins(linlist, node2_prev, node1_head, node1_tail, node2_next);
        __csll_node_ins(linlist, node1_prev, node2_head, node2_tail, node1_next);
    }
    return true; /* Swapping was successful */
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_reverse(cutils_csll_SinglyLinkedList_void_ptr *linlist)
{
    /* If pointer to list is pointing to NULL */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("reverse")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    /* If list is empty */
    if (!linlist->length)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("reverse")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }

    /* CORE FUNCTIONALITY
       Create/get/set essential values */
    SLLNode *node_prev = linlist->head,
            *node_curr = node_prev->next,
            *node_next;
    /* Swap items */
    node_prev->next = NULL;
    while (node_curr)
    {
        /* Get next node */
        node_next = node_curr->next;
        /* Reverse order */
        node_curr->next = node_prev;
        node_prev = node_curr;
        /* Set next node */
        node_curr = node_next;
    }
    /* Set head and tail pointers */
    linlist->tail = linlist->head;
    linlist->head = node_prev;
    return true; /* Successfully reversed */
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_append(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                             size_t count,
                                             void *source)
{
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("append")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else if (!source)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("append", "3rd", source)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }
    else
#ifndef CSLL_OPT
    if (count)
    {
#endif
    #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("append")
        if (!__csll_node_new(linlist,
                /* message */EXCEPTION_MSG,
         /* message length */sizeof EXCEPTION_MSG,
          /* previous node */linlist->tail,
              /* next node */NULL,
             /* item count */count,
          /* data if items */(char *)source))
            return false; /* Internal allocation failed */
        #undef EXCEPTION_MSG
#ifndef CSLL_OPT
    }
#endif
    return true; /* Successfully added new items or nothing */
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_push(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           size_t index,
                                           size_t count,
                                           void *source)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("append")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else if (!source)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("append", "3rd", source)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }
    else if (count)
    {
#endif /* CSLL_OPT */

        /* CORE FUNCTIONALITY */
        SLLNode *node_prev,
                *node_next;
        /* If insert as first item(s) */
        if (!index)
        {
            node_prev = NULL;
            node_next = linlist->head;
        }
        /* If insert as nth item(s) */
        else
        {
            node_prev = linlist->head;
            for (size_t i=1;; i++)
            {
                /* Get next node */
                if (node_prev)
                    node_next = node_prev->next;
                else
                    node_next = NULL;
                /* If index is a match */
                if (index == i)
                    break;
                /* Set next node */
                node_prev = node_next;
            }
        }
    #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("push")
        if (!__csll_node_new(linlist,
                /* message */EXCEPTION_MSG,
         /* message length */sizeof EXCEPTION_MSG,
          /* previous node */node_prev,
              /* next node */node_next,
             /* item count */count,
          /* data if items */(char *)source))
            return false; /* Internal allocation failed */
    #undef EXCEPTION_MSG
#ifndef CSLL_OPT
    }
#endif
    return true; /* Successfully added new items or nothing */
}


/*----------------------------------------------------------------------------*/
size_t
cutils_csll_SinglyLinkedList_void_ptr_pull(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           size_t index,
                                           size_t count)
{
    size_t length;
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("pull")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    /* Nothing to remove */
    else if (!count)
    {
        return 0; /* Successfully removed nothing */
    }
    /* Empty list */
    else if (!(length = linlist->length))
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("pull")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("pull", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
#else
    /* Nothing to remove or Empty array */
    if (!count || !(length = linlist->length)) return 0;
#endif /* CSLL_OPT */

    /* CORE FUNCTIONALITY
       if sub-sequence size out of bound */
    else if ((index + count) >= length)
        count = length - index;

    /* Create/get/set essential values */
    SLLNode *node_prev,
            *node_curr,
            *node_next,
            *temp = linlist->head;
    size_t counter = 0;

    /* If index is 0 */
    if (!index)
    {
        /* Start counting */
        counter = count;
        /* Set start and first item */
        node_prev = NULL;
        node_curr = temp;
    }
    /* Start iterate through the list */
    for (size_t i=1;; i++)
    {
        /* Get next node too if current node is not NULL */
        if (temp)
            node_next = temp->next;
        else
            node_next = NULL;

        /* If nth or last node of the sub-sequence */
        if (counter)
        {
            /* Free node and its data from memory */
            free(node_curr);
            /* If end of the sub-sequence */
            if (!--counter)
            {
                /* Pop out the already deleted nodes */
                __csll_node_pop(linlist, node_prev, node_next);
                linlist->length -= count;
                return count;
            }
            /* Get next node */
            node_curr = temp = node_next;
            continue;
        }
        /* If index is a match */
        if (index == i)
        {
            /* Start counting */
            counter = count;
            /* Set start and first item */
            node_prev = temp;
            node_curr = node_next;
        }
        /* Set next node */
        temp = node_next;
    }
}


/*----------------------------------------------------------------------------*/
/* TODO: pop() has only three extra statements compared to pull()
         1) else if (!destination) ...
         2) char *dest = (char *)destination;
         3) memcpy(dest + (count - counter)*item_size, node_curr->data, item_size);
         try to "merge" these two together -- with a macro?
         also sub() has the same lines except no popping and freeing
         (and their error message "names" differes of course) */
size_t
cutils_csll_SinglyLinkedList_void_ptr_pop(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index,
                                          size_t count,
                                          void *destination)
{
    size_t length;
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("pop")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    /* Nothing to remove */
    else if (!count)
    {
        return 0; /* Successfully removed nothing */
    }
    /* Invalid destination */
    else if (!destination)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("pop", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully popped nothing */
    }
    /* Empty list */
    else if (!(length = linlist->length))
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("pop")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("pop", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
#else
    /* Nothing to remove or Empty array */
    if (!count || !(length = linlist->length)) return 0;
#endif /* CSLL_OPT */

    /* CORE FUNCTIONALITY
       if sub-sequence size out of bound */
    else if ((index + count) >= length)
        count = length - index;

    /* Create/get/set essential values */
    SLLNode *node_prev,
            *node_curr,
            *node_next,
            *temp = linlist->head;
    size_t size = linlist->size,
           counter = 0;
    char *_destination = (char *)destination;

    /* If index is 0 */
    if (!index)
    {
        /* Start counting */
        counter = count;
        /* Set start and first item */
        node_prev = NULL;
        node_curr = temp;
    }
    /* Start iterate through the list */
    for (size_t i=1;; i++)
    {
        /* Get next node too if current node is not NULL */
        if (temp)
            node_next = temp->next;
        else
            node_next = NULL;

        /* If nth or last node of the sub-sequence */
        if (counter)
        {
            /* Free node and its data from memory */
            memcpy(_destination + (count - counter)*size, node_curr->data, size);
            free(node_curr);
            /* If end of the sub-sequence */
            if (!--counter)
            {
                /* Pop out the already deleted nodes */
                __csll_node_pop(linlist, node_prev, node_next);
                linlist->length -= count;
                return count;
            }
            /* Set next node */
            node_curr = temp = node_next;
            continue;
        }
        /* If index is a match */
        if (index == i)
        {
            /* Start counting */
            counter = count;
            /* Set start and first item */
            node_prev = temp;
            node_curr = node_next;
        }
        /* Set next node */
        temp = node_next;
    }
}


/*----------------------------------------------------------------------------*/
size_t
cutils_csll_SinglyLinkedList_void_ptr_sub(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index,
                                          size_t count,
                                          void *destination)
{
    size_t length;
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("sub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    /* Nothing to remove */
    else if (!count)
    {
        return 0; /* Successfully removed nothing */
    }
    /* Invalid destination */
    else if (!destination)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("sub", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully popped nothing */
    }
    /* Empty list */
    else if (!(length = linlist->length))
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("sub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("sub", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
#else
    /* Nothing to remove or Empty array */
    if (!count || !(length = linlist->length)) return 0;
#endif /* CSLL_OPT */

    /* CORE FUNCTIONALITY
       if sub-sequence size out of bound */
    else if ((index + count) >= length)
        count = length - index;

    /* Create/get/set essential values */
    SLLNode *node_prev,
            *node_curr,
            *node_next,
            *temp = linlist->head;
    size_t size = linlist->size,
           counter = 0;
    char *_destination = (char *)destination;

    /* If index is 0 */
    if (!index)
    {
        /* Start counting */
        counter = count;
        /* Set start and first item */
        node_prev = NULL;
        node_curr = temp;
    }
    /* Start iterate through the list */
    for (size_t i=1;; i++)
    {
        /* Get next node too if current node is not NULL */
        if (temp)
            node_next = temp->next;
        else
            node_next = NULL;

        /* If nth or last node of the sub-sequence */
        if (counter)
        {
            /* Free node and its data from memory */
            memcpy(_destination + (count - counter)*size, node_curr->data, size);
            /* If end of the sub-sequence */
            if (!--counter)
                return count;
            /* Set next node */
            node_curr = temp = node_next;
            continue;
        }
        /* If index is a match */
        if (index == i)
        {
            /* Start counting */
            counter = count;
            /* Set start and first item */
            node_prev = temp;
            node_curr = node_next;
        }
        /* Set next node */
        temp = node_next;
    }
}


/*----------------------------------------------------------------------------*/
void
cutils_csll_SinglyLinkedList_void_ptr_truncate(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                               size_t index)
{
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("truncate")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else
#endif /* CSLL_OPT */
    /* CORE FUNCTIONALITY
       Index out of range */
    if (index >= linlist->length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("truncate", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Out of range */
    }
    /* Create/get/set essential values */
    SLLNode *prev = linlist->head,
            *node;
    bool delete = false;
    /* If index is 0 */
    if (!index)
    {
        linlist->length = 0;
        linlist->tail = NULL;
        delete = true;
    }
    /* Remove items starts from index */
    for (size_t i=1; prev; i++)
    {
        /* Get next node */
        node = prev->next;
        /* Delete node if node is at or after index */
        if (delete)
            free(prev);
        /* If index is a match */
        else if (i == index)
        {
            linlist->length = i;
            /* Set tail node */
            linlist->tail = prev;
            prev->next = NULL;
            delete = true;
        }
        /* Set next node */
        prev = node;
    }
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_set(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index,
                                          size_t count,
                                          void *source)
{
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("set")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    /* Nothing to set */
    else if (!count)
    {
        return true; /* Successfully set nothing */
    }
    /* Invalid source */
    else if (!source)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("set", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully set nothing */
    }
    /* Out of range */
    else if (index >= linlist->length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("set", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Out of range */
    }
#else
    /* Nothing to set */
    if (!count) return true; /* Successfully set nothing */
#endif /* CSLL_OPT */

    /* Create/get/cast essential values */
    SLLNode *node = linlist->head;
    char *data = (char *)source;
    size_t counter = 0,
           item_size = linlist->size;

    /* CORE FUNCTIONALITY
       Iterate through list and set values */
    for (size_t i=0; node; i++)
    {
        /* If set values to node */
        if (counter)
        {
            memcpy(node->data, data + (count - counter)*item_size, item_size);
            if (!--counter)
                return true;
        }
        /* If index is a match */
        else if (i == index)
        {
            memcpy(node->data, data, item_size);
            counter = count - 1;
        }
        /* Set next node */
        node = node->next;
    }
    return false;
}


/*----------------------------------------------------------------------------*/
void *
cutils_csll_SinglyLinkedList_void_ptr_get(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("get")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return NULL; /* Cannot operate on nothing */
    }
    else if (index >= linlist->length)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("get", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return NULL;
    }
#endif /* CSLL_OPT */

    /* Create/get/set essential values */
    SLLNode *node = linlist->head;
    /* CORE FUNCTIONALITY
       Iterate through list and return data at given index */
    for (size_t i=0; node; i++)
    {
        /* If index is a match */
        if (i == index)
            return node->data;
        /* Set next node */
        node = node->next;
    }
#ifndef CSLL_OPT
    #define EXCEPTION_MSG CEXC_MSG_EMPTY("get")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
    #undef EXCEPTION_MSG
#endif /* CSLL_OPT */
    return NULL;
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_find(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           bool (*compare)(const void*, const void*, size_t),
                                           const void *item,
                                           size_t *index)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("find")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else if (!index)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("find", "4th", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Invalid data */
    }
    else
#endif /* CSLL_OPT */
    if (linlist->length)
    {
        /* Create/get/set essential values */
        SLLNode *node = linlist->head;
        size_t item_size = linlist->size;
        /* CORE FUNCTIONALITY
           Iterate through list and find matching items */
        for (size_t i=0; node; i++)
        {
            /* If item is a match */
            if (compare(node->data, item, item_size))
            {
                *index = i;
                return true; /* Found first appearance of item */
            }
            /* Set next node */
            node = node->next;
        }
        return false; /* Did not find any appearances of item */
    }
#ifndef CSLL_OPT
    #define EXCEPTION_MSG CEXC_MSG_EMPTY("find")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
    #undef EXCEPTION_MSG
#endif /* CSLL_OPT */
    return false;
}


/*----------------------------------------------------------------------------*/
/* NOTE: maybe rename const void *item --> const void *target ?
         if it will be done, de the same in DynamicArray methods as well */
size_t
cutils_csll_SinglyLinkedList_void_ptr_findall(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                              bool (*compare)(const void*, const void*, size_t),
                                              const void *item,
                                              size_t *indices)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("find")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    else if (!indices)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("find", "4th", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Invalid data */
    }
    else
#endif /* CSLL_OPT */
    if (linlist->length)
    {
        /* Create/get/set essential values */
        SLLNode *node = linlist->head;
        size_t count = 0,
               item_size = linlist->size;
        /* CORE FUNCTIONALITY
           Iterate through list and find matching items */
        for (size_t i=0; node; i++)
        {
            /* If item is a match */
            if (compare(node->data, item, item_size))
                indices[count++] = i;
            /* Set next node */
            node = node->next;
        }
        return count; /* Number of items found */
    }
#ifndef CSLL_OPT
    #define EXCEPTION_MSG CEXC_MSG_EMPTY("find")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
    #undef EXCEPTION_MSG
#endif /* CSLL_OPT */
    return 0;
}

/*----------------------------------------------------------------------------*/
cutils_csll_SinglyLinkedList_void_ptr_iterator *
cutils_csll_SinglyLinkedList_void_ptr_iter(cutils_csll_SinglyLinkedList_void_ptr *linlist)
{
    cutils_csll_SinglyLinkedList_void_ptr_iterator *node =
        malloc(sizeof(cutils_csll_SinglyLinkedList_void_ptr_iterator));
    if (!node)
    {
        #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("iter")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Internal allocation failed */
    }
    /* Set iterator */
    node->next = linlist->head;
    /* Return iterator */
    return node;
}


/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_next(cutils_csll_SinglyLinkedList_void_ptr_iterator *node,
                                           void *data)
{
    /* If not last item */
    if (node->next)
    {
        *(void **)data = node->next->data;
        node->next = node->next->next;
        return true;
    }
    /* If last item */
    else
    {
        free(node);
        return false;
    }
}


/*----------------------------------------------------------------------------*/
char *
cutils_csll_SinglyLinkedList_void_ptr_format(const void *data,
                                             char **buffer,
                                             size_t *buffer_size)
{
    /* buffer_size could be used to realloc buffer if
       it is too small to contain the the formatted item */
    if (!*(char *)data)
        snprintf(*buffer, *buffer_size, "<pointer to NULL>");
    else
        snprintf(*buffer, *buffer_size, "<pointer to %p>", data);
    return *buffer;
}


/*----------------------------------------------------------------------------*/
void
cutils_csll_SinglyLinkedList_void_ptr_print(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                            FILE *stream,
                                            const char *name,
                                            char *(*format)(const void*, char**, size_t*))
{
    /* If list is empty */
    if (!linlist->length)
        fprintf(stream, "%s{}\n", name);
    /* If list is filled */
    else
    {
        fprintf(stream, "%s{", name);
        size_t buffer_size = 128;
        char *buffer = malloc(buffer_size);
        if (!buffer)
        {
            #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("print")
            cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
            #undef EXCEPTION_MSG
            fprintf(stream, "...}\n");
            return;
        }
        SLLNode *node = linlist->head;
        /* Print first item */
        fprintf(stream, "%s", format(node->data, &buffer, &buffer_size));
        /* Print all remaining items, with leading comma */
        while ((node = node->next))
            fprintf(stream, ", %s", format(node->data, &buffer, &buffer_size));
        /* Clean up and close the format */
        free(buffer);
        fprintf(stream, "}\n");
    }
}

/*----------------------------------------------------------------------------*/
bool
cutils_csll_SinglyLinkedList_void_ptr_compare(const void *item1,
                                              const void *item2,
                                              size_t item_size)
{
    return !memcmp(item1, item2, item_size);
}
