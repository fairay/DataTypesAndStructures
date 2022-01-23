#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define EPS             1e-7
#define MAX_LEN_FILE    30
#define MAX_LEN_NAME    20
#define MAX_LEN_PHONE   16
#define MAX_LEN_ADR     20
#define MAX_TABLE_SIZE  100

#define TEST_REPEATS    50000

#define OFFICIAL        "official"
#define PERSONAL        "personal"
#define PHONE_SYMBLOS   "0123456789+-"

// Имена полей
#define INDEX           "index"
#define SURNAME         "surname"
#define NAME            "name"
#define PHONE           "phone"
#define ADDRESS         "address"
#define STATUS          "status"
#define POST            "post"
#define ORGANISATION    "organisation"
#define YEAR            "year"
#define MONTH           "month"
#define DAY             "day"

#define STR_KEY         0
#define INT_KEY         1

// Коды ошибок
#define OK               0
#define WRONG_N         -1
#define WRONG_FORMAT    -2
#define WRONG_STATUS    -3
#define WRONG_PHONE     -4
#define WRONG_DOB       -5
#define INVALID_FILE    -6
#define WRONG_POSITION  -8
#define TABLE_OVERFLOW  -9
#define EMPTY_TABLE     -10

// Режимы работы программы
#define WRONG_MODE      -2
#define START           -1
#define EXIT            0
#define SHOW_INFO       1
#define CHANGE_FILE     10
#define SCAN_FILE       11
#define WRITE_FILE      12
#define PRINT_TABLE     20
#define ADD_ENTRY       21
#define DEL_ENTRY       22
#define SORT_TABLE_BUB  30
#define SORT_TABLE_Q    31
#define SORT_KEY_BUB    32
#define SORT_KEY_Q      33
#define TEST_EFF        40
#define PRINT_BD        41

typedef struct{
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;
} dob_t;

typedef struct{
    char post[MAX_LEN_NAME + 1];
    char org[MAX_LEN_NAME + 1];
} pos_org_t;

typedef struct{
    char surname[MAX_LEN_NAME + 1];
    char name[MAX_LEN_NAME + 1];
    char phone[MAX_LEN_PHONE + 1];
    char address[MAX_LEN_ADR + 1];

    char status[MAX_LEN_NAME + 1];
    union
    {
        dob_t pers;
        pos_org_t off;
    } info;

} sub_t;

typedef struct
{
    int ind;
    char key[MAX_LEN_NAME];
} key_t;

// Programm functions
void exit_mode(void);
int change_file_mode(char old_name[]);
void print_table_mode(sub_t table[], int table_size);
void print_table_key(sub_t table[], key_t key_table[], int table_size);
void print_keytable_mode(key_t key_table[], int table_size);
int add_entry_mode(sub_t table[], int* table_size);
int delete_entry_mode(sub_t table[], int* table_size);
int efficiency_test_mode(sub_t table[], int n);
void wrong_mode(void);

// File functions
int check_validity(char file_name[]);
int scan_file(char file_name[], sub_t table[],int* table_size);
int write_file(char file_name[], sub_t table[], int table_size);
int print_bd_friends(sub_t table[], int table_size);

// Sub_t cdio and other functions
void print_sub(sub_t sub);
int scan_sub(sub_t* sub);
void shift_table_l(sub_t table[], int pos, int n);

void create_keytable(sub_t table[], key_t key_table[], int n);

int check_dob_validity(dob_t dob);
int is_leap(int year);
int convert_days(dob_t date, int is_leap);
int check_phone_validity(char phone[]);

// Deletion check functions
int is_del_surname(sub_t sub, char key[]);
int is_del_name(sub_t sub, char key[]);
int is_del_phone(sub_t sub, char key[]);
int is_del_address(sub_t sub, char key[]);
int is_del_status(sub_t sub, char key[]);
int is_del_post(sub_t sub, char key[]);
int is_del_org(sub_t sub, char key[]);
int is_del_year(sub_t sub, int key);
int is_del_month(sub_t sub, int key);
int is_del_day(sub_t sub, int key);

// Sorts
void sort_keytable_bubble(key_t key_table[], int n);
void sort_table_bubble(sub_t table[], int n);
void sort_keytable_qsort(key_t key_table[], int l, int r);
void sort_table_qsort(sub_t table[], int l, int r);

// Test of efficiency
void test_key_bubble(sub_t sourse_table[], int n, double *time, long int *mem);
void test_key_qsort(sub_t sourse_table[], int n, double *time, long int *mem);
void test_table_bubble(sub_t sourse_table[], int n, double *time, long int *mem);
void test_table_qsort(sub_t sourse_table[], int n, double *time, long int *mem);

#endif // HEAD_H
