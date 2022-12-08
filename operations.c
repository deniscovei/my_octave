// Covei Denis - 312CA
#include <stdio.h>
#include <stdlib.h>
#include "types_and_defs.h"
#include "mem_alloc.h"
#include "errors.h"

void get_matrix_sum(int ***res_mat, int **a, int **b, int n_rows,
					int n_collumns)
{
	// initializarea matricei rezultat
	int **c = malloc_matrix(n_rows, n_collumns);

	// adunarea matricelor
	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++) {
			c[i][j] = (a[i][j] + b[i][j]) % MOD;
			if (c[i][j] < 0)
				c[i][j] += MOD;
		}
	}

	free_matrix(*res_mat, n_rows);
	*res_mat = c;
}

void get_matrix_difference(int ***res_mat, int **a, int **b, int n_rows,
						   int n_collumns)
{
	// initializarea matricei rezultat
	int **c = malloc_matrix(n_rows, n_collumns);

	// adunarea matricelor
	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++) {
			c[i][j] = (a[i][j] - b[i][j]) % MOD;
			if (c[i][j] < 0)
				c[i][j] += MOD;
		}
	}

	free_matrix(*res_mat, n_rows);
	*res_mat = c;
}

// (n, m) = (n, p) * (p, m)
void get_matrix_product(int ***res_mat, int **a, int **b, int n, int p, int m)
{
	// initializarea matricei rezultat
	int **c = calloc_matrix(n, m);

	/* inmultirea matricelor
	   c = a * b */
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < p; k++) {
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
				if (c[i][j] < 0)
					c[i][j] += MOD;
			}
		}
	}

	free_matrix(*res_mat, n);
	*res_mat = c;
}

int my_max(int a, int b)
{
	return (a > b) ? a : b;
}

void my_swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void new_matrix(int ****v_mat, magnitude **size, int *cnt_mat)
{
	int n_rows, n_collumns;
	scanf("%d %d", &n_rows, &n_collumns);

	// declararea noii matrice
	int **new_mat = malloc_matrix(n_rows, n_collumns);
	if (check_memory_allocation((void *)new_mat))
		return;

	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++)
			scanf("%d", &new_mat[i][j]);
	}

	// adaugarea in lista a noii matrice
	(*cnt_mat)++;

	*v_mat = (int ***)realloc((*v_mat), (*cnt_mat) * sizeof(int **));
	check_memory_allocation((void *)*v_mat);
	(*v_mat)[(*cnt_mat) - 1] = new_mat;

	*size = (magnitude *)realloc(*size, (*cnt_mat) * sizeof(magnitude));
	check_memory_allocation((void *)*size);
	(*size)[(*cnt_mat) - 1] = (magnitude){n_rows, n_collumns};
}

void get_sizes(magnitude *size, int cnt_mat)
{
	int id;
	scanf("%d", &id);
	if (check_error(valid_id(id, cnt_mat)))
		return;

	int n_rows = size[id].rows;
	int n_collumns = size[id].collumns;

	printf("%d %d\n", n_rows, n_collumns);
}

void print_matrix(int ***v_mat, magnitude *size, int cnt_mat)
{
	// citirea id-ului
	int id;
	scanf("%d", &id);
	if (check_error(valid_id(id, cnt_mat)))
		return;

	// copierea matricei
	int **mat = v_mat[id];
	int n_rows = size[id].rows;
	int n_collumns = size[id].collumns;

	// afisarea matricei
	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

void resize_matrix(int ***v_mat, magnitude *size, int cnt_mat)
{
	// citirea id-ului
	int id;
	scanf("%d", &id);
	if (check_error(valid_id(id, cnt_mat)))
		return;

	// citirea liniilor
	int n_rows;
	scanf("%d", &n_rows);
	int *row = malloc(n_rows * sizeof(int));
	check_memory_allocation((void *)row);

	for (int i = 0; i < n_rows; i++)
		scanf("%d", &row[i]);

	// citirea coloanelor
	int n_collumns;
	scanf("%d", &n_collumns);
	int *collumn = malloc(n_collumns * sizeof(int));
	check_memory_allocation((void *)collumn);

	for (int j = 0; j < n_collumns; j++)
		scanf("%d", &collumn[j]);

	// formarea matricei redimensionate
	int **new_mat = malloc_matrix(n_rows, n_collumns);

	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++)
			new_mat[i][j] = v_mat[id][row[i]][collumn[j]];
	}

	// inlcouirea matricei din lista cu matricea redimensionata
	free_matrix(v_mat[id], size[id].rows);

	v_mat[id] = new_mat;
	size[id] = (magnitude){n_rows, n_collumns};

	// eliberarea memoriei pentru alocarile locale in functie
	free(row);
	free(collumn);
}

