/*
 * tpl_objects.c
 *
 *  Created on: Dec 5, 2010
 *      Author: price
 */

#include "priv_libtemplate.h"

tpl_object_t* tpl_create_string(tpl_object_t* parent, tpl_char_t* str) {
	apr_pool_t *mp = 0;
	if (likely(parent!=0)) {
		mp = ((tpl_object_generic*) parent->content)->pool;
	} else {
		apr_pool_create(&mp,0);
	}

	tpl_object_t* ret = apr_palloc(mp, sizeof(tpl_object_t));
	tpl_object_string* l_str = ret->content = apr_palloc(mp,
			sizeof(tpl_object_string));

}
