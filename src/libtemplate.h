/*
 * libtemplate.h
 *
 *  Created on: Dec 5, 2010
 *      Author: price
 */

#ifndef LIBTEMPLATE_H_
#define LIBTEMPLATE_H_

#define TPL_VERBOSE 1

typedef double tpl_double_t;
typedef float tpl_float_t;
typedef int tpl_int_t;
typedef unsigned int tpl_uint_t;
typedef tpl_uint_t tpl_bool_t;
typedef void* tpl_ptr_t;
typedef char tpl_char_t;
typedef unsigned char tpl_byte_t;

#define tpl_true 1
#define tpl_false 0

tpl_ptr_t* tpl_initialize();
tpl_int_t tpl_uninitialize();

tpl_int_t tpl_get_last_error_code();
tpl_char_t* tpl_get_last_error_msg();

typedef struct tpl_input_stream_t tpl_input_stream_t;
typedef tpl_char_t (*tpl_read_t)(tpl_input_stream_t* is);
typedef tpl_bool_t (*tpl_has_more_t)(tpl_input_stream_t* is);
typedef tpl_int_t (*tpl_rclose_t)(tpl_input_stream_t* is);

typedef struct tpl_output_stream_t tpl_output_stream_t;
typedef tpl_int_t (*tpl_write_t)(tpl_char_t* buffer, tpl_int_t len,
		tpl_output_stream_t* os);
typedef tpl_bool_t (*tpl_flush_t)(tpl_output_stream_t* os);
typedef tpl_int_t (*tpl_wclose_t)(tpl_output_stream_t* os);

struct tpl_input_stream_t {
	tpl_ptr_t stream;
	tpl_read_t read;
	tpl_has_more_t has_more;
	tpl_rclose_t close;
};

struct tpl_output_stream_t {
	tpl_ptr_t stream;
	tpl_write_t write;
	tpl_flush_t flush;
	tpl_wclose_t close;
};

typedef tpl_ptr_t tpl_template_t;

typedef enum tpl_type_obj_t {
	tpl_type_int_t,
	tpl_type_uint_t,
	tpl_type_float_t,
	tpl_type_double_t,
	tpl_type_boolean_t,
	tpl_type_string_t,
	tpl_type_array_t,
	tpl_type_map_t
} tpl_type_obj_t;

typedef struct tpl_object_t {
	tpl_type_obj_t type;
	tpl_ptr_t content;
} tpl_object_t;

tpl_object_t* tpl_create_string(tpl_object_t* parent, tpl_char_t* str);

tpl_object_t* tpl_create_array(tpl_object_t* parent, tpl_int_t i_len);
tpl_object_t* tpl_array_get(tpl_object_t* array, tpl_uint_t index);
tpl_object_t* tpl_array_push(tpl_object_t* array, tpl_object_t* obj);
tpl_int_t tpl_array_length(tpl_object_t* array);

tpl_object_t* tpl_create_map(tpl_object_t* parent);
tpl_object_t* tpl_create_boolean(tpl_object_t* parent, tpl_bool_t bool_val);
tpl_object_t* tpl_create_float(tpl_object_t* parent, tpl_float_t f);
tpl_object_t* tpl_create_double(tpl_object_t* parent, tpl_double_t df);
tpl_object_t* tpl_create_int(tpl_object_t* parent, tpl_int_t i);
tpl_object_t* tpl_create_uint(tpl_object_t* parent, tpl_uint_t ui);

tpl_bool_t tpl_destroy_object(tpl_object_t* obj);
tpl_bool_t tpl_empty_object(tpl_object_t* obj);

//Here it must never be null.
tpl_char_t* tpl_object_to_cstring(tpl_object_t* parent, tpl_object_t* obj);

#endif /* LIBTEMPLATE_H_ */
