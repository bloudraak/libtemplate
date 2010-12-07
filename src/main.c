/*
 ============================================================================
 Name        : libtemplate.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "libtemplate.h"

int main(void) {
	tpl_initialize();
	tpl_object_t* str = tpl_create_string(0, "Test small string.");
	tpl_object_t* child_str = tpl_create_string(str, "Test small string.");

	tpl_object_t* map = tpl_create_map(str);
	tpl_map_set(map, "test", child_str);
	child_str = tpl_map_get(map, "test");

	printf("Strings are equal %i\n", tpl_object_equal(str, child_str));

	tpl_destroy_object(str);
	return EXIT_SUCCESS;
}
