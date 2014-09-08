/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.219 (20140908)                       **
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
         the total number of nodes (length + reserved_length)
         - - -
         Update1: after refactoring SLL, so now each node can be vary in size,
         it is most likely that the previous problem is not a problem any more,
         since, it is very unlikely that a node will match an "empty" one
         later on*/

#define FILE_STARTS_HERE
#include <stdio.h>   /* FILE, snprintf() */
#include <stdlib.h>  /* size_t, malloc(), free(), labs() */
#include <string.h>  /* memcpy() */

/* If 'optimised' or the 'exceptions are not available' */
#if defined CSLL_OPT
  #define cutils_cexc_raise(msg, len)
#else
  #include "cexc.h"
  #include "internal/defs.h"
#endif

/*----------------------------------------------------------------------------*/
/* Exception messages */
#undef  TYPE_REPR
#define TYPE_REPR "SinglyLinkedList"
#undef  SUBTYPE_REPR
#define SUBTYPE_REPR TYPE_REPR "_iterator"

/*----------------------------------------------------------------------------*/
/* Shorthands for this source */
#undef _concat_underscore
#undef concat_underscore
#undef LINKED_LIST
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD
#define _concat_underscore(token1, token2) token1##_##token2
#define concat_underscore(token1, token2) _concat_underscore(token1, token2)
#define LINKED_LIST cutils_csll_SinglyLinkedList_void_ptr
#define METHOD(func)  concat_underscore(LINKED_LIST, func)
#define SUPPORT(type) concat_underscore(LINKED_LIST, type)
#define SUPPORT_METHOD(type, func) concat_underscore(LINKED_LIST, type##_##func)

/*----------------------------------------------------------------------------*/
/* Support type */
typedef struct sll_node
{
    struct sll_node *next;  /* Pointer to next node (link) */
    char data[];            /* Internally stored data */

} SLLNode;



/*----------------------------------------------------------------------------*/
/* Base type */
typedef struct
{
    size_t length;  /* Number of items in the list */
    SLLNode *head;  /* Pointer to first node */
    SLLNode *tail;  /* Pointer to last node */

} LINKED_LIST;



/*----------------------------------------------------------------------------*/
/* Iterator type (doubly linked node) */
typedef struct
{
    LINKED_LIST *list;
    SLLNode *prev;  /* Pointer to previous node */
    SLLNode *curr;  /* Pointer to current node */
    SLLNode *next;  /* Pointer to next node (link) */
} SLLIterator;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Iterator type (public alias) */
typedef SLLIterator SUPPORT(iterator);



/*----------------------------------------------------------------------------*/
static inline void
__csll_node_ins(LINKED_LIST *linlist,
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
__csll_node_pop(LINKED_LIST *linlist,
                SLLNode *node_prev,  /* node before sub-sequence */
                SLLNode *node_next)  /* node after sub-sequence */
{
    /* If current node was nth item */
    if (node_prev)
        node_prev->next = node_next;
    /* If current node was first item */
    else
        linlist->head = node_next;

    /* If current node was last item */
    if (!node_next)
        linlist->tail = node_prev;
}



/*----------------------------------------------------------------------------*/
static inline bool
__csll_node_new(LINKED_LIST *linlist,
                const char *exception_msg,
                size_t exception_msg_size,
                SLLNode *node_prev,
                SLLNode *node_next,
                size_t item_size,
                size_t item_count,
                char *items)
{
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
METHOD(new)(LINKED_LIST **linlist,
            size_t item_size,
            size_t count,
            void *source)
{
    /* Allocate space for list */
    LINKED_LIST *_linlist = malloc(sizeof(LINKED_LIST));
    if (!_linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "new")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        *linlist = NULL;
        return false; /* Internal allocation failed */
    }
    /* Set list to empty */
    _linlist->head = NULL;
    _linlist->tail = NULL;
    _linlist->length = 0;
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
              /* item size */item_size,
             /* item count */count,
          /* data if items */(char *)source))
            return false; /* Internal allocation failed */
        #undef EXCEPTION_MSG
