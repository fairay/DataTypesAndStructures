#include "head.h"


void create_keytable(sub_t table[], key_t key_table[], int n)
{
    for (int i = 0; i < n; i++)
    {
        key_table[i].ind = i;
        strcpy(key_table[i].key, table[i].surname);
    }
}

void swap_keytable(key_t key_table[], int i, int j)
{
    key_t temp;
    temp = key_table[j];
    key_table[j] = key_table[i];
    key_table[i] = temp;

}

int key_split(key_t key_table[], int l, int r)
{
    int p;
    int split;
    p = r;
    split = l;
    for (int i = l; i < r; i++)
    {
        if (strcmp(key_table[i].key, key_table[p].key) < 0)
        {
            swap_keytable(key_table, i, split);
            split++;
        }
    }
    swap_keytable(key_table, p, split);
    return (split);
}

int table_split(sub_t table[], int l, int r)
{
    sub_t temp_sub;
    int p;
    int split;
    p = r;
    split = l;
    for (int i = l; i < r; i++)
    {
        if (strcmp(table[i].surname, table[p].surname) < 0)
        {
            temp_sub = table[i];
            table[i] = table[split];
            table[split] = temp_sub;
            split++;
        }
    }
    temp_sub = table[p];
    table[p] = table[split];
    table[split] = temp_sub;
    return (split);
}



void sort_keytable_bubble(key_t key_table[], int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (strcmp(key_table[j].key, key_table[j + 1].key) > 0)
                swap_keytable(key_table, j, j + 1);
}

void sort_table_bubble(sub_t table[], int n)
{
    int i, j;
    sub_t temp_sub;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (strcmp(table[j].surname, table[j + 1].surname) > 0)
            {
                temp_sub = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp_sub;
            }
}

void sort_keytable_qsort(key_t key_table[], int l, int r)
{
    int p;
    if (r - l > 0)
    {
        p = key_split(key_table, l, r);
        sort_keytable_qsort(key_table, l, p - 1);
        sort_keytable_qsort(key_table, p + 1, r);
    }
}

void sort_table_qsort(sub_t table[], int l, int r)
{
    int p;
    if (r - l > 0)
    {
        p = table_split(table, l, r);
        sort_table_qsort(table, l, p - 1);
        sort_table_qsort(table, p + 1, r);
    }
}
