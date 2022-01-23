#include "head.h"

void put_stop(void)
{
    put_sbot();
    printf("| %16s | %9s | %16s |\n", "Addres", "Time", "Next");
    put_sbot();
}

void put_sbot(void)
{
    printf("|------------------|-----------|------------------|\n");
}


int lque_empty(lqueue_t que)
{
    return (list_empty(que.pout));
}

int lque_len(lqueue_t que)
{
    int len = 0;
    list_t temp = que.pout;

    while (!list_empty(temp))
    {
        len++;
        temp = temp->next;
    }
    return len;
}


lqueue_t create_lque(free_mem_t* free_adr)
{
    lqueue_t que;
    que.free = free_adr;

    que.pin = NULL;
    que.pout = NULL;

    return que;
}

void delete_lque(lqueue_t *que)
{
    while (!lque_empty(*que))
        pop_lque(que);

    que->free = NULL;
}

void print_lque(lqueue_t que)
{
    list_t temp = que.pout;
    if (lque_empty(que))
        puts("Queue is empty\n");
    else
    {
        puts("Queue:\n");
        put_stop();
        while (!list_empty(temp))
        {
            printf("| %16p | %9.2f | %16p |\n", (void*)temp, temp->time, (void*)temp->next);
            temp = temp->next;
        }
        put_sbot();
    }
}


int push_lque(lqueue_t *que, float new_time)
{
    cell_t* new_cell = pop_free(que->free);
    if (!new_cell)
        return ALLOC_FAIL;

    new_cell->time = new_time;
    new_cell->next = NULL;
    if (lque_empty(*que))
        que->pout = new_cell;
    else
        que->pin->next = new_cell;
    que->pin = new_cell;

    return OK;
}

float pop_lque(lqueue_t *que)
{
    float time = -1;
    if (lque_empty(*que))
        return time;

    list_t temp = (que->pout)->next;
    push_free(que->free, que->pout);
    time = que->pout->time;
    que->pout = temp;
    return time;
}

float peak_lque(lqueue_t que)
{
    if (lque_empty(que))
        return -1;
    else
        return que.pout->time;
}