#ifndef CSLL_OPT
    }
#endif
    return true; /* The list have been successfully allocated */
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
METHOD(new_default1)(LINKED_LIST **linlist)
{
    return METHOD(new)(linlist, 0, 0, NULL);
}



/*----------------------------------------------------------------------------*/
void
METHOD(del)(LINKED_LIST *linlist)
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
METHOD(len)(LINKED_LIST *linlist)
{
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "len")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Cannot operate on nothing */
    }
#endif
    return linlist->length;
}



/*----------------------------------------------------------------------------*/
void
METHOD(clear)(LINKED_LIST *linlist)
{
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "clear")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return; /* Cannot operate on nothing */
    }
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
    /* Set list empty */
    linlist->length = 0;
    linlist->head = NULL;
    linlist->tail = NULL;
}



/*----------------------------------------------------------------------------*/
bool
METHOD(swap)(LINKED_LIST *linlist,
             size_t index1,
             size_t index2,
             size_t count)
{
    size_t length;
#ifndef CSLL_OPT
    /* If pointer to list is pointing to NULL */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return true; /* Successfully did nothing */
    }
#ifndef CSLL_OPT
    /* If index1 or index2 out of range */
    else if (index1 >= length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "swap", "2nd", index1)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Not valid index */
    }
    else if (index2 >= length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "swap", "3rd", index2)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Not valid index */
    }
    /* If blocks are overlapping */
    if (labs(index1 - index2) < count)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_OVERLAP(TYPE_REPR, "swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Not valid count */
    }
    /* If blocks are out of bounds */
    if ((index1 + count) > length || (index2 + count) > length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "swap", "4th", count)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
METHOD(swap_default3)(LINKED_LIST *linlist,
                      size_t index1,
                      size_t index2)
{
    return METHOD(swap)(linlist, index1, index2, 1);
}



/*----------------------------------------------------------------------------*/
bool
METHOD(reverse)(LINKED_LIST *linlist)
{
    /* If pointer to list is pointing to NULL */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "reverse")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on nothing */
    }
    /* If list is empty */
    if (!linlist->length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "reverse")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
METHOD(append)(LINKED_LIST *linlist,
               size_t item_size,
               size_t count,
               void *source)
{
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "append")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on nothing */
    }
    else if (!source)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "append", "3rd", source)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return true; /* Successfully did nothing */
    }
    else
#ifndef CSLL_OPT
    if (count)
    {
#endif
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "append")
        if (!__csll_node_new(linlist,
                /* message */EXCEPTION_MSG,
         /* message length */sizeof EXCEPTION_MSG,
          /* previous node */linlist->tail,
              /* next node */NULL,
              /* item size */item_size,
             /* item count */count,
          /* data if items */(char *)source))
            return false; /* Internal allocation failed */
#ifndef CSLL_OPT
    }
#endif
    return true; /* Successfully added new items or nothing */
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
METHOD(append_default3)(LINKED_LIST *linlist,
                        size_t item_size,
                        void *source)
{
    return METHOD(append)(linlist, item_size, 1, source);
}



/*----------------------------------------------------------------------------*/
bool
METHOD(push)(LINKED_LIST *linlist,
             size_t index,
             size_t item_size,
             size_t count,
             void *source)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "append")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on nothing */
    }
    else if (!source)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "append", "3rd", source)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "push")
        if (!__csll_node_new(linlist,
                /* message */EXCEPTION_MSG,
         /* message length */sizeof EXCEPTION_MSG,
          /* previous node */node_prev,
              /* next node */node_next,
              /* item size */item_size,
             /* item count */count,
          /* data if items */(char *)source))
            return false; /* Internal allocation failed */
#ifndef CSLL_OPT
    }
#endif
    return true; /* Successfully added new items or nothing */
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
METHOD(push_default4)(LINKED_LIST *linlist,
                      size_t index,
                      size_t item_size,
                      void *source)
{
    return METHOD(push)(linlist, index, item_size, 1, source);
}



