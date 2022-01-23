#include "head.h"

int input_modes(matrix_t* mat, spr_mat_t* spr_mat, int* n, int* m, int mode)
{
    int sc;
    int new_n, new_m;

    printf("Input matrix size (N x M): ");
    sc = scanf("%d%d", &new_n, &new_m);
    if (sc != 2)
        return WRONG_FORMAT;
    else if ((new_n < 1) || (new_m < 1))
        return WRONG_SIZE;

    delete_matrix(mat);
    delete_spr_mat(spr_mat);
    (*n) = new_n;
    (*m) = new_m;
    sc = create_matrix(mat, *n, *m);
    if (sc != OK)   return sc;
    sc = create_spr_mat(spr_mat, *n, *m);
    if (sc != OK)   return sc;

    switch (mode)
    {
        case DEFAULT_INPUT:
            puts("Input matrix:");
            sc = input_matrix(*mat);
            if (sc != OK)
                return sc;
            break;

        case IJA_INPUT:
            sc = ija_input(*mat);
            if (sc != OK)
                return sc;
            break;

        case PERCENT_INPUT:
            sc = percent_input(*mat);
            if (sc != OK)
                return sc;
            break;
    }

    sc = matrix_to_spr(*mat, spr_mat);
    if (sc != OK)
        return sc;

    return OK;

}

int input_column_modes(matrix_t* mat, spr_mat_t* spr_mat, int n)
{
    int sc;
    int mode;

    delete_matrix(mat);
    delete_spr_mat(spr_mat);

    sc = create_matrix(mat, n, 1);
    if (sc != OK)   return sc;
    sc = create_spr_mat(spr_mat, n, 1);
    if (sc != OK)   return sc;

    puts("Input modes:");
    puts("+ /10/ Default input");
    puts("+ /11/ Position and element input");
    puts("+ /12/ Generate matrix with given percentage of zero elements");
    printf("Chose the input mode for column-vector (size %d x 1):\n", n);
    sc = scanf("%d", &mode);

    if (sc != 1)
        return WRONG_FORMAT;

    switch (mode)
    {
        case DEFAULT_INPUT:
            puts("Input column:");
            sc = input_matrix(*mat);
            if (sc != OK)
                return sc;
            break;

        case IJA_INPUT:
            sc = ia_input(*mat);
            if (sc != OK)
                return sc;
            break;

        case PERCENT_INPUT:
            sc = percent_input(*mat);
            if (sc != OK)
                return sc;
            break;

        default:
            return WRONG_MODE;
    }

    sc = matrix_to_spr(*mat, spr_mat);
    if (sc != OK)
        return sc;

    return OK;
}

int ija_input(matrix_t mat)
{
    int a_n = 0;
    int sc;
    int row, col, value;

    printf("Input number of nonezero elements: ");
    sc = scanf("%d", &a_n);
    if (sc != 1)
        return WRONG_FORMAT;
    else if ((a_n < 0) || (a_n > mat.n * mat.m))
        return WRONG_QUANTITY;

    if (a_n)
        printf("Input elements in format: row, column, value:\n");
    for (int i = 0; i < a_n; i++)
    {
        printf("%d) ", i + 1);
        sc = scanf("%d%d%d", &row, &col, &value);
        if (sc != 3)
            return WRONG_FORMAT;
        else if (!value)
            return WRONG_FORMAT;
        else if ((row < 0) || (col < 0) || (row > mat.n) || (col > mat.m))
            return WRONG_POSITION;
        else if (mat.a[row][col])
            return WRONG_POSITION;
        else
            mat.a[row][col] = value;
    }
    return OK;
}

int ia_input(matrix_t mat)
{
    int a_n = 0;
    int sc;
    int row, value;

    printf("Input number of nonezero elements: ");
    sc = scanf("%d", &a_n);
    if (sc != 1)
        return WRONG_FORMAT;
    else if ((a_n < 0) || (a_n > mat.n))
        return WRONG_QUANTITY;

    if (a_n)
        printf("Input elements in format: row, value:\n");
    for (int i = 0; i < a_n; i++)
    {
        printf("%d) ", i + 1);
        sc = scanf("%d%d", &row, &value);
        if (sc != 2)
            return WRONG_FORMAT;
        else if (!value)
            return WRONG_FORMAT;
        else if ((row < 0) || (row > mat.n))
            return WRONG_POSITION;
        else if (mat.a[row][0])
            return WRONG_POSITION;
        else
            mat.a[row][0] = value;
    }
    return OK;
}

