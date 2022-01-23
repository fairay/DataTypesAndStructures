#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


// Error codes
#define OK              0
#define ALLOC_FAIL      -1
#define WRONG_FORMAT    -2
#define WRONG_FILE      -5
#define NEGATIVE_VAL    -6
#define NO_ELEMENT      -9
#define EMPTY_FILE      -10
#define NO_CITY         -11
#define DOUBLE_EDGE     -12

#define MAX_STR         100
#define IN_FILE         "data.txt"
#define OUT_FILE        "out_graph.gv"
#define GRAPHICS_SIZE   150

typedef int* array_t;
typedef char str_t[MAX_STR + 1];
typedef struct
{
    array_t node_arr;
    int size;
    int len;
} path_t;

typedef struct
{
    int size;
    int count;
    int pin;
    int pout;
    array_t arr;
} aqueue_t;

typedef struct edge_tag
{
    int node;
    int dist;
    int cost;
    struct edge_tag *next;
} edge_t;
typedef edge_t* ledge_t;

// Node type
typedef struct
{
    str_t name;
    ledge_t list;
} node_t;


typedef node_t* node_arr_t;
// List graph
typedef struct
{
    node_arr_t node_arr;
    int size;
} lgraph_t;

typedef array_t* matrix_t;
typedef str_t* str_arr_t;



// Main functions
int err_message(int code);

/// Path functions
path_t create_path(int size);
void print_path(lgraph_t *graph, path_t path);
void delete_path(path_t *path);
int is_in_path(path_t path, int node1, int node2);

/// Graph functions
lgraph_t create_lgraph(void);
int finput_lgraph(char file_name[], lgraph_t *graph);
void foutput_lgraph(lgraph_t *graph, path_t path);
void delete_lgraph(lgraph_t *graph);
void add_node_path(path_t *path, int node);
int resize_path(path_t *path, int new_size);

path_t bfs(lgraph_t *graph, int st, int fin);

int find_node(lgraph_t *graph, char name[]);
int add_node(lgraph_t *graph, char name[]);
int add_edge(lgraph_t*, char[], char[], int, int);
int path_dist(lgraph_t *graph, path_t path);
int path_cost(lgraph_t *graph, path_t path);

/// Array CDIO
int create_array(array_t *a, size_t n);
void print_array(array_t a, size_t n);
void delete_array(array_t *a);
int resize_array(array_t *a, int n);

/// Queue functions
aqueue_t create_aque(void);
void print_aque(aqueue_t que);
void delete_aque(aqueue_t *que);

int aque_empty(aqueue_t que);
int aque_len(aqueue_t que);

int push_aque(aqueue_t *que, int new_time);
int pop_aque(aqueue_t *que);
int peak_aque(aqueue_t que);

/// Test functions
void test_mode(void);
void compare(void);

#endif // HEAD_H
