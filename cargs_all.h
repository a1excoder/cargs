#ifndef CARGS_H
#define CARGS_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NDEBUG

enum EXIT_CODES
{
	RETURN_DATA_IS_NULL = 1,
	RETURN_PARAM_IS_NULL
};

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
	assert(argv != NULL);

	cargs_init_struct.argc = argc;
	cargs_init_struct.argv = argv;
}

struct return_data set_get_arg(
	char const * const c_full_name, 
	char const * const c_cut_name, 
	char const * const c_description,
	_Bool is_extremely,
	_Bool param,
	_Bool priority,
	int errcode
)
{
	assert(c_full_name != NULL && c_cut_name != NULL && c_description);

	for (int i = 0; i < cargs_init_struct.argc; ++i) {
		if (!strcmp(c_full_name, cargs_init_struct.argv[i]) || 
			!strcmp(c_cut_name, cargs_init_struct.argv[i])) {

			if (!param) {
				if (priority == 1) {
					puts(c_description);
					exit(0);
				}

				return (struct return_data){.param = NULL, .flag_status = 1};
			}
			if (i + 1 < cargs_init_struct.argc) {

				/*
					if (cargs_init_struct.argv[i + 1][0] != '-') return (struct return_data){
						.param = cargs_init_struct.argv[i + 1], .flag_status = 1
					};
				*/
				return (struct return_data){
					.param = cargs_init_struct.argv[i + 1], 
					.flag_status = 1};

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


_Bool check_flag(struct return_data const * const ret_data) {
	if (ret_data == NULL) exit(RETURN_DATA_IS_NULL);
	return ret_data->flag_status;
}

const char *get_param(struct return_data const * const ret_data) {
	if (ret_data == NULL) exit(RETURN_DATA_IS_NULL);
	if (ret_data->param == NULL) exit(RETURN_PARAM_IS_NULL);
	return ret_data->param;
}

#endif // CARGS_H
