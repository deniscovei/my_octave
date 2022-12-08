// Covei Denis - 312CA
#include "types_and_defs.h"
#include <stdio.h>
#include <stdbool.h>

enum error {no_err, id_err, exp_err, mult_err, cmd_err};

int valid_id(int id, int cnt_mat)
{
	/* returneaza 0 pentru id valid (no_err)
	   returneaza indexul erorii specifice pentru id invalid */
	return (0 <= id && id < cnt_mat) ? no_err : id_err;
}

int valid_exponent(int exp)
{
	/* returneaza 0 pentru id valid (no_err)
	   returneaza indexul erorii specifice pentru exponent invalid */
	return (exp >= 0) ? no_err : exp_err;
}

int is_quadratic(int id, int cnt_mat, magnitude dimension)
{
	/* returneaza 0 pentru id valid (no_err)
	   returneaza indexul erorii specifice pentru id invalid sau
	   in cazul in care matricea nu este patratica */
	if (valid_id(id, cnt_mat) == 0)
		return (dimension.rows == dimension.collumns) ? no_err : mult_err;
	return mult_err;
}

int valid_command(char cmd_id)
{
	/* returneaza 0 pentru comanda valida (no_err)
	   returneaza indexul erorii specifice pentru comanda invalida */
	if ('A' <= cmd_id && cmd_id <= 'Z' && cmd_id != '\n')
		return cmd_err;
	else
		return no_err;
}

int valid_multiplication(magnitude dimension)
{
	return (dimension.rows == dimension.collumns) ? no_err : mult_err;
}

bool check_error(int error_id)
{
	/* returneaza 1 daca s-au descoperit erori
	   returneaza 0 daca nu s-au descoperit erori */
	switch (error_id) {
	case id_err:
		printf("No matrix with the given index\n");
		break;
	case exp_err:
		printf("Power should be positive\n");
		break;
	case mult_err:
		printf("Cannot perform matrix multiplication\n");
		break;
	case cmd_err:
		printf("Unrecognized command\n");
		break;
	default:
		return 0;
	}
	return 1;
}
