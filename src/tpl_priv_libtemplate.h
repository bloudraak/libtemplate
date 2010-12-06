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

#endif /* PRIV_LIBTEMPLATE_H_ */
