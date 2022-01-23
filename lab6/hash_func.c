#include "head.h"

void put_bot(void)
{
    printf("|-----|-----------|------|\n");
}

void put_top(void)
{
    put_bot();
    printf("| %3s | %9s | %3s |\n", "#", "Value", "Hash");
    put_bot();
}


int min_prime(int a)
{
    int is_prime = 0;
    int i = 2;
    while (!is_prime)
    {
        is_prime = 1;
        i = 2;
        while (i * i <= a)
        {
            if (a % i)
                i++;
            else
            {
                is_prime = 0;
                break;
            }
        }
        if (!is_prime)
            a++;
    }
    return a;
}

int hash_f0(int size, int num)
{
    return abs(num % size);
}

int hash_f1(int size, int num)
{
    int hash;
    num *= num;
    hash = num << 24;
    hash ^= num >> 24;
    num = num >> 8;
    return abs((num ^ hash) % size);
}

int hash_f2(int size, int num)
{
    return abs(size * ((GOLDEN_RATIO * num) - (int)(GOLDEN_RATIO * num)));
}

int hash_f3(int size, int num)
{
    num += num << 3;
    num ^= num >> 11;
    num += num << 15;
    return abs(num % size);
}

int hash_f4(int size, int num)
{
    num *= num;
    num = num >> 11;
    return abs(num % size);
}

static int (*hash_f[HASH_N])(int, int) = { hash_f0, hash_f1, hash_f2, hash_f3 };


/// Array CDIO
int create_array(array_t *arr, int size)
{
    (*arr) = (array_t)calloc(size, sizeof(int));
    if (*arr)
        return OK;
    else
        return ALLOC_FAIL;
}

void delete_array(array_t *arr)
{
    free(*arr);
    (*arr) = NULL;
}

/// Hash table CDIO
int create_table(table_t* table, int size)
{
    int code;
    table->size = min_prime(size * 1.2 + 1);
    table->count = 0;
    table->hash_n = 0;
    table->func = hash_f[table->hash_n];

    code = create_array(&table->arr, table->size);
    if (code)   return code;
    code = create_array(&table->is_busy, table->size);
    if (code)   return code;

    return OK;
}

int finput_table(char file_name[], table_t* table)
{
    int sc, number, size = 0;
    FILE *f = fopen(file_name, "r");
    if (!f)     return WRONG_FILE;

    sc = fscanf(f, "%d", &number);
    while (sc == 1)
    {
        size++;
        sc = fscanf(f, "%d", &number);
    }
    if (sc != EOF)  return WRONG_FORMAT;

    fclose(f);
    f = fopen(file_name, "r");
    if (!f)     return WRONG_FILE;

    sc = create_table(table, size);
    if (sc)     return sc;

    for (int i = 0; i < size; i++)
    {
        fscanf(f, "%d", &number);
        add_table(table, number);
    }
    fclose(f);
    return OK;
}

void print_table(table_t table)
{
    put_top();
    for (int i = 0; i < table.size; i++)
    {
        if (table.is_busy[i])
            printf("| %3d | %9d | %4d |\n", i, table.arr[i],
                   table.func(table.size, table.arr[i]));
        else
            printf("| %3d |    ---    |  --  |\n", i);
    }
    put_bot();
}

void delete_table(table_t* table)
{
    delete_array(&table->arr);
    delete_array(&table->is_busy);
    table->size = 0;
    table->count = 0;
    return;
}

int resize_table(table_t* table)
{
    table_t new_table;
    int code = create_table(&new_table, table->size * 1.2);
    if (code)   return code;

    for (int i = 0; i < table->size; i++)
        if (table->is_busy[i])
            add_table(&new_table, table->arr[i]);
    delete_table(table);
    (*table) = new_table;
    return OK;
}

int restruct_table(table_t* table)
{
    table_t new_table;
    int code = create_table(&new_table, table->size / 1.2 - 1);
    if (code)   return code;
    new_table.hash_n = (table->hash_n + 1) % HASH_N;
    new_table.func = hash_f[new_table.hash_n];

    for (int i = 0; i < table->size; i++)
        if (table->is_busy[i])
            add_table(&new_table, table->arr[i]);
    delete_table(table);
    (*table) = new_table;
    return OK;
}


int add_table(table_t* table, int val)
{
    if (table->count * 1.1 >= table->size - 1)
        resize_table(table);

    int pos = table->func(table->size, val);
    while (table->is_busy[pos])
    {
        if (table->arr[pos] == val)
            return OK;
        pos = (pos + 1) % table->size;
    }

    table->arr[pos] = val;
    table->is_busy[pos] = 1;
    table->count++;

    return OK;
}

int del_table(table_t* table, int val)
{
    if (!table->count)
        return 0;

    int i = 0, del_pos =- 1, up_border, temp_hash;
    int pos = table->func(table->size, val);
    up_border = pos - 1;
    while (table->is_busy[pos] && (i < table->size))
    {
        if (table->arr[pos] == val)
        {
            table->arr[pos] = 0;
            table->is_busy[pos] = 0;
            table->count--;
            del_pos = pos;
            break;
        }
        pos = (pos + 1) % table->size;
        i++;
    }

    print_table(*table);

    if (del_pos == -1)
        return OK;

    //  Определение верхней границы
    while (table->is_busy[up_border])
        up_border = (table->size + up_border - 1) % table->size;
    up_border = (up_border + 1) % table->size;

    pos = (del_pos + 1) % table->size;
    printf("up - %d, del_pos - %d\n", up_border, del_pos);
    while (table->is_busy[pos])
    {
        temp_hash = table->func(table->size, table->arr[pos]);
        if (((up_border <= del_pos) && (up_border <= temp_hash && temp_hash <= del_pos)) ||
            ((up_border > del_pos) && (up_border <= temp_hash || temp_hash <= del_pos)))
        {
            table->arr[del_pos] = table->arr[pos];
            table->is_busy[del_pos] = 1;

            table->arr[pos] = 0;
            table->is_busy[pos] = 0;
            del_pos = pos;
        }
        pos = (pos + 1) % table->size;
    }

    return OK;
}

int find_table(table_t* table, int val)
{
    int i = 0;
    int pos = table->func(table->size, val);
    while (table->is_busy[pos] && (i < table->size))
    {
        if (table->arr[pos] == val)
            break;
        pos = (pos + 1) % table->size;
        i++;
    }
    if (table->is_busy[pos] && (i < table->size))
        return pos;
    else
        return -1;
}

int count_find_table(table_t* table, int val)
{
    int i = 1;
    int pos = table->func(table->size, val);
    while (table->is_busy[pos] && (i <= table->size))
    {
        if (table->arr[pos] == val)
            break;
        pos = (pos + 1) % table->size;
        i++;
    }
    return i;
}

float table_aver_count(table_t* table)
{
    int aver = 0;
    for (int i = 0; i < table->size; i++)
        if (table->is_busy[i])
            aver += count_find_table(table, table->arr[i]);
    return (float)aver / table->count;
}
