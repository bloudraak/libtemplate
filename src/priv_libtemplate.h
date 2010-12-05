/*
 * priv_libtemplate.h
 *
 *  Created on: Dec 5, 2010
 *      Author: price
 */

#include "libtemplate.h"
#include "apr-1.0/apr_pools.h"
#ifndef PRIV_LIBTEMPLATE_H_
#define PRIV_LIBTEMPLATE_H_

#ifdef __GNUC__
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#else
#define likely
#define unlikely
#endif

typedef struct tpl_object_generic {
	apr_pool_t* pool;
	tpl_bool_t has_parent;
} tpl_object_generic;

typedef struct tpl_object_string {
	tpl_object_generic base_object;
	tpl_char_t* str;
} tpl_object_string;

#endif /* PRIV_LIBTEMPLATE_H_ */