int percent_input(matrix_t mat)
{
    float perc;
    int a_n;
    int sc;

    printf("Input percent of zero elements (<=100%%): ");
    sc = scanf("%f", &perc);
    if (sc != 1)
        return WRONG_FORMAT;
    else if ((perc < 0) || (perc > 100))
        return WRONG_FORMAT;
    a_n = mat.n * mat.m - (int)(mat.n * mat.m * perc / 100);
    printf("Filling matrix with %d random nonzero elements\n", a_n);

    fill_nonzero(mat, a_n);

    return OK;
}

// Multiplications
int default_multiply(matrix_t out, matrix_t mat, matrix_t col)
{
    for (int i = 0; i < mat.n; i++)
    {
        out.a[i][0] = 0;
        for (int j = 0; j < mat.m; j++)
            out.a[i][0] += mat.a[i][j] * col.a[j][0];
    }
    return OK;
}

int sparse_multiply(spr_mat_t* out, spr_mat_t mat, spr_mat_t col)
{
    int temp = 0;
    int count = 0;
    int i, j;

    for (i = 0; i < mat.n; i++)
    {
        out->ia[i] = count;
        for (j = mat.ia[i]; j < mat.ia[i + 1]; j++)
        {
            if (col.ia[mat.ja[j]] != col.ia[mat.ja[j] + 1])
                temp += mat.a[j] * col.a[col.ia[mat.ja[j]]];             //spr_find_ij(col, i)
        }
        if (temp)
        {
            out->a[count++] = temp;
            temp = 0;
        }
    }
    out->ia[mat.n] = count;
    return resize_spr_mat_number(out, count);
}


// Comparing time and memory

