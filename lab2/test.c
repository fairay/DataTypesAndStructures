#include "head.h"

void copy_table(sub_t to[], sub_t from[], int n)
{
    for (int i = 0; i < n; i++)
        to[i] = from[i];
}

void shuffle_table(sub_t table[], int n)
{
    sub_t temp;
    int swap_pos;

    for (int i = 0; i < n; i++)
    {
        swap_pos = rand() % n;

        temp = table[i];
        table[i] = table[swap_pos];
        table[swap_pos] = temp;
    }
}

void test_key_bubble(sub_t sourse_table[], int n, double *time, long int *mem)
{
    sub_t table[n];
    key_t key_table[n];
    clock_t sort_t, shuf_t;

    copy_table(table, sourse_table, n);

    shuf_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
    {
        shuffle_table(table, n);
        create_keytable(table, key_table, n);
    }
    shuf_t = clock() - shuf_t;

    sort_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
    {
        shuffle_table(table, n);
        create_keytable(table, key_table, n);
        sort_keytable_bubble(key_table, n);
    }
    sort_t = clock() - sort_t;

    printf("Bubble sort with key table takes: \n");
    printf("%lf miliseconds\n", ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000));
    printf("%ld bytes\n", (long int)(sizeof(table) + sizeof(key_table)));

    (*time) = ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000);
    (*mem) = (long int)(sizeof(table) + sizeof(key_table));
}

void test_key_qsort(sub_t sourse_table[], int n, double *time, long int *mem)
{
    sub_t table[n];
    key_t key_table[n];
    clock_t sort_t, shuf_t;

    copy_table(table, sourse_table, n);

    shuf_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
    {
        shuffle_table(table, n);
        create_keytable(table, key_table, n);
    }
    shuf_t = clock() - shuf_t;

    sort_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
    {
        shuffle_table(table, n);
        create_keytable(table, key_table, n);
        sort_keytable_qsort(key_table, 0, n - 1);
    }
    sort_t = clock() - sort_t;

    printf("Quicksort with key table takes: \n");
    printf("%lf miliseconds\n", ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000));
    printf("%ld bytes\n", (long int)(sizeof(table) + sizeof(key_table)));

    (*time) = ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000);
    (*mem) = (long int)(sizeof(table) + sizeof(key_table));
}

void test_table_bubble(sub_t sourse_table[], int n, double *time, long int *mem)
{
    sub_t table[n];
    clock_t sort_t, shuf_t;

    copy_table(table, sourse_table, n);

    shuf_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
        shuffle_table(table, n);
    shuf_t = clock() - shuf_t;

    sort_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
    {
        shuffle_table(table, n);
        sort_table_bubble(table, n);
    }
    sort_t = clock() - sort_t;

    printf("Bubble sort with table takes: \n");
    printf("%lf miliseconds\n", ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000));
    printf("%ld bytes\n", (long int)(sizeof(table)));

    (*time) = ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000);
    (*mem) = (long int)(sizeof(table));
}

void test_table_qsort(sub_t sourse_table[], int n, double *time, long int *mem)
{
    sub_t table[n];
    clock_t sort_t, shuf_t;

    copy_table(table, sourse_table, n);

    shuf_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
        shuffle_table(table, n);
    shuf_t = clock() - shuf_t;

    sort_t = clock();
    for (int i = 0; i < TEST_REPEATS; i++)
    {
        shuffle_table(table, n);
        sort_table_qsort(table, 0, n - 1);
    }
    sort_t = clock() - sort_t;

    printf("Quicksort with table takes: \n");
    printf("%lf miliseconds\n", ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000));
    printf("%ld bytes\n", (long int)(sizeof(table)));

    (*time) = ((double)(sort_t - shuf_t)) / (CLK_TCK * TEST_REPEATS / 1000);
    (*mem) = (long int)(sizeof(table));
}
