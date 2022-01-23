#include "head.h"


int err_message(int code)
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

        case WRONG_MODE:
            printf("wrong command");
            break;

        case FINPUT_FAIL:
            printf("wrong file format");
            break;

        case OVERFLOW:
            printf("hash table overflow");
            break;

        case WRONG_FILE:
            printf("wrong file");
            break;

        case WRONG_TIME:
            printf("time range is incorrect");
    }
    printf("\n");
    return code;
}

int add_file(char file_name[], int number)
{
    int is_in = 0;
    FILE *f;
    /*
    f = fopen(file_name, "r");
    if (!f)     return WRONG_FILE;

    sc = fscanf(f, "%d", &val);
    while (sc != EOF && !(is_in))
    {
        if (val == number)
            is_in = 1;
        sc = fscanf(f, "%d", &val);
    }
    fclose(f);
    */
    if (!is_in)
    {
        f = fopen(file_name, "a");
        if (!f)     return WRONG_FILE;
        fprintf(f, "%d ", number);
        fclose(f);
    }

    return OK;
}

int add_file_test(FILE *f, int number)
{
    fprintf(f, "%d ", number);
    return OK;
}

int count_file_find(FILE *f, int number)
{
    int count = 1;
    int temp, sc;
    sc = fscanf(f, "%d", &temp);
    while (sc != EOF && number != temp)
    {
        count++;
        sc = fscanf(f, "%d", &temp);
    }
    return count;
}


int file_mode(void)
{
    int code, number;
    char file_name[256];
    tree_t tree = create_tree();
    tree_t avl_tree = create_tree();
    table_t table;

    system("cls");
    printf("Input file name: ");
    code = scanf("%s", file_name);
    if (code != 1)
    {
        printf("Error: file corrupted\n");
        return WRONG_INPUT;
    }
    code = finput_tree(file_name, &tree);
    if (code != OK)
    {
        printf("Error: incorrect format of file\n");
        delete_tree(&tree);
        return code;
    }

    printf("Scaned tree:\n");
    print_tree(tree);

    code = finput_tree(file_name, &avl_tree);
    if (code != OK)
    {
        delete_tree(&tree);
        return code;
    }
    deep_balance(&avl_tree);
    printf("Balanced tree:\n");
    print_tree(avl_tree);

    printf("Hash table:\n");
    code = finput_table(file_name, &table);
    if (code != OK)
    {
        delete_table(&table);
        delete_tree(&tree);
        delete_tree(&avl_tree);
        return code;
    }

    printf("Scaned table:\n");
    print_table(table);

    printf(">>> Add new number: ");
    code = scanf("%d", &number);
    if (code != 1)
    {
        delete_table(&table);
        delete_tree(&tree);
        delete_tree(&avl_tree);
        return err_message(WRONG_FORMAT);
    }

    add_node(&tree, number);
    add_node_avl(&avl_tree, number);
    add_table(&table, number);
    add_file(file_name, number);
    printf(">>> Added\n");

    printf("Tree:\n");
    print_tree(tree);
    printf("Balanced tree:\n");
    print_tree(avl_tree);
    printf("Table:\n");
    print_table(table);

    delete_table(&table);
    delete_tree(&tree);
    delete_tree(&avl_tree);
    return OK;
}

int main(void)
{
    srand(time(NULL));
    int code = OK, mode;
    printf("%d\n\n", (8 + 1 - 7) % 8);
    printf("Tree, AVL tree and hash table program\n");
    printf("/-----------------------\n");
    printf("| Modes                 \n");
    printf("| 1) Test mode          \n");
    printf("| 2) Work with file     \n");
    printf("| 3) Analysis           \n");
    printf("\\-----------------------\n");
    printf(">>> Input mode: ");
    code = scanf("%d", &mode);
    if (code != 1)
    {
        return err_message(WRONG_FORMAT);
    }

    code = OK;
    switch (mode)
    {
        case 1:
            test_mode();
            break;

        case 2:
            code = file_mode();
            break;

        case 3:
            compare();
            break;

        default:
            return err_message(WRONG_MODE);
            break;
    }
    return code;
}
