/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.222 (20140908)                       **
**                                                                            **
**                                File: cshm.c                                **
**                                                                            **
**   For more information about the project, visit <http://www.cutils.org>.   **
**                       Copyright (C) 2014 Peter Varo                        **
**                                                                            **
**  This program is free software: you can redistribute it and/or modify it   **
**   under the terms of the GNU General Public License as published by the    **
**       Free Software Foundation, either version 3 of the License, or        **
**                    (at your option) any later version.                     **
**                                                                            **
**    This program is distributed in the hope that it will be useful, but     **
**         WITHOUT ANY WARRANTY; without even the implied warranty of         **
**            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            **
**            See the GNU General Public License for more details.            **
**                                                                            **
**     You should have received a copy of the GNU General Public License      **
**     along with this program, most likely a file in the root directory,     **
**        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        **
**                                                                            **
************************************************************************ INFO */

#define FILE_STARTS_HERE
#include <stdlib.h>   /* malloc(), free() */
#ifdef CDAR_JEM
  #include <jemalloc/jemalloc.h>  /* malloc(), free() */
#endif

/* Include standard headers */
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool, true, false */

/* Include cutils headers */
#include "internal/xxhash.h"
#include "csll.h"

/* If 'optimised' or the 'exceptions are not available' */
#if defined CDAR_OPT
  #define cutils_cexc_raise(msg, len)
#else
  #include "cexc.h"
  #include "internal/defs.h"
#endif

/*----------------------------------------------------------------------------*/
/* TODO: Newest xxhash has XXH64 which is way faster than XXH32, but works only
         on 64 bit systems. Update xxhash to latest. Create an architecture
         dependent macro dispatcher between the hash functions */
#undef  xxhash_hash
#define xxhash_hash(...) XXH32(__VA_ARGS__)


/*----------------------------------------------------------------------------*/
/* Type representations */
#undef  TYPE_REPR
#define TYPE_REPR "StaticHashMap"
#undef  SUBTYPE_REPR
#define SUBTYPE_REPR TYPE_REPR "_iterator"

/*----------------------------------------------------------------------------*/
/* Shorthands for this source */
#undef _concat_underscore
#undef concat_underscore
#undef HASH_MAP
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD
#define _concat_underscore(token1, token2) token1##_##token2
#define concat_underscore(token1, token2) _concat_underscore(token1, token2)
#define HASH_MAP cutils_cshm_StaticHashMap_void_ptr_and_void_ptr
#define METHOD(func)  concat_underscore(HASH_MAP, func)
#define SUPPORT(type) concat_underscore(HASH_MAP, type)
#define SUPPORT_METHOD(type, func) concat_underscore(HASH_MAP, type##_##func)

/*----------------------------------------------------------------------------*/
/* Base type */
typedef struct
{
    size_t length;
    cutils_csll_SinglyLinkedList_void_ptr *slots[];
} HASH_MAP;



/*----------------------------------------------------------------------------*/
/* Support types */
typedef struct
{
    size_t offset; /* relative offset from key to get the value (key size) */
    char key[];    /* key + value */
} SHMItem;



/*----------------------------------------------------------------------------*/
typedef struct
{
    size_t index;
    HASH_MAP *hashmap;
    cutils_csll_SinglyLinkedList_void_ptr_iterator *iterator;
} SHMIterator;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Iterator type (public alias) */
typedef SHMIterator SUPPORT(iterator);



/*----------------------------------------------------------------------------*/
static inline bool
__cshm_next(SHMIterator *iterator,
            SHMItem **item,
            const char *exception_msg,
            const size_t exception_msg_size)
{
    /* If list-iterator is not empty */
    if (cutils_csll_SinglyLinkedList_void_ptr_iterator_next(iterator->iterator, item))
        return true;

    /*  If list-iterator is empty => local reference of array of lists */
    cutils_csll_SinglyLinkedList_void_ptr **slots = iterator->hashmap->slots;

    /* Get the next iterator from the array */
    for (size_t i=iterator->index + 1; i<iterator->hashmap->length; i++)
    {
        /* Create new list-iterator */
        cutils_csll_SinglyLinkedList_void_ptr_iterator *list_iterator =
            cutils_csll_SinglyLinkedList_void_ptr_iter(slots[i]);
        if (!list_iterator)
        {
            cutils_cexc_raise(exception_msg, exception_msg_size);
            return false;
        }

        /* If finally list-iterator is not empty */
        if (cutils_csll_SinglyLinkedList_void_ptr_iterator_next(list_iterator, item))
        {
            /* Set new index and list-iterator and return */
            iterator->index = i;
            iterator->iterator = list_iterator;
            return true;
        }
    }
    /* If hash-iterator becomes empty */
    return false;
}



