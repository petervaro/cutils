/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.219 (20140908)                       **
**                                                                            **
**                                File: csll.c                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#include <stddef.h>         /* ptrdiff_t */
#include <string.h>         /* strlen() */
#include "internal/fmtc.h"  /* cutils_fmtc_repr */
#include "internal/fcmp.h"  /* cutils_fcmp_compare */
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

/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_char;
typedef SLLIterator cutils_csll_SinglyLinkedList_char_iterator;
bool cutils_csll_SinglyLinkedList_char_new(cutils_csll_SinglyLinkedList_char**l,size_t c,char*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(char),c,a);}
void(*cutils_csll_SinglyLinkedList_char_del)(cutils_csll_SinglyLinkedList_char*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_char_len)(cutils_csll_SinglyLinkedList_char*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_char_truncate)(cutils_csll_SinglyLinkedList_char*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_char_clear)(cutils_csll_SinglyLinkedList_char*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_char_iterator* cutils_csll_SinglyLinkedList_char_iter(cutils_csll_SinglyLinkedList_char*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_char_iterator_del(cutils_csll_SinglyLinkedList_char_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_char_iterator_next(cutils_csll_SinglyLinkedList_char_iterator*i,char**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_char_iterator_pull(cutils_csll_SinglyLinkedList_char_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_char_swap)(cutils_csll_SinglyLinkedList_char*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_char_reverse)(cutils_csll_SinglyLinkedList_char*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_char_append(cutils_csll_SinglyLinkedList_char*l,size_t c,char*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(char),c,a);}
bool cutils_csll_SinglyLinkedList_char_push(cutils_csll_SinglyLinkedList_char*l,size_t i,size_t c,char*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(char),c,a);}
size_t(*cutils_csll_SinglyLinkedList_char_pull)(cutils_csll_SinglyLinkedList_char*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_char_set(cutils_csll_SinglyLinkedList_char*l,size_t i,size_t c,char*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(char),c,a);}
bool cutils_csll_SinglyLinkedList_char_pop(cutils_csll_SinglyLinkedList_char*l,size_t i,size_t c,char*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(char),c,a);}
char cutils_csll_SinglyLinkedList_char_get(cutils_csll_SinglyLinkedList_char*l,size_t i){return *(char*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_char_sub(cutils_csll_SinglyLinkedList_char*l,size_t i,size_t c,char*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(char),c,a);}
void(*cutils_csll_SinglyLinkedList_char_map)(cutils_csll_SinglyLinkedList_char*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_char_find(cutils_csll_SinglyLinkedList_char*l,bool(*f)(const void*,const void*,size_t),char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(char),p,i);}
size_t cutils_csll_SinglyLinkedList_char_findall(cutils_csll_SinglyLinkedList_char*l,bool(*f)(const void*,const void*,size_t),char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(char),p,i);}
void(*cutils_csll_SinglyLinkedList_char_print)(cutils_csll_SinglyLinkedList_char*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_char_format(const char*i,char**b,size_t*s){cutils_fmtc_repr(*b,*s,i,1);return true;}
bool cutils_csll_SinglyLinkedList_char_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_char_new_default1(cutils_csll_SinglyLinkedList_char**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(char),0,NULL);}
void cutils_csll_SinglyLinkedList_char_truncate_default1(cutils_csll_SinglyLinkedList_char*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_char_swap_default3(cutils_csll_SinglyLinkedList_char*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_char_append_default2(cutils_csll_SinglyLinkedList_char*l,char*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(char),1,a);}
bool cutils_csll_SinglyLinkedList_char_push_default3(cutils_csll_SinglyLinkedList_char*l,size_t i,char*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(char),1,a);}
size_t cutils_csll_SinglyLinkedList_char_pull_default2(cutils_csll_SinglyLinkedList_char*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_char_set_default3(cutils_csll_SinglyLinkedList_char*l,size_t i,char*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(char),1,a);}
bool cutils_csll_SinglyLinkedList_char_pop_default3(cutils_csll_SinglyLinkedList_char*l,size_t i,char*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(char),1,a);}
bool cutils_csll_SinglyLinkedList_char_sub_default3(cutils_csll_SinglyLinkedList_char*l,size_t i,char*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(char),1,a);}
void cutils_csll_SinglyLinkedList_char_map_default3(cutils_csll_SinglyLinkedList_char*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_char_find_default3(cutils_csll_SinglyLinkedList_char*l,char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_char_compare,sizeof(char),p,i);}
size_t cutils_csll_SinglyLinkedList_char_findall_default3(cutils_csll_SinglyLinkedList_char*l,char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_char_compare,sizeof(char),p,i);}
void cutils_csll_SinglyLinkedList_char_print_default1(cutils_csll_SinglyLinkedList_char*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"char",cutils_csll_SinglyLinkedList_char_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_signed_char;
typedef SLLIterator cutils_csll_SinglyLinkedList_signed_char_iterator;
bool cutils_csll_SinglyLinkedList_signed_char_new(cutils_csll_SinglyLinkedList_signed_char**l,size_t c,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(signed char),c,a);}
void(*cutils_csll_SinglyLinkedList_signed_char_del)(cutils_csll_SinglyLinkedList_signed_char*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_signed_char_len)(cutils_csll_SinglyLinkedList_signed_char*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_signed_char_truncate)(cutils_csll_SinglyLinkedList_signed_char*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_signed_char_clear)(cutils_csll_SinglyLinkedList_signed_char*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_signed_char_iterator* cutils_csll_SinglyLinkedList_signed_char_iter(cutils_csll_SinglyLinkedList_signed_char*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_signed_char_iterator_del(cutils_csll_SinglyLinkedList_signed_char_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_signed_char_iterator_next(cutils_csll_SinglyLinkedList_signed_char_iterator*i,signed char**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_signed_char_iterator_pull(cutils_csll_SinglyLinkedList_signed_char_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_signed_char_swap)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_signed_char_reverse)(cutils_csll_SinglyLinkedList_signed_char*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_signed_char_append(cutils_csll_SinglyLinkedList_signed_char*l,size_t c,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(signed char),c,a);}
bool cutils_csll_SinglyLinkedList_signed_char_push(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,size_t c,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(signed char),c,a);}
size_t(*cutils_csll_SinglyLinkedList_signed_char_pull)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_signed_char_set(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,size_t c,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(signed char),c,a);}
bool cutils_csll_SinglyLinkedList_signed_char_pop(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,size_t c,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(signed char),c,a);}
signed char cutils_csll_SinglyLinkedList_signed_char_get(cutils_csll_SinglyLinkedList_signed_char*l,size_t i){return *(signed char*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_signed_char_sub(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,size_t c,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(signed char),c,a);}
void(*cutils_csll_SinglyLinkedList_signed_char_map)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_signed_char_find(cutils_csll_SinglyLinkedList_signed_char*l,bool(*f)(const void*,const void*,size_t),signed char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(signed char),p,i);}
size_t cutils_csll_SinglyLinkedList_signed_char_findall(cutils_csll_SinglyLinkedList_signed_char*l,bool(*f)(const void*,const void*,size_t),signed char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(signed char),p,i);}
void(*cutils_csll_SinglyLinkedList_signed_char_print)(cutils_csll_SinglyLinkedList_signed_char*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_signed_char_format(const signed char*i,char**b,size_t*s){snprintf(*b,*s,"%c",*i);return true;}
bool cutils_csll_SinglyLinkedList_signed_char_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_signed_char_new_default1(cutils_csll_SinglyLinkedList_signed_char**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(signed char),0,NULL);}
void cutils_csll_SinglyLinkedList_signed_char_truncate_default1(cutils_csll_SinglyLinkedList_signed_char*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_signed_char_swap_default3(cutils_csll_SinglyLinkedList_signed_char*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_signed_char_append_default2(cutils_csll_SinglyLinkedList_signed_char*l,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(signed char),1,a);}
bool cutils_csll_SinglyLinkedList_signed_char_push_default3(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(signed char),1,a);}
size_t cutils_csll_SinglyLinkedList_signed_char_pull_default2(cutils_csll_SinglyLinkedList_signed_char*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_signed_char_set_default3(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(signed char),1,a);}
bool cutils_csll_SinglyLinkedList_signed_char_pop_default3(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(signed char),1,a);}
bool cutils_csll_SinglyLinkedList_signed_char_sub_default3(cutils_csll_SinglyLinkedList_signed_char*l,size_t i,signed char*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(signed char),1,a);}
void cutils_csll_SinglyLinkedList_signed_char_map_default3(cutils_csll_SinglyLinkedList_signed_char*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_signed_char_find_default3(cutils_csll_SinglyLinkedList_signed_char*l,signed char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_signed_char_compare,sizeof(signed char),p,i);}
size_t cutils_csll_SinglyLinkedList_signed_char_findall_default3(cutils_csll_SinglyLinkedList_signed_char*l,signed char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_signed_char_compare,sizeof(signed char),p,i);}
void cutils_csll_SinglyLinkedList_signed_char_print_default1(cutils_csll_SinglyLinkedList_signed_char*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"signed_char",cutils_csll_SinglyLinkedList_signed_char_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_unsigned_char;
typedef SLLIterator cutils_csll_SinglyLinkedList_unsigned_char_iterator;
bool cutils_csll_SinglyLinkedList_unsigned_char_new(cutils_csll_SinglyLinkedList_unsigned_char**l,size_t c,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned char),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_char_del)(cutils_csll_SinglyLinkedList_unsigned_char*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_unsigned_char_len)(cutils_csll_SinglyLinkedList_unsigned_char*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_unsigned_char_truncate)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_unsigned_char_clear)(cutils_csll_SinglyLinkedList_unsigned_char*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_unsigned_char_iterator* cutils_csll_SinglyLinkedList_unsigned_char_iter(cutils_csll_SinglyLinkedList_unsigned_char*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_unsigned_char_iterator_del(cutils_csll_SinglyLinkedList_unsigned_char_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_unsigned_char_iterator_next(cutils_csll_SinglyLinkedList_unsigned_char_iterator*i,unsigned char**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_unsigned_char_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_char_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_unsigned_char_swap)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_unsigned_char_reverse)(cutils_csll_SinglyLinkedList_unsigned_char*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_unsigned_char_append(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t c,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned char),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_char_push(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,size_t c,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned char),c,a);}
size_t(*cutils_csll_SinglyLinkedList_unsigned_char_pull)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_unsigned_char_set(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,size_t c,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned char),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_char_pop(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,size_t c,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned char),c,a);}
unsigned char cutils_csll_SinglyLinkedList_unsigned_char_get(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i){return *(unsigned char*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_unsigned_char_sub(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,size_t c,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned char),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_char_map)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_unsigned_char_find(cutils_csll_SinglyLinkedList_unsigned_char*l,bool(*f)(const void*,const void*,size_t),unsigned char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(unsigned char),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_char_findall(cutils_csll_SinglyLinkedList_unsigned_char*l,bool(*f)(const void*,const void*,size_t),unsigned char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(unsigned char),p,i);}
void(*cutils_csll_SinglyLinkedList_unsigned_char_print)(cutils_csll_SinglyLinkedList_unsigned_char*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_unsigned_char_format(const unsigned char*i,char**b,size_t*s){snprintf(*b,*s,"%u",*i);return true;}
bool cutils_csll_SinglyLinkedList_unsigned_char_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_unsigned_char_new_default1(cutils_csll_SinglyLinkedList_unsigned_char**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned char),0,NULL);}
void cutils_csll_SinglyLinkedList_unsigned_char_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_char*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_unsigned_char_swap_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_unsigned_char_append_default2(cutils_csll_SinglyLinkedList_unsigned_char*l,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned char),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_char_push_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned char),1,a);}
size_t cutils_csll_SinglyLinkedList_unsigned_char_pull_default2(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_unsigned_char_set_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned char),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_char_pop_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned char),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_char_sub_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t i,unsigned char*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned char),1,a);}
void cutils_csll_SinglyLinkedList_unsigned_char_map_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_unsigned_char_find_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,unsigned char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_unsigned_char_compare,sizeof(unsigned char),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_char_findall_default3(cutils_csll_SinglyLinkedList_unsigned_char*l,unsigned char*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_unsigned_char_compare,sizeof(unsigned char),p,i);}
void cutils_csll_SinglyLinkedList_unsigned_char_print_default1(cutils_csll_SinglyLinkedList_unsigned_char*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"unsigned_char",cutils_csll_SinglyLinkedList_unsigned_char_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_char_ptr;
typedef SLLIterator cutils_csll_SinglyLinkedList_char_ptr_iterator;
bool cutils_csll_SinglyLinkedList_char_ptr_new(cutils_csll_SinglyLinkedList_char_ptr**l,size_t c,char**a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(char*),c,a);}
void(*cutils_csll_SinglyLinkedList_char_ptr_del)(cutils_csll_SinglyLinkedList_char_ptr*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_char_ptr_len)(cutils_csll_SinglyLinkedList_char_ptr*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_char_ptr_truncate)(cutils_csll_SinglyLinkedList_char_ptr*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_char_ptr_clear)(cutils_csll_SinglyLinkedList_char_ptr*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_char_ptr_iterator* cutils_csll_SinglyLinkedList_char_ptr_iter(cutils_csll_SinglyLinkedList_char_ptr*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_char_ptr_iterator_del(cutils_csll_SinglyLinkedList_char_ptr_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_char_ptr_iterator_next(cutils_csll_SinglyLinkedList_char_ptr_iterator*i,char***p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_char_ptr_iterator_pull(cutils_csll_SinglyLinkedList_char_ptr_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_char_ptr_swap)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_char_ptr_reverse)(cutils_csll_SinglyLinkedList_char_ptr*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_char_ptr_append(cutils_csll_SinglyLinkedList_char_ptr*l,size_t c,char**a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(char*),c,a);}
bool cutils_csll_SinglyLinkedList_char_ptr_push(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,size_t c,char**a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(char*),c,a);}
size_t(*cutils_csll_SinglyLinkedList_char_ptr_pull)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_char_ptr_set(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,size_t c,char**a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(char*),c,a);}
bool cutils_csll_SinglyLinkedList_char_ptr_pop(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,size_t c,char**a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(char*),c,a);}
char* cutils_csll_SinglyLinkedList_char_ptr_get(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i){return *(char**)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_char_ptr_sub(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,size_t c,char**a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(char*),c,a);}
void(*cutils_csll_SinglyLinkedList_char_ptr_map)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_char_ptr_find(cutils_csll_SinglyLinkedList_char_ptr*l,bool(*f)(const void*,const void*,size_t),char**p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(char*),p,i);}
size_t cutils_csll_SinglyLinkedList_char_ptr_findall(cutils_csll_SinglyLinkedList_char_ptr*l,bool(*f)(const void*,const void*,size_t),char**p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(char*),p,i);}
void(*cutils_csll_SinglyLinkedList_char_ptr_print)(cutils_csll_SinglyLinkedList_char_ptr*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_char_ptr_format(const char**i,char**b,size_t*s){size_t l=strlen(*i);if(*s<l+3)if(!(*b=realloc(*b,(*s=l*2+3))))return false;cutils_fmtc_repr(*b,*s,*i,l);return true;}
bool cutils_csll_SinglyLinkedList_char_ptr_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_char_ptr_new_default1(cutils_csll_SinglyLinkedList_char_ptr**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(char*),0,NULL);}
void cutils_csll_SinglyLinkedList_char_ptr_truncate_default1(cutils_csll_SinglyLinkedList_char_ptr*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_char_ptr_swap_default3(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_char_ptr_append_default2(cutils_csll_SinglyLinkedList_char_ptr*l,char**a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(char*),1,a);}
bool cutils_csll_SinglyLinkedList_char_ptr_push_default3(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,char**a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(char*),1,a);}
size_t cutils_csll_SinglyLinkedList_char_ptr_pull_default2(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_char_ptr_set_default3(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,char**a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(char*),1,a);}
bool cutils_csll_SinglyLinkedList_char_ptr_pop_default3(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,char**a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(char*),1,a);}
bool cutils_csll_SinglyLinkedList_char_ptr_sub_default3(cutils_csll_SinglyLinkedList_char_ptr*l,size_t i,char**a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(char*),1,a);}
void cutils_csll_SinglyLinkedList_char_ptr_map_default3(cutils_csll_SinglyLinkedList_char_ptr*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_char_ptr_find_default3(cutils_csll_SinglyLinkedList_char_ptr*l,char**p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_char_ptr_compare,sizeof(char*),p,i);}
size_t cutils_csll_SinglyLinkedList_char_ptr_findall_default3(cutils_csll_SinglyLinkedList_char_ptr*l,char**p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_char_ptr_compare,sizeof(char*),p,i);}
void cutils_csll_SinglyLinkedList_char_ptr_print_default1(cutils_csll_SinglyLinkedList_char_ptr*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"char_ptr",cutils_csll_SinglyLinkedList_char_ptr_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_short;
typedef SLLIterator cutils_csll_SinglyLinkedList_short_iterator;
bool cutils_csll_SinglyLinkedList_short_new(cutils_csll_SinglyLinkedList_short**l,size_t c,short*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(short),c,a);}
void(*cutils_csll_SinglyLinkedList_short_del)(cutils_csll_SinglyLinkedList_short*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_short_len)(cutils_csll_SinglyLinkedList_short*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_short_truncate)(cutils_csll_SinglyLinkedList_short*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_short_clear)(cutils_csll_SinglyLinkedList_short*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_short_iterator* cutils_csll_SinglyLinkedList_short_iter(cutils_csll_SinglyLinkedList_short*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_short_iterator_del(cutils_csll_SinglyLinkedList_short_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_short_iterator_next(cutils_csll_SinglyLinkedList_short_iterator*i,short**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_short_iterator_pull(cutils_csll_SinglyLinkedList_short_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_short_swap)(cutils_csll_SinglyLinkedList_short*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_short_reverse)(cutils_csll_SinglyLinkedList_short*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_short_append(cutils_csll_SinglyLinkedList_short*l,size_t c,short*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(short),c,a);}
bool cutils_csll_SinglyLinkedList_short_push(cutils_csll_SinglyLinkedList_short*l,size_t i,size_t c,short*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(short),c,a);}
size_t(*cutils_csll_SinglyLinkedList_short_pull)(cutils_csll_SinglyLinkedList_short*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_short_set(cutils_csll_SinglyLinkedList_short*l,size_t i,size_t c,short*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(short),c,a);}
bool cutils_csll_SinglyLinkedList_short_pop(cutils_csll_SinglyLinkedList_short*l,size_t i,size_t c,short*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(short),c,a);}
short cutils_csll_SinglyLinkedList_short_get(cutils_csll_SinglyLinkedList_short*l,size_t i){return *(short*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_short_sub(cutils_csll_SinglyLinkedList_short*l,size_t i,size_t c,short*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(short),c,a);}
void(*cutils_csll_SinglyLinkedList_short_map)(cutils_csll_SinglyLinkedList_short*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_short_find(cutils_csll_SinglyLinkedList_short*l,bool(*f)(const void*,const void*,size_t),short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(short),p,i);}
size_t cutils_csll_SinglyLinkedList_short_findall(cutils_csll_SinglyLinkedList_short*l,bool(*f)(const void*,const void*,size_t),short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(short),p,i);}
void(*cutils_csll_SinglyLinkedList_short_print)(cutils_csll_SinglyLinkedList_short*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_short_format(const short*i,char**b,size_t*s){snprintf(*b,*s,"%hd",*i);return true;}
bool cutils_csll_SinglyLinkedList_short_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_short_new_default1(cutils_csll_SinglyLinkedList_short**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(short),0,NULL);}
void cutils_csll_SinglyLinkedList_short_truncate_default1(cutils_csll_SinglyLinkedList_short*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_short_swap_default3(cutils_csll_SinglyLinkedList_short*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_short_append_default2(cutils_csll_SinglyLinkedList_short*l,short*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(short),1,a);}
bool cutils_csll_SinglyLinkedList_short_push_default3(cutils_csll_SinglyLinkedList_short*l,size_t i,short*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(short),1,a);}
size_t cutils_csll_SinglyLinkedList_short_pull_default2(cutils_csll_SinglyLinkedList_short*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_short_set_default3(cutils_csll_SinglyLinkedList_short*l,size_t i,short*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(short),1,a);}
bool cutils_csll_SinglyLinkedList_short_pop_default3(cutils_csll_SinglyLinkedList_short*l,size_t i,short*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(short),1,a);}
bool cutils_csll_SinglyLinkedList_short_sub_default3(cutils_csll_SinglyLinkedList_short*l,size_t i,short*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(short),1,a);}
void cutils_csll_SinglyLinkedList_short_map_default3(cutils_csll_SinglyLinkedList_short*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_short_find_default3(cutils_csll_SinglyLinkedList_short*l,short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_short_compare,sizeof(short),p,i);}
size_t cutils_csll_SinglyLinkedList_short_findall_default3(cutils_csll_SinglyLinkedList_short*l,short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_short_compare,sizeof(short),p,i);}
void cutils_csll_SinglyLinkedList_short_print_default1(cutils_csll_SinglyLinkedList_short*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"short",cutils_csll_SinglyLinkedList_short_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_unsigned_short;
typedef SLLIterator cutils_csll_SinglyLinkedList_unsigned_short_iterator;
bool cutils_csll_SinglyLinkedList_unsigned_short_new(cutils_csll_SinglyLinkedList_unsigned_short**l,size_t c,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned short),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_short_del)(cutils_csll_SinglyLinkedList_unsigned_short*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_unsigned_short_len)(cutils_csll_SinglyLinkedList_unsigned_short*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_unsigned_short_truncate)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_unsigned_short_clear)(cutils_csll_SinglyLinkedList_unsigned_short*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_unsigned_short_iterator* cutils_csll_SinglyLinkedList_unsigned_short_iter(cutils_csll_SinglyLinkedList_unsigned_short*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_unsigned_short_iterator_del(cutils_csll_SinglyLinkedList_unsigned_short_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_unsigned_short_iterator_next(cutils_csll_SinglyLinkedList_unsigned_short_iterator*i,unsigned short**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_unsigned_short_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_short_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_unsigned_short_swap)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_unsigned_short_reverse)(cutils_csll_SinglyLinkedList_unsigned_short*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_unsigned_short_append(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t c,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned short),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_short_push(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,size_t c,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned short),c,a);}
size_t(*cutils_csll_SinglyLinkedList_unsigned_short_pull)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_unsigned_short_set(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,size_t c,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned short),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_short_pop(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,size_t c,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned short),c,a);}
unsigned short cutils_csll_SinglyLinkedList_unsigned_short_get(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i){return *(unsigned short*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_unsigned_short_sub(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,size_t c,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned short),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_short_map)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_unsigned_short_find(cutils_csll_SinglyLinkedList_unsigned_short*l,bool(*f)(const void*,const void*,size_t),unsigned short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(unsigned short),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_short_findall(cutils_csll_SinglyLinkedList_unsigned_short*l,bool(*f)(const void*,const void*,size_t),unsigned short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(unsigned short),p,i);}
void(*cutils_csll_SinglyLinkedList_unsigned_short_print)(cutils_csll_SinglyLinkedList_unsigned_short*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_unsigned_short_format(const unsigned short*i,char**b,size_t*s){snprintf(*b,*s,"%hu",*i);return true;}
bool cutils_csll_SinglyLinkedList_unsigned_short_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_unsigned_short_new_default1(cutils_csll_SinglyLinkedList_unsigned_short**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned short),0,NULL);}
void cutils_csll_SinglyLinkedList_unsigned_short_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_short*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_unsigned_short_swap_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_unsigned_short_append_default2(cutils_csll_SinglyLinkedList_unsigned_short*l,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned short),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_short_push_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned short),1,a);}
size_t cutils_csll_SinglyLinkedList_unsigned_short_pull_default2(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_unsigned_short_set_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned short),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_short_pop_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned short),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_short_sub_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t i,unsigned short*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned short),1,a);}
void cutils_csll_SinglyLinkedList_unsigned_short_map_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_unsigned_short_find_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,unsigned short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_unsigned_short_compare,sizeof(unsigned short),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_short_findall_default3(cutils_csll_SinglyLinkedList_unsigned_short*l,unsigned short*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_unsigned_short_compare,sizeof(unsigned short),p,i);}
void cutils_csll_SinglyLinkedList_unsigned_short_print_default1(cutils_csll_SinglyLinkedList_unsigned_short*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"unsigned_short",cutils_csll_SinglyLinkedList_unsigned_short_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_int;
typedef SLLIterator cutils_csll_SinglyLinkedList_int_iterator;
bool cutils_csll_SinglyLinkedList_int_new(cutils_csll_SinglyLinkedList_int**l,size_t c,int*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(int),c,a);}
void(*cutils_csll_SinglyLinkedList_int_del)(cutils_csll_SinglyLinkedList_int*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_int_len)(cutils_csll_SinglyLinkedList_int*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_int_truncate)(cutils_csll_SinglyLinkedList_int*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_int_clear)(cutils_csll_SinglyLinkedList_int*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_int_iterator* cutils_csll_SinglyLinkedList_int_iter(cutils_csll_SinglyLinkedList_int*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_int_iterator_del(cutils_csll_SinglyLinkedList_int_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_int_iterator_next(cutils_csll_SinglyLinkedList_int_iterator*i,int**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_int_iterator_pull(cutils_csll_SinglyLinkedList_int_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_int_swap)(cutils_csll_SinglyLinkedList_int*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_int_reverse)(cutils_csll_SinglyLinkedList_int*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_int_append(cutils_csll_SinglyLinkedList_int*l,size_t c,int*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(int),c,a);}
bool cutils_csll_SinglyLinkedList_int_push(cutils_csll_SinglyLinkedList_int*l,size_t i,size_t c,int*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(int),c,a);}
size_t(*cutils_csll_SinglyLinkedList_int_pull)(cutils_csll_SinglyLinkedList_int*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_int_set(cutils_csll_SinglyLinkedList_int*l,size_t i,size_t c,int*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(int),c,a);}
bool cutils_csll_SinglyLinkedList_int_pop(cutils_csll_SinglyLinkedList_int*l,size_t i,size_t c,int*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(int),c,a);}
int cutils_csll_SinglyLinkedList_int_get(cutils_csll_SinglyLinkedList_int*l,size_t i){return *(int*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_int_sub(cutils_csll_SinglyLinkedList_int*l,size_t i,size_t c,int*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(int),c,a);}
void(*cutils_csll_SinglyLinkedList_int_map)(cutils_csll_SinglyLinkedList_int*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_int_find(cutils_csll_SinglyLinkedList_int*l,bool(*f)(const void*,const void*,size_t),int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(int),p,i);}
size_t cutils_csll_SinglyLinkedList_int_findall(cutils_csll_SinglyLinkedList_int*l,bool(*f)(const void*,const void*,size_t),int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(int),p,i);}
void(*cutils_csll_SinglyLinkedList_int_print)(cutils_csll_SinglyLinkedList_int*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_int_format(const int*i,char**b,size_t*s){snprintf(*b,*s,"%d",*i);return true;}
bool cutils_csll_SinglyLinkedList_int_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_int_new_default1(cutils_csll_SinglyLinkedList_int**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(int),0,NULL);}
void cutils_csll_SinglyLinkedList_int_truncate_default1(cutils_csll_SinglyLinkedList_int*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_int_swap_default3(cutils_csll_SinglyLinkedList_int*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_int_append_default2(cutils_csll_SinglyLinkedList_int*l,int*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(int),1,a);}
bool cutils_csll_SinglyLinkedList_int_push_default3(cutils_csll_SinglyLinkedList_int*l,size_t i,int*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(int),1,a);}
size_t cutils_csll_SinglyLinkedList_int_pull_default2(cutils_csll_SinglyLinkedList_int*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_int_set_default3(cutils_csll_SinglyLinkedList_int*l,size_t i,int*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(int),1,a);}
bool cutils_csll_SinglyLinkedList_int_pop_default3(cutils_csll_SinglyLinkedList_int*l,size_t i,int*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(int),1,a);}
bool cutils_csll_SinglyLinkedList_int_sub_default3(cutils_csll_SinglyLinkedList_int*l,size_t i,int*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(int),1,a);}
void cutils_csll_SinglyLinkedList_int_map_default3(cutils_csll_SinglyLinkedList_int*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_int_find_default3(cutils_csll_SinglyLinkedList_int*l,int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_int_compare,sizeof(int),p,i);}
size_t cutils_csll_SinglyLinkedList_int_findall_default3(cutils_csll_SinglyLinkedList_int*l,int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_int_compare,sizeof(int),p,i);}
void cutils_csll_SinglyLinkedList_int_print_default1(cutils_csll_SinglyLinkedList_int*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"int",cutils_csll_SinglyLinkedList_int_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_unsigned_int;
typedef SLLIterator cutils_csll_SinglyLinkedList_unsigned_int_iterator;
bool cutils_csll_SinglyLinkedList_unsigned_int_new(cutils_csll_SinglyLinkedList_unsigned_int**l,size_t c,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned int),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_int_del)(cutils_csll_SinglyLinkedList_unsigned_int*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_unsigned_int_len)(cutils_csll_SinglyLinkedList_unsigned_int*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_unsigned_int_truncate)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_unsigned_int_clear)(cutils_csll_SinglyLinkedList_unsigned_int*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_unsigned_int_iterator* cutils_csll_SinglyLinkedList_unsigned_int_iter(cutils_csll_SinglyLinkedList_unsigned_int*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_unsigned_int_iterator_del(cutils_csll_SinglyLinkedList_unsigned_int_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_unsigned_int_iterator_next(cutils_csll_SinglyLinkedList_unsigned_int_iterator*i,unsigned int**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_unsigned_int_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_int_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_unsigned_int_swap)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_unsigned_int_reverse)(cutils_csll_SinglyLinkedList_unsigned_int*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_unsigned_int_append(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t c,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned int),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_int_push(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,size_t c,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned int),c,a);}
size_t(*cutils_csll_SinglyLinkedList_unsigned_int_pull)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_unsigned_int_set(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,size_t c,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned int),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_int_pop(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,size_t c,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned int),c,a);}
unsigned int cutils_csll_SinglyLinkedList_unsigned_int_get(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i){return *(unsigned int*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_unsigned_int_sub(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,size_t c,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned int),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_int_map)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_unsigned_int_find(cutils_csll_SinglyLinkedList_unsigned_int*l,bool(*f)(const void*,const void*,size_t),unsigned int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(unsigned int),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_int_findall(cutils_csll_SinglyLinkedList_unsigned_int*l,bool(*f)(const void*,const void*,size_t),unsigned int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(unsigned int),p,i);}
void(*cutils_csll_SinglyLinkedList_unsigned_int_print)(cutils_csll_SinglyLinkedList_unsigned_int*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_unsigned_int_format(const unsigned int*i,char**b,size_t*s){snprintf(*b,*s,"%uu",*i);return true;}
bool cutils_csll_SinglyLinkedList_unsigned_int_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_unsigned_int_new_default1(cutils_csll_SinglyLinkedList_unsigned_int**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned int),0,NULL);}
void cutils_csll_SinglyLinkedList_unsigned_int_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_int*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_unsigned_int_swap_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_unsigned_int_append_default2(cutils_csll_SinglyLinkedList_unsigned_int*l,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned int),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_int_push_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned int),1,a);}
size_t cutils_csll_SinglyLinkedList_unsigned_int_pull_default2(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_unsigned_int_set_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned int),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_int_pop_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned int),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_int_sub_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t i,unsigned int*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned int),1,a);}
void cutils_csll_SinglyLinkedList_unsigned_int_map_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_unsigned_int_find_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,unsigned int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_unsigned_int_compare,sizeof(unsigned int),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_int_findall_default3(cutils_csll_SinglyLinkedList_unsigned_int*l,unsigned int*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_unsigned_int_compare,sizeof(unsigned int),p,i);}
void cutils_csll_SinglyLinkedList_unsigned_int_print_default1(cutils_csll_SinglyLinkedList_unsigned_int*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"unsigned_int",cutils_csll_SinglyLinkedList_unsigned_int_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_long;
typedef SLLIterator cutils_csll_SinglyLinkedList_long_iterator;
bool cutils_csll_SinglyLinkedList_long_new(cutils_csll_SinglyLinkedList_long**l,size_t c,long*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(long),c,a);}
void(*cutils_csll_SinglyLinkedList_long_del)(cutils_csll_SinglyLinkedList_long*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_long_len)(cutils_csll_SinglyLinkedList_long*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_long_truncate)(cutils_csll_SinglyLinkedList_long*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_long_clear)(cutils_csll_SinglyLinkedList_long*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_long_iterator* cutils_csll_SinglyLinkedList_long_iter(cutils_csll_SinglyLinkedList_long*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_long_iterator_del(cutils_csll_SinglyLinkedList_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_long_iterator_next(cutils_csll_SinglyLinkedList_long_iterator*i,long**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_long_iterator_pull(cutils_csll_SinglyLinkedList_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_long_swap)(cutils_csll_SinglyLinkedList_long*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_long_reverse)(cutils_csll_SinglyLinkedList_long*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_long_append(cutils_csll_SinglyLinkedList_long*l,size_t c,long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(long),c,a);}
bool cutils_csll_SinglyLinkedList_long_push(cutils_csll_SinglyLinkedList_long*l,size_t i,size_t c,long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(long),c,a);}
size_t(*cutils_csll_SinglyLinkedList_long_pull)(cutils_csll_SinglyLinkedList_long*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_long_set(cutils_csll_SinglyLinkedList_long*l,size_t i,size_t c,long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(long),c,a);}
bool cutils_csll_SinglyLinkedList_long_pop(cutils_csll_SinglyLinkedList_long*l,size_t i,size_t c,long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(long),c,a);}
long cutils_csll_SinglyLinkedList_long_get(cutils_csll_SinglyLinkedList_long*l,size_t i){return *(long*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_long_sub(cutils_csll_SinglyLinkedList_long*l,size_t i,size_t c,long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(long),c,a);}
void(*cutils_csll_SinglyLinkedList_long_map)(cutils_csll_SinglyLinkedList_long*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_long_find(cutils_csll_SinglyLinkedList_long*l,bool(*f)(const void*,const void*,size_t),long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(long),p,i);}
size_t cutils_csll_SinglyLinkedList_long_findall(cutils_csll_SinglyLinkedList_long*l,bool(*f)(const void*,const void*,size_t),long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(long),p,i);}
void(*cutils_csll_SinglyLinkedList_long_print)(cutils_csll_SinglyLinkedList_long*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_long_format(const long*i,char**b,size_t*s){snprintf(*b,*s,"%ldl",*i);return true;}
bool cutils_csll_SinglyLinkedList_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_long_new_default1(cutils_csll_SinglyLinkedList_long**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(long),0,NULL);}
void cutils_csll_SinglyLinkedList_long_truncate_default1(cutils_csll_SinglyLinkedList_long*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_long_swap_default3(cutils_csll_SinglyLinkedList_long*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_long_append_default2(cutils_csll_SinglyLinkedList_long*l,long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(long),1,a);}
bool cutils_csll_SinglyLinkedList_long_push_default3(cutils_csll_SinglyLinkedList_long*l,size_t i,long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(long),1,a);}
size_t cutils_csll_SinglyLinkedList_long_pull_default2(cutils_csll_SinglyLinkedList_long*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_long_set_default3(cutils_csll_SinglyLinkedList_long*l,size_t i,long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(long),1,a);}
bool cutils_csll_SinglyLinkedList_long_pop_default3(cutils_csll_SinglyLinkedList_long*l,size_t i,long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(long),1,a);}
bool cutils_csll_SinglyLinkedList_long_sub_default3(cutils_csll_SinglyLinkedList_long*l,size_t i,long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(long),1,a);}
void cutils_csll_SinglyLinkedList_long_map_default3(cutils_csll_SinglyLinkedList_long*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_long_find_default3(cutils_csll_SinglyLinkedList_long*l,long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_long_compare,sizeof(long),p,i);}
size_t cutils_csll_SinglyLinkedList_long_findall_default3(cutils_csll_SinglyLinkedList_long*l,long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_long_compare,sizeof(long),p,i);}
void cutils_csll_SinglyLinkedList_long_print_default1(cutils_csll_SinglyLinkedList_long*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"long",cutils_csll_SinglyLinkedList_long_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_unsigned_long;
typedef SLLIterator cutils_csll_SinglyLinkedList_unsigned_long_iterator;
bool cutils_csll_SinglyLinkedList_unsigned_long_new(cutils_csll_SinglyLinkedList_unsigned_long**l,size_t c,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned long),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_long_del)(cutils_csll_SinglyLinkedList_unsigned_long*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_unsigned_long_len)(cutils_csll_SinglyLinkedList_unsigned_long*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_unsigned_long_truncate)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_unsigned_long_clear)(cutils_csll_SinglyLinkedList_unsigned_long*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_unsigned_long_iterator* cutils_csll_SinglyLinkedList_unsigned_long_iter(cutils_csll_SinglyLinkedList_unsigned_long*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_unsigned_long_iterator_del(cutils_csll_SinglyLinkedList_unsigned_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_unsigned_long_iterator_next(cutils_csll_SinglyLinkedList_unsigned_long_iterator*i,unsigned long**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_unsigned_long_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_unsigned_long_swap)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_unsigned_long_reverse)(cutils_csll_SinglyLinkedList_unsigned_long*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_unsigned_long_append(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t c,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned long),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_push(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,size_t c,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned long),c,a);}
size_t(*cutils_csll_SinglyLinkedList_unsigned_long_pull)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_unsigned_long_set(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,size_t c,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned long),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_pop(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,size_t c,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned long),c,a);}
unsigned long cutils_csll_SinglyLinkedList_unsigned_long_get(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i){return *(unsigned long*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_unsigned_long_sub(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,size_t c,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned long),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_long_map)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_unsigned_long_find(cutils_csll_SinglyLinkedList_unsigned_long*l,bool(*f)(const void*,const void*,size_t),unsigned long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(unsigned long),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_long_findall(cutils_csll_SinglyLinkedList_unsigned_long*l,bool(*f)(const void*,const void*,size_t),unsigned long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(unsigned long),p,i);}
void(*cutils_csll_SinglyLinkedList_unsigned_long_print)(cutils_csll_SinglyLinkedList_unsigned_long*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_unsigned_long_format(const unsigned long*i,char**b,size_t*s){snprintf(*b,*s,"%luul",*i);return true;}
bool cutils_csll_SinglyLinkedList_unsigned_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_unsigned_long_new_default1(cutils_csll_SinglyLinkedList_unsigned_long**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned long),0,NULL);}
void cutils_csll_SinglyLinkedList_unsigned_long_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_long*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_unsigned_long_swap_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_unsigned_long_append_default2(cutils_csll_SinglyLinkedList_unsigned_long*l,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned long),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_push_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned long),1,a);}
size_t cutils_csll_SinglyLinkedList_unsigned_long_pull_default2(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_unsigned_long_set_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned long),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_pop_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned long),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_sub_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t i,unsigned long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned long),1,a);}
void cutils_csll_SinglyLinkedList_unsigned_long_map_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_unsigned_long_find_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,unsigned long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_unsigned_long_compare,sizeof(unsigned long),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_long_findall_default3(cutils_csll_SinglyLinkedList_unsigned_long*l,unsigned long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_unsigned_long_compare,sizeof(unsigned long),p,i);}
void cutils_csll_SinglyLinkedList_unsigned_long_print_default1(cutils_csll_SinglyLinkedList_unsigned_long*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"unsigned_long",cutils_csll_SinglyLinkedList_unsigned_long_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_long_long;
typedef SLLIterator cutils_csll_SinglyLinkedList_long_long_iterator;
bool cutils_csll_SinglyLinkedList_long_long_new(cutils_csll_SinglyLinkedList_long_long**l,size_t c,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(long long),c,a);}
void(*cutils_csll_SinglyLinkedList_long_long_del)(cutils_csll_SinglyLinkedList_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_long_long_len)(cutils_csll_SinglyLinkedList_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_long_long_truncate)(cutils_csll_SinglyLinkedList_long_long*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_long_long_clear)(cutils_csll_SinglyLinkedList_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_long_long_iterator* cutils_csll_SinglyLinkedList_long_long_iter(cutils_csll_SinglyLinkedList_long_long*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_long_long_iterator_del(cutils_csll_SinglyLinkedList_long_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_long_long_iterator_next(cutils_csll_SinglyLinkedList_long_long_iterator*i,long long**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_long_long_iterator_pull(cutils_csll_SinglyLinkedList_long_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_long_long_swap)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_long_long_reverse)(cutils_csll_SinglyLinkedList_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_long_long_append(cutils_csll_SinglyLinkedList_long_long*l,size_t c,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(long long),c,a);}
bool cutils_csll_SinglyLinkedList_long_long_push(cutils_csll_SinglyLinkedList_long_long*l,size_t i,size_t c,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(long long),c,a);}
size_t(*cutils_csll_SinglyLinkedList_long_long_pull)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_long_long_set(cutils_csll_SinglyLinkedList_long_long*l,size_t i,size_t c,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(long long),c,a);}
bool cutils_csll_SinglyLinkedList_long_long_pop(cutils_csll_SinglyLinkedList_long_long*l,size_t i,size_t c,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(long long),c,a);}
long long cutils_csll_SinglyLinkedList_long_long_get(cutils_csll_SinglyLinkedList_long_long*l,size_t i){return *(long long*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_long_long_sub(cutils_csll_SinglyLinkedList_long_long*l,size_t i,size_t c,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(long long),c,a);}
void(*cutils_csll_SinglyLinkedList_long_long_map)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_long_long_find(cutils_csll_SinglyLinkedList_long_long*l,bool(*f)(const void*,const void*,size_t),long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(long long),p,i);}
size_t cutils_csll_SinglyLinkedList_long_long_findall(cutils_csll_SinglyLinkedList_long_long*l,bool(*f)(const void*,const void*,size_t),long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(long long),p,i);}
void(*cutils_csll_SinglyLinkedList_long_long_print)(cutils_csll_SinglyLinkedList_long_long*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_long_long_format(const long long*i,char**b,size_t*s){snprintf(*b,*s,"%lldll",*i);return true;}
bool cutils_csll_SinglyLinkedList_long_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_long_long_new_default1(cutils_csll_SinglyLinkedList_long_long**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(long long),0,NULL);}
void cutils_csll_SinglyLinkedList_long_long_truncate_default1(cutils_csll_SinglyLinkedList_long_long*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_long_long_swap_default3(cutils_csll_SinglyLinkedList_long_long*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_long_long_append_default2(cutils_csll_SinglyLinkedList_long_long*l,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(long long),1,a);}
bool cutils_csll_SinglyLinkedList_long_long_push_default3(cutils_csll_SinglyLinkedList_long_long*l,size_t i,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(long long),1,a);}
size_t cutils_csll_SinglyLinkedList_long_long_pull_default2(cutils_csll_SinglyLinkedList_long_long*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_long_long_set_default3(cutils_csll_SinglyLinkedList_long_long*l,size_t i,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(long long),1,a);}
bool cutils_csll_SinglyLinkedList_long_long_pop_default3(cutils_csll_SinglyLinkedList_long_long*l,size_t i,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(long long),1,a);}
bool cutils_csll_SinglyLinkedList_long_long_sub_default3(cutils_csll_SinglyLinkedList_long_long*l,size_t i,long long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(long long),1,a);}
void cutils_csll_SinglyLinkedList_long_long_map_default3(cutils_csll_SinglyLinkedList_long_long*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_long_long_find_default3(cutils_csll_SinglyLinkedList_long_long*l,long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_long_long_compare,sizeof(long long),p,i);}
size_t cutils_csll_SinglyLinkedList_long_long_findall_default3(cutils_csll_SinglyLinkedList_long_long*l,long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_long_long_compare,sizeof(long long),p,i);}
void cutils_csll_SinglyLinkedList_long_long_print_default1(cutils_csll_SinglyLinkedList_long_long*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"long_long",cutils_csll_SinglyLinkedList_long_long_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_unsigned_long_long;
typedef SLLIterator cutils_csll_SinglyLinkedList_unsigned_long_long_iterator;
bool cutils_csll_SinglyLinkedList_unsigned_long_long_new(cutils_csll_SinglyLinkedList_unsigned_long_long**l,size_t c,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned long long),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_long_long_del)(cutils_csll_SinglyLinkedList_unsigned_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_unsigned_long_long_len)(cutils_csll_SinglyLinkedList_unsigned_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_unsigned_long_long_truncate)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_unsigned_long_long_clear)(cutils_csll_SinglyLinkedList_unsigned_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_unsigned_long_long_iterator* cutils_csll_SinglyLinkedList_unsigned_long_long_iter(cutils_csll_SinglyLinkedList_unsigned_long_long*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_del(cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_next(cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*i,unsigned long long**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_unsigned_long_long_swap)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_unsigned_long_long_reverse)(cutils_csll_SinglyLinkedList_unsigned_long_long*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_unsigned_long_long_append(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t c,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned long long),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_push(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,size_t c,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned long long),c,a);}
size_t(*cutils_csll_SinglyLinkedList_unsigned_long_long_pull)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_unsigned_long_long_set(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,size_t c,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned long long),c,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_pop(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,size_t c,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned long long),c,a);}
unsigned long long cutils_csll_SinglyLinkedList_unsigned_long_long_get(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i){return *(unsigned long long*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_sub(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,size_t c,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned long long),c,a);}
void(*cutils_csll_SinglyLinkedList_unsigned_long_long_map)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_unsigned_long_long_find(cutils_csll_SinglyLinkedList_unsigned_long_long*l,bool(*f)(const void*,const void*,size_t),unsigned long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(unsigned long long),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_long_long_findall(cutils_csll_SinglyLinkedList_unsigned_long_long*l,bool(*f)(const void*,const void*,size_t),unsigned long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(unsigned long long),p,i);}
void(*cutils_csll_SinglyLinkedList_unsigned_long_long_print)(cutils_csll_SinglyLinkedList_unsigned_long_long*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_unsigned_long_long_format(const unsigned long long*i,char**b,size_t*s){snprintf(*b,*s,"%lluull",*i);return true;}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_new_default1(cutils_csll_SinglyLinkedList_unsigned_long_long**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(unsigned long long),0,NULL);}
void cutils_csll_SinglyLinkedList_unsigned_long_long_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_long_long*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_swap_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_append_default2(cutils_csll_SinglyLinkedList_unsigned_long_long*l,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(unsigned long long),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_push_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(unsigned long long),1,a);}
size_t cutils_csll_SinglyLinkedList_unsigned_long_long_pull_default2(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_set_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(unsigned long long),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_pop_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(unsigned long long),1,a);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_sub_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t i,unsigned long long*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(unsigned long long),1,a);}
void cutils_csll_SinglyLinkedList_unsigned_long_long_map_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_unsigned_long_long_find_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,unsigned long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_unsigned_long_long_compare,sizeof(unsigned long long),p,i);}
size_t cutils_csll_SinglyLinkedList_unsigned_long_long_findall_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*l,unsigned long long*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_unsigned_long_long_compare,sizeof(unsigned long long),p,i);}
void cutils_csll_SinglyLinkedList_unsigned_long_long_print_default1(cutils_csll_SinglyLinkedList_unsigned_long_long*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"unsigned_long_long",cutils_csll_SinglyLinkedList_unsigned_long_long_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_float;
typedef SLLIterator cutils_csll_SinglyLinkedList_float_iterator;
bool cutils_csll_SinglyLinkedList_float_new(cutils_csll_SinglyLinkedList_float**l,size_t c,float*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(float),c,a);}
void(*cutils_csll_SinglyLinkedList_float_del)(cutils_csll_SinglyLinkedList_float*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_float_len)(cutils_csll_SinglyLinkedList_float*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_float_truncate)(cutils_csll_SinglyLinkedList_float*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_float_clear)(cutils_csll_SinglyLinkedList_float*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_float_iterator* cutils_csll_SinglyLinkedList_float_iter(cutils_csll_SinglyLinkedList_float*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_float_iterator_del(cutils_csll_SinglyLinkedList_float_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_float_iterator_next(cutils_csll_SinglyLinkedList_float_iterator*i,float**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_float_iterator_pull(cutils_csll_SinglyLinkedList_float_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_float_swap)(cutils_csll_SinglyLinkedList_float*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_float_reverse)(cutils_csll_SinglyLinkedList_float*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_float_append(cutils_csll_SinglyLinkedList_float*l,size_t c,float*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(float),c,a);}
bool cutils_csll_SinglyLinkedList_float_push(cutils_csll_SinglyLinkedList_float*l,size_t i,size_t c,float*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(float),c,a);}
size_t(*cutils_csll_SinglyLinkedList_float_pull)(cutils_csll_SinglyLinkedList_float*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_float_set(cutils_csll_SinglyLinkedList_float*l,size_t i,size_t c,float*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(float),c,a);}
bool cutils_csll_SinglyLinkedList_float_pop(cutils_csll_SinglyLinkedList_float*l,size_t i,size_t c,float*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(float),c,a);}
float cutils_csll_SinglyLinkedList_float_get(cutils_csll_SinglyLinkedList_float*l,size_t i){return *(float*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_float_sub(cutils_csll_SinglyLinkedList_float*l,size_t i,size_t c,float*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(float),c,a);}
void(*cutils_csll_SinglyLinkedList_float_map)(cutils_csll_SinglyLinkedList_float*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_float_find(cutils_csll_SinglyLinkedList_float*l,bool(*f)(const void*,const void*,size_t),float*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(float),p,i);}
size_t cutils_csll_SinglyLinkedList_float_findall(cutils_csll_SinglyLinkedList_float*l,bool(*f)(const void*,const void*,size_t),float*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(float),p,i);}
void(*cutils_csll_SinglyLinkedList_float_print)(cutils_csll_SinglyLinkedList_float*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_float_format(const float*i,char**b,size_t*s){snprintf(*b,*s,"%ff",*i);return true;}
bool cutils_csll_SinglyLinkedList_float_compare(const void*p1,const void*p2,size_t s){return cutils_fcmp_float_compare(*(float*)p1,*(float*)p2);}
bool cutils_csll_SinglyLinkedList_float_new_default1(cutils_csll_SinglyLinkedList_float**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(float),0,NULL);}
void cutils_csll_SinglyLinkedList_float_truncate_default1(cutils_csll_SinglyLinkedList_float*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_float_swap_default3(cutils_csll_SinglyLinkedList_float*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_float_append_default2(cutils_csll_SinglyLinkedList_float*l,float*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(float),1,a);}
bool cutils_csll_SinglyLinkedList_float_push_default3(cutils_csll_SinglyLinkedList_float*l,size_t i,float*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(float),1,a);}
size_t cutils_csll_SinglyLinkedList_float_pull_default2(cutils_csll_SinglyLinkedList_float*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_float_set_default3(cutils_csll_SinglyLinkedList_float*l,size_t i,float*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(float),1,a);}
bool cutils_csll_SinglyLinkedList_float_pop_default3(cutils_csll_SinglyLinkedList_float*l,size_t i,float*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(float),1,a);}
bool cutils_csll_SinglyLinkedList_float_sub_default3(cutils_csll_SinglyLinkedList_float*l,size_t i,float*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(float),1,a);}
void cutils_csll_SinglyLinkedList_float_map_default3(cutils_csll_SinglyLinkedList_float*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_float_find_default3(cutils_csll_SinglyLinkedList_float*l,float*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_float_compare,sizeof(float),p,i);}
size_t cutils_csll_SinglyLinkedList_float_findall_default3(cutils_csll_SinglyLinkedList_float*l,float*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_float_compare,sizeof(float),p,i);}
void cutils_csll_SinglyLinkedList_float_print_default1(cutils_csll_SinglyLinkedList_float*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"float",cutils_csll_SinglyLinkedList_float_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_double;
typedef SLLIterator cutils_csll_SinglyLinkedList_double_iterator;
bool cutils_csll_SinglyLinkedList_double_new(cutils_csll_SinglyLinkedList_double**l,size_t c,double*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(double),c,a);}
void(*cutils_csll_SinglyLinkedList_double_del)(cutils_csll_SinglyLinkedList_double*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_double_len)(cutils_csll_SinglyLinkedList_double*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_double_truncate)(cutils_csll_SinglyLinkedList_double*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_double_clear)(cutils_csll_SinglyLinkedList_double*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_double_iterator* cutils_csll_SinglyLinkedList_double_iter(cutils_csll_SinglyLinkedList_double*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_double_iterator_del(cutils_csll_SinglyLinkedList_double_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_double_iterator_next(cutils_csll_SinglyLinkedList_double_iterator*i,double**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_double_iterator_pull(cutils_csll_SinglyLinkedList_double_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_double_swap)(cutils_csll_SinglyLinkedList_double*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_double_reverse)(cutils_csll_SinglyLinkedList_double*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_double_append(cutils_csll_SinglyLinkedList_double*l,size_t c,double*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(double),c,a);}
bool cutils_csll_SinglyLinkedList_double_push(cutils_csll_SinglyLinkedList_double*l,size_t i,size_t c,double*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(double),c,a);}
size_t(*cutils_csll_SinglyLinkedList_double_pull)(cutils_csll_SinglyLinkedList_double*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_double_set(cutils_csll_SinglyLinkedList_double*l,size_t i,size_t c,double*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(double),c,a);}
bool cutils_csll_SinglyLinkedList_double_pop(cutils_csll_SinglyLinkedList_double*l,size_t i,size_t c,double*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(double),c,a);}
double cutils_csll_SinglyLinkedList_double_get(cutils_csll_SinglyLinkedList_double*l,size_t i){return *(double*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_double_sub(cutils_csll_SinglyLinkedList_double*l,size_t i,size_t c,double*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(double),c,a);}
void(*cutils_csll_SinglyLinkedList_double_map)(cutils_csll_SinglyLinkedList_double*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_double_find(cutils_csll_SinglyLinkedList_double*l,bool(*f)(const void*,const void*,size_t),double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(double),p,i);}
size_t cutils_csll_SinglyLinkedList_double_findall(cutils_csll_SinglyLinkedList_double*l,bool(*f)(const void*,const void*,size_t),double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(double),p,i);}
void(*cutils_csll_SinglyLinkedList_double_print)(cutils_csll_SinglyLinkedList_double*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_double_format(const double*i,char**b,size_t*s){snprintf(*b,*s,"%lf",*i);return true;}
bool cutils_csll_SinglyLinkedList_double_compare(const void*p1,const void*p2,size_t s){return cutils_fcmp_double_compare(*(double*)p1,*(double*)p2);}
bool cutils_csll_SinglyLinkedList_double_new_default1(cutils_csll_SinglyLinkedList_double**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(double),0,NULL);}
void cutils_csll_SinglyLinkedList_double_truncate_default1(cutils_csll_SinglyLinkedList_double*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_double_swap_default3(cutils_csll_SinglyLinkedList_double*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_double_append_default2(cutils_csll_SinglyLinkedList_double*l,double*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(double),1,a);}
bool cutils_csll_SinglyLinkedList_double_push_default3(cutils_csll_SinglyLinkedList_double*l,size_t i,double*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(double),1,a);}
size_t cutils_csll_SinglyLinkedList_double_pull_default2(cutils_csll_SinglyLinkedList_double*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_double_set_default3(cutils_csll_SinglyLinkedList_double*l,size_t i,double*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(double),1,a);}
bool cutils_csll_SinglyLinkedList_double_pop_default3(cutils_csll_SinglyLinkedList_double*l,size_t i,double*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(double),1,a);}
bool cutils_csll_SinglyLinkedList_double_sub_default3(cutils_csll_SinglyLinkedList_double*l,size_t i,double*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(double),1,a);}
void cutils_csll_SinglyLinkedList_double_map_default3(cutils_csll_SinglyLinkedList_double*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_double_find_default3(cutils_csll_SinglyLinkedList_double*l,double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_double_compare,sizeof(double),p,i);}
size_t cutils_csll_SinglyLinkedList_double_findall_default3(cutils_csll_SinglyLinkedList_double*l,double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_double_compare,sizeof(double),p,i);}
void cutils_csll_SinglyLinkedList_double_print_default1(cutils_csll_SinglyLinkedList_double*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"double",cutils_csll_SinglyLinkedList_double_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_long_double;
typedef SLLIterator cutils_csll_SinglyLinkedList_long_double_iterator;
bool cutils_csll_SinglyLinkedList_long_double_new(cutils_csll_SinglyLinkedList_long_double**l,size_t c,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(long double),c,a);}
void(*cutils_csll_SinglyLinkedList_long_double_del)(cutils_csll_SinglyLinkedList_long_double*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_long_double_len)(cutils_csll_SinglyLinkedList_long_double*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_long_double_truncate)(cutils_csll_SinglyLinkedList_long_double*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_long_double_clear)(cutils_csll_SinglyLinkedList_long_double*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_long_double_iterator* cutils_csll_SinglyLinkedList_long_double_iter(cutils_csll_SinglyLinkedList_long_double*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_long_double_iterator_del(cutils_csll_SinglyLinkedList_long_double_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_long_double_iterator_next(cutils_csll_SinglyLinkedList_long_double_iterator*i,long double**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_long_double_iterator_pull(cutils_csll_SinglyLinkedList_long_double_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_long_double_swap)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_long_double_reverse)(cutils_csll_SinglyLinkedList_long_double*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_long_double_append(cutils_csll_SinglyLinkedList_long_double*l,size_t c,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(long double),c,a);}
bool cutils_csll_SinglyLinkedList_long_double_push(cutils_csll_SinglyLinkedList_long_double*l,size_t i,size_t c,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(long double),c,a);}
size_t(*cutils_csll_SinglyLinkedList_long_double_pull)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_long_double_set(cutils_csll_SinglyLinkedList_long_double*l,size_t i,size_t c,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(long double),c,a);}
bool cutils_csll_SinglyLinkedList_long_double_pop(cutils_csll_SinglyLinkedList_long_double*l,size_t i,size_t c,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(long double),c,a);}
long double cutils_csll_SinglyLinkedList_long_double_get(cutils_csll_SinglyLinkedList_long_double*l,size_t i){return *(long double*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_long_double_sub(cutils_csll_SinglyLinkedList_long_double*l,size_t i,size_t c,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(long double),c,a);}
void(*cutils_csll_SinglyLinkedList_long_double_map)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_long_double_find(cutils_csll_SinglyLinkedList_long_double*l,bool(*f)(const void*,const void*,size_t),long double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(long double),p,i);}
size_t cutils_csll_SinglyLinkedList_long_double_findall(cutils_csll_SinglyLinkedList_long_double*l,bool(*f)(const void*,const void*,size_t),long double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(long double),p,i);}
void(*cutils_csll_SinglyLinkedList_long_double_print)(cutils_csll_SinglyLinkedList_long_double*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_long_double_format(const long double*i,char**b,size_t*s){snprintf(*b,*s,"%Lf",*i);return true;}
bool cutils_csll_SinglyLinkedList_long_double_compare(const void*p1,const void*p2,size_t s){return cutils_fcmp_long_double_compare(*(long double*)p1,*(long double*)p2);}
bool cutils_csll_SinglyLinkedList_long_double_new_default1(cutils_csll_SinglyLinkedList_long_double**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(long double),0,NULL);}
void cutils_csll_SinglyLinkedList_long_double_truncate_default1(cutils_csll_SinglyLinkedList_long_double*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_long_double_swap_default3(cutils_csll_SinglyLinkedList_long_double*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_long_double_append_default2(cutils_csll_SinglyLinkedList_long_double*l,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(long double),1,a);}
bool cutils_csll_SinglyLinkedList_long_double_push_default3(cutils_csll_SinglyLinkedList_long_double*l,size_t i,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(long double),1,a);}
size_t cutils_csll_SinglyLinkedList_long_double_pull_default2(cutils_csll_SinglyLinkedList_long_double*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_long_double_set_default3(cutils_csll_SinglyLinkedList_long_double*l,size_t i,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(long double),1,a);}
bool cutils_csll_SinglyLinkedList_long_double_pop_default3(cutils_csll_SinglyLinkedList_long_double*l,size_t i,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(long double),1,a);}
bool cutils_csll_SinglyLinkedList_long_double_sub_default3(cutils_csll_SinglyLinkedList_long_double*l,size_t i,long double*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(long double),1,a);}
void cutils_csll_SinglyLinkedList_long_double_map_default3(cutils_csll_SinglyLinkedList_long_double*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_long_double_find_default3(cutils_csll_SinglyLinkedList_long_double*l,long double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_long_double_compare,sizeof(long double),p,i);}
size_t cutils_csll_SinglyLinkedList_long_double_findall_default3(cutils_csll_SinglyLinkedList_long_double*l,long double*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_long_double_compare,sizeof(long double),p,i);}
void cutils_csll_SinglyLinkedList_long_double_print_default1(cutils_csll_SinglyLinkedList_long_double*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"long_double",cutils_csll_SinglyLinkedList_long_double_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_bool;
typedef SLLIterator cutils_csll_SinglyLinkedList_bool_iterator;
bool cutils_csll_SinglyLinkedList_bool_new(cutils_csll_SinglyLinkedList_bool**l,size_t c,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(bool),c,a);}
void(*cutils_csll_SinglyLinkedList_bool_del)(cutils_csll_SinglyLinkedList_bool*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_bool_len)(cutils_csll_SinglyLinkedList_bool*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_bool_truncate)(cutils_csll_SinglyLinkedList_bool*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_bool_clear)(cutils_csll_SinglyLinkedList_bool*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_bool_iterator* cutils_csll_SinglyLinkedList_bool_iter(cutils_csll_SinglyLinkedList_bool*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_bool_iterator_del(cutils_csll_SinglyLinkedList_bool_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_bool_iterator_next(cutils_csll_SinglyLinkedList_bool_iterator*i,bool**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_bool_iterator_pull(cutils_csll_SinglyLinkedList_bool_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_bool_swap)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_bool_reverse)(cutils_csll_SinglyLinkedList_bool*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_bool_append(cutils_csll_SinglyLinkedList_bool*l,size_t c,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(bool),c,a);}
bool cutils_csll_SinglyLinkedList_bool_push(cutils_csll_SinglyLinkedList_bool*l,size_t i,size_t c,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(bool),c,a);}
size_t(*cutils_csll_SinglyLinkedList_bool_pull)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_bool_set(cutils_csll_SinglyLinkedList_bool*l,size_t i,size_t c,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(bool),c,a);}
bool cutils_csll_SinglyLinkedList_bool_pop(cutils_csll_SinglyLinkedList_bool*l,size_t i,size_t c,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(bool),c,a);}
bool cutils_csll_SinglyLinkedList_bool_get(cutils_csll_SinglyLinkedList_bool*l,size_t i){return *(bool*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_bool_sub(cutils_csll_SinglyLinkedList_bool*l,size_t i,size_t c,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(bool),c,a);}
void(*cutils_csll_SinglyLinkedList_bool_map)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_bool_find(cutils_csll_SinglyLinkedList_bool*l,bool(*f)(const void*,const void*,size_t),bool*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(bool),p,i);}
size_t cutils_csll_SinglyLinkedList_bool_findall(cutils_csll_SinglyLinkedList_bool*l,bool(*f)(const void*,const void*,size_t),bool*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(bool),p,i);}
void(*cutils_csll_SinglyLinkedList_bool_print)(cutils_csll_SinglyLinkedList_bool*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_bool_format(const bool*i,char**b,size_t*s){snprintf(*b,*s,"%s",*i?"true":"false");return true;}
bool cutils_csll_SinglyLinkedList_bool_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_bool_new_default1(cutils_csll_SinglyLinkedList_bool**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(bool),0,NULL);}
void cutils_csll_SinglyLinkedList_bool_truncate_default1(cutils_csll_SinglyLinkedList_bool*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_bool_swap_default3(cutils_csll_SinglyLinkedList_bool*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_bool_append_default2(cutils_csll_SinglyLinkedList_bool*l,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(bool),1,a);}
bool cutils_csll_SinglyLinkedList_bool_push_default3(cutils_csll_SinglyLinkedList_bool*l,size_t i,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(bool),1,a);}
size_t cutils_csll_SinglyLinkedList_bool_pull_default2(cutils_csll_SinglyLinkedList_bool*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_bool_set_default3(cutils_csll_SinglyLinkedList_bool*l,size_t i,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(bool),1,a);}
bool cutils_csll_SinglyLinkedList_bool_pop_default3(cutils_csll_SinglyLinkedList_bool*l,size_t i,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(bool),1,a);}
bool cutils_csll_SinglyLinkedList_bool_sub_default3(cutils_csll_SinglyLinkedList_bool*l,size_t i,bool*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(bool),1,a);}
void cutils_csll_SinglyLinkedList_bool_map_default3(cutils_csll_SinglyLinkedList_bool*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_bool_find_default3(cutils_csll_SinglyLinkedList_bool*l,bool*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_bool_compare,sizeof(bool),p,i);}
size_t cutils_csll_SinglyLinkedList_bool_findall_default3(cutils_csll_SinglyLinkedList_bool*l,bool*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_bool_compare,sizeof(bool),p,i);}
void cutils_csll_SinglyLinkedList_bool_print_default1(cutils_csll_SinglyLinkedList_bool*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"bool",cutils_csll_SinglyLinkedList_bool_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_size_t;
typedef SLLIterator cutils_csll_SinglyLinkedList_size_t_iterator;
bool cutils_csll_SinglyLinkedList_size_t_new(cutils_csll_SinglyLinkedList_size_t**l,size_t c,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(size_t),c,a);}
void(*cutils_csll_SinglyLinkedList_size_t_del)(cutils_csll_SinglyLinkedList_size_t*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_size_t_len)(cutils_csll_SinglyLinkedList_size_t*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_size_t_truncate)(cutils_csll_SinglyLinkedList_size_t*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_size_t_clear)(cutils_csll_SinglyLinkedList_size_t*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_size_t_iterator* cutils_csll_SinglyLinkedList_size_t_iter(cutils_csll_SinglyLinkedList_size_t*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_size_t_iterator_del(cutils_csll_SinglyLinkedList_size_t_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_size_t_iterator_next(cutils_csll_SinglyLinkedList_size_t_iterator*i,size_t**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_size_t_iterator_pull(cutils_csll_SinglyLinkedList_size_t_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_size_t_swap)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_size_t_reverse)(cutils_csll_SinglyLinkedList_size_t*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_size_t_append(cutils_csll_SinglyLinkedList_size_t*l,size_t c,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(size_t),c,a);}
bool cutils_csll_SinglyLinkedList_size_t_push(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t c,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(size_t),c,a);}
size_t(*cutils_csll_SinglyLinkedList_size_t_pull)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_size_t_set(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t c,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(size_t),c,a);}
bool cutils_csll_SinglyLinkedList_size_t_pop(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t c,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(size_t),c,a);}
size_t cutils_csll_SinglyLinkedList_size_t_get(cutils_csll_SinglyLinkedList_size_t*l,size_t i){return *(size_t*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_size_t_sub(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t c,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(size_t),c,a);}
void(*cutils_csll_SinglyLinkedList_size_t_map)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_size_t_find(cutils_csll_SinglyLinkedList_size_t*l,bool(*f)(const void*,const void*,size_t),size_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(size_t),p,i);}
size_t cutils_csll_SinglyLinkedList_size_t_findall(cutils_csll_SinglyLinkedList_size_t*l,bool(*f)(const void*,const void*,size_t),size_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(size_t),p,i);}
void(*cutils_csll_SinglyLinkedList_size_t_print)(cutils_csll_SinglyLinkedList_size_t*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_size_t_format(const size_t*i,char**b,size_t*s){snprintf(*b,*s,"%zu",*i);return true;}
bool cutils_csll_SinglyLinkedList_size_t_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_size_t_new_default1(cutils_csll_SinglyLinkedList_size_t**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(size_t),0,NULL);}
void cutils_csll_SinglyLinkedList_size_t_truncate_default1(cutils_csll_SinglyLinkedList_size_t*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_size_t_swap_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_size_t_append_default2(cutils_csll_SinglyLinkedList_size_t*l,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(size_t),1,a);}
bool cutils_csll_SinglyLinkedList_size_t_push_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(size_t),1,a);}
size_t cutils_csll_SinglyLinkedList_size_t_pull_default2(cutils_csll_SinglyLinkedList_size_t*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_size_t_set_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(size_t),1,a);}
bool cutils_csll_SinglyLinkedList_size_t_pop_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(size_t),1,a);}
bool cutils_csll_SinglyLinkedList_size_t_sub_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t i,size_t*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(size_t),1,a);}
void cutils_csll_SinglyLinkedList_size_t_map_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_size_t_find_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_size_t_compare,sizeof(size_t),p,i);}
size_t cutils_csll_SinglyLinkedList_size_t_findall_default3(cutils_csll_SinglyLinkedList_size_t*l,size_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_size_t_compare,sizeof(size_t),p,i);}
void cutils_csll_SinglyLinkedList_size_t_print_default1(cutils_csll_SinglyLinkedList_size_t*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"size_t",cutils_csll_SinglyLinkedList_size_t_format);}
/*----------------------------------------------------------------------------*/
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_csll_SinglyLinkedList_ptrdiff_t;
typedef SLLIterator cutils_csll_SinglyLinkedList_ptrdiff_t_iterator;
bool cutils_csll_SinglyLinkedList_ptrdiff_t_new(cutils_csll_SinglyLinkedList_ptrdiff_t**l,size_t c,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(ptrdiff_t),c,a);}
void(*cutils_csll_SinglyLinkedList_ptrdiff_t_del)(cutils_csll_SinglyLinkedList_ptrdiff_t*)=cutils_csll_SinglyLinkedList_void_ptr_del;
size_t(*cutils_csll_SinglyLinkedList_ptrdiff_t_len)(cutils_csll_SinglyLinkedList_ptrdiff_t*)=cutils_csll_SinglyLinkedList_void_ptr_len;
void(*cutils_csll_SinglyLinkedList_ptrdiff_t_truncate)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t)=cutils_csll_SinglyLinkedList_void_ptr_truncate;
void(*cutils_csll_SinglyLinkedList_ptrdiff_t_clear)(cutils_csll_SinglyLinkedList_ptrdiff_t*)=cutils_csll_SinglyLinkedList_void_ptr_clear;
cutils_csll_SinglyLinkedList_ptrdiff_t_iterator* cutils_csll_SinglyLinkedList_ptrdiff_t_iter(cutils_csll_SinglyLinkedList_ptrdiff_t*l){return cutils_csll_SinglyLinkedList_void_ptr_iter(l);}
void cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_del(cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_del(i);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_next(cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*i,ptrdiff_t**p){return cutils_csll_SinglyLinkedList_void_ptr_iterator_next(i,p);}
void cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_pull(cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*i){return cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(i);}
bool(*cutils_csll_SinglyLinkedList_ptrdiff_t_swap)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_swap;
bool(*cutils_csll_SinglyLinkedList_ptrdiff_t_reverse)(cutils_csll_SinglyLinkedList_ptrdiff_t*)=cutils_csll_SinglyLinkedList_void_ptr_reverse;
bool cutils_csll_SinglyLinkedList_ptrdiff_t_append(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t c,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(ptrdiff_t),c,a);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_push(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,size_t c,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(ptrdiff_t),c,a);}
size_t(*cutils_csll_SinglyLinkedList_ptrdiff_t_pull)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t)=cutils_csll_SinglyLinkedList_void_ptr_pull;
bool cutils_csll_SinglyLinkedList_ptrdiff_t_set(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,size_t c,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(ptrdiff_t),c,a);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_pop(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,size_t c,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(ptrdiff_t),c,a);}
ptrdiff_t cutils_csll_SinglyLinkedList_ptrdiff_t_get(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i){return *(ptrdiff_t*)cutils_csll_SinglyLinkedList_void_ptr_get(l,i);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_sub(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,size_t c,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(ptrdiff_t),c,a);}
void(*cutils_csll_SinglyLinkedList_ptrdiff_t_map)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,void(*)())=cutils_csll_SinglyLinkedList_void_ptr_map;
bool cutils_csll_SinglyLinkedList_ptrdiff_t_find(cutils_csll_SinglyLinkedList_ptrdiff_t*l,bool(*f)(const void*,const void*,size_t),ptrdiff_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,f,sizeof(ptrdiff_t),p,i);}
size_t cutils_csll_SinglyLinkedList_ptrdiff_t_findall(cutils_csll_SinglyLinkedList_ptrdiff_t*l,bool(*f)(const void*,const void*,size_t),ptrdiff_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,f,sizeof(ptrdiff_t),p,i);}
void(*cutils_csll_SinglyLinkedList_ptrdiff_t_print)(cutils_csll_SinglyLinkedList_ptrdiff_t*,FILE*,const char*,bool(*)())=cutils_csll_SinglyLinkedList_void_ptr_print;
bool cutils_csll_SinglyLinkedList_ptrdiff_t_format(const ptrdiff_t*i,char**b,size_t*s){snprintf(*b,*s,"%td",*i);return true;}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_new_default1(cutils_csll_SinglyLinkedList_ptrdiff_t**l){return cutils_csll_SinglyLinkedList_void_ptr_new(l,sizeof(ptrdiff_t),0,NULL);}
void cutils_csll_SinglyLinkedList_ptrdiff_t_truncate_default1(cutils_csll_SinglyLinkedList_ptrdiff_t*l){return cutils_csll_SinglyLinkedList_void_ptr_truncate(l,0);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_swap_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i1,size_t i2){return cutils_csll_SinglyLinkedList_void_ptr_swap(l,i1,i2,1);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_append_default2(cutils_csll_SinglyLinkedList_ptrdiff_t*l,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_append(l,sizeof(ptrdiff_t),1,a);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_push_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_push(l,i,sizeof(ptrdiff_t),1,a);}
size_t cutils_csll_SinglyLinkedList_ptrdiff_t_pull_default2(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i){return cutils_csll_SinglyLinkedList_void_ptr_pull(l,i,1);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_set_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_set(l,i,sizeof(ptrdiff_t),1,a);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_pop_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_pop(l,i,sizeof(ptrdiff_t),1,a);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_sub_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t i,ptrdiff_t*a){return cutils_csll_SinglyLinkedList_void_ptr_sub(l,i,sizeof(ptrdiff_t),1,a);}
void cutils_csll_SinglyLinkedList_ptrdiff_t_map_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,size_t c,void(*f)()){return cutils_csll_SinglyLinkedList_void_ptr_map(l,0,c,f);}
bool cutils_csll_SinglyLinkedList_ptrdiff_t_find_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,ptrdiff_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_find(l,cutils_csll_SinglyLinkedList_ptrdiff_t_compare,sizeof(ptrdiff_t),p,i);}
size_t cutils_csll_SinglyLinkedList_ptrdiff_t_findall_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*l,ptrdiff_t*p,size_t*i){return cutils_csll_SinglyLinkedList_void_ptr_findall(l,cutils_csll_SinglyLinkedList_ptrdiff_t_compare,sizeof(ptrdiff_t),p,i);}
void cutils_csll_SinglyLinkedList_ptrdiff_t_print_default1(cutils_csll_SinglyLinkedList_ptrdiff_t*l){return cutils_csll_SinglyLinkedList_void_ptr_print(l,stdout,"ptrdiff_t",cutils_csll_SinglyLinkedList_ptrdiff_t_format);}