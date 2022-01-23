#include "head.h"

void print_tree_menu(void)
{
    printf("/-----------------------\n");
    printf("| Actions               \n");
    printf("| 0) Exit               \n");
    printf("| 1) Add element        \n");
    printf("| 2) Delete element     \n");
    printf("| 3) Find element       \n");
    printf("| 4) Scan from file     \n");
    printf("| 5) Calculate average comparations\n");
    printf("| 6) Postfix traversal  \n");
    printf("| 7) Prefix traversal   \n");
    printf("| 8) Infix traversal    \n");
    printf("\\-----------------------\n");
}

void print_hash_menu(void)
{
    printf("/-----------------------\n");
    printf("| Actions               \n");
    printf("| 0) Exit               \n");
    printf("| 1) Add element        \n");
    printf("| 2) Delete element     \n");
    printf("| 3) Find element       \n");
    printf("| 4) Scan from file     \n");
    printf("| 5) Calculate average comparations\n");
    printf("| 6) Change max comparisons \n");
    printf("\\-----------------------\n");
}


void test_tree(void)
{
    int code;
    int mode = WRONG_INPUT;
    int number;
    char trash[10];
    char file_name[256];
    tree_t tree = create_tree();
    tree_t *find = NULL;

    system("cls");
    while (mode != EXIT)
    {
        printf("Binary tree\n");
        print_tree_menu();
        if (tree)
        {
            printf("Tree:\n");
            print_tree(tree);
        }

        printf("\n>>> Input action: ");
        code = scanf("%d", &mode);
        system("cls");
        if (code != 1)
        {
            mode = WRONG_INPUT;
            gets(trash);
        }

        switch (mode)
        {
            case EXIT:
                printf("Exit\n");
                mode = EXIT;
                break;
            case WRONG_INPUT:
                printf("Wrong input\n\n");
                break;

            case ADD:
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                add_node(&tree, number);
                break;

            case DEL:
                if (!tree)
                {
                    printf("Error: tree is empty!\n");
                    break;
                }
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                code = delete_node(&tree, number);
                if (code == NO_ELEMENT)
                    printf(">>> Node are not in tree\n");
                else
                    printf(">>> Node deleted\n");
                break;

            case FIND:
                if (!tree)
                {
                    printf("Error: tree is empty!\n");
                    break;
                }
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                number = find_cmp(tree, number);

                find = find_node(&tree, number);
                if (!find)
                    printf(">>> Element not found\n\n");
                else
                    printf(">>> Element found\n\n");

                printf(">>> %d comparisons\n", number);
                break;

            case SCAN_FILE:
                printf(">>> Input file name: ");
                code = scanf("%s", file_name);
                if (code != 1)
                {
                    printf("Wrong file\n");
                    break;
                }

                delete_tree(&tree);
                code = finput_tree(file_name, &tree);
                if (code != OK)
                {
                    delete_tree(&tree);
                    printf("Corrupted file\n");
                }
                break;

            case AVER_COUNT:
                if (tree)
                    printf(">>> Average comparisons: %.2f\n", tree_aver_count(tree));
                else
                    printf(">>> Error: empty tree\n");
                break;

            case PREFIX:
                if (!tree)
                {
                    printf("Error: tree is empty!\n");
                    break;
                }
                printf("Prefix traversal: ");
                prefix_trav(tree);
                printf("\n");
                break;

            case INFIX:
                if (!tree)
                {
                    printf("Error: tree is empty!\n");
                    break;
                }
                printf("Infix traversal: ");
                infix_trav(tree);
                printf("\n");
                break;

            case POSTFIX:
                if (!tree)
                {
                    printf("Error: tree is empty!\n");
                    break;
                }
                printf("Postfix traversal: ");
                postfix_trav(tree);
                printf("\n");
                break;

            default:
                err_message(WRONG_MODE);
                break;
        }
    }
    delete_tree(&tree);
}

