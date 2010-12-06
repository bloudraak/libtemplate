/*
 * tpl_objects.h
 *
 *  Created on: Dec 6, 2010
 *      Author: price
 */

#include "tpl_priv_libtemplate.h"
#include "apr-1.0/apr_general.h"
#include "apr-1.0/apr_tables.h"
#include "apr-1.0/apr_hash.h"

#ifndef TPL_OBJECTS_H_
#define TPL_OBJECTS_H_

typedef struct tpl_object_generic {
	apr_pool_t* pool;
	tpl_bool_t has_parent;
	union {
		tpl_char_t* str;
		tpl_int_t i;
		tpl_uint_t ui;
		apr_array_header_t *array;
		apr_hash_t *hash_table;
		tpl_bool_t bool_val;
		tpl_float_t f;
		tpl_double_t df;
	} tpl_variant;

} tpl_object_generic;

#endif /* TPL_OBJECTS_H_ */
