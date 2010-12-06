/*
 * tpl_objects.c
 *
 *  Created on: Dec 5, 2010
 *      Author: price
 */

#include "tpl_objects.h"
#include "apr-1.0/apr_strings.h"
#include "stdio.h"
#include "stdlib.h"

tpl_bool_t tpl_destroy_object(tpl_object_t* obj) {
	tpl_object_generic* base_obj = (tpl_object_generic*) obj->content;
	if (unlikely(base_obj->has_parent == tpl_false)) {
		return tpl_false;
	}

	apr_pool_destroy(base_obj->pool);
	return tpl_true;
}

//COMMON TO ALL OBJECT CREATION
#define TPL_INIT_OBJECT 															\
	apr_pool_t *mp = 0; 														\
	tpl_bool_t has_parent; 														\
	if (likely(parent!=0)) { 													\
		mp = ((tpl_object_generic*) parent->content)->pool; 					\
		has_parent = tpl_true; 													\
	} else { 																	\
		apr_pool_create(&mp,0); 												\
		has_parent = tpl_false; 												\
	} 																			\
																				\
	tpl_object_t* ret = apr_palloc(mp, sizeof(tpl_object_t));

//END COMMON PART

tpl_object_t* tpl_create_string(tpl_object_t* parent, tpl_char_t* str) {
	TPL_INIT_OBJECT
	tpl_object_string* l_str = ret->content = apr_palloc(mp,
			sizeof(tpl_object_string));

	l_str->base_object.pool = mp;
	l_str->base_object.has_parent = has_parent;
	l_str->str = apr_pstrdup(mp, str);

	ret->content = (tpl_ptr_t*) l_str;
	ret->type = tpl_type_string_t;

	return ret;
}
