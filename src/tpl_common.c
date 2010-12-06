/*
 * tpl_common.c
 *
 *  Created on: Dec 6, 2010
 *      Author: price
 */

#include "tpl_priv_libtemplate.h"
#include "apr-1.0/apr.h"

tpl_ptr_t* tpl_initialize() {
	apr_initialize();
}
