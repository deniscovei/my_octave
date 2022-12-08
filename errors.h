// Covei Denis - 312CA
#pragma once

#include "types_and_defs.h"
#include <stdbool.h>

enum error {no_err, id_err, exp_err, mult_err, cmd_err};

int valid_id(int id, int cnt_mat);
int valid_exponent(int exp);
int is_quadratic(int id, int cnt_mat, magnitude dimension);
int valid_command(char cmd_id);
int valid_multiplication(magnitude dimension);
bool check_error(int error_id);
