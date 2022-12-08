// Covei Denis - 312CA
#include <stdio.h>
#include <stdlib.h>
#include "types_and_defs.h"
#include "mem_alloc.h"
#include "errors.h"
#include "operations.h"

int main(void)
{
	int ***v_mat = (int ***)malloc(0);
	check_memory_allocation((void *)v_mat);
	magnitude *size = (magnitude *)malloc(0);
	check_memory_allocation((void *)size);
	int cnt_mat = 0;

	while (1) {
		char command_id;

		scanf("%c", &command_id);

		switch (command_id) {
		case 'L':
			new_matrix(&v_mat, &size, &cnt_mat);
			break;
		case 'D':
			get_sizes(size, cnt_mat);
			break;
		case 'P':
			print_matrix(v_mat, size, cnt_mat);
			break;
		case 'C':
			resize_matrix(v_mat, size, cnt_mat);
			break;
		case 'M':
			multiply_matrices(&v_mat, &size, &cnt_mat);
			break;
		case 'S':
			multiply_matrices_strassen(&v_mat, &size, &cnt_mat);
			break;
		case 'O':
			sort_matrices(v_mat, size, cnt_mat);
			break;
		case 'T':
			transpose_matrix(v_mat, size, cnt_mat);
			break;
		case 'R':
			exponentiate_matrix(v_mat, size, cnt_mat);
			break;
		case 'F':
			delete_matrix(&v_mat, &size, &cnt_mat);
			break;
		case 'Q':
			quit(&v_mat, &size, &cnt_mat);
			return 0;
		default:
			check_error(valid_command(command_id));
			break;
		}

		/* in cazul in care o alocare a esuat pe parcurs incheiem programul cu
		   statusul -1; functia se apeleaza cu un pointer nenul pentru a depista
		   valoarea variabilei statice din interiorul definitiei functiei*/
		if (check_memory_allocation((void *)1)) {
			quit(&v_mat, &size, &cnt_mat);
			return -1;
		}
	}
	return 0;
}
