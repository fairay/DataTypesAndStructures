#include "head.h"

void print_table_head(void)
{
    printf("|---|---------------------|---------------------|\
-----------------|---------------------|----------|\
----------------------------------------\n");
    printf("| # |%20s |%20s |%16s |%20s |%9s | %-20s  \n", \
           "Surname", "Name", "Phone", "Address", "Status", "Info");
    printf("|---|---------------------|---------------------|\
-----------------|---------------------|----------|\
----------------------------------------\n");
}

void print_table_end(void)
{
    printf("|===|=====================|=====================|\
=================|=====================|==========|\
========================================\n");
}

void print_keytable_head(void)
{
    printf("|---|---------|---------------------|\n");
    printf("| # |%8s |%20s |\n", "Index", "Key");
    printf("|---|---------|---------------------|\n");
}

void print_keytable_end(void)
{
    printf("|===|=========|=====================|\n");
}

void exit_mode(void)
{
    puts("Exit the program...");
}

int change_file_mode(char old_name[])
{
    int sc;
    char new_name[MAX_LEN_FILE];

    printf("Input new file name (with no spaces): ");
    sc = scanf("%s", new_name);
    if (sc != 1)
        return WRONG_FORMAT;

    sc = check_validity(new_name);
    if (sc != OK)
        return sc;

    strcpy(old_name, new_name);
    printf("File successfully changed on: %s", old_name);

    return OK;
}

void print_table_mode(sub_t table[], int table_size)
{
    if (table_size == 0)
        printf("Tabel is empty\n");
    else
    {
        print_table_head();
        for (int i = 0; i < table_size; i++)
        {
            printf("|%2d |", i + 1);
            print_sub(table[i]);
        }
        print_table_end();
    }
}

void print_table_key(sub_t table[], key_t key_table[], int table_size)
{
    {
        if (table_size == 0)
            printf("Tabel is empty\n");
        else
        {
            print_table_head();
            for (int i = 0; i < table_size; i++)
            {
                printf("|%2d |", key_table[i].ind + 1);
                print_sub(table[key_table[i].ind]);
            }
            print_table_end();
        }
    }
}

void print_keytable_mode(key_t key_table[], int table_size)
{
    if (table_size == 0)
        printf("Keytabel is empty\n");
    else
    {
        print_keytable_head();
        for (int i = 0; i < table_size; i++)
        {
            printf("|%2d |", i + 1);
            printf("%8d |", key_table[i].ind + 1);
            printf("%20s |", key_table[i].key);
            printf("\n");
        }
        print_keytable_end();
    }
}

int add_entry_mode(sub_t table[], int* table_size)
{
    sub_t input_entry;
    int code;

    if (*table_size >= MAX_TABLE_SIZE)
        return TABLE_OVERFLOW;

    printf("Input new subscriber info:\n");
    code = scan_sub(&input_entry);
    if (code == OK)
    {
        table[*table_size] = input_entry;
        *(table_size) += 1;
    }

    return code;
}

/*
int delete_entry_mode(sub_t table[], int* table_size)
{
    int pos, sc;
    char trash[] = "\0";
    printf("Input the index of the deleting entry: ");
    sc = scanf("%d", &pos);

    if (sc != 1)
    {
        gets(trash);
        return WRONG_FORMAT;
    }
    else if ((pos > *table_size) || (pos <= 0))
        return WRONG_POSITION;

    pos--;
    for (int i = pos; i < *table_size - 1; i++)
        table[i] = table[i + 1];
    *table_size -= 1;
    return OK;
}
*/

