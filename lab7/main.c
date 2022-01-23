#include "head.h"

/*
 * В системе двусторонних дорог за проезд
 * каждой дороги взимается некоторая пошлина.
 * Найти путь из города A в город B с минимальной величиной S + P, где
 * S - сумма длин дорог пути
 * P - сумма пошлин проезжаемых дорог
 */

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

        case EMPTY_FILE:
            printf("empty file");
            break;

        case WRONG_FILE:
            printf("wrong file");
            break;

        case NO_CITY:
            printf("city are not in graph");
            break;

        case DOUBLE_EDGE:
            printf("2+ edges between two citys");
            break;

        case NEGATIVE_VAL:
            printf("negtive value");
            break;
    }
    printf("\n");
    return code;
}


long int factorial_tail(int n, long int res)
{
    if (n == 1)
        return res;
    return factorial_tail(n - 1, res * n);
}

long int factorial_inter(int n)
{
    if (n <= 0)
        return -1;

    return factorial_tail(n, 1);
}



list_t find_middle(list_t list)
{
    list_t temp = list;
    list_t mid = list;

    while (temp)
    {
        temp = temp->next;
        if (!temp)
            return mid;

        temp = temp->next;
        if (!temp)
            return mid;

        mid = mid->next;
    }

    return mid;
}


int main(void)
{
    unsigned int a = 8, b = 3;
    printf("%d %d %d %ud\n", a&b, 8|3, 8^3, (unsigned int)~a);
    int code, sc = 0;
    path_t path;
    char city_a[MAX_STR + 1];
    char city_b[MAX_STR + 1];
    char file_name[MAX_STR + 1] = "";
    int node_a, node_b;

    lgraph_t graph = create_lgraph();

    printf("Input file name (0 for data.txt): ");
    sc = scanf("%s", file_name);
    if (sc != 1)
        return err_message(WRONG_FORMAT);
    if (!strcmp(file_name, "0"))
        strcpy(file_name, IN_FILE);

    code = finput_lgraph(file_name, &graph);
    if (code != OK)
    {
        delete_lgraph(&graph);
        return err_message(code);
    }

    sc = 0;
    printf("\nChouse the cities to find path:\n");
    printf("City A: ");
    sc += scanf("%s", city_a);
    node_a = find_node(&graph, city_a);
    if (node_a == -1)
    {
        delete_lgraph(&graph);
        return err_message(NO_CITY);
    }

    printf("City B: ");
    sc += scanf("%s", city_b);
    node_b = find_node(&graph, city_b);
    if (node_b == -1)
    {
        delete_lgraph(&graph);
        return err_message(NO_CITY);
    }

    if (sc != 2)
    {
        delete_lgraph(&graph);
        return err_message(WRONG_FORMAT);
    }

    path = bfs(&graph, node_a, node_b);
    print_path(&graph, path);

    foutput_lgraph(&graph, path);
    delete_lgraph(&graph);
    delete_path(&path);
    return OK;
}