void comparing(void)
{
    double time[10];
    long int memory[10];

    matrix_t matrix;
    matrix_t column;
    matrix_t out;
    spr_mat_t spr_matrix;
    spr_mat_t spr_column;
    spr_mat_t spr_out;

    create_matrix(&matrix, TEST_SIZE, TEST_SIZE);
    create_matrix(&column, TEST_SIZE, 1);
    create_matrix(&out, TEST_SIZE, 1);

    create_spr_mat(&spr_matrix, TEST_SIZE, TEST_SIZE);
    create_spr_mat(&spr_column, TEST_SIZE, 1);
    create_spr_mat(&spr_out, TEST_SIZE, 1);

    // Creating vector-column
    fill_nonzero(column, TEST_SIZE - 50);
    matrix_to_spr(column, &spr_column);

    printf("Test of time and memory at %dx%d matrix", TEST_SIZE, TEST_SIZE);

    printf("\nMatrix with one element (%lf%% of nonzeros)\n", (double)(1) / (TEST_SIZE * TEST_SIZE));
    fill_nonzero(matrix, 1);

    printf("Default:\n");
    test_default(out, matrix, column, &time[0], &memory[0]);
    printf("Sparse:\n");
    matrix_to_spr(matrix, &spr_matrix);
    test_sparse(&spr_out, spr_matrix, spr_column, &time[1], &memory[1]);

    delete_spr_mat(&spr_out);
    delete_spr_mat(&spr_matrix);
    create_spr_mat(&spr_out, TEST_SIZE, 1);
    create_spr_mat(&spr_matrix, TEST_SIZE, TEST_SIZE);

    puts("\nMatrix with 10% of nonzeros");
    fill_nonzero(matrix, TEST_SIZE * TEST_SIZE / 10);
    printf("Default:\n");
    test_default(out, matrix, column, &time[2], &memory[2]);
    printf("Sparse:\n");
    matrix_to_spr(matrix, &spr_matrix);
    test_sparse(&spr_out, spr_matrix, spr_column, &time[3], &memory[3]);

    delete_spr_mat(&spr_out);
    delete_spr_mat(&spr_matrix);
    create_spr_mat(&spr_out, TEST_SIZE, 1);
    create_spr_mat(&spr_matrix, TEST_SIZE, TEST_SIZE);

    puts("\nMatrix with 30% of nonzeros");
    fill_nonzero(matrix, TEST_SIZE * TEST_SIZE / 5);
    printf("Default:\n");
    test_default(out, matrix, column, &time[4], &memory[4]);
    printf("Sparse:\n");
    matrix_to_spr(matrix, &spr_matrix);
    test_sparse(&spr_out, spr_matrix, spr_column, &time[5], &memory[5]);

    delete_spr_mat(&spr_out);
    delete_spr_mat(&spr_matrix);
    create_spr_mat(&spr_out, TEST_SIZE, 1);
    create_spr_mat(&spr_matrix, TEST_SIZE, TEST_SIZE);

    puts("\nMatrix with 50% of nonzeros");
    fill_nonzero(matrix, TEST_SIZE * TEST_SIZE * (0.5 - 0.3));
    printf("Default:\n");
    test_default(out, matrix, column, &time[6], &memory[6]);
    printf("Sparse:\n");
    matrix_to_spr(matrix, &spr_matrix);
    test_sparse(&spr_out, spr_matrix, spr_column, &time[7], &memory[7]);

    delete_spr_mat(&spr_out);
    delete_spr_mat(&spr_matrix);
    create_spr_mat(&spr_out, TEST_SIZE, 1);
    create_spr_mat(&spr_matrix, TEST_SIZE, TEST_SIZE);

    puts("\nMatrix with 90% of nonzeros");
    fill_nonzero(matrix, TEST_SIZE * TEST_SIZE * (0.9 - 0.5));
    printf("Default:\n");
    test_default(out, matrix, column, &time[8], &memory[8]);
    printf("Sparse:\n");
    matrix_to_spr(matrix, &spr_matrix);
    test_sparse(&spr_out, spr_matrix, spr_column, &time[9], &memory[9]);

    delete_matrix(&matrix);
    delete_matrix(&column);
    delete_matrix(&out);
    delete_spr_mat(&spr_matrix);
    delete_spr_mat(&spr_column);
    delete_spr_mat(&spr_out);

    printf("\n\nTest of time and memory at %dx%d matrix\n", TEST_SIZE, TEST_SIZE);
    printf("\nTime in ms.: \n");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("Method/Fullnes \t 1 element\t 10%% \t\t 30%% \t\t 50%% \t\t 90%%\n");
    printf("Standard \t %6lf ms.\t %6lf ms.\t %6lf ms.\t %6lf ms.\t %6lf ms.\n", time[0], time[2], time[4], time[6], time[8]);
    printf("Sparse \t\t %6lf ms.\t %6lf ms.\t %6lf ms.\t %6lf ms.\t %6lf ms.\n", time[1], time[3], time[5], time[7], time[9]);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    printf("\nMemory in bytes: \n");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("Method/Fullnes \t 1 element\t 10%% \t\t 30%% \t\t 50%% \t\t 90%%\n");
    printf("Standard \t %6ld b\t %6ld b\t %6ld b\t %6ld b\t %6ld b\n", memory[0], memory[2], memory[4], memory[6], memory[8]);
    printf("Sparse \t\t %-6ld b\t %-6ld b\t %-6ld b\t %-6ld b\t %-6ld b\n", memory[1], memory[3], memory[5], memory[7], memory[9]);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    printf("\n Comparing sprase method with standard\n\n");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("Fullnes \t Time \t\t Memory \n");
    printf("1 element \t %10lf%% \t %10lf%% \t\n\n", 100 * time[1] / time[0], 100 * (double)memory[1] / memory[0]);
    printf("10%% \t\t %10lf%% \t %10lf%% \t\n\n", 100 * time[3] / time[2], 100 * (double)memory[3] / memory[2]);
    printf("30%% \t\t %10lf%% \t %10lf%% \t\n\n", 100 * time[5] / time[4], 100 * (double)memory[5] / memory[4]);
    printf("50%% \t\t %10lf%% \t %10lf%% \t\n\n", 100 * time[7] / time[6], 100 * (double)memory[7] / memory[6]);
    printf("90%% \t\t %10lf%% \t %10lf%% \t\n", 100 * time[9] / time[8], 100 * (double)memory[9] / memory[8]);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
}

void test_default(matrix_t out, matrix_t mat, matrix_t col, double *time, long int *memory)
{
    clock_t t;

    t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
        default_multiply(out, mat, col);
    t = clock() - t;

    (*time) = ((double)(t)) / (CLK_TCK * TEST_REPEATS / 1000);
    (*memory) = (long int)(sizeof(int) * mat.n * mat.m);
    // out.n + col.n + mat.n * mat.m

    printf("%lf miliseconds\n", *time);
    printf("%ld bytes\n", *memory);
}

void test_sparse(spr_mat_t* out, spr_mat_t mat, spr_mat_t col, double *time, long int *memory)
{
    clock_t t;
    t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
        sparse_multiply(out, mat, col);
    t = clock() - t;

    (*time) = ((double)(t)) / (CLK_TCK * TEST_REPEATS / 1000);
    (*memory) = (long int)(sizeof(int) * (mat.n+1 + mat.num*2));
    // ((out->n+1 + out->num*2) + (col.n+1 + col.num*2) + (mat.n+1 + mat.num*2))

    printf("%lf miliseconds\n", *time);
    printf("%ld bytes\n", *memory);
}
