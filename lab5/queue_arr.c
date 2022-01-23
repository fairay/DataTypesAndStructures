#include "head.h"

void put_abot(void)
{
    printf("|-----|-----------|\n");
}

void put_atop(void)
{
    put_abot();
    printf("| %3s | %9s |\n", "#", "Time");
    put_abot();
}


// Dynamic array CDIO and other functions
// CDIO

int create_array(array_t *a, size_t n)
{
    (*a) = (array_t)calloc(n, sizeof(float));
    if (*a)
        return OK;
    else
        return ALLOC_FAIL;
}

void delete_array(array_t *a)
{
    free(*a);
    (*a) = NULL;
}

void print_array(array_t a, size_t n)
{
    for (int i = 0; i < n; i++)
        printf("%f ", a[i]);
    printf("\n");
}

// Applied functions
int resize_array(array_t *a, int n)
{
    array_t new_arr = NULL;
    new_arr = (array_t)realloc((*a), n * sizeof(float));
    if (new_arr)
    {
        (*a) = new_arr;
        new_arr = NULL;
        return OK;
    }
    else
        return ALLOC_FAIL;
}


// Array queue functions
aqueue_t create_aque(void)
{
    int code;
    aqueue_t que;

    que.size = 10;
    que.pin = 0;
    que.pout = 0;
    que.count = 0;

    code = create_array(&que.time_arr, que.size);
    if (code != OK)     delete_aque(&que);

    return que;
}

void print_aque(aqueue_t que)
{
    int i;

    if (aque_empty(que))
        puts("Queue is empty\n");
    else
    {
        puts("Array queue:");
        put_atop();
        for (i = que.pout; i != que.pin; i = (i + 1) % que.size)
            printf("| %3d | %9.2f |\n", i, que.time_arr[i]);
        put_abot();
    }
}

void delete_aque(aqueue_t *que)
{
    delete_array(&que->time_arr);
    que->size = 0;
    que->count = 0;
    que->pin = 0;
    que->pout = 0;
}

int increase_aque(aqueue_t *que, int new_size)
{
    int code = resize_array(&que->time_arr, new_size);
    int delta = new_size - que->size;

    if (code != OK) return code;

    if (que->pout > que->pin)
    {
        for (int i = que->size - 1; i >= que->pout; i--)
            que->time_arr[i + delta] = que->time_arr[i];
        que->pout = que->pout + delta;
    }

    que->size = new_size;

    return OK;
}

int decrease_aque(aqueue_t *que, int new_size)
{
    int code, delta = que->size - new_size;
    if (que->pout > que->pin)
    {
        for (int i = que->pout; i < que->size; i++)
            que->time_arr[i - delta] = que->time_arr[i];
        que->pout = que->pout - delta;
    }

    else if (que->pin >= new_size)
    {
        for (int i = 0; i < que->count; i++)
            que->time_arr[i] = que->time_arr[que->pout + i];
        que->pout = 0;
        que->pin = que->count;
    }
    code = resize_array(&que->time_arr, new_size);
    que->size = new_size;
    return code;
}


// Queue functions
int aque_empty(aqueue_t que)
{
    return (que.count == 0);
}

int aque_len(aqueue_t que)
{
    return que.count;
}


int push_aque(aqueue_t *que, float new_time)
{
    int code = OK;
    if (que->count + 1 >= que->size)
        code = increase_aque(que, que->size * 3 / 2);
    if (code != OK)
        return code;

    que->time_arr[que->pin] = new_time;
    que->pin = (que->pin + 1) % que->size;
    que->count = que->count + 1;
    return code;
}

float pop_aque(aqueue_t *que)
{
    float time = -1;
    if (que->count == 0)
        return time;
    time = que->time_arr[que->pout];
    que->time_arr[que->pout] = 0;

    que->pout = (que->pout + 1) % que->size;
    que->count = que->count - 1;
    /*
    if ((que->count + 3) * 3 < que->size)
        decrease_aque(que, que->size / 2);
    */
    return time;
}

float peak_aque(aqueue_t que)
{
    if (aque_empty(que))
        return -1;
    else
        return que.time_arr[que.pout];
}