int delete_entry_mode(sub_t table[], int* table_size)
{
    int pos, sc;
    int i = 0;
    char status[20];
    char trash[] = "\0";
    char key_str[50];
    int key_int;
    int type = STR_KEY;

    int count = 0;

    int (*is_del)();

    printf("Chose the key of deletion (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s):\n",
           INDEX, SURNAME, NAME, PHONE, ADDRESS, STATUS, POST, ORGANISATION,
           YEAR, MONTH, DAY);
    sc = scanf("%s", status);
    if (sc != 1)
    {
        gets(trash);
        return WRONG_FORMAT;
    }

    if (!strcmp(status, INDEX))
    {
        printf("Input the index of the deleting entry: ");
        sc = scanf("%d", &pos);

        if (sc != 1)
        {
            gets(trash);
            return WRONG_FORMAT;
        }
        else if ((pos > *table_size) || (pos <= 0))
            return WRONG_POSITION;

        pos--;
        shift_table_l(table, pos, *table_size);
        *table_size -= 1;
        return OK;
    }

    else if (!strcmp(status, YEAR))
    {
        type = INT_KEY;
        is_del = is_del_year;
    }
    else if (!strcmp(status, MONTH))
    {
        type = INT_KEY;
        is_del = is_del_month;
    }
    else if (!strcmp(status, DAY))
    {
        type = INT_KEY;
        is_del = is_del_day;
    }

    else if (!strcmp(status, SURNAME))
        is_del = is_del_surname;
    else if (!strcmp(status, NAME))
        is_del = is_del_name;
    else if (!strcmp(status, PHONE))
        is_del = is_del_phone;
    else if (!strcmp(status, ADDRESS))
        is_del = is_del_address;
    else if (!strcmp(status, STATUS))
        is_del = is_del_status;
    else if (!strcmp(status, POST))
        is_del = is_del_post;
    else if (!strcmp(status, ORGANISATION))
        is_del = is_del_org;
    else
        return WRONG_FORMAT;

    printf("Input deletion value: ");
    if (type == STR_KEY)
        sc = scanf("%s", key_str);
    else
        sc = scanf("%d", &key_int);
    if (sc != 1)
    {
        gets(trash);
        return WRONG_FORMAT;
    }

    while (i < *table_size)
    {
        if (((type == STR_KEY) && (is_del(table[i], key_str))) ||
            ((type == INT_KEY) && (is_del(table[i], key_int))))
        {
            shift_table_l(table, i, *table_size);
            *table_size -= 1;
            count++;
        }
        else
            i++;
    }
    printf("Delete %d entrys\n", count);
    return OK;
}

int print_bd_friends(sub_t table[], int table_size)
{
    int sc = 0;
    int count = 0;
    int i;
    int is_bd[table_size];
    dob_t today;
    int days, temp;
    int year = 365;


    printf("Input current date (DD MM YYYY): ");
    sc += scanf("%husd", &today.day);
    sc += scanf("%husd", &today.month);
    sc += scanf("%husd", &today.year);
    if (sc != 3)
        return WRONG_FORMAT;
    else if (check_dob_validity(today) != OK)
        return WRONG_DOB;

    days = convert_days(today, is_leap(today.year));
    if (is_leap(today.year))
        year++;

    for (i = 0; i < table_size; i++)
    {
        if (strcmp(table[i].status, PERSONAL) == 0)
        {
            temp = convert_days(table[i].info.pers, is_leap(today.year));
            is_bd[i] = (((days + 7) % year - 7 < (temp + 7) % year - 7) &&
                        ((days + 7) % year >= (temp + 7) % year - 7));
            if (is_bd[i])
                count++;
        }
        else
            is_bd[i] = 0;
    }

    if (!count)
    {
        printf("No friends found\n");
        return OK;
    }

    print_table_head();
    for (i = 0; i < table_size; i++)
    {
        if (is_bd[i])
        {
            printf("|%2d |", i + 1);
            print_sub(table[i]);
        }
    }
    print_table_end();
    return OK;
}

int efficiency_test_mode(sub_t table[], int n)
{
    if (n == 0)
        return EMPTY_TABLE;


    double time[4];
    long int memory[4];

    test_key_bubble(table, n, &time[0], &memory[0]);
    test_key_qsort(table, n, &time[1], &memory[1]);
    test_table_bubble(table, n, &time[2], &memory[2]);
    test_table_qsort(table, n, &time[3], &memory[3]);

    printf("\nComparing time in ms.: \n");
    printf("\t\t With key\t With table\n");
    printf("Bubble sort\t %6f ms.\t %6f ms.\n", time[0], time[2]);
    printf("Quick sort\t %6f ms.\t %6f ms.\n", time[1], time[3]);

    printf("\nComparing time in %%:\n");
    printf("\t\t With key\t With table\n");
    printf("Bubble sort\t %6f %%\t %6f %%\n", 100 * time[0] / time[2], 100 * time[2] / time[2]);
    printf("Quick sort\t %6f %%\t %6f %%\n", 100 * time[1] / time[2], 100 * time[3] / time[2]);

    printf("\nComparing bubble sort with key and with table:\n");
    printf("Time: -%6f %%\n", 100 - 100 * time[0] / time[2]);
    printf("Memory: +%6f %%\n", 100.0 - 100 * (double)memory[2] / memory[0]);

    printf("\nComparing quick sort with key and with table:\n");
    printf("Time: -%6f %%\n", 100 - 100 * time[1] / time[3]);
    printf("Memory: +%6f %%\n", 100.0 - 100 * (double)memory[3] / memory[1]);

    printf("\nComparing quick sort and bubble sort:\n");
    printf("Time: -%6f %%\n", 100 - 100 * time[1] / time[0]);
    printf("Memory: +%6f %%\n", 100.0 - 100 * (double)memory[1] / memory[0]);
    return OK;
}

void wrong_mode(void)
{
    puts("Unknown or incorrect action name");
}

