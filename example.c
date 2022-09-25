#include <stdio.h>
#include "cargs_all.h"

int main(int argc, char const *argv[])
{
	double first_num, last_num;

	cargs_init(argc, argv);

	set_get_arg("--help", "-h", "arguments description\n\t"
		"[--func | -f] fymbol of math function\n\t"
		"[--num1 | -n1] first number for calculate\n\t"
		"[--num2 | -n2] last number for calculate", 0, 0, 1, 6);

	struct return_data func_res = set_get_arg("--func", "-f", "fymbol of math function", 1, 1, 0, 3);
	struct return_data first_num_res = set_get_arg("--num1", "-n1", "first number for calculate", 1, 1, 0, 4);
	struct return_data last_num_res = set_get_arg("--num2", "-n2", "last number for calculate", 1, 1, 0, 5);

	if (check_flag(&func_res) && 
		check_flag(&first_num_res) && 
		check_flag(&last_num_res)) {

		first_num = atof(get_param(&first_num_res));
		last_num = atof(get_param(&last_num_res));

		printf("[0] is [%c]\n", get_param(&func_res)[0]);
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
