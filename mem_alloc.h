// Covei Denis - 312CA
#pragma once

void free_matrix(int **, int);
int check_memory_allocation(void *ptr);
int **malloc_matrix(int n_rows, int n_collumns);
int **calloc_matrix(int n_rows, int n_collumns);
void free_matrix(int **mat, int n_rows);