/*----------------------------------------------------------------------------*/
size_t
METHOD(pull)(LINKED_LIST *linlist,
             size_t index,
             size_t count)
{
    size_t length;
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "pull")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "pull")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "pull", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
METHOD(pull_default2)(LINKED_LIST *linlist,
                      size_t index)
{
    return METHOD(pull)(linlist, index, 1);
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
METHOD(pop)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *destination)
{
    size_t length;
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "pop")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "pop", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Successfully popped nothing */
    }
    /* Empty list */
    else if (!(length = linlist->length))
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "pop")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "pop", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
            memcpy(_destination + (count - counter)*item_size,
                   node_curr->data, item_size);
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

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
METHOD(pop_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *destination)
{
    return METHOD(pop)(linlist, index, item_size, 1, destination);
}



/*----------------------------------------------------------------------------*/
size_t
METHOD(sub)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *destination)
{
    size_t length;
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "sub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "sub", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Successfully popped nothing */
    }
    /* Empty list */
    else if (!(length = linlist->length))
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "sub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "sub", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
            memcpy(_destination + (count - counter)*item_size,
                   node_curr->data, item_size);
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

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
METHOD(sub_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *destination)
{
    return METHOD(sub)(linlist, index, item_size, 1, destination);
}



/*----------------------------------------------------------------------------*/
void
METHOD(truncate)(LINKED_LIST *linlist,
                 size_t index)
{
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "truncate")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return; /* Cannot operate on nothing */
    }
    else
#endif /* CSLL_OPT */
    /* CORE FUNCTIONALITY
       Index out of range */
    if (index >= linlist->length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "truncate", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
METHOD(truncate_default1)(LINKED_LIST *linlist)
{
    METHOD(truncate)(linlist, 0);
}



/*----------------------------------------------------------------------------*/
/* TODO: this is considered to be a very dangerous function, because right now
         the function can't check the current SLLNode's size. It's not a problem,
         when the size is lesser than or equal to the new item, but it will lead
         to SEGFAULT when it is greater. One solution can be to store the
         item_size in each SLLNode, however, that is a very large extra memory
         overhead. Also, if the content of the list is homogeneous, it is a very
         redundant solution too. Another possible option is, to offer a
         pre-defined SLLBoundedNode, which knows its own size, and which can be
         added as the 'data' of a regular SLLNode. In that case only a very thin
         wrapper will be needed, to get access to the original item data */
bool
METHOD(set)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *source)
{
#ifndef CSLL_OPT
    /* Not initialised */
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "set")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "set", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return true; /* Successfully set nothing */
    }
    /* Out of range */
    else if (index >= linlist->length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "set", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Out of range */
    }
#else
    /* Nothing to set */
    if (!count) return true; /* Successfully set nothing */
#endif /* CSLL_OPT */

    /* Create/get/cast essential values */
    SLLNode *node = linlist->head;
    char *data = (char *)source;
    size_t counter = 0;

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

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
METHOD(set_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *source)
{
    return METHOD(set)(linlist, index, item_size, 1, source);
}



/*----------------------------------------------------------------------------*/
void *
METHOD(get)(LINKED_LIST *linlist,
            size_t index)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "get")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return NULL; /* Cannot operate on nothing */
    }
    else if (index >= linlist->length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "get", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "get")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
#endif /* CSLL_OPT */
    return NULL;
}



/*----------------------------------------------------------------------------*/
bool
METHOD(compare)(const void *item1,
                const void *item2,
                size_t item_size)
{
    return !memcmp(item1, item2, item_size);
}



/*----------------------------------------------------------------------------*/
bool
METHOD(find)(LINKED_LIST *linlist,
             bool (*compare)(const void*, const void*, size_t),
             size_t item_size,
             const void *item,
             size_t *index)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "find")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on nothing */
    }
    else if (!index)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "find", "4th", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Invalid data */
    }
    else
