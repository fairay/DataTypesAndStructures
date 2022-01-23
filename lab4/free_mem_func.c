#include "head.h"

void push_free(free_mem_t *stack, cell_t* new_cell)
{
    new_cell->next = *stack;
    *stack = new_cell;
}

cell_t* pop_free(free_mem_t *stack)
{
    cell_t *pop_cell;
    if (s_empty(*stack))
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
    if (s_empty(stack))
        puts("Free memory space is empty\n");
    else
    {
        puts("Free memory space:\n");
        put_stop();
        while (!s_empty(temp))
        {
            printf("| %16p |[%4d,%4d]| %16p |\n", (void*)temp, temp->pos.i, temp->pos.j, (void*)temp->next);
            temp = temp->next;
        }
        put_sbot();
    }
}

