#include "head.h"

void put_abot(void)
{
    printf("|-----|-----------|\n");
}

void put_atop(void)
{
    put_abot();
    printf("| %3s | %9s |\n", "#", "Data");
    put_abot();
}


// Dynamic array CDIO and other functions
// CDIO

int create_array(array_t *a, size_t n)
{
    (*a) = (array_t)calloc(n, sizeof(int));
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


// Applied functions
int resize_array(array_t *a, size_t n)
{
    array_t new_arr = NULL;
    new_arr = (array_t)realloc((*a), n * sizeof(int));
    if (new_arr)
    {
        (*a) = new_arr;
        new_arr = NULL;
        return OK;
    }
    else
        return ALLOC_FAIL;
}


// Array stack functions
arr_st_t create_arr_st(void)
{
    arr_st_t arr_st;

    arr_st.top = -1;
    arr_st.size = 10;
    arr_st.stack = (pos_t*)malloc(arr_st.size * sizeof(pos_t));
    if (!arr_st.stack)  delete_arr_st(&arr_st);

    return arr_st;
}

void print_arr(arr_st_t st)
{
    if (arr_empty(st))
        puts("Stack is empty\n");
    else
    {
        puts("Array stack:");

        put_atop();
        for (int i = st.top; i >= 0; i--)
            printf("| %3d |[%4d,%4d]|\n", st.top - i + 1, st.stack[i].i, st.stack[i].j);
        put_abot();
    }
}

void delete_arr_st(arr_st_t *arr_st)
{
    free(arr_st->stack);
    arr_st->stack = NULL;
    arr_st->size = 0;
    arr_st->top = -1;
}

int resize_arr_st(arr_st_t *arr_st, int new_size)
{
    pos_t* new_st = NULL;
    new_st = (pos_t*)realloc(arr_st->stack, new_size * sizeof(pos_t));
    if (new_st)
    {
        arr_st->stack = new_st;
        new_st = NULL;
        arr_st->size = new_size;
        return OK;
    }
    else
        return ALLOC_FAIL;
}


// Stack functions
int arr_empty(arr_st_t st)
{
    return (st.top < 0);
}

int push_arr(arr_st_t *st, pos_t new_pos)
{
    int code = OK;
    if (st->size == st->top + 1)
        code = resize_arr_st(st, st->size * 2);
    if (code != OK) return code;

    st->top = st->top + 1;
    st->stack[st->top] = new_pos;
    return code;
}

pos_t pop_arr(arr_st_t *st)
{
    pos_t pos = { -1, -1 };
    if (st->top < 0)
        return pos;

    pos = st->stack[st->top];
    st->top = st->top - 1;
    if ((st->top + 3) * 3 < st->size)
        resize_arr_st(st, st->size / 2);

    return pos;
}

pos_t peak_arr(arr_st_t st)
{
    return st.stack[st.top];
}