#endif /* CSLL_OPT */
    if (linlist->length)
    {
        /* Create/get/set essential values */
        SLLNode *node = linlist->head;
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
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "find")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
#endif /* CSLL_OPT */
    return false;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
METHOD(find_default4)(LINKED_LIST *linlist,
                      size_t item_size,
                      const void *item,
                      size_t *index)
{
    return METHOD(find)(linlist, METHOD(compare), item_size, item, index);
}



/*----------------------------------------------------------------------------*/
/* NOTE: maybe rename const void *item --> const void *target ?
         if it will be done, do the same in DynamicArray methods as well */
size_t
METHOD(findall)(LINKED_LIST *linlist,
                bool (*compare)(const void*, const void*, size_t),
                size_t item_size,
                const void *item,
                size_t *indices)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "find")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Cannot operate on nothing */
    }
    else if (!indices)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "find", "4th", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return 0; /* Invalid data */
    }
    else
#endif /* CSLL_OPT */
    if (linlist->length)
    {
        /* Create/get/set essential values */
        SLLNode *node = linlist->head;
        size_t count = 0;
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
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "find")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
#endif /* CSLL_OPT */
    return 0;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
METHOD(findall_default4)(LINKED_LIST *linlist,
                         size_t item_size,
                         const void *item,
                         size_t *index)
{
    return METHOD(findall)(linlist, METHOD(compare), item_size, item, index);
}



/*----------------------------------------------------------------------------*/
SUPPORT(iterator) *
METHOD(iter)(LINKED_LIST *linlist)
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "iter")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return NULL; /* Cannot operate on nothing */
    }
#endif
    SLLIterator *iterator = malloc(sizeof(SLLIterator));
    if (!iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "iter")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return NULL; /* Internal allocation failed */
    }
    /* Set iterator */
    iterator->list = linlist;
    iterator->prev = iterator->curr = NULL;
    iterator->next = linlist->head;
    /* Return iterator */
    return iterator;
}



/*----------------------------------------------------------------------------*/
void
SUPPORT_METHOD(iterator, del)(SUPPORT(iterator) *iterator)
{
    free(iterator);
}



/*----------------------------------------------------------------------------*/
bool
SUPPORT_METHOD(iterator, next)(SUPPORT(iterator) *iterator,
                               void *data)
{
#ifndef CSLL_OPT
    if (!iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(SUBTYPE_REPR, "next")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on nothing */
    }
    else if (!data)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(SUBTYPE_REPR, "next", "2nd", data)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Invalid data */
    }
    else
#endif
    /* If not last item */
    if (iterator->next)
    {
        *(void **)data = iterator->next->data;
        iterator->prev = iterator->curr;
        iterator->curr = iterator->next;
        iterator->next = iterator->next->next;
        return true;
    }
    /* If last item */
    else
    {
        free(iterator);
        return false;
    }
}



/*----------------------------------------------------------------------------*/
/* NOTE: If the list is modified directly or through another iterator, while
         there is an iterator already created, it will lead to undefined
         behaviour, as the 'next' pointer will most likely point to a deleted
         node. An example:

             SinglyLinkedList_type_iterator *i1 = iter(list);
             SinglyLinkedList_type_iterator *i2 = iter(list);
             next(i1);
             pull(i1);
             next(i2);

         If possible, solve this. One option is to create a virtual-pointer
         array inside the list object, and the nodes are going to point to the
         entries of the this array, instead of directly pointing to each other.
         However this is a working solution, this will make the linked-list
         super heavy, probably unnecessarily heavy. */
void
SUPPORT_METHOD(iterator, pull)(SUPPORT(iterator) *iterator)
{
#ifndef CSLL_OPT
    if (!iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(SUBTYPE_REPR, "pull")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return; /* Cannot operate on nothing */
    }
#endif
    /* Pop out current node */
    __csll_node_pop(iterator->list, iterator->prev, iterator->next);
    iterator->list->length--;
    /* Destroy current node */
    free(iterator->curr);
    /* Update iterator pointer */
    iterator->curr = iterator->prev;
}



