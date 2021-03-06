#include "head.h"

void put_stop(void)
{
    put_sbot();
    printf("| %16s | %9s | %16s |\n", "Addres", "Data", "Next");
    put_sbot();
}

void put_sbot(void)
{
    printf("|------------------|-----------|------------------|\n");
}

int s_empty(list_t stack)
{
    return (stack == NULL);
}

void clean_stack(list_t* stack)
{
    list_t temp = *stack;
    while (!s_empty(*stack))
    {
        temp = (*stack)->next;
        free(*stack);
        *stack = temp;
    }
}

int list_empty(list_st_t st)
{
    return (s_empty(st.stack));
}



list_st_t create_list(free_mem_t* free_adr)
{
    list_st_t st;
    st.stack = NULL;
    st.free = free_adr;
    return st;
}

void delete_list(list_st_t *st)
{
    st->free = NULL;
    clean_stack(&st->stack);
}

void print_list(list_st_t st)
{
    list_t temp = st.stack;
    if (list_empty(st))
        puts("Stack is empty\n");
    else
    {
        puts("Stack:\n");
        put_stop();
        while (!s_empty(temp))
        {
            printf("| %16p |[%4d,%4d]| %16p |\n", (void*)temp, temp->pos.i, temp->pos.j, (void*)temp->next);
            temp = temp->next;
        }
        put_sbot();
    }
}


int push_list(list_st_t *st, pos_t new_pos)
{
    cell_t* new_cell = pop_free(st->free);
    if (!new_cell)
        return ALLOC_FAIL;

    new_cell->pos = new_pos;
    new_cell->next = st->stack;
    st->stack = new_cell;
    return OK;
}

pos_t pop_list(list_st_t* st)
{
    pos_t pos = { -1, -1 };
    if (list_empty(*st))
        return pos;

    list_t temp = (st->stack)->next;
    push_free(st->free, st->stack);
    pos = st->stack->pos;
    st->stack = temp;
    return pos;
}

pos_t peak_list(list_st_t st)
{
    return st.stack->pos;
}
