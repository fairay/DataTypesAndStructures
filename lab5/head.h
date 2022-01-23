#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Error codes
#define OK              0
#define ALLOC_FAIL      -1
#define WRONG_FORMAT    -2
#define WRONG_SIZE      -3
#define WRONG_MODE      -6
#define FINPUT_FAIL     -7
#define NO_WAY          -4
#define NO_EXIT         -5
#define WRONG_TIME      -8

#define EPS             10e-5
#define TEST_REPEAT     50

#define WRONG_INPUT     -1
#define EXIT             0
#define PUSH_LIST        10
#define POP_LIST         11
#define PUSH_ARR         20
#define POP_ARR          21
#define COMPARE          30

#define T1          { 1, 5 }
#define T2          { 0, 3 }
#define T3          { 0, 4 }
#define T4          { 0, 1 }
#define SHOW_STEP   100
#define MAX_REQUEST 1000

#define TEST1       { 3, 3 }
#define TEST2       { 1.5, 1.5 }
#define TEST3       { 2, 2 }
#define TEST4       { 0.5, 0.5 }
#define TEST_SIZE   100000

// List element type
typedef struct cell_tag
{
    float time;
    struct cell_tag *next;
} cell_t;

typedef cell_t* list_t;

// Free memory cells type
typedef list_t free_mem_t;

// List queue type ( with free memory var)
typedef struct
{
    free_mem_t* free;
    list_t pin;
    list_t pout;
} lqueue_t;

typedef float* array_t;

// Array stack type
typedef struct
{
    int size;
    int count;
    int pin;
    int pout;
    array_t time_arr;
} aqueue_t;

typedef struct
{
    float t1[2];
    float t2[2];
    float t3[2];
    float t4[2];
    int step;
    int max_1;
} options_t;

typedef struct
{
    long int memory;
    double time;
} stats_t;

// Main functions
int show_error_message(int code);

// List functions
int list_empty(list_t list);
void clean_list(list_t* list);

// Free memory cells functions
void push_free(free_mem_t *stack, cell_t* new_cell);
cell_t* pop_free(free_mem_t *stack);
void print_free(free_mem_t stack);


// List queue functions
void put_stop(void);
void put_sbot(void);

int lque_empty(lqueue_t que);
int lque_len(lqueue_t que);
int list_len(list_t list);

lqueue_t create_lque(free_mem_t* free_adr);
void delete_lque(lqueue_t *que);
void print_lque(lqueue_t que);

int push_lque(lqueue_t *que, float new_time);
float pop_lque(lqueue_t *que);
float peak_lque(lqueue_t que);


// Dynamic array functions
int create_array(array_t *a, size_t n);
void delete_array(array_t *a);
int resize_array(array_t *a, int n);

// Array queue functions
aqueue_t create_aque(void);
void print_aque(aqueue_t que);
void delete_aque(aqueue_t *que);

int aque_empty(aqueue_t que);
int aque_len(aqueue_t que);

int push_aque(aqueue_t *que, float new_time);
float pop_aque(aqueue_t *que);
float peak_aque(aqueue_t que);


// Serving machine functions
options_t default_options(void);
options_t test_options(void);
void print_options(options_t opt);
options_t change_options(options_t opt);

stats_t sv_work_list(options_t opt, free_mem_t *free_adr);
stats_t sv_work_arr(options_t opt);

// Test functions
void test_mode(void);
void compare(void);

#endif // HEAD_H