/*----------------------------------------------------------------------------*/
void
METHOD(map)(LINKED_LIST *linlist,
            size_t index,
            size_t count,
            void (*function)())
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "map")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return; /* Cannot operate on nothing */
    }
    else if (!linlist->length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "map")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return; /* Successfully did nothing */
    }
    else if (index >= linlist->length)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "map", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return;
    }
    else if (!function)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "map", "4th", function)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return; /* Cannot call NULL on items */
    }
    else
#endif
    /* CORE FUNCTIONALITY */
    if (!count)
        return; /* Successfully mapped function on 0 items */
    /* Get/set/cast values */
    SLLNode *node = linlist->head;
    size_t counter = 0;
    /* Call function on each item in list */
    for (size_t i=0; node; i++)
    {
        /* Start counting items */
        if (counter)
        {
            function(i, node->data);
            if (!--counter)
                return;
        }
        /* If index is a mathc for 'start from' */
        else if (i == index)
        {
            function(i, node->data);
            counter = count - 1;
        }
        /* Move on to the next node */
        node = node->next;
    }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
METHOD(map_default3)(LINKED_LIST *linlist,
                     size_t count,
                     void (*function)())
{
    METHOD(map)(linlist, 0, count, function);
}



/*----------------------------------------------------------------------------*/
bool
METHOD(format)(const void *data,
               char **buffer,
               size_t *buffer_size)
{
    /* buffer_size could be used to realloc buffer if
       it is too small to contain the the formatted item */
    snprintf(*buffer, *buffer_size, REPRESENTATION_OF_REAL_POINTERS, data);
    return *buffer;
}



/*----------------------------------------------------------------------------*/
void
METHOD(print)(LINKED_LIST *linlist,
              FILE *stream,
              const char *sub_type,
              bool(*format)())
{
#ifndef CSLL_OPT
    if (!linlist)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "print")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        fprintf(stream, REPRESENTATION_OF_NULL_POINTERS "\n");
        return; /* Cannot operate on nothing */
    }
#endif
    char *opening;

    /* If object is "sub-typed" */
    if (sub_type)
        opening = TYPE_REPR "_%s{";
    else
        opening = TYPE_REPR "{";

    fprintf(stream, opening, sub_type);
    /* If list is filled */
    if (linlist->length)
    {
        /* Create a dynamically allocated buffer for representation */
        size_t buffer_size = 128;
        char *buffer = malloc(buffer_size);
        if (!buffer)
        {
            #undef  EXCEPTION_MSG
            #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "print")
            cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
            fprintf(stream, "...}\n");
            return;
        }
        /* Create/get/set/cast essentaial values */
        SLLNode *node = linlist->head;
        char **buffer_ptr = &buffer;
        /* Print all remaining items, with leading comma */
        for (size_t i=0; node; i++)
        {
            /* If not the first item */
            if (i) fprintf(stream, ", ");
            /* If formatting representation was successful */
            if (!format(node->data, buffer_ptr, &buffer_size))
            {
                #undef  EXCEPTION_MSG
                #define EXCEPTION_MSG \
                    EXCEPTION_MESSAGE_REALLOC_FAIL(TYPE_REPR, "print")
                cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
                fprintf(stream, "...");
                break;
            }
            /* Print representation and re-set buffer pointer */
            fprintf(stream, "%s", *buffer_ptr);
            *buffer_ptr = buffer;

            /* Move to next node */
            node = node->next;
        }
        /* Clean up and close the format */
        free(buffer);
    }
    fprintf(stream, "}\n");
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
METHOD(print_default2)(LINKED_LIST *linlist,
                       bool(*format)())
{
    METHOD(print)(linlist, stdout, "void_ptr", format);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
METHOD(print_default1)(LINKED_LIST *linlist)
{
    METHOD(print)(linlist, stdout, "void_ptr", METHOD(format));
}