/*----------------------------------------------------------------------------*/
bool
METHOD(new)(HASH_MAP **hashmap,
            size_t count)
{
    /* If count is 0 => hashing will produce zero division */
    if (!count)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "new", "2nd", "count")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        goto Exception_Count_Is_Zero;
    }

    /* Allocate space for hash map */
    HASH_MAP *_hashmap =
        malloc(sizeof(HASH_MAP) +
               count * sizeof(cutils_csll_SinglyLinkedList_void_ptr*));
    if (!_hashmap)
        goto Exception_Struct_Allocation_Failed;

    /* Temporary pointer to a slot and local reference to all slots */
    cutils_csll_SinglyLinkedList_void_ptr *linlist;
    cutils_csll_SinglyLinkedList_void_ptr **slots = _hashmap->slots;

    /* Create slots */
    size_t i, last_index = 0;
    for (i=0; i<count; last_index=i++)
    {
        /* Create linked-list */
        if (!cutils_csll_SinglyLinkedList_void_ptr_new(&linlist, 0, 0, NULL))
            goto Exception_List_Allocation_Failed;
        /* Store linked-list */
        slots[i] = linlist;
    }

    /* Set static values */
    _hashmap->length = count;

    /* If everything went fine, return indicating success */
    *hashmap = _hashmap;
    return true;

    /* If something went wrong during the allocation of linked-list slots */
    Exception_List_Allocation_Failed:
        /* Free all allocated linked-lists */
        for (i=0; i<last_index; i++)
            cutils_csll_SinglyLinkedList_void_ptr_del(slots[i]);
        /* Destroy base-type */
        free(_hashmap);

    /* If something went wrong during the dynamic allocation */
    Exception_Struct_Allocation_Failed:
        /* Raise exception */
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "new")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);

    /* If count is zero */
    Exception_Count_Is_Zero:
        /* Set pointer to NULL and return indication failure */
        *hashmap = NULL;
        return false;
}


/*----------------------------------------------------------------------------*/
void
METHOD(del)(HASH_MAP *hashmap)
{
#ifndef CSHM_OPT
    /* If hash map is not a pointer to NULL */
    if (hashmap)
    {
#endif
        /* Local reference */
        cutils_csll_SinglyLinkedList_void_ptr **slots = hashmap->slots;
        /* Delete all linked lists (and their data) in slots */
        for (size_t i=0; i<hashmap->length; i++)
            cutils_csll_SinglyLinkedList_void_ptr_del(slots[i]);
        /* Destroy hashmap */
        free(hashmap);
    }
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
METHOD(add)(HASH_MAP *hashmap,
            bool (*compare)(const void*, const void*, size_t),
            int key_size, /* xxhash key size => int */
            size_t value_size,
            const void *key,
            const void *value)
{
#ifndef CSHM_OPT
    if (!hashmap)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "add")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
    else if (!key)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "add", "3rd", "key")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
    else if (!value)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "add", "4th", "key")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
#endif

    /* Get/set/cast essential values */
    size_t item_size = sizeof(SHMItem) + key_size + value_size;

    /* TODO: try to get a pointer from the SinglyLinkedList_void_ptr_append()
             which is "empty" and has the size of 'item_size' and can be
             casted to SHMItem => so adding a new item to the hashmap will
             only require one malloc instead of two */

    /* Create a key-value item */
    SHMItem *item = malloc(item_size);
    if (!item)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "add")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false;
    }

    /* Set key and value in item */
    item->offset = key_size;
    memcpy(item->key, key, key_size);
    memcpy(item->key + key_size, value, value_size);

    /* Local reference of list */
    cutils_csll_SinglyLinkedList_void_ptr *linlist =
        hashmap->slots[xxhash_hash(key, key_size, 0) % hashmap->length];

    /* Create an iterator of list */
    cutils_csll_SinglyLinkedList_void_ptr_iterator *iterator =
        cutils_csll_SinglyLinkedList_void_ptr_iter(linlist);

    /* If key already in the list, remove it */
    SHMItem *temp_item;
    while (cutils_csll_SinglyLinkedList_void_ptr_iterator_next(iterator, &temp_item))
        /* If key-size are the same and key content is the same */
        if (key_size == temp_item->offset &&
            compare(temp_item->key, key, key_size))
        {
            /* Remove current item, delete this iterator and break searching */
            cutils_csll_SinglyLinkedList_void_ptr_iterator_pull(iterator);
            cutils_csll_SinglyLinkedList_void_ptr_iterator_del(iterator);
            break;
        }

    /* Add new item to list */
    bool check =
        cutils_csll_SinglyLinkedList_void_ptr_append(linlist, item_size, 1, item);

    /* Clean up and return */
    free(item);
    if (!check)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "add")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false;
    }
    return true;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