void test_avl_tree(void)
{
    int code;
    int mode = WRONG_INPUT;
    int number;
    char trash[10];
    char file_name[256];
    tree_t tree = create_tree();
    tree_t* find = NULL;

    system("cls");
    while (mode != EXIT)
    {
        printf("Binary AVL tree\n");
        print_tree_menu();
        if (tree)
        {
            printf("AVL tree:\n");
            print_tree(tree);
        }

        printf("\n>>> Input action: ");
        code = scanf("%d", &mode);
        system("cls");
        if (code != 1)
        {
            mode = WRONG_INPUT;
            gets(trash);
        }

        switch (mode)
        {
            case EXIT:
                printf("Exit\n");
                mode = EXIT;
                break;
            case WRONG_INPUT:
                printf("Wrong input\n\n");
                break;

            case ADD:
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                add_node_avl(&tree, number);
                break;

            case DEL:
                if (!tree)
                {
                    printf("Error: AVL tree is empty!\n");
                    break;
                }
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                code = delete_node_avl(&tree, number);
                if (code == NO_ELEMENT)
                    printf(">>> Node are not in tree\n");
                else
                    printf(">>> Node deleted\n");
                break;

            case FIND:
                if (!tree)
                {
                    printf("Error: AVL tree is empty!\n");
                    break;
                }
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                number = find_cmp(tree, number);

                find = find_node(&tree, number);
                if (!find)
                    printf(">>> Element not found\n\n");
                else
                    printf(">>> Element found\n\n");

                printf(">>> %d comparisons\n", number);
                break;

            case SCAN_FILE:

                printf(">>> Input file name: ");
                code = scanf("%s", file_name);
                if (code != 1)
                {
                    printf("Wrong file\n");
                    break;
                }

                delete_tree(&tree);
                code = finput_tree_avl(file_name, &tree);
                if (code != OK)
                {
                    delete_tree(&tree);
                    printf("Corrupted file\n");
                }
                break;

            case AVER_COUNT:
                if (tree)
                    printf(">>> Average comparisons: %.2f\n", tree_aver_count(tree));
                else
                    printf(">>> Error: empty tree\n");
                break;

            case PREFIX:
                if (!tree)
                {
                    printf("Error: AVL tree is empty!\n");
                    break;
                }
                printf("Prefix traversal: ");
                prefix_trav(tree);
                printf("\n");
                break;

            case INFIX:
                if (!tree)
                {
                    printf("Error: AVL tree is empty!\n");
                    break;
                }
                printf("Infix traversal: ");
                infix_trav(tree);
                printf("\n");
                break;

            case POSTFIX:
                if (!tree)
                {
                    printf("Error: AVL tree is empty!\n");
                    break;
                }
                printf("Postfix traversal: ");
                postfix_trav(tree);
                printf("\n");
                break;

            default:
                err_message(WRONG_MODE);
                break;
        }
    }
    delete_tree(&tree);
}

void test_hash_table(void)
{
    int code;
    int mode = WRONG_INPUT;
    int number, pos, count;
    int max_cmp = 4;
    char trash[10];
    char file_name[256];
    table_t table;
    create_table(&table, 4);

    system("cls");
    while (mode != EXIT)
    {
        printf("Hash table\n");
        print_hash_menu();
        if (table.count)
        {
            printf("Maximum find comparations allowed: %d\n", max_cmp);
            printf("Table:\n");
            print_table(table);
        }

        printf("\n>>> Input action: ");
        code = scanf("%d", &mode);
        system("cls");
        if (code != 1)
        {
            mode = WRONG_INPUT;
            gets(trash);
        }

        switch (mode)
        {
            case EXIT:
                printf("Exit\n");
                mode = EXIT;
                break;
            case WRONG_INPUT:
                printf("Wrong input\n\n");
                break;

            case ADD:
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                add_table(&table, number);
                break;

            case DEL:
                if (!table.count)
                {
                    printf("Error: hash table is empty!\n");
                    break;
                }
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                del_table(&table, number);
                break;

            case FIND:
                printf(">>> Input number: ");
                code = scanf("%d", &number);
                if (code != 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                    break;
                }

                count = count_find_table(&table, number);
                pos = find_table(&table, number);
                printf("\n>>> After %d comparisons\n", count);
                if (pos == -1)
                    printf(">>> Element not found\n\n");
                else
                    printf(">>> Element %d is on position %d\n\n", number, pos);
                if (count > max_cmp && pos != -1)
                {
                    printf("Comparison limit exceeded. Restructuring the table\n");
                    restruct_table(&table);
                }
                break;

            case SCAN_FILE:
                printf(">>> Input file name: ");
                code = scanf("%s", file_name);
                if (code != 1)
                {
                    printf("Wrong file\n");
                    break;
                }

                delete_table(&table);
                code = finput_table(file_name, &table);
                if (code != OK)
                {
                    delete_table(&table);
                    printf("Corrupted file\n");
                }
                break;

            case AVER_COUNT:
                if (table.count)
                    printf(">>> Average comparisons: %.2f\n", table_aver_count(&table));
                else
                    printf(">>> Error: empty table\n");
                break;

            case CHANGE_MAX_CMP:
                printf(">>> Input number: ");
                code = scanf("%d", &max_cmp);
                if (code != 1 || max_cmp < 1)
                {
                    printf("Wrong number\n");
                    mode = WRONG_INPUT;
                    gets(trash);
                }
                break;

            default:
                err_message(WRONG_MODE);
                break;
        }
    }
    delete_table(&table);
}

void test_mode(void)
{
    int code;
    int mode = WRONG_INPUT;
    char trash[10];

    system("cls");
    printf("Test mode\n");
    printf("/-----------------------\n");
    printf("| Modes                 \n");
    printf("| 1) Tree               \n");
    printf("| 2) AVL tree           \n");
    printf("| 3) Hash table         \n");
    printf("\\-----------------------\n");
    printf(">>> Input mode: ");
    code = scanf("%d", &mode);
    if (code != 1)
    {
        printf("Wrong input\n");
        gets(trash);
        return;
    }

    switch (mode)
    {
        case 1:
            test_tree();
            break;
        case 2:
            test_avl_tree();
            break;
        case 3:
            test_hash_table();
            break;
        default:
            err_message(WRONG_MODE);
            break;
    }
}


/// Comparing
stats_t test_tree_add(int data[], int find[])
{
    stats_t stat;
    tree_t tree = create_tree();

    stat.add_time = clock();
    for (int i = 0; i < TEST_N; i++)
        add_node(&tree, data[i]);

    stat.add_time = (double)(clock() - stat.add_time) / CLK_TCK * 1000;
    stat.add_mem = (double)sizeof(node_t) * TEST_N / 1024;

    stat.find_time = clock();
    stat.find_cmp = 0;
    for (int j = 0; j < REPEATS; j++)
        for (int i = 0; i < FIND_N; i++)
            stat.find_cmp += find_cmp(tree, find[i]);
    stat.find_time = (double)(clock() - stat.find_time) / CLK_TCK * 1000 / REPEATS;
    stat.find_cmp /= REPEATS;

    delete_tree(&tree);
    return stat;
}

stats_t test_avl_tree_add(int data[], int find[])
{
    stats_t stat;
    tree_t tree = create_tree();

    stat.add_time = clock();
    for (int i = 0; i < TEST_N; i++)
        add_node_avl(&tree, data[i]);

    stat.add_time = (double)(clock() - stat.add_time) / CLK_TCK * 1000;
    stat.add_mem = (double)sizeof(node_t) * TEST_N / 1024;

    stat.find_time = clock();
    stat.find_cmp = 0;
    for (int j = 0; j < REPEATS; j++)
        for (int i = 0; i < FIND_N; i++)
            stat.find_cmp += find_cmp(tree, find[i]);
    stat.find_time = (double)(clock() - stat.find_time) / CLK_TCK * 1000 / REPEATS;
    stat.find_cmp /= REPEATS;

    return stat;
}