void multiply_matrices(int ****v_mat, magnitude **size, int *cnt_mat)
{
	// citirea id-uurilor
	int id0, id1;
	scanf("%d %d", &id0, &id1);
	if (check_error(valid_id(id0, *cnt_mat)) ||
		check_error(valid_id(id1, *cnt_mat))) {
		return;
	}

	// copierea primei matrice
	int n_rows0 = (*size)[id0].rows;
	int n_collumns0 = (*size)[id0].collumns;
	int **mat0 = (*v_mat)[id0];

	// copierea celei de-a doua matrice
	int n_rows1 = (*size)[id1].rows;
	int n_collumns1 = (*size)[id1].collumns;
	int **mat1 = (*v_mat)[id1];

	if (check_error(valid_multiplication((magnitude){n_collumns0, n_rows1})))
		return;

	// formarea matricei rezultata prin inmultire
	int n_rows = n_rows0;
	int n_collumns = n_collumns1;
	int common_size = n_rows1;
	int **res_mat = calloc_matrix(n_rows, n_collumns);

	// inmultirea matricelor
	get_matrix_product(&res_mat, mat0, mat1, n_rows, common_size, n_collumns);

	// adaugarea in lista a noii matrice
	(*cnt_mat)++;

	*v_mat = (int ***)realloc((*v_mat), (*cnt_mat) * sizeof(int **));
	check_memory_allocation((void *)*v_mat);
	(*v_mat)[(*cnt_mat) - 1] = res_mat;

	*size = (magnitude *)realloc(*size, (*cnt_mat) * sizeof(magnitude));
	check_memory_allocation((void *)*size);
	(*size)[(*cnt_mat) - 1] = (magnitude){n_rows, n_collumns};
}

int **get_submatrix(int **mat, int corner[])
{
	int row0 = corner[0];
	int col0 = corner[1];
	int row1 = corner[2];
	int col1 = corner[3];

	int n_rows = row1 - row0;
	int n_collumns = col1 - col0;

	int **res_mat = malloc_matrix(row1 - row0, col1 - col0);

	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++)
			res_mat[i][j] = mat[i + row0][j + col0];
	}

	return res_mat;
}

/* inlocuieste submatricea delimitata de colturile (row0, col0) si (row1, col1)
   ale matricei res_mat cu matricea mat */
void replace_submatrix(int **res_mat, int **mat, int corner[])
{
	int row0 = corner[0];
	int col0 = corner[1];
	int row1 = corner[2];
	int col1 = corner[3];

	int n_rows = row1 - row0;
	int n_collumns = col1 - col0;

	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++)
			res_mat[i + row0][j + col0] = mat[i][j];
	}
}

