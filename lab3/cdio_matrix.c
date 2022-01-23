#include "head.h"

// Dynamic matrix CDIO and other functions
// CDIO

int create_matrix(matrix_t *mat, size_t row_n, size_t col_n)
{
    mat->n = row_n;
    mat->m = col_n;

    if (!row_n)
    {
        mat->a = NULL;
        return OK;
    }

    mat->a = (array_t*)malloc(row_n * sizeof(array_t));
    if (mat->a)
    {
        for (int i = 0; i < row_n; i++)
        {
            if (create_array(&mat->a[i], col_n) != OK)
            {
                delete_matrix(mat);
                return ALLOC_FAIL;
            }
        }
    }
    else
    {
        delete_matrix(mat);
        return ALLOC_FAIL;
    }
    return OK;
}

void delete_matrix(matrix_t *mat)
{
    for (int i = 0; i < mat->n; i++)
        delete_array(&mat->a[i]);

    free(mat->a);
    (mat->a) = NULL;
}

int input_matrix(matrix_t mat)
{
    int code;

    for (int i = 0; i < mat.n; i++)
    {
        code = input_array(mat.a[i], mat.m);
        if (code != OK)
            return WRONG_FORMAT;
    }

    return OK;
}

int print_matrix(matrix_t mat)
{
    if (!(mat.n && mat.m))
        return EMPTY_MATRIX;
    if (mat.m > MAX_PRINT_SIZE)
        return TOO_LARGE_PRINT;

    for (int i = 0; i < mat.n; i++)
        print_array(mat.a[i], mat.m);
    return OK;
}

int resize_matrix(matrix_t *mat, size_t n)
{
    if (n == mat->n)
        return OK;

    array_t* new_mat = (array_t*)realloc((mat->a), n * sizeof(array_t));
    if (new_mat)
    {
        mat->n = n;
        mat->a = new_mat;
        new_mat = NULL;
        return OK;
    }
    else
        return ALLOC_FAIL;
}

void fill_nonzero(matrix_t mat, int a_n)
{
    int row, col;

    while (a_n > 0)
    {
        row = rand() % mat.n;
        col = rand() % mat.m;
        if (!mat.a[row][col])
        {
            mat.a[row][col] = 1 + rand() % 10;
            a_n--;
        }
    }
}


// Dynamic array CDIO and other functions
// CDIO

int create_array(array_t *a, size_t n)
{
    (*a) = (array_t)calloc(n, sizeof(int));
    if (*a)
        return OK;
    else
        return ALLOC_FAIL;
}

void delete_array(array_t *a)
{
    free(*a);
    (*a) = NULL;
}

int input_array(array_t a, size_t n)
{
    int sc = 0;
    for (int i = 0; i < n; i++)
        sc += scanf("%d", &a[i]);

    if (sc != n)
        return WRONG_FORMAT;
    else
        return OK;
}

void print_array(array_t a, size_t n)
{
    for (int i = 0; i < n; i++)
        printf("%4d ", a[i]);
    printf("\n");
}

// Applied functions
int resize_array(array_t *a, size_t n)
{
    array_t new_arr = NULL;
    new_arr = (array_t)realloc((*a), n * sizeof(int));
    if (new_arr)
    {
        (*a) = new_arr;
        new_arr = NULL;
        return OK;
    }
    else
        return ALLOC_FAIL;
}
