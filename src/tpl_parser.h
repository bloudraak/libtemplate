/*
 * tpl_parser.h
 *
 *  Created on: Dec 11, 2010
 *      Author: price
 */

#include "tpl_objects.h"

#ifndef TPL_PARSER_H_
#define TPL_PARSER_H_

typedef struct tpl_parser tpl_parser;

tpl_parser* tpl_create_parser(tpl_input_stream_t* is);

#endif /* TPL_PARSER_H_ */
