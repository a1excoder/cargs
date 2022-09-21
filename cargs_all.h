#ifndef CARGS_H
#define CARGS_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// #define NDEBUG

struct cargs
{
	char const **argv;
	int argc;
} static cargs_init_struct;

struct return_data {
	char const * const param;
	_Bool flag_status;
};

void cargs_init(int argc, char const *argv[]) {
	assert(argv != NULL); // argc > 1 && 

	cargs_init_struct.argc = argc;
	cargs_init_struct.argv = argv;
}

struct return_data set_get_arg(
	char const * const c_full_name, 
	char const * const c_cut_name, 
	char const * const c_description,
	_Bool is_extremely,
	_Bool param,
	int errcode
)
{
	assert(c_full_name != NULL && c_cut_name != NULL && c_description);

	for (int i = 0; i < cargs_init_struct.argc; ++i) {
		if (!strcmp(c_full_name, cargs_init_struct.argv[i]) || 
			!strcmp(c_cut_name, cargs_init_struct.argv[i])) {

			if (!param) return (struct return_data){.param = NULL, .flag_status = 1};
			if (i + 1 < cargs_init_struct.argc) {

				if (cargs_init_struct.argv[i + 1][0] != '-') return (struct return_data){
					.param = cargs_init_struct.argv[i + 1], .flag_status = 1
				};

				goto error_exit;
			}

			goto error_exit;
		}
	}

	if (is_extremely) goto error_exit;
	return (struct return_data){.param = NULL, .flag_status = 0};

error_exit:
	fprintf(stderr, "[ERROR] - [%s | %s] %s\n", c_full_name, c_cut_name, c_description);
	exit(errcode);
}

#endif // CARGS_H