#include "head.h"

void print_head(void)
{
    puts("v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^");
    puts("Program for operations with spare matrix");
    puts("Multimpication integer matrix and column-vector using default and sprase form");
    puts("v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^\n\n");
}

void print_functions(void)
{
    puts("Program functions:");
    printf("+-------------------------------------------\n");
    puts("+ |00| Exit");
    puts("+ |01| Show program functions");
    puts("+                    ");
    puts("+ // Input matrix //");
    puts("+ /10/ Default input");
    puts("+ /11/ Position and element input");
    puts("+ /12/ Generate matrix with given percentage of zero elements");
    puts("+                    ");
    puts("+ // Output matrix //");
    printf("+ [20] Default print (only <%d size)\n", MAX_PRINT_SIZE);
    puts("+ [21] Print sparse matrix");
    puts("+ ");
    puts("+ <30> Default multiply with column vector");
    puts("+ <31> Sparse multiply with column vector");
    puts("+ ");
    puts("+ :40: Compare efficiency");
    printf("+-------------------------------------------\n\n");
}

int show_error_message(int code)
{
    printf("Error: ");
    switch (code)
    {
        case ALLOC_FAIL:
            printf("memory allocation failed");
            break;

        case WRONG_FORMAT:
            printf("wrong input data format");
            break;

        case WRONG_SIZE:
            printf("wrong matrix size");
            break;

        case TOO_LARGE_PRINT:
            printf("matrix have more then %d columns", MAX_PRINT_SIZE);
            break;

        case EMPTY_MATRIX:
            printf("matrix is empty or contains only zeros");
            break;

        case WRONG_QUANTITY:
            printf("wrong quantity of elements");
            break;

        case WRONG_POSITION:
            printf("wrong input position");
            break;
    }
    printf("\n");
    return code;
}

int main(void)
{
    srand(time(NULL));
    int mode = START;
    int code = OK;
    int sc;
    char trash_str[] = "\0";

    int n = 0, m = 0;

    matrix_t matrix;
    matrix_t column;
    matrix_t out;

    spr_mat_t sparse_matrix;
    spr_mat_t sparse_column;
    spr_mat_t sparse_out;

    create_matrix(&matrix, n, m);
    create_matrix(&column, n, m);
    create_matrix(&out, n, m);

    create_spr_mat(&sparse_matrix, n, m);
    create_spr_mat(&sparse_column, n, m);
    create_spr_mat(&sparse_out, n, m);

    print_head();
    print_functions();

    while (mode != EXIT)
    {
        printf("\n=======================\n");
        printf("(print %d to show functions)\n", SHOW_INFO);
        printf("Chose action: ");
        sc = scanf("%d", &mode);
        if (sc != 1)
        {
            mode = WRONG_MODE;
            gets(trash_str);
        }
        printf("=======================\n");

        switch (mode)
        {
            case EXIT:
                puts("Exit the program...");
                break;

            case SHOW_INFO:
                print_functions();
                break;

            case DEFAULT_INPUT:
                printf("*** Input matrix ***\n\n");
                code = input_modes(&matrix, &sparse_matrix, &n, &m, mode);
                if (code != OK)
                    show_error_message(code);
                else
                    puts("Scaned successfully");
                break;

            case IJA_INPUT:
                printf("*** Input matrix ***\n\n");
                code = input_modes(&matrix, &sparse_matrix, &n, &m, mode);
                if (code != OK)
                    show_error_message(code);
                else
                    puts("Scaned successfully");
                break;


            case PERCENT_INPUT:
                printf("*** Input matrix ***\n\n");
                code = input_modes(&matrix, &sparse_matrix, &n, &m, mode);
                if (code != OK)
                    show_error_message(code);
                else
                    puts("Scaned successfully");
                break;

            case DEFAULT_OUTPUT:
                printf("*** Printing matrix ***\n\n");
                code = print_matrix(matrix);
                if (code != OK)
                    show_error_message(code);
                break;

            case SPARSE_OUTPUT:
                printf("*** Printing sparse matrix ***\n\n");
                code = print_spr_mat(&sparse_matrix);
                if (code != OK)
                    show_error_message(code);
                break;

            case DEF_MULTIPLY:
                printf("*** Default multiplication of matrix and column-vector ***\n\n");
                if (n)
                {
                    delete_matrix(&out);
                    delete_spr_mat(&sparse_out);

                    create_matrix(&out, n, 1);
                    create_spr_mat(&sparse_out, n, 1);

                    code = input_column_modes(&column, &sparse_column, m);
                    if (code == OK)
                    {
                        printf("\n\n Input column:\n");
                        print_matrix(column);
                        default_multiply(out, matrix, column);
                        printf("\n\n Resault column:\n");
                        print_matrix(out);
                    }
                    else
                        show_error_message(code);
                }
                else
                    show_error_message(EMPTY_MATRIX);

                break;

        case SPR_MULTIPLY:
            printf("*** Sparse multiplication of matrix and column-vector ***\n\n");
            if (n)
            {
                delete_matrix(&out);
                delete_spr_mat(&sparse_out);

                create_matrix(&out, n, 1);
                create_spr_mat(&sparse_out, n, 1);

                code = input_column_modes(&column, &sparse_column, m);
                if (code == OK)
                {
                    printf("\n\n Input column:\n");
                    code = print_spr_mat(&sparse_column);
                    if (code != OK)
                        show_error_message(code);
                    sparse_multiply(&sparse_out, sparse_matrix, sparse_column);
                    printf("\n\n Resault sparse column:\n");
                    code = print_spr_mat(&sparse_out);
                    if (code != OK)
                        show_error_message(code);
                }
                else
                    show_error_message(code);
            }
            else
                show_error_message(EMPTY_MATRIX);

            break;

            case COMPARE:
                printf("*** Comparing time and memory ***\n\n");
                comparing();
                break;

            default:
                puts("Unknown or incorrect action name");
                break;
        }
    }


    delete_matrix(&matrix);
    delete_matrix(&column);
    delete_matrix(&out);

    delete_spr_mat(&sparse_matrix);
    delete_spr_mat(&sparse_column);
    delete_spr_mat(&sparse_out);

    return OK;
}
