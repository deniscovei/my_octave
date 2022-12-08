// Covei Denis - 312CA
#pragma once

#include "types_and_defs.h"

void get_matrix_sum(int ***res_mat, int **a, int **b, int n_rows,
					int n_collumns);
void get_matrix_difference(int ***res_mat, int **a, int **b, int n_rows,
						   int n_collumns);
void get_matrix_product(int ***res_mat, int **a, int **b, int n, int p, int m);
int my_max(int a, int b);
void my_swap(int *a, int *b);
void new_matrix(int ****v_mat, magnitude **size, int *cnt_mat);
void get_sizes(magnitude *size, int cnt_mat);
void print_matrix(int ***v_mat, magnitude *size, int cnt_mat);
void resize_matrix(int ***v_mat, magnitude *size, int cnt_mat);
void multiply_matrices(int ****v_mat, magnitude **size, int *cnt_mat);
int **get_submatrix(int **mat, int corner[]);
void replace_submatrix(int **res_mat, int **mat, int corner[]);
void get_matrix_product_strassen(int ***res_mat, int **a, int **b, int n);
void multiply_matrices_strassen(int ****v_mat, magnitude **size, int *cnt_mat);
int get_sum(int **mat, int n_rows, int n_collumns);
void swap_matrices(int id0, int id1, int ***v_mat, magnitude *size);
void sort_matrices(int ***v_mat, magnitude *size, int cnt_mat);
void transpose_matrix(int ***v_mat, magnitude *size, int cnt_mat);
void exponentiate_matrix(int ***v_mat, magnitude *size, int cnt_mat);
void delete_matrix(int ****v_mat, magnitude **size, int *cnt_mat);
void quit(int ****v_mat, magnitude **size, int *cnt_mat);
