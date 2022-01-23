#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRINT_SIZE      30
#define TEST_REPEATS        300
#define TEST_SIZE           2000

// Error codes
#define OK              0
#define ALLOC_FAIL      -1
#define WRONG_FORMAT    -2
#define WRONG_SIZE      -3
#define TOO_LARGE_PRINT -4
#define EMPTY_MATRIX    -5
#define WRONG_QUANTITY  -6
#define WRONG_POSITION  -7

// Program modes
#define WRONG_MODE      -2
#define START           -1
#define EXIT            0
#define SHOW_INFO       1
#define DEFAULT_INPUT   10
#define IJA_INPUT       11
#define PERCENT_INPUT   12
#define DEFAULT_OUTPUT  20
#define SPARSE_OUTPUT   21
#define DEF_MULTIPLY    30
#define SPR_MULTIPLY    31
#define COMPARE         40

typedef int* array_t;

typedef struct
{
    int num;        // Number of not zero elements
    int n, m;       // n*m size of matrix
    array_t a;
    array_t ja;
    array_t ia;
} spr_mat_t;        // Sparse matrix type

typedef struct
{
    int n, m;
    array_t* a;
} matrix_t;         // Matrix type

// Sprase matrix functions
int create_spr_mat(spr_mat_t* mat, int n, int m);
int print_spr_mat(spr_mat_t* mat);
void delete_spr_mat(spr_mat_t* mat);

int matrix_to_spr(matrix_t mat, spr_mat_t* spr_mat);
int spr_find_ij(spr_mat_t* mat, int i, int j);
int resize_spr_mat_number(spr_mat_t* mat, int count);

// Matrix functions
int create_matrix(matrix_t *a, size_t row_n, size_t col_n);
void delete_matrix(matrix_t *a);
int input_matrix(matrix_t a);
int print_matrix(matrix_t a);
int resize_matrix(matrix_t *a, size_t n);
void fill_nonzero(matrix_t mat, int a_n);

// Array functions
int create_array(array_t *a, size_t n);
void delete_array(array_t *a);
int input_array(array_t a, size_t n);
void print_array(array_t a, size_t n);
int resize_array(array_t *a, size_t n);

// Program modes
int input_modes(matrix_t* mat, spr_mat_t* spr_mat, int* n, int* m, int mode);
int ija_input(matrix_t mat);
int ia_input(matrix_t mat);
int percent_input(matrix_t mat);

int input_column_modes(matrix_t* mat, spr_mat_t* spr_mat, int n);

int default_multiply(matrix_t out, matrix_t mat, matrix_t col);
int sparse_multiply(spr_mat_t* out, spr_mat_t mat, spr_mat_t col);

// Comparing functions
void comparing(void);
void test_default(matrix_t out, matrix_t mat, matrix_t col, double *time, long int *memory);
void test_sparse(spr_mat_t* out, spr_mat_t mat, spr_mat_t col, double *time, long int *memory);

#endif // HEAD_H
