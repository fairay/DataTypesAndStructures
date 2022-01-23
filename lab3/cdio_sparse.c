#include "head.h"

void print_table_end(void)
{
    printf("---------+----------+-------+-------|\n");
}

void print_table_head(void)
{
    print_table_end();
    printf("      #  |%9s |%6s |%6s |\n", "A[i][j]", "i", "j");
    print_table_end();
}


int create_spr_mat(spr_mat_t* mat, int n, int m)
{
    int code = OK;
    mat->n = n;
    mat->m = m;
    mat->num = n * m;

    code = create_array(&mat->a, mat->num);
    if (code != OK) return code;

    code = create_array(&mat->ja, mat->num);
    if (code != OK) return code;

    code = create_array(&mat->ia, mat->n + 1);
    if (code != OK) return code;

    return OK;
}

int print_spr_mat(spr_mat_t* mat)
{
    int i, j;

    if (mat->n == 0)
        return EMPTY_MATRIX;

    print_table_head();

    for (i = 0; i < mat->n; i++)
        for (j = mat->ia[i]; j < mat->ia[i + 1]; j++)
            printf("%8d |%9d |%6d |%6d |\n", j + 1, mat->a[j], i, mat->ja[j]);

    print_table_end();
    return OK;
}

void delete_spr_mat(spr_mat_t* mat)
{
    free(mat->a);
    mat->a = NULL;

    free(mat->ja);
    mat->ja = NULL;

    free(mat->ia);
    mat->ia = NULL;
}


int resize_spr_mat_number(spr_mat_t* mat, int count)
{
    int code;

    if (!count)
    {
        delete_array(&mat->a);
        delete_array(&mat->ja);
    }
    else if (mat->num != count)
    {
        code = resize_array(&(mat->a), count);
        if (code != OK) return code;
        code = resize_array(&mat->ja, count);
        if (code != OK) return code;
    }
    mat->num = count;
    return OK;
}

int matrix_to_spr(matrix_t mat, spr_mat_t* spr_mat)
{
    int count = 0;
    for (int i = 0; i < mat.n; i++)
    {
        spr_mat->ia[i]  = count;
        for(int j = 0; j < mat.m; j++)
        {
            if (mat.a[i][j])
            {
                spr_mat->a[count] = mat.a[i][j];
                spr_mat->ja[count] = j;
                count++;
            }
        }
    }
    spr_mat->ia[mat.n] = count;
    return resize_spr_mat_number(spr_mat, count);
}

int spr_find_ij(spr_mat_t* mat, int i, int j)
{
    int left, right, middle;
    left = mat->ia[i];
    right = mat->ia[i + 1];

    if (left == right)
        return 0;

    while (left <= right)
    {
        middle = (left + right) / 2;
        if (mat->ja[middle] > j)
            left = middle + 1;
        else if (mat->ja[middle] < j)
            right = middle - 1;
        else
            return mat->a[middle];
    }
    return 0;
}
