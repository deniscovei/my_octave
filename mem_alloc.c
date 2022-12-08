// Covei Denis - 312CA
#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **, int);

/* verifica daca alocarea de memorie a fost efectuata cu succes;
   intoarce un status codificat prin:
		0 - pentru alocare efectuata cu succes
		1 - pentru alocare esuata */
int check_memory_allocation(void *ptr)
{
	// initial status este by default initializat cu 0, deci nu avem erori
	static int status;
	if (!ptr) {
		printf("Could not allocate memory...");
		status = 1;
	}
	return status;
}

int **malloc_matrix(int n_rows, int n_collumns)
{
	int **mat = (int **)malloc(n_rows * sizeof(int *));
	if (check_memory_allocation((void *)mat)) {
		free(mat);
		return NULL;
	}

	for (int i = 0; i < n_rows; i++) {
		mat[i] = (int *)malloc(n_collumns * sizeof(int));
		if (check_memory_allocation((void *)mat[i])) {
			free_matrix(mat, i - 1);
			return NULL;
		}
	}

	return mat;
}

int **calloc_matrix(int n_rows, int n_collumns)
{
	int **mat = (int **)malloc(n_rows * sizeof(int *));
	if (check_memory_allocation((void *)mat)) {
		free(mat);
		return NULL;
	}

	for (int i = 0; i < n_rows; i++) {
		mat[i] = (int *)calloc(n_collumns, sizeof(int));
		if (check_memory_allocation((void *)mat[i])) {
			free_matrix(mat, i - 1);
			return NULL;
		}
	}

	return mat;
}

void free_matrix(int **mat, int n_rows)
{
	for (int i = 0; i < n_rows; i++)
		free(mat[i]);

	free(mat);
}

