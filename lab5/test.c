#include "head.h"

void print_menu(void)
{
    printf(">>> Test actions:\n");
    printf("0  | Exit\n");
    printf("10 | Push list queue\n");
    printf("11 | Pop list queue\n");
    printf("20 | Push array queue\n");
    printf("21 | Pop array queue\n");
    printf("30 | Compare queues\n");
}

void test_mode(void)
{
    system("cls");
    int code = WRONG_INPUT;
    int sc;
    char trash[10];
    float time;

    free_mem_t free_mem = NULL;
    lqueue_t lque = create_lque(&free_mem);
    aqueue_t aque = create_aque();

    print_menu();

    while (code != EXIT)
    {
        printf("\n-------------------\n");
        printf(">>> Chouse action: ");
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
                printf("Input time: ");
                sc = scanf("%f", &time);
                if (sc != 1 || time < 0)
                {
                    show_error_message(WRONG_FORMAT);
                    break;
                }
                push_lque(&lque, time);
                print_lque(lque);
                printf("\n");
                print_free(free_mem);
                break;

            case POP_LIST:
                time = pop_lque(&lque);
                if (fabs(time + 1) < EPS)
                    printf("No poped element\n");
                else
                    printf("Poped time: %f\n", time);
                print_lque(lque);
                printf("\n");
                print_free(free_mem);
                break;

            case PUSH_ARR:
                printf("Input time: ");
                sc = scanf("%f", &time);
                if (sc != 1 || time < 0)
                {
                    show_error_message(WRONG_FORMAT);
                    break;
                }
                push_aque(&aque, time);
                print_aque(aque);
                break;

            case POP_ARR:
                time = pop_aque(&aque);
                if (fabs(time + 1) < EPS)
                    printf("No poped element\n");
                else
                    printf("Poped element: %f\n", time);
                print_aque(aque);
                break;

            case EXIT:
                printf("Exit...\n");
                break;

            case COMPARE:
                compare();
                break;

            default:
                show_error_message(WRONG_FORMAT);
                break;
        }
    }

    delete_lque(&lque);
    delete_aque(&aque);
    clean_list(&free_mem);
}

void compare(void)
{
    free_mem_t free_mem = NULL;
    double time_list = 0, time_arr = 0;
    long int memory_list = 0, memory_arr = 0;
    stats_t temp;

    // options_t opt = test_options();
    options_t opt = default_options();
    opt.max_1 = TEST_SIZE;
    opt.step = TEST_SIZE + 1;

    for (int i = 0; i < TEST_REPEAT; i++)
    {
        system("cls");
        print_options(opt);
        printf("Loading %.2f %%...", (float)(100 * i) / (TEST_REPEAT * 2));
        temp = sv_work_list(opt, &free_mem);
        time_list += temp.time;
        memory_list += temp.memory;
        clean_list(&free_mem);
        // print_free(free_mem);
    }

    for (int i = 0; i < TEST_REPEAT; i++)
    {
        system("cls");
        printf("Loading %.2f %%...", (float)(100 * i) / (TEST_REPEAT * 2) + 50);
        temp = sv_work_arr(opt);
        time_arr += temp.time;
        memory_arr += temp.memory;
    }

    system("cls");

    time_list /= TEST_REPEAT;
    time_arr /= TEST_REPEAT;
    memory_list /= TEST_REPEAT;
    memory_arr /= TEST_REPEAT;

    printf("\n\nTest of time and memory at SM work on %d requests from queue 1\n", TEST_SIZE);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("Stack \t List \t \t Array \t\t Advantage\n");
    printf("Time \t %.3lf ms.\t %.3lf ms. \t %.1lf times \n", time_list, time_arr, time_list / time_arr);
    printf("Memory \t %6ld b\t %6ld b \t %.1lf times \n", memory_list, memory_arr, (double) memory_list / memory_arr);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

}