METHOD(add_default5)(HASH_MAP *hashmap,
                     int key_size,
                     size_t value_size,
                     const void *key,
                     const void *value)
{
    return METHOD(add)(hashmap, METHOD(compare), key_size, value_size, key, value);
}



/*----------------------------------------------------------------------------*/
void *
METHOD(get)(HASH_MAP *hashmap,
            bool (*compare)(const void*, const void*, size_t),
            size_t key_size,
            const void *key)
{
#ifndef CSHM_OPT
    if (!hashmap)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "get")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
    else if (!key)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "get", "3rd", "key")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
#endif
    /* Get nth (based on the hash value of the key) linked-list */
    cutils_csll_SinglyLinkedList_void_ptr *linlist =
        hashmap->slots[xxhash_hash(key, key_size, 0) % hashmap->length];
    /* Create an iterator */
    cutils_csll_SinglyLinkedList_void_ptr_iterator *iterator =
        cutils_csll_SinglyLinkedList_void_ptr_iter(linlist);

    /* Search for key */
    SHMItem *item;
    while (cutils_csll_SinglyLinkedList_void_ptr_iterator_next(iterator, &item))
        /* If found key, return the value */
        if (compare(item->key, key, key_size))
            return item->key + item->offset;
    /* If not found return a pointer to NULL */
    return NULL;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void *
METHOD(get_default3)(HASH_MAP *hashmap,
                     size_t key_size,
                     const void *key)
{
    return METHOD(get)(hashmap, METHOD(compare), key_size, key);
}



/*----------------------------------------------------------------------------*/
SUPPORT(iterator) *
METHOD(iter)(HASH_MAP *hashmap)
{
#ifndef CSHM_OPT
    if (!hashmap)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "iter")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return NULL; /* Cannot operate on NULL */
    }
#endif
    SHMIterator *hash_iterator =
        malloc(sizeof(SHMIterator));
    if (!hash_iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "iter")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return NULL;
    }

    cutils_csll_SinglyLinkedList_void_ptr_iterator *list_iterator =
        cutils_csll_SinglyLinkedList_void_ptr_iter(hashmap->slots[0]);
    if (!list_iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "iter")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        free(hash_iterator);
        return NULL;
    }

    /* Set iterator */
    hash_iterator->index = 0;
    hash_iterator->hashmap = hashmap;
    hash_iterator->iterator = list_iterator;

    /* Return new iterator object */
    return hash_iterator;
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
                               void *key)
{
#ifndef CSHM_OPT
    if (!iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(SUBTYPE_REPR, "keys")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
    else if (!key)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(SUBTYPE_REPR, "keys", "2nd", key)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
#endif
    /* Prepare exception message to be used on internal allocation failure */
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(SUBTYPE_REPR, "keys")

    SHMItem *item;
    if (__cshm_next(iterator, &item, EXCEPTION_MSG, sizeof EXCEPTION_MSG))
    {
        *(void **)key = item->key;
        return true;
    }
    free(iterator);
    return false;
}



/*----------------------------------------------------------------------------*/
bool
SUPPORT_METHOD(iterator, values)(SUPPORT(iterator) *iterator,
                                 void *value)
{
#ifndef CSHM_OPT
    if (!iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(SUBTYPE_REPR, "values")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
    else if (!value)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(SUBTYPE_REPR, "values", "2nd", value)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
#endif
    /* Prepare exception message to be used on internal allocation failure */
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(SUBTYPE_REPR, "values")

    SHMItem *item;
    if (__cshm_next(iterator, &item, EXCEPTION_MSG, sizeof EXCEPTION_MSG))
    {
        *(void **)value = item->key + item->offset;
        return true;
    }
    free(iterator);
    return false;
}



/*----------------------------------------------------------------------------*/
bool
SUPPORT_METHOD(iterator, items)(SUPPORT(iterator) *iterator,
                                void *key,
                                void *value)
{
#ifndef CSHM_OPT
    if (!iterator)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(SUBTYPE_REPR, "items")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
    else if (!key)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(SUBTYPE_REPR, "items", "2nd", key)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
    else if (!value)
    {
        #undef  EXCEPTION_MSG
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(SUBTYPE_REPR, "items", "3rd", value)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        return false; /* Cannot operate on NULL */
    }
#endif
    /* Prepare exception message to be used on internal allocation failure */
    #undef  EXCEPTION_MSG
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(SUBTYPE_REPR, "items")

    SHMItem *item;
    if (__cshm_next(iterator, &item, EXCEPTION_MSG, sizeof EXCEPTION_MSG))
    {
        *(void **)key   = item->key;
        *(void **)value = item->key + item->offset;
        return true;
    }
    free(iterator);
    return false;
}
