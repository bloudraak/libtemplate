/*
 * tpl_template_elems.h
 *
 *  Created on: Dec 7, 2010
 *      Author: price
 */

#include "tpl_objects.h"
#ifndef TPL_TEMPLATE_ELEMS_H_
#define TPL_TEMPLATE_ELEMS_H_

struct tpl_template_context_t {
	tpl_object_t* map;
};

struct tpl_template_t {
	tpl_template_context_t* context;
};

#endif /* TPL_TEMPLATE_ELEMS_H_ */
