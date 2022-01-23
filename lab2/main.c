#include "head.h"

void print_head(void)
{
    puts("v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^");
    puts("Program for operations with subscribers data table: ");
    puts("Surname, Name, Phone, Address, Status, Info\n");
    puts("Info for personal status: birthday (in format DD.MM.YYYY)");
    puts("Info for official status: post and organisation");
    puts("v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^\n\n");
}

void print_functions(void)
{
    puts("Program functions:");
    printf("++++++++++++++++++++++++++++++++++++++++++++\n");
    puts("+ |00| Exit");
    puts("+ |01| Show program functions");

    puts("+ /10/ Change file");
    puts("+ /11/ Scan file");
    puts("+ /12/ Write file");

    puts("+ [20] Print table");
    puts("+ [21] Add entry");
    puts("+ [22] Delete entry");

    puts("+ {30} Sort table (bubble sort)");
    puts("+ {31} Sort table (quick sort)");
    puts("+ {32} Sort table with key table (bubble sort)");
    puts("+ {33} Sort table with key table (quick sort)");

    puts("+ :40: Compare effeciensy");
    puts("+ :41: Print friends with BD in next 7 days");

    printf("++++++++++++++++++++++++++++++++++++++++++++\n\n");
}

int show_error_message(int code)
{
    printf("Error: ");
    switch (code)
    {
        case WRONG_FORMAT:
            printf("incorrect input format");
            break;
        case WRONG_STATUS:
            printf("incorrect status");
            break;
        case WRONG_PHONE:
            printf("phone using forbidden simblos");
            break;
        case WRONG_DOB:
            printf("nonexistent date");
            break;
        case INVALID_FILE:
            printf("can't open the file");
            break;
        case WRONG_POSITION:
            printf("delete index are not in table");
            break;
        case TABLE_OVERFLOW:
            printf("table have maximum allowed size");
            break;
        case EMPTY_TABLE:
            printf("table is empty");
            break;
    }
    printf("\n");
    return code;
}

int main(void)
{
    srand(time(NULL));
    int mode = START;
    int code = OK;
    int sc;

    char trash_str[] = "\0";
    char file_name[MAX_LEN_FILE] = "text.txt";

    sub_t table[MAX_TABLE_SIZE];
    key_t key_table[MAX_TABLE_SIZE];
    int table_size = 0;


    print_head();
    print_functions();

    printf("Current file: %s\n", file_name);
    sc = scan_file(file_name, table, &table_size);
    if (sc != OK)
        show_error_message(sc);
    else
        printf("Scaned %d entrys\n", table_size);


    while (mode != EXIT)
    {
        printf("\n=======================\n");
        printf("(print %d to show functions)\n", SHOW_INFO);
        printf("Chose action: ");
        sc = scanf("%d", &mode);
        if (sc != 1)
        {
            mode = WRONG_MODE;
            gets(trash_str);
        }
        printf("=======================\n");

        switch (mode)
        {
            case EXIT:
                exit_mode();
                break;

            case SHOW_INFO:
                print_functions();
                break;

            // File actions
            case CHANGE_FILE:
                printf("*** Changing file ***\n\n");
                sc = change_file_mode(file_name);
                if (sc != OK)
                    show_error_message(sc);
                break;

            case SCAN_FILE:
                printf("*** Scaning file ***\n\n");
                sc = scan_file(file_name, table, &table_size);
                if (sc != OK)
                    show_error_message(sc);
                else
                    printf("Scaned %d entrys\n", table_size);
                break;

            case WRITE_FILE:
                printf("*** Writing file ***\n\n");
                sc = write_file(file_name, table, table_size);
                if (sc != OK)
                    show_error_message(sc);
                else
                    printf("Table written in %s successfully\n", file_name);
                break;

             // CDIO functions
            case PRINT_TABLE:
                printf("*** Printing table ***\n\n");
                print_table_mode(table, table_size);
                break;

            case ADD_ENTRY:
                printf("*** Adding entry ***\n\n");
                sc = add_entry_mode(table, &table_size);
                if (sc != OK)
                    show_error_message(sc);
                else
                    printf("Entry added successfully\n");
                break;

            case DEL_ENTRY:
                printf("*** Deleting entry ***\n\n");
                sc = delete_entry_mode(table, &table_size);
                if (sc != OK)
                    show_error_message(sc);
                else
                    printf("Entry deleted successfully\n");
                break;

            case PRINT_BD:
                printf("*** Printing friends with BD in next 7 days ***\n\n");
                sc = print_bd_friends(table, table_size);
                if (sc != OK)
                    show_error_message(sc);
                break;

             // Sort functions
            case SORT_TABLE_BUB:
                printf("*** Sorting table (bubble) ***\n\n");
                sort_table_bubble(table, table_size);

                printf("Sorted table:\n\n");
                print_table_mode(table, table_size);
                break;

            case SORT_TABLE_Q:
                printf("*** Sorting table (qsort) ***\n\n");
                sort_table_qsort(table, 0, table_size - 1);

                printf("Sorted table:\n\n");
                print_table_mode(table, table_size);
                break;

            case SORT_KEY_BUB:
                printf("*** Sorting table (bubble with key table) ***\n\n");
                create_keytable(table, key_table, table_size);
                sort_keytable_bubble(key_table, table_size);

                printf("Sorted keytable:\n\n");
                print_keytable_mode(key_table, table_size);

                printf("\nSorted table:\n\n");
                print_table_key(table, key_table, table_size);
                break;

            case SORT_KEY_Q:
                printf("*** Sorting table (qsort with key table) ***\n\n");
                create_keytable(table, key_table, table_size);
                sort_keytable_qsort(key_table, 0, table_size - 1);

                printf("Sorted keytable:\n\n");
                print_keytable_mode(key_table, table_size);

                printf("\nSorted table:\n\n");
                print_table_key(table, key_table, table_size);
                break;

             // Efficiency test
            case TEST_EFF:
                printf("*** Calculating sort time and memory value ***\n\n");
                sc = efficiency_test_mode(table, table_size);
                if (sc != OK)
                    show_error_message(sc);
                break;

            default:
                wrong_mode();
                break;
        }
    }

    return code;
}
