/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.119 (20140906)                       **
**                                                                            **
**                    File: internal/singly_linked_list.h                     **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

/* !!! DON NOT ADD GUARD TO THIS FILE !!! */

#define FILE_STARTS_HERE
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool */

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
typedef struct {} LINKED_LIST;
typedef struct {} SUPPORT(iterator);

/*----------------------------------------------------------------------------*/
extern bool
METHOD(new)(LINKED_LIST **linlist,
            size_t item_size,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(new_default1)(LINKED_LIST **linlist);
/*----------------------------------------------------------------------------*/
extern void
METHOD(del)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern void
METHOD(clear)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(len)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(swap)(LINKED_LIST *linlist,
             size_t index1,
             size_t index2,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(swap_default3)(LINKED_LIST *linlist,
                      size_t index1,
                      size_t index2);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(reverse)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(append)(LINKED_LIST *linlist,
               size_t item_size,
               size_t count,
               void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(append_default3)(LINKED_LIST *linlist,
                        size_t item_size,
                        void *source);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(push)(LINKED_LIST *linlist,
             size_t index,
             size_t item_size,
             size_t count,
             void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(push_default4)(LINKED_LIST *linlist,
                      size_t index,
                      size_t item_size,
                      void *source);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pull)(LINKED_LIST *linlist,
             size_t index,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pull_default2)(LINKED_LIST *linlist,
                      size_t index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pop)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pop_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(sub)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(sub_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern void
METHOD(truncate)(LINKED_LIST *linlist,
                 size_t index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(truncate_default1)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(set)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(set_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *source);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(get)(LINKED_LIST *linlist,
            size_t index);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(find)(LINKED_LIST *linlist,
             bool (*compare)(const void*, const void*, size_t),
             size_t item_size,
             const void *item,
             size_t *index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(find_default4)(LINKED_LIST *linlist,
                      size_t item_size,
                      const void *item,
                      size_t *index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(findall)(LINKED_LIST *linlist,
                bool (*compare)(const void*, const void*, size_t),
                size_t item_size,
                const void *item,
                size_t *indices);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(findall_default4)(LINKED_LIST *linlist,
                         size_t item_size,
                         const void *item,
                         size_t *index);
/*----------------------------------------------------------------------------*/
extern SUPPORT(iterator) *
METHOD(iter)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern void
SUPPORT_METHOD(iterator, del)(SUPPORT(iterator) *node);
/*----------------------------------------------------------------------------*/
extern bool
SUPPORT_METHOD(iterator, next)(SUPPORT(iterator) *node,
                               void *data);
/*----------------------------------------------------------------------------*/
extern void
SUPPORT_METHOD(iterator, pull)(SUPPORT(iterator) *iterator);
/*----------------------------------------------------------------------------*/
extern void
METHOD(map)(LINKED_LIST *linlist,
            size_t index,
            size_t count,
            void (*function)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(map_default3)(LINKED_LIST *linlist,
                     size_t count,
                     void (*function)());
/*----------------------------------------------------------------------------*/
extern void
METHOD(print)(LINKED_LIST *linlist,
              FILE *stream,
              const char *sub_type,
              bool(*format)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(print_default1)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(format)(const void *data,
               char **buffer,
               size_t *buffer_size);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(compare)(const void *item1,
                const void *item2,
                size_t item_size);

/*----------------------------------------------------------------------------*/
/* Undefine helper macros */
#undef _concat_underscore
#undef concat_underscore
#undef LINKED_LIST
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD
