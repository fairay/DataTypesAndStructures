#include "head.h"

void print_menu(void)
{
    printf("\nTest actions:\n");
    printf("0  | Exit\n");
    printf("10 | Push list stack\n");
    printf("11 | Pop list stack\n");
    printf("20 | Push array stack\n");
    printf("21 | Pop array stack\n");
    printf("30 | Compare stacks\n");
}

void test_mode(void)
{
    int code = WRONG_INPUT;
    int sc;
    char trash[10];
    pos_t pos;

    free_mem_t free_mem = NULL;
    list_st_t list = create_list(&free_mem);
    arr_st_t arr = create_arr_st();

    print_menu();

    while (code != EXIT)
    {
        printf("\n-------------------\n");
        printf("Chouse action: ");
        sc = scanf("%d", &code);
        if (sc != 1)
        {
            gets(trash);
            code = WRONG_INPUT;
        }
        printf("-------------------\n\n");

        switch (code)
        {
            case PUSH_LIST:
                printf("Input position [i, j]: ");
                sc = scanf("%d%d", &pos.i, &pos.j);
                if (sc != 2)
                {
                    show_error_message(WRONG_FORMAT);
                    break;
                }
                push_list(&list, pos);
                print_list(list);
                printf("\n");
                print_free(free_mem);
                break;

            case POP_LIST:
                pos = pop_list(&list);
                if (pos.i == -1)
                    printf("No poped element\n");
                else
                    printf("Poped element: [%d, %d]\n", pos.i, pos.j);
                print_list(list);
                printf("\n");
                print_free(free_mem);
                break;

            case PUSH_ARR:
                printf("Input position [i, j]: ");
                sc = scanf("%d%d", &pos.i, &pos.j);
                if (sc != 2)
                {
                    show_error_message(WRONG_FORMAT);
                    break;
                }
                push_arr(&arr, pos);
                print_arr(arr);
                break;

            case POP_ARR:
                pos = pop_arr(&arr);
                if (pos.i == -1)
                    printf("No poped element\n");
                else
                    printf("Poped element: [%d, %d]\n", pos.i, pos.j);
                print_arr(arr);
                break;

                case EXIT:
                    printf("Exit...\n");
                    break;

                case COMPARE:
                    compare(TEST_SIZE);
                    break;

                default:
                    show_error_message(WRONG_FORMAT);
                    break;
        }
    }

    delete_list(&list);
    clean_stack(&free_mem);

    delete_arr_st(&arr);
}


void test_list(int size, double *time, long int *memory)
{
    clock_t t;
    free_mem_t free_mem = NULL;
    list_st_t list = create_list(&free_mem);
    pos_t pos = { 100, 100 };

    printf("Test push and pop on list: \n");
    t = clock();
    for (int i = 0; i < size; i++)
        push_list(&list, pos);

    for (int i = 0; i < size; i++)
        pos = pop_list(&list);
    t = clock() - t;

    (*time) = ((double)(t)) / ((double)CLK_TCK * size / 1000 / 1000 / 1000);
    (*memory) = (long int)(sizeof(cell_t) * size / 1024);

    printf("%lf nanoseconds\n", *time);
    printf("%ld Kbytes\n", *memory);

    delete_list(&list);
    clean_stack(&free_mem);
}

void test_list_free(int size, double *time, long int *memory)
{
    clock_t t;
    free_mem_t free_mem = NULL;
    list_st_t list = create_list(&free_mem);
    pos_t pos = { 100, 100 };

    printf("Test push and pop on list with full free memory: \n");

    for (int i = 0; i < size; i++)
        push_list(&list, pos);

    t = clock();
    for (int i = 0; i < size; i++)
        pos = pop_list(&list);
    for (int i = 0; i < size; i++)
        push_list(&list, pos);
    t = clock() - t;

    (*time) = ((double)(t)) / ((double)CLK_TCK * size / 1000 / 1000 / 1000);
    (*memory) = (long int)(sizeof(cell_t) * size / 1024);

    printf("%lf nanoseconds\n", *time);
    printf("%ld Kbytes\n", *memory);

    delete_list(&list);
    clean_stack(&free_mem);
}

void test_array(int size, double *time, long int *memory)
{
    clock_t t;
    int n;
    arr_st_t arr = create_arr_st();
    pos_t pos = { 100, 100 };

    printf("Test push and pop on list: \n");
    t = clock();
    for (int i = 0; i < size; i++)
        push_arr(&arr, pos);
    n = arr.size;
    for (int i = 0; i < size; i++)
        pos = pop_arr(&arr);
    t = clock() - t;

    (*time) = ((double)(t)) / ((double)CLK_TCK * size / 1000 / 1000 / 1000);
    (*memory) = (long int)(sizeof(pos_t) * n / 1024);

    printf("%lf nanoseconds\n", *time);
    printf("%ld Kbytes\n", *memory);

    delete_arr_st(&arr);
}

void compare(int size)
{
    double time[3];
    long int memory[3];

    test_list(TEST_SIZE, &time[0], &memory[0]);
    test_list_free(TEST_SIZE, &time[1], &memory[1]);
    test_array(TEST_SIZE, &time[2], &memory[2]);


    printf("\n\nTest of time and memory at push and pop of %d elements\n", TEST_SIZE);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("Stack \t List \t\t List+free \t Array\n");
    printf("Time \t %6lf ns.\t %6lf ns.\t %6lf ns.\n", time[0], time[1], time[2]);
    printf("Memory \t %6ld Kb\t %6ld Kb\t %6ld Kb\n", memory[0], memory[1], memory[2]);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

}