void get_matrix_product_strassen(int ***res_mat, int **a, int **b, int n)
{
	int v_corner[4][4] = { {0, 0, n / 2, n / 2},
						{0, n / 2, n / 2, n},
						{n / 2, 0, n, n / 2},
						{n / 2, n / 2, n, n}};
	if (n == 1) {
		(*res_mat)[0][0] = (a[0][0] * b[0][0]) % MOD;
		if ((*res_mat)[0][0] < 0)
			(*res_mat)[0][0] += MOD;
		return;
	}
	int **aux0 = malloc_matrix(n / 2, n / 2);
	int **aux1 = malloc_matrix(n / 2, n / 2);

	int **_a[3];
	#define _a (_a - 1)
	for (int i = 1; i <= 4; i++)
		_a[i] = get_submatrix(a, v_corner[i - 1]);

	int **_b[3];
	#define _b (_b - 1)
	for (int i = 1; i <= 4; i++)
		_b[i] = get_submatrix(b, v_corner[i - 1]);

	int **_m[7];
	#define _m (_m - 1)
	for (int i = 1; i <= 7; i++)
		_m[i] = malloc_matrix(n / 2, n / 2);
	// _m[1] = (_a[1] + _a[4]) * (_b[1] + _b[4])
	get_matrix_sum(&aux0, _a[1], _a[4], n / 2, n / 2);
	get_matrix_sum(&aux1, _b[1], _b[4], n / 2, n / 2);
	get_matrix_product_strassen(&_m[1], aux0, aux1, n / 2);
	// _m[2] = (_a[3] + _a[4]) * _b[1]
	get_matrix_sum(&aux0, _a[3], _a[4], n / 2, n / 2);
	get_matrix_product_strassen(&_m[2], aux0, _b[1], n / 2);
	// _m[3] = _a[1] * (_b[2] - _b[4])
	get_matrix_difference(&aux0, _b[2], _b[4], n / 2, n / 2);
	get_matrix_product_strassen(&_m[3], _a[1], aux0, n / 2);
	// _m[4] = _a[4] * (_b[3] - _b[1])
	get_matrix_difference(&aux0, _b[3], _b[1], n / 2, n / 2);
	get_matrix_product_strassen(&_m[4], _a[4], aux0, n / 2);
	// _m[5] = (_a[1] + _a[2]) * _b[4]
	get_matrix_sum(&aux0, _a[1], _a[2], n / 2, n / 2);
	get_matrix_product_strassen(&_m[5], aux0, _b[4], n / 2);
	// _m[6] = (_a[3] - _a[1]) * (_b[1] + _b[2])
	get_matrix_difference(&aux0, _a[3], _a[1], n / 2, n / 2);
	get_matrix_sum(&aux1, _b[1], _b[2], n / 2, n / 2);
	get_matrix_product_strassen(&_m[6], aux0, aux1, n / 2);
	// _m[7] = (_a[2] - _a[4]) * (_b[3] + _b[4])
	get_matrix_difference(&aux0, _a[2], _a[4], n / 2, n / 2);
	get_matrix_sum(&aux1, _b[3], _b[4], n / 2, n / 2);
	get_matrix_product_strassen(&_m[7], aux0, aux1, n / 2);
	int **_res_mat[4];
	#define _res_mat (_res_mat - 1)
	for (int i = 1; i <= 4; i++)
		_res_mat[i] = malloc_matrix(n / 2, n / 2);
	// _res_mat[1] = _m[1] + _m[4] - _m[5] + _m[7]
	get_matrix_sum(&_res_mat[1], _m[1], _m[4], n / 2, n / 2);
	get_matrix_difference(&_res_mat[1], _res_mat[1], _m[5], n / 2, n / 2);
	get_matrix_sum(&_res_mat[1], _res_mat[1], _m[7], n / 2, n / 2);
	// _res_mat[2] = _m[3]+_m[5]
	get_matrix_sum(&_res_mat[2], _m[3], _m[5], n / 2, n / 2);
	// _res_mat[3] = _m[2]+_m[4]
	get_matrix_sum(&_res_mat[3], _m[2], _m[4], n / 2, n / 2);
	// _res_mat[4] = _m[1]-_m[2]+_m[3]+_m[6]
	get_matrix_difference(&_res_mat[4], _m[1], _m[2], n / 2, n / 2);
	get_matrix_sum(&_res_mat[4], _res_mat[4], _m[3], n / 2, n / 2);
	get_matrix_sum(&_res_mat[4], _res_mat[4], _m[6], n / 2, n / 2);
	// res_mat
	for (int i = 1; i <= 4; i++)
		replace_submatrix(*res_mat, _res_mat[i], v_corner[i - 1]);
	free_matrix(aux0, n / 2);
	free_matrix(aux1, n / 2);
	for (int i = 1; i <= 4; i++) {
		free_matrix(_a[i], n / 2);
		free_matrix(_b[i], n / 2);
		free_matrix(_res_mat[i], n / 2);
	}
	for (int i = 1; i <= 7; i++)
		free_matrix(_m[i], n / 2);
}

void multiply_matrices_strassen(int ****v_mat, magnitude **size, int *cnt_mat)
{
	// citirea id-uurilor
	int id0, id1;
	scanf("%d %d", &id0, &id1);

	int n_rows = (*size)[id0].collumns;
	int n_collumns = (*size)[id1].rows;

	if (check_error(valid_id(id0, *cnt_mat)) ||
		check_error(valid_id(id1, *cnt_mat)) ||
		check_error(valid_multiplication((magnitude){n_rows, n_collumns})))
		return;

	// formarea matricei rezultata prin inmultire
	int n = n_rows;
	int **res_mat = calloc_matrix(n, n);

	// inmultirea matricelor folosind algoritmul lui Strassen
	int **mat0 = (*v_mat)[id0];
	int **mat1 = (*v_mat)[id1];
	get_matrix_product_strassen(&res_mat, mat0, mat1, n);

	// adaugarea in lista a noii matrice
	(*cnt_mat)++;

	*v_mat = (int ***)realloc((*v_mat), (*cnt_mat) * sizeof(int **));
	check_memory_allocation((void *)*v_mat);
	(*v_mat)[(*cnt_mat) - 1] = res_mat;

	*size = (magnitude *)realloc(*size, (*cnt_mat) * sizeof(magnitude));
	check_memory_allocation((void *)*size);
	(*size)[(*cnt_mat) - 1] = (magnitude){n, n};
}

