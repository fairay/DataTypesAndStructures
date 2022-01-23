#include "head.h"


int show_error_message(int code)
{
    printf("Error: ");
    switch (code)
    {
        case ALLOC_FAIL:
            printf("memory allocation failed");
            break;

        case WRONG_FORMAT:
            printf("wrong input data format");
            break;

        case WRONG_SIZE:
            printf("wrong matrix size");
            break;

        case WRONG_MODE:
            printf("wrong command");
            break;

        case FINPUT_FAIL:
            printf("wrong file format");
            break;

        case NO_WAY:
            printf("no such way in maze");
            break;

        case NO_EXIT:
            printf("maze hasn't two exits");
            break;

        case WRONG_TIME:
            printf("time range is incorrect");
    }
    printf("\n");
    return code;
}

/*
int main(void)
{
    srand(time(NULL));
    int code = OK;
    int sc, key;
    int size_n, size_m;
    char file_name[256];

    pos_t start, end;

    free_mem_t free_mem = NULL;
    maze_t maze;
    list_st_t way_list;
    arr_st_t way_arr;


    puts("Choose the mode:");
    puts("0) Generate maze randomly");
    puts("1) Scan maze from file");
    puts("2) Test mode");
    
    sc = scanf("%d", &key);
    if (sc != 1)    return show_error_message(WRONG_FORMAT);
    switch (key)
    {
        case 0:
            printf("Input maze size (only odd >= 3): ");
            sc = scanf("%d%d", &size_n, &size_m);
            if (sc != 2)    return show_error_message(WRONG_FORMAT);
            if (size_n < 3 || size_m < 3)   return show_error_message(WRONG_SIZE);

            size_n += (size_n + 1) % 2;
            size_m += (size_m + 1) % 2;
            maze = create_maze(size_n, size_m);
            if (!maze.a)    return ALLOC_FAIL;
            fill_maze(maze, &free_mem);
            break;

        case 1:
            printf("Input file name: ");
            sc = scanf("%s", file_name);
            if (sc != 1)    return show_error_message(WRONG_FORMAT);

            maze = finput_maze(file_name);
            if (!maze.a)    return show_error_message(FINPUT_FAIL);
            break;
        case 2:
            test_mode();
            return OK;
            
        default:
            return show_error_message(WRONG_MODE);
    }

    printf("\n_________________________\n");
    printf("Input maze\n");
    printf("_________________________\n\n");
    print_maze(maze);

    code = find_exit(maze, &start, &end);
    if (code != OK) show_error_message(code);
    printf("In: [%d, %d]\n", start.i, start.j);
    printf("Out: [%d, %d]\n", end.i, end.j);

    printf("\n\nList stack pathfinding:\n\n");
    way_list = find_way_list(maze, start, end, &free_mem);
    print_list(way_list);
    print_way_list(maze, way_list);


    delete_list(&way_list);
    clean_stack(&free_mem);
    print_free(free_mem);

    printf("\n\nArray stack pathfinding:\n\n");
    printf("In: [%d, %d]\n", start.i, start.j);
    printf("Out: [%d, %d]\n", end.i, end.j);
    way_arr = find_way_arr(maze, start, end);
    print_arr(way_arr);
    print_way_arr(maze, way_arr);

    delete_arr_st(&way_arr);
    delete_maze(&maze);
    return code;
}
*/

int main(void)
{
    srand(time(NULL));
    int code = OK;
    int sc;
    int mode;

    free_mem_t free_mem = NULL;
    options_t options = default_options();

    print_options(options);
    printf(">>> Change options of serving machine? (Yes - 1): ");
    sc = scanf("%d", &mode);
    if (sc != 1)
        return show_error_message(WRONG_FORMAT);
    if (mode == 1)
    {
        options = change_options(options);
        print_options(options);
    }

    puts("\nProgramm modes:");
    puts("0) Analysis mode");
    puts("1) Run serving machine on array queue");
    puts("2) Run serving machine on list queue");
    printf("\n>>> Choose the mode: ");

    sc = scanf("%d", &mode);
    if (sc != 1)
        return show_error_message(WRONG_FORMAT);
    switch (mode)
    {
        case 0:
            test_mode();
            break;
        case 1:
            sv_work_arr(options);
            break;
        case 2:
            sv_work_list(options, &free_mem);
            break;
    }

    clean_list(&free_mem);
    return code;
}
