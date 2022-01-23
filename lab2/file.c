#include "head.h"


int check_validity(char file_name[])
{
    FILE* f = fopen(file_name, "r");
    if (!f)
        return INVALID_FILE;
    fclose(f);
    return OK;
}

int scan_file(char file_name[], sub_t table[], int* table_size)
{
    if (check_validity(file_name) != OK)
        return INVALID_FILE;

    int i = 0;
    FILE* f = fopen(file_name, "r");

    while (!feof(f))
    {
        fscanf(f, "%s", table[i].surname);
        fscanf(f, "%s", table[i].name);
        fscanf(f, "%s", table[i].phone);
        fscanf(f, "%s", table[i].address);
        fscanf(f, "%s", table[i].status);
        if (strcmp(table[i].status, PERSONAL) == 0)
        {
            fscanf(f, "%husd", &table[i].info.pers.day);
            fscanf(f, "%husd", &table[i].info.pers.month);
            fscanf(f, "%husd", &table[i].info.pers.year);
        }
        else
        {
            fscanf(f, "%s", table[i].info.off.post);
            fscanf(f, "%s", table[i].info.off.org);
        }
        i++;
    }
    fclose(f);
    (*table_size) = i;
    return OK;
}

int write_file(char file_name[], sub_t table[], int table_size)
{
    FILE* f = fopen(file_name, "w");
    if (!f)
        return INVALID_FILE;

    for (int i = 0; i < table_size; i++)
    {
        fprintf(f, "%s ", table[i].surname);
        fprintf(f, "%s ", table[i].name);
        fprintf(f, "%s ", table[i].phone);
        fprintf(f, "%s ", table[i].address);
        fprintf(f, "%s ", table[i].status);
        if (strcmp(table[i].status, PERSONAL) == 0)
        {
            fprintf(f, "%hu ", table[i].info.pers.day);
            fprintf(f, "%hu ", table[i].info.pers.month);
            fprintf(f, "%hu", table[i].info.pers.year);
        }
        else
        {
            fprintf(f, "%s ", table[i].info.off.post);
            fprintf(f, "%s", table[i].info.off.org);
        }

        if (i != table_size - 1)
            fprintf(f, "\n");
    }

    fclose(f);
    return OK;
}
