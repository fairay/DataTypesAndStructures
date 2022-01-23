#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_SIZE       2500000

// Error codes
#define OK              0
#define ALLOC_FAIL      -1
#define WRONG_FORMAT    -2
#define WRONG_SIZE      -3
#define WRONG_MODE      -6
#define FINPUT_FAIL     -7
#define NO_WAY          -4
#define NO_EXIT         -5

#define WRONG_INPUT     -1
#define EXIT             0
#define PUSH_LIST        10
#define POP_LIST         11
#define PUSH_ARR         20
#define POP_ARR          21
#define COMPARE          30

// Direction codes
#define U       0
#define R       1
#define D       2
#define L       3

#define WALL        0
#define TRACK       1
#define WALK        2

// Position type
typedef struct
{
    int i;
    int j;
} pos_t;

// List element type
typedef struct cell_tag
{
    pos_t pos;
    struct cell_tag *next;
} cell_t;

typedef cell_t* list_t;

// Free memory cells type
typedef list_t free_mem_t;

// List stack type ( with free memory var)
typedef struct
{
    list_t* free;
    list_t stack;
} list_st_t;

// Dynamic array type
typedef int* array_t;

// Array stack type
typedef struct
{
    int size;
    int top;
    pos_t* stack;
} arr_st_t;

// Maze type
typedef struct
{
    int n, m;
    array_t* a;
} maze_t;


// Main functions
int show_error_message(int code);

// Free memory cells functions
void push_free(free_mem_t *stack, cell_t* new_cell);
cell_t* pop_free(free_mem_t *stack);
void print_free(free_mem_t stack);


// List stack functions
void put_stop(void);
void put_sbot(void);
int s_empty(list_t stack);
void clean_stack(list_t* stack);
int list_empty(list_st_t st);

list_st_t create_list(free_mem_t* free_adr);
void delete_list(list_st_t *st);
void print_list(list_st_t stack);

int push_list(list_st_t *st, pos_t new_pos);
pos_t pop_list(list_st_t* st);
pos_t peak_list(list_st_t st);


// Dynamic array functions
int create_array(array_t *a, size_t n);
void delete_array(array_t *a);

int resize_array(array_t *a, size_t n);

// Array stack functions
arr_st_t create_arr_st(void);
void delete_arr_st(arr_st_t *arr_st);
void print_arr(arr_st_t st);
int resize_arr_st(arr_st_t *arr_st, int new_size);

int arr_empty(arr_st_t st);
int push_arr(arr_st_t *st, pos_t new_pos);
pos_t pop_arr(arr_st_t *st);
pos_t peak_arr(arr_st_t st);


// Maze functions
maze_t create_maze(int n, int m);
void delete_maze(maze_t *maze);
maze_t finput_maze(char file_name[]);

void print_maze(maze_t maze);
void print_way_list(maze_t maze, list_st_t way);
void print_way_arr(maze_t maze, arr_st_t way);

void clean_maze(maze_t maze);
int find_exit(maze_t maze, pos_t* exit1, pos_t* exit2);
void fill_maze(maze_t maze, free_mem_t *free_adr);
list_st_t find_way_list(maze_t maze, pos_t start, pos_t end, free_mem_t *free_adr);
arr_st_t find_way_arr(maze_t maze, pos_t start, pos_t end);


// Test functions
void test_mode(void);
void compare(int size);

#endif // HEAD_H
