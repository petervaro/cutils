/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.110 (20140906)                       **
**                                                                            **
**                       File: internal/dynamic_array.h                       **
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

/* !!! DON NOT ADD GUARD TO THIS FILE !!! */

#define FILE_STARTS_HERE
#include <stdlib.h>   /* size_t */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
/* Shorthands for this source */
#undef _concat_underscore
#undef concat_underscore
#undef DYNAMIC_ARRAY
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD
#define _concat_underscore(token1, token2) token1##_##token2
#define concat_underscore(token1, token2) _concat_underscore(token1, token2)
#define DYNAMIC_ARRAY cutils_cdar_DynamicArray_void_ptr
#define METHOD(func)  concat_underscore(DYNAMIC_ARRAY, func)
#define SUPPORT(type) concat_underscore(DYNAMIC_ARRAY, type)
#define SUPPORT_METHOD(type, func) concat_underscore(DYNAMIC_ARRAY, type##_##func)

/*----------------------------------------------------------------------------*/
typedef struct {} DYNAMIC_ARRAY;
/*----------------------------------------------------------------------------*/
extern bool
METHOD(new)(DYNAMIC_ARRAY **dynarr,
            size_t item_size,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(new_default3)(DYNAMIC_ARRAY **dynarr,
                     size_t item_size,
                     size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(new_default2)(DYNAMIC_ARRAY **dynarr,
                     size_t item_size);
/*----------------------------------------------------------------------------*/
extern void
METHOD(del)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(data)(DYNAMIC_ARRAY *dynarr,
             size_t *size,
             size_t *count);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(raw)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(len)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(size)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern void
METHOD(clear)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(resize)(DYNAMIC_ARRAY *dynarr,
               size_t count);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(swap)(DYNAMIC_ARRAY *dynarr,
             size_t index1,
             size_t index2,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(swap_default3)(DYNAMIC_ARRAY *dynarr,
                      size_t index1,
                      size_t index2);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(reverse)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(append)(DYNAMIC_ARRAY *dynarr,
               size_t count,
               void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(append_default2)(DYNAMIC_ARRAY *dynarr,
                        void *source);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(push)(DYNAMIC_ARRAY *dynarr,
             size_t index,
             size_t count,
             void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(push_default3)(DYNAMIC_ARRAY *dynarr,
                      size_t index,
                      void *source);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pull)(DYNAMIC_ARRAY *dynarr,
             size_t index,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pull_default2)(DYNAMIC_ARRAY *dynarr,
                      size_t index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pop)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pop_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t index,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(sub)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(sub_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t index,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern void
METHOD(truncate)(DYNAMIC_ARRAY *dynarr,
                 size_t index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(truncate_default1)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(set)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(set_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t index,
                     void *source);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(get)(DYNAMIC_ARRAY *dynarr,
            size_t index);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(find)(DYNAMIC_ARRAY *dynarr,
             bool (*compare)(const void*, const void*, size_t),
             const void *item,
             size_t *index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(find_default3)(DYNAMIC_ARRAY *dynarr,
                      const void *item,
                      size_t *index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(findall)(DYNAMIC_ARRAY *dynarr,
                bool (*compare)(const void*, const void*, size_t),
                const void *item,
                size_t *indices);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(findall_default3)(DYNAMIC_ARRAY *dynarr,
                         const void *item,
                         size_t *index);
/*----------------------------------------------------------------------------*/
extern void
METHOD(sort)(DYNAMIC_ARRAY *dynarr,
             int (*compare)(const void*, const void*));
/*----------------------------------------------------------------------------*/
extern void
METHOD(sortsub)(DYNAMIC_ARRAY *dynarr,
                size_t index,
                size_t count,
                int (*compare)(const void*, const void*));
/*----------------------------------------------------------------------------*/
extern void
METHOD(map)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void (*function)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(map_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t count,
                     void (*function)());
/*----------------------------------------------------------------------------*/
extern void
METHOD(print)(DYNAMIC_ARRAY *dynarr,
              FILE *stream,
              const char *sub_type,
              bool(*format)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(print_default1)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(format)(const void *item,
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
#undef DYNAMIC_ARRAY
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD
