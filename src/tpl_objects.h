/*
 * tpl_objects.h
 *
 *  Created on: Dec 6, 2010
 *      Author: price
 */

#include "tpl_priv_libtemplate.h"

#ifndef TPL_OBJECTS_H_
#define TPL_OBJECTS_H_

typedef struct tpl_object_generic {
	apr_pool_t* pool;
	tpl_bool_t has_parent;
} tpl_object_generic;

typedef struct tpl_object_string {
	tpl_object_generic base_object;
	tpl_char_t* str;
} tpl_object_string;

#endif /* TPL_OBJECTS_H_ */