stats_t test_hash_add(int repeats, int size, int data[], int find[])
{
    int i;
    stats_t stat;
    table_t table;
    create_table(&table, size);

    stat.add_time = clock();
    for (i = 0; i < repeats; i++)
        add_table(&table, data[i]);

    stat.add_time = (double)(clock() - stat.add_time) / CLK_TCK * 1000;
    stat.add_mem = (double)sizeof(int) * 2 * table.size / 1024;

    stat.find_time = clock();
    stat.find_cmp = 0;
    for (int j = 0; j < REPEATS; j++)
        for (int i = 0; i < FIND_N; i++)
            stat.find_cmp += count_find_table(&table, find[i]);
    stat.find_time = (double)(clock() - stat.find_time) / CLK_TCK * 1000 / REPEATS;
    stat.find_cmp /= REPEATS;

    return stat;
}

stats_t test_file_add(int repeats, int data[], int find[])
{
    stats_t stat;

    FILE *f = fopen("test.txt", "w+");

    stat.add_time = clock();
    for (int i = 0; i < repeats; i++)
        add_file_test(f, data[i]);
    fclose(f);

    stat.add_time = (double)(clock() - stat.add_time) / CLK_TCK * 1000;
    stat.add_mem = (double)sizeof(char) * 6 * repeats / 1024;

    // int count_file_find(char file_name[], int number)

    f = fopen("test.txt", "r");
    stat.find_time = clock();
    stat.find_cmp = 0;
    for (int i = 0; i < FIND_N; i++)
    {
        fseek(f, 0 , SEEK_SET);
        stat.find_cmp += count_file_find(f, find[i]);
    }
    fclose(f);

    stat.find_time = (double)(clock() - stat.find_time) / CLK_TCK * 1000;

    return stat;
}

void compare(void)
{
    array_t data;
    int find[FIND_N];
    stats_t stat[5];

    create_array(&data, TEST_N);
    for (int i = 0; i < TEST_N; i++)
        data[i] = (rand() * rand()) % (TEST_N * 13);
    for (int i = 0; i < FIND_N; i++)
        find[i] = data[rand() * rand() % TEST_N];

    system("cls");
    printf(">>> Comparing time and memory of adding %d and searching for %d int numbers\n\n", TEST_N, FIND_N);
    printf("|---------------|---------------|---------------|---------------|---------------|\n");
    printf("| Struct \t| Time add \t| Memory \t| Time find \t| Find cmp \t|\n");
    printf("|---------------|---------------|---------------|---------------|---------------|\n");

    stat[0] = test_tree_add(data, find);
    printf("| Tree \t\t| %6.2lf ms.\t| %8.3lf Kb \t| %6.3lf ms. \t| %8ld cmp \t|\n",
           stat[0].add_time, stat[0].add_mem, stat[0].find_time, stat[0].find_cmp);

    stat[1] = test_avl_tree_add(data, find);
    printf("| AVL Tree \t| %6.2lf ms.\t| %8.3lf Kb \t| %6.3lf ms. \t| %8ld cmp \t|\n",
           stat[1].add_time, stat[1].add_mem, stat[1].find_time, stat[1].find_cmp);

    stat[2] = test_hash_add(TEST_N, 100, data, find);
    printf("| Hash table \t| %6.2lf ms.\t| %8.3lf Kb \t| %6.3lf ms. \t| %8ld cmp \t| (resize)\n",
           stat[2].add_time, stat[2].add_mem, stat[2].find_time, stat[2].find_cmp);

    stat[3] = test_hash_add(TEST_N, TEST_N, data, find);
    printf("| Hash table \t| %6.2lf ms.\t| %8.3lf Kb \t| %6.3lf ms. \t| %8ld cmp \t| (full size)\n",
           stat[3].add_time, stat[3].add_mem, stat[3].find_time, stat[3].find_cmp);

    stat[4] = test_file_add(TEST_N, data, find);
    printf("| File \t\t| %6.2lf ms.\t| %8.3lf Kb \t| %6.2lf ms. \t| %8ld cmp\t|\n",
           stat[4].add_time, stat[4].add_mem, stat[4].find_time, stat[4].find_cmp);
    printf("|---------------|---------------|---------------|---------------|---------------|\n");
    delete_array(&data);
}
