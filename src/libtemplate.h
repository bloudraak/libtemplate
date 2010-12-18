/*
 * libtemplate.h
 *
 *  Created on: Dec 5, 2010
 *      Author: price
 */

#ifndef LIBTEMPLATE_H_
#define LIBTEMPLATE_H_

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

tpl_int_t tpl_get_last_error_code(tpl_ptr_t* lib_handle);
tpl_char_t* tpl_get_last_error_msg(tpl_ptr_t* lib_handle);

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
tpl_object_t* tpl_create_string_with_len(tpl_object_t* parent, tpl_char_t* str,
		tpl_uint_t length);
tpl_int_t tpl_string_length(tpl_object_t* str);

tpl_object_t* tpl_create_array(tpl_object_t* parent, tpl_int_t i_len);
tpl_object_t* tpl_array_get(tpl_object_t* array, tpl_uint_t index);
tpl_bool_t tpl_array_pop(tpl_object_t* array);
tpl_object_t* tpl_array_push(tpl_object_t* array, tpl_object_t* obj);
tpl_int_t tpl_array_length(tpl_object_t* array);
tpl_bool_t tpl_array_clear(tpl_object_t* array);

tpl_object_t* tpl_create_map(tpl_object_t* parent);
tpl_object_t* tpl_map_get(tpl_object_t* map, tpl_char_t* key);
tpl_int_t tpl_map_set(tpl_object_t* map, tpl_char_t* key, tpl_object_t* obj);
tpl_bool_t tpl_map_clear(tpl_object_t* map);

tpl_object_t* tpl_create_boolean(tpl_object_t* parent, tpl_bool_t bool_val);
tpl_object_t* tpl_create_float(tpl_object_t* parent, tpl_float_t f);
tpl_object_t* tpl_create_double(tpl_object_t* parent, tpl_double_t df);
tpl_object_t* tpl_create_int(tpl_object_t* parent, tpl_int_t i);
tpl_object_t* tpl_create_uint(tpl_object_t* parent, tpl_uint_t ui);

tpl_bool_t tpl_destroy_object(tpl_object_t** obj);
tpl_bool_t tpl_empty_object(tpl_object_t** obj);

tpl_bool_t tpl_object_equal(tpl_object_t* obj1, tpl_object_t* obj2);
tpl_ptr_t tpl_get_raw_ptr(tpl_object_t* obj);

//Here it must never be null.
tpl_char_t* tpl_object_to_cstring(tpl_object_t* parent, tpl_object_t* obj);

typedef struct tpl_template_t tpl_template_t;
typedef struct tpl_template_elem_t tpl_template_elem_t;
typedef struct tpl_template_context_t tpl_template_context_t;
typedef struct tpl_elem_array_t tpl_elem_array_t;

typedef tpl_int_t (*tpl_execute_t)(tpl_template_elem_t* tpl_e,
		tpl_output_stream_t* out);
typedef tpl_int_t (*tpl_validate_t)(tpl_template_elem_t* tpl_e);
typedef tpl_int_t (*tpl_destructor_t)(tpl_template_elem_t* tpl_e);

struct tpl_template_elem_t {
	tpl_ptr_t data;
	tpl_template_context_t* template_context;
	tpl_template_context_t* provided_context;
	tpl_template_context_t* params;
	tpl_elem_array_t* children;
	tpl_execute_t execute;
	tpl_validate_t validate;
	tpl_destructor_t destructor;
};

tpl_object_t* tpl_get_object_map(tpl_template_context_t* context);
tpl_ptr_t* tpl_alloc(tpl_object_t* parent, tpl_uint_t size);
tpl_ptr_t* tpl_alloc_on_ctx(tpl_template_context_t* parent, tpl_uint_t size);

//Element array

tpl_bool_t tpl_register_element(tpl_char_t* name, tpl_execute_t execute,
		tpl_validate_t validate, tpl_destructor_t destructor);
tpl_template_elem_t* tpl_array_get(tpl_elem_array_t* array, tpl_uint_t index);
tpl_int_t tpl_array_length(tpl_elem_array_t* array);

#endif /* LIBTEMPLATE_H_ */
