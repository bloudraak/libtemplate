/*
 * tpl_objects.c
 *
 *  Created on: Dec 5, 2010
 *      Author: price
 */

#include "tpl_objects.h"
#include "apr-1.0/apr_strings.h"
#include "apr-1.0/apr_hash.h"
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

tpl_bool_t tpl_empty_object(tpl_object_t* obj) {
	tpl_object_generic* base_obj = (tpl_object_generic*) obj->content;
	if (unlikely(base_obj->has_parent == tpl_false)) {
		return tpl_false;
	}

	apr_pool_clear(base_obj->pool);
	return tpl_true;
}

//COMMON TO ALL OBJECT CREATION
#define TPL_INIT_OBJECT 														\
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
	tpl_object_t* ret = apr_palloc(mp, sizeof(tpl_object_t));					\
	tpl_object_generic* l_obj = ret->content = apr_palloc(mp,					\
					sizeof(tpl_object_generic));								\
																				\
	l_obj->pool = mp;															\
	l_obj->has_parent = has_parent;												\
	ret->content = (tpl_ptr_t*) l_obj;

//END COMMON PART

tpl_object_t* tpl_create_string(tpl_object_t* parent, tpl_char_t* str) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.str = apr_pstrdup(mp, str);
	ret->type = tpl_type_string_t;

	return ret;
}

tpl_object_t* tpl_create_array(tpl_object_t* parent, tpl_int_t i_len) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.array = apr_array_make(mp, i_len,
			sizeof(const tpl_object_t*));
	ret->type = tpl_type_array_t;

	return ret;
}

tpl_object_t* tpl_array_get(tpl_object_t* array, tpl_uint_t index) {
	if (unlikely(array->type != tpl_type_array_t)) {
		return 0;
	}

	tpl_object_generic* base_obj = (tpl_object_generic*) array->content;
	return ((tpl_object_t**) base_obj->tpl_variant.array->elts)[index];
}

tpl_bool_t tpl_array_pop(tpl_object_t* array) {
	if (unlikely(array->type != tpl_type_array_t)) {
		return tpl_false;
	}

	tpl_object_generic* base_obj = (tpl_object_generic*) array->content;
	apr_array_pop(base_obj->tpl_variant.array);
	return tpl_true;
}

tpl_int_t tpl_array_length(tpl_object_t* array) {
	if (unlikely(array->type != tpl_type_array_t)) {
		return -1;
	}

	return ((tpl_object_generic*) array->content)->tpl_variant.array->nelts;
}

tpl_bool_t tpl_array_clear(tpl_object_t* array) {
	if (unlikely(array->type != tpl_type_array_t)) {
		return tpl_false;
	}

	tpl_object_generic* base_obj = (tpl_object_generic*) array->content;
	apr_array_clear(base_obj->tpl_variant.array);
	return tpl_true;
}

tpl_object_t* tpl_create_map(tpl_object_t* parent) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.hash_table = apr_hash_make(mp);
	ret->type = tpl_type_map_t;

	return ret;
}

tpl_object_t* tpl_map_get(tpl_object_t* map, tpl_char_t* key) {
	if (unlikely(map->type != tpl_type_map_t)) {
		return 0;
	}

	tpl_object_generic* base_obj = (tpl_object_generic*) map->content;
	return apr_hash_get(base_obj->tpl_variant.hash_table, key,
			APR_HASH_KEY_STRING);
}

tpl_int_t tpl_map_set(tpl_object_t* map, tpl_char_t* key, tpl_object_t* obj) {
	if (unlikely(map->type != tpl_type_map_t)) {
		return -1;
	}

	tpl_object_generic* base_obj = (tpl_object_generic*) map->content;
	apr_hash_set(base_obj->tpl_variant.hash_table, key, APR_HASH_KEY_STRING,
			obj);

	return 0;
}

tpl_bool_t tpl_map_clear(tpl_object_t* map) {
	if (unlikely(map->type != tpl_type_map_t)) {
		return tpl_false;
	}

	tpl_object_generic* base_obj = (tpl_object_generic*) map->content;
	apr_hash_clear(base_obj->tpl_variant.hash_table);

	return tpl_true;
}

tpl_object_t* tpl_create_boolean(tpl_object_t* parent, tpl_bool_t bool_val) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.bool_val = bool_val;
	ret->type = tpl_type_boolean_t;

	return ret;
}

tpl_object_t* tpl_create_float(tpl_object_t* parent, tpl_float_t f) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.f = f;
	ret->type = tpl_type_float_t;

	return ret;
}

tpl_object_t* tpl_create_double(tpl_object_t* parent, tpl_double_t df) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.df = df;
	ret->type = tpl_type_double_t;

	return ret;
}

tpl_object_t* tpl_create_int(tpl_object_t* parent, tpl_int_t i) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.i = i;
	ret->type = tpl_type_int_t;

	return ret;
}

tpl_object_t* tpl_create_uint(tpl_object_t* parent, tpl_uint_t ui) {
	TPL_INIT_OBJECT

	l_obj->tpl_variant.ui = ui;
	ret->type = tpl_type_uint_t;

	return ret;
}