int get_sum(int **mat, int n_rows, int n_collumns)
{
	int sum = 0;

	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++) {
			sum = (sum + mat[i][j]) % MOD;
			if (sum < 0)
				sum += MOD;
		}
	}

	return sum;
}

void swap_matrices(int id0, int id1, int ***v_mat, magnitude *size)
{
	int **tmp = v_mat[id0];
	v_mat[id0] = v_mat[id1];
	v_mat[id1] = tmp;
	my_swap(&size[id0].rows, &size[id1].rows);
	my_swap(&size[id0].collumns, &size[id1].collumns);
}

void sort_matrices(int ***v_mat, magnitude *size, int cnt_mat)
{
	int *sum = (int *)malloc(cnt_mat * sizeof(int));

	for (int id = 0; id < cnt_mat; id++)
		sum[id] = get_sum(v_mat[id], size[id].rows, size[id].collumns);

	for (int i = 0; i < cnt_mat; i++) {
		for (int j = i + 1; j < cnt_mat; j++) {
			if (sum[i] > sum[j]) {
				my_swap(&sum[i], &sum[j]);
				swap_matrices(i, j, v_mat, size);
			}
		}
	}

	free(sum);
}

void transpose_matrix(int ***v_mat, magnitude *size, int cnt_mat)
{
	// citirea id-ului
	int id;
	scanf("%d", &id);
	if (check_error(valid_id(id, cnt_mat)))
		return;

	// formarea transpusei
	int n_rows = size[id].collumns;
	int n_collumns = size[id].rows;
	int **tr_mat = malloc_matrix(n_rows, n_collumns);

	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_collumns; j++)
			tr_mat[i][j] = v_mat[id][j][i];
	}

	// eliberarea memoriei vechii matrice
	free_matrix(v_mat[id], size[id].rows);

	// inlcouirea matricei cu transpusa sa
	v_mat[id] = tr_mat;
	size[id] = (magnitude){n_rows, n_collumns};
}

void exponentiate_matrix(int ***v_mat, magnitude *size, int cnt_mat)
{
	// citirea id-ului si puterii
	int id, exp;
	scanf("%d %d", &id, &exp);

	// verificarea posibilelor erori
	if (check_error(valid_id(id, cnt_mat)) ||
		check_error(valid_exponent(exp)) ||
		check_error(is_quadratic(id, cnt_mat, size[id])))
		return;

	// copierea matricei
	int **mat = v_mat[id];

	// formarea matricei ridicate la putere
	int n = size[id].rows;
	int **res_mat = calloc_matrix(n, n);
	for (int i = 0; i < n; i++)
		res_mat[i][i] = 1;

	// exponetierea matricei
	while (exp) {
		if (exp & 1) {
			// res_mat = res_mat * mat
			get_matrix_product(&res_mat, res_mat, mat, n, n, n);
		}
		// mat = mat * mat
		get_matrix_product(&mat, mat, mat, n, n, n);
		exp >>= 1;
	}

	// eliberarea memoriei matricei vechi
	free_matrix(mat, n);

	// inlocuirea matricei vechi cu matricea exponentiata
	v_mat[id] = res_mat;
}

void delete_matrix(int ****v_mat, magnitude **size, int *cnt_mat)
{
	// citirea id-ului
	int id;
	scanf("%d", &id);
	if (check_error(valid_id(id, *cnt_mat)))
		return;

	for (int i = id + 1; i < (*cnt_mat); i++)
		swap_matrices(i - 1, i, *v_mat, *size);

    // eliberarea memoriei matricei
	int id_end = (*cnt_mat) - 1;
	free_matrix((*v_mat)[id_end], (*size)[id_end].rows);

    // stergerea din lista a matricei
	(*cnt_mat)--;

	if (*cnt_mat) {
		*v_mat = (int ***)realloc((*v_mat), (*cnt_mat) * sizeof(int **));
		check_memory_allocation((void *)*v_mat);
	}

	if (*cnt_mat) {
		*size = (magnitude *)realloc(*size, (*cnt_mat) * sizeof(magnitude));
		check_memory_allocation((void *)*size);
	}
}

void quit(int ****v_mat, magnitude **size, int *cnt_mat)
{
	for (int id = 0; id < (*cnt_mat); id++)
		free_matrix((*v_mat)[id], (*size)[id].rows);

	free(*v_mat);
	free(*size);
}
