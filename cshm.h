/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.222 (20140908)                       **
**                                                                            **
**                                File: cshm.h                                **
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

#ifndef _C_STATIC_HASH_MAP_H_18841687438603127_
#define _C_STATIC_HASH_MAP_H_18841687438603127_

#define FILE_STARTS_HERE
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool */

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
typedef struct {} HASH_MAP;
typedef struct {} SUPPORT(iterator);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(new)(HASH_MAP **hashmap,
            size_t count);
/*----------------------------------------------------------------------------*/
extern void
METHOD(del)(HASH_MAP *hashmap);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(add)(HASH_MAP *hashmap,
            bool (*compare)(const void*, const void*, size_t),
            int key_size,
            size_t value_size,
            const void *key,
            const void *value);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(add_default5)(HASH_MAP *hashmap,
                     int key_size,
                     size_t value_size,
                     const void *key,
                     const void *value);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(get)(HASH_MAP *hashmap,
            bool (*compare)(const void*, const void*, size_t),
            size_t key_size,
            const void *key);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void *
METHOD(get_default3)(HASH_MAP *hashmap,
                     size_t key_size,
                     const void *key);
/*----------------------------------------------------------------------------*/
extern SUPPORT(iterator) *
METHOD(iter)(HASH_MAP *hashmap);
/*----------------------------------------------------------------------------*/
extern void
SUPPORT_METHOD(iterator, del)(SUPPORT(iterator) *iterator);
/*----------------------------------------------------------------------------*/
extern bool
SUPPORT_METHOD(iterator, next)(SUPPORT(iterator) *iterator,
                               void *key);
/*----------------------------------------------------------------------------*/
extern bool
SUPPORT_METHOD(iterator, values)(SUPPORT(iterator) *iterator,
                                 void *value);
/*----------------------------------------------------------------------------*/
extern bool
SUPPORT_METHOD(iterator, items)(SUPPORT(iterator) *iterator,
                                void *key,
                                void *value);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(compare)(const void *item1,
                const void *item2,
                size_t item_size);

/*----------------------------------------------------------------------------*/
/* Undefine helper macros */
#undef _concat_underscore
#undef concat_underscore
#undef HASH_MAP
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD

#endif /* _C_STATIC_HASH_MAP_H_18841687438603127_ */
