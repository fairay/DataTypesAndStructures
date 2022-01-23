#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// Error codes
#define OK              0
#define ALLOC_FAIL      -1
#define WRONG_FORMAT    -2
#define WRONG_SIZE      -3
#define WRONG_MODE      -6
#define FINPUT_FAIL     -7
#define OVERFLOW        -4
#define WRONG_FILE      -5
#define WRONG_TIME      -8
#define NO_ELEMENT      -9


#define EPS             10e-5
#define GOLDEN_RATIO    0.6180339888
#define TEST_N          100000
#define FIND_N          1000
#define REPEATS         100
#define HASH_N          4

// Symbols codes
#define UD      179
#define DR      218
#define UR      192
#define LR      196

#define WRONG_INPUT     -1
#define EXIT             0
#define ADD              1
#define DEL              2
#define FIND             3
#define SCAN_FILE        4
#define AVER_COUNT       5
#define POSTFIX          6
#define PREFIX           7
#define INFIX            8
#define CHANGE_MAX_CMP   6

// Tree element type
typedef struct node_tag
{
    int val;
    int bal;
    struct node_tag *left;
    struct node_tag *right;
} node_t;

typedef node_t *tree_t;

typedef int* array_t;
typedef struct
{
    int size;
    int count;
    int hash_n;
    int (*func) (int, int);
    array_t arr;
    array_t is_busy;
} table_t;

typedef struct
{
    double add_mem;
    double add_time;
    double find_time;
    long int find_cmp;
} stats_t;


// Main functions
int err_message(int code);
int add_file(char file_name[], int number);
int add_file_test(FILE *f, int number);
int count_file_find(FILE *f, int number);

int create_node(tree_t *node, int val);
void clean_node(tree_t *node);

tree_t create_tree(void);
int finput_tree(char file_name[], tree_t *tree);
int finput_tree_avl(char file_name[], tree_t *tree);
void print_tree(tree_t tree);
void delete_tree(tree_t *tree);

int add_node(tree_t *tree, int val);
int add_node_avl(tree_t *tree, int val);

int delete_node(tree_t *tree, int val);
int delete_node_avl(tree_t *tree, int val);

void print_head(char head[]);
void print_node(tree_t tree, char head[]);

tree_t* find_node(tree_t* tree, int val);
int find_depth(tree_t tree);
int find_cmp(tree_t tree, int val);
float tree_aver_count(tree_t tree);
tree_t* find_exchange(tree_t* tree);
int balance_node(tree_t *tree);
int deep_balance(tree_t *tree);

// Rotations
void r_rotate(tree_t *tree);
void l_rotate(tree_t *tree);
void dr_rotate(tree_t *tree);
void dl_rotate(tree_t *tree);

// Travel functions
void prefix_trav(tree_t tree);
void postfix_trav(tree_t tree);
void infix_trav(tree_t tree);

/// Dynamic array functions
int create_array(array_t *arr, int size);
void delete_array(array_t *arr);

/// Hash table functions
// CDIO
int create_table(table_t* table, int size);
int finput_table(char file_name[], table_t* table);
void print_table(table_t table);
void delete_table(table_t* table);
int resize_table(table_t* table);
int restruct_table(table_t* table);

// Functions
int add_table(table_t* table, int val);
int del_table(table_t* table, int val);
int find_table(table_t* table, int val);
int count_find_table(table_t* table, int val);
float table_aver_count(table_t* table);

/// Test functions
void test_mode(void);
void compare(void);

#endif // HEAD_H
