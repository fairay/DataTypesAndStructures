#include "head.h"

int list_empty(list_t list)
{
    return (list == NULL);
}

void clean_list(list_t* list)
{
    list_t temp = *list;
    while (!list_empty(*list))
    {
        temp = (*list)->next;
        free(*list);
        *list = temp;
    }
}

int list_len(list_t list)
{
    int len = 0;
    list_t temp = list;

    while (!list_empty(temp))
    {
        len++;
        temp = temp->next;
    }
    return len;
}


void push_free(free_mem_t *stack, cell_t* new_cell)
{
    new_cell->next = *stack;
    *stack = new_cell;
}

cell_t* pop_free(free_mem_t *stack)
{
    cell_t *pop_cell;
    if (list_empty(*stack))
        (pop_cell) = (cell_t*)malloc(sizeof(cell_t));
    else
    {
        (pop_cell) = (*stack);
        (*stack) = (*stack)->next;
    }
    return pop_cell;
}

void print_free(free_mem_t stack)
{
    list_t temp = stack;
    if (list_empty(stack))
        puts("Free memory space is empty\n");
    else
    {
        puts("Free memory space:\n");
        put_stop();
        while (!list_empty(temp))
        {
            printf("| %16p | %9.2f | %16p |\n", (void*)temp, temp->time, (void*)temp->next);
            temp = temp->next;
        }
        put_sbot();
    }
}
