# cargs
very simple lib written in C for get arguments from console after bin file name


### Mini documentation

```c
// function description

// initialize function, use how it`s in example 
void cargs_init(int argc, char const *argv[]);

// set and get param with setable rules
struct return_data set_get_arg(
	char const * const c_full_name, // full name argument [--help]
	char const * const c_cut_name, // cut name argument [-h]
	char const * const c_description, // description of argument
	_Bool is_extremely, // set 1 if this arg necessarily needed and 0 if not needed
	_Bool param, // set 1 if this arg need parameter and 0 if not need
	_Bool priority, // set 1 if after this arg need to write description and exit with 0 code when it found in command line and 0 if not need
	int errcode // set code number for extreme close app - exit(errcode)
);

// return 1 if flag(arg) found in command line and 0 if not found close app with erorr code if param of function is NULL
_Bool check_flag(struct return_data const * const ret_data);

// return pointer on parameter and if param of function or pointer on param string is NULL app is closing with error code
const char *get_param(struct return_data const * const ret_data);
```


### how to use library in example
```c
#include <stdio.h>

// include lib header file
#include "cargs_all.h"

int main(int argc, char const *argv[])
{
  // init two double variables for example
	double first_num, last_num;

  // call init function
	cargs_init(argc, argv);
  
  // call set argument function
  set_get_arg("--help", "-h", "arguments description\n\t"
		"[--func | -f] fymbol of math function\n\t"
		"[--num1 | -n1] first number for calculate\n\t"
		"[--num2 | -n2] last number for calculate", 0, 0, 1, 6);
  
  // and call other [set & get] argument functions for write return data to structs
  struct return_data func_res = set_get_arg("--func", "-f", "fymbol of math function", 1, 1, 0, 3);
  struct return_data first_num_res = set_get_arg("--num1", "-n1", "first number for calculate", 1, 1, 0, 4);
  struct return_data last_num_res = set_get_arg("--num2", "-n2", "last number for calculate", 1, 1, 0, 5);
  
  // check flags of return data
  if (check_flag(&func_res) && 
		check_flag(&first_num_res) && 
		check_flag(&last_num_res)) {
  // if all flags is valid go to next instructions
  
    // set variables returned data from get_param functions
		first_num = atof(get_param(&first_num_res));
		last_num = atof(get_param(&last_num_res));

    // sometimes use for debug
		// printf("[0] is [%c]\n", get_param(&func_res)[0]);
    
    // use get_param for check first symbol of param
		switch (get_param(&func_res)[0]) {
			case '+':
				printf("%lf + %lf = %lf\n", first_num, last_num, first_num + last_num);
				break;
			case '-':
				printf("%lf - %lf = %lf\n", first_num, last_num, first_num - last_num);
				break;
			case '*':
				printf("%lf * %lf = %lf\n", first_num, last_num, first_num * last_num);
				break;
			case '/':
				printf("%lf / %lf = %lf\n", first_num, last_num, first_num / last_num);
				break;
			default:
				printf("[ERROR] - uknown math operation\n");
				exit(7);
		}

	}

	return 0;
}
```
