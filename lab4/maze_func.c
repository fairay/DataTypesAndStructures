#include "head.h"

// Directions U, R, D, L
static int urdl[] = { U, R, D, L };
static int move[4][2] = {
    { -1,  0 },
    {  0,  1 },
    {  1,  0 },
    {  0, -1 } };


pos_t move_by(pos_t pos, int way)
{
    pos.i += move[way][0];
    pos.j += move[way][1];
    return pos;
}

pos_t make_move2(maze_t maze, pos_t pos, int way)
{
    for (int i = 0; i < 2; i++)
    {
        pos = move_by(pos, way);
        maze.a[pos.i][pos.j] = 2;
    }
    return pos;
}

void shuffle_ways(int ways[4])
{
    int temp;
    int swap_pos;

    for (int i = 0; i < 4; i++)
    {
        swap_pos = rand() % 4;

        temp = ways[i];
        ways[i] = ways[swap_pos];
        ways[swap_pos] = temp;
    }
}

pos_t rand_pos2(int n, int m)
{
    pos_t pos;
    pos.i = rand() % (n / 2) * 2 + 1;
    pos.j = rand() % (m / 2) * 2 + 1;
    return pos;
}

int is_able(maze_t maze, pos_t pos, int way)
{
    pos = move_by(pos, way);
    if (pos.i < 0 || pos.i >= maze.n)
        return 0;
    if (pos.j < 0 || pos.j >= maze.m)
        return 0;
    return (maze.a[pos.i][pos.j] == 1);
}

int is_able2(maze_t maze, pos_t pos, int way)
{
    pos = move_by(pos, way);
    pos = move_by(pos, way);

    if (pos.i < 0 || pos.i >= maze.n)
        return 0;
    if (pos.j < 0 || pos.j >= maze.m)
        return 0;
    return (maze.a[pos.i][pos.j] != 2);
}

int define_direct(pos_t pos1, pos_t pos2)
{
    int dir;
    pos_t delta = { pos1.i - pos2.i, pos1.j - pos2.j };
    for (dir = 0; dir < 4; dir++)
        if (move[dir][0] == delta.i && move[dir][1] == delta.j)
            break;
    return dir;
}


maze_t create_maze(int n, int m)
{
    maze_t maze;

    maze.n = n;
    maze.m = m;

    maze.a = (array_t*)calloc(n, sizeof(array_t));
    if (maze.a)
    {
        for (int i = 0; i < n; i++)
            if (create_array(&maze.a[i], m) != OK)
                delete_maze(&maze);
    }

    return maze;
}

void print_maze(maze_t maze)
{
    for (int i = 0; i < maze.n; i++)
    {
        for (int j = 0; j < maze.m; j++)
        {
            if (maze.a[i][j] == 1)
                printf("  ");
            else if (maze.a[i][j])
                printf("()");
            else
                printf("%c%c", 219, 219);
        }
        printf("\n");
    }
}

maze_t finput_maze(char file_name[])
{
    int n, m, sc = 0;
    maze_t maze = { -1, -1, NULL };
    FILE *f = fopen(file_name, "r");
    if (!f)
        return maze;

    sc = fscanf(f, "%d%d", &n, &m);
    if (sc != 2 || n < 3 || m < 3)
        return maze;
    maze = create_maze(n, m);
    if (!maze.a)
        return maze;

    sc = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            sc = fscanf(f, "%d", &maze.a[i][j]);
            if (sc != 1)
            {
                delete_maze(&maze);
                return maze;
            }
        }

    fclose(f);

    return maze;
}

void delete_maze(maze_t *maze)
{
    for (int i = 0; i < maze->n; i++)
        delete_array(&maze->a[i]);

    free(maze->a);
    maze->a = NULL;
}


void print_way_list(maze_t maze, list_st_t way)
{
    list_t temp = way.stack;
    if (s_empty(temp))
        printf("No way was founded!\n");
    while (!s_empty(temp))
    {
        maze.a[temp->pos.i][temp->pos.j] = WALK;
        temp = temp->next;
    }

    for (int i = 0; i < maze.n; i++)
    {
        for (int j = 0; j < maze.m; j++)
        {
            if (maze.a[i][j] == WALK)
            {
                printf("* ");
                maze.a[i][j] = 1;
            }
            else if (maze.a[i][j])
                printf("  ");
            else
                printf("%c%c", 219, 219);
        }
        printf("\n");
    }

    clean_maze(maze);
}

void print_way_arr(maze_t maze, arr_st_t way)
{
    if (way.top == -1)
        printf("No way was founded!\n");

    for (int i = 0; i <= way.top; i++)
        maze.a[way.stack[i].i][way.stack[i].j] = WALK;

    for (int i = 0; i < maze.n; i++)
    {
        for (int j = 0; j < maze.m; j++)
        {
            if (maze.a[i][j] == WALK)
            {
                printf("* ");
                maze.a[i][j] = 1;
            }
            else if (maze.a[i][j])
                printf("  ");
            else
                printf("%c%c", 219, 219);
        }
        printf("\n");
    }
    clean_maze(maze);
}



void clean_maze(maze_t maze)
{
    for (int i = 0; i < maze.n; i++)
        for (int j = 0; j < maze.m; j++)
            if (maze.a[i][j])
                maze.a[i][j] = 1;
}

void fill_maze(maze_t maze, free_mem_t *free_adr)
{
    int ways[] = { U, R, D, L };
    int i;
    int is_stop;
    int len = 0, max_len = maze.n / 5 + 2;
    list_st_t hubs = create_list(free_adr);
    pos_t pos = rand_pos2(maze.n, maze.m);

    maze.a[pos.i][pos.j] = 2;
    push_list(&hubs, pos);

    while (!list_empty(hubs))
    {
        len = 0;
        pos = peak_list(hubs);
        while (1)
        {
            shuffle_ways(ways);
            is_stop = 1;
            for (i = 0; i < 4; i++)
                if (is_able2(maze, pos, ways[i]))
                {
                    is_stop = 0;
                    break;
                }
            if (is_stop || len > max_len)
            {
                pop_list(&hubs);
                break;
            }

            pos = make_move2(maze, pos, ways[i]);
            push_list(&hubs, pos);
            len++;
        }
    }

    pos = rand_pos2(maze.n, maze.m);
    maze.a[pos.i][0] = 2;
    pos = rand_pos2(maze.n, maze.m);
    maze.a[pos.i][maze.m-1] = 2;

    clean_maze(maze);
    delete_list(&hubs);
}

int find_exit(maze_t maze, pos_t* exit1, pos_t* exit2)
{
    int flag = 0;
    for (int i = 1; i < maze.n - 1; i++)
    {
        if (maze.a[i][0])
        {
            if (flag)
            {
                flag++;
                exit2->i = i;
                exit2->j = 0;
                return OK;
            }
            else
            {
                flag++;
                exit1->i = i;
                exit1->j = 0;
            }
        }
        if (maze.a[i][maze.m - 1])
        {
            if (flag)
            {
                flag++;
                exit2->i = i;
                exit2->j = maze.m - 1;
                return OK;
            }
            else
            {
                flag++;
                exit1->i = i;
                exit1->j = maze.m - 1;
            }
        }
    }

    for (int j = 1; j < maze.m - 1; j++)
    {
        if (maze.a[0][j])
        {
            if (flag)
            {
                flag++;
                exit2->i = 0;
                exit2->j = j;
                return OK;
            }
            else
            {
                flag++;
                exit1->i = 0;
                exit1->j = j;
            }
        }
        if (maze.a[maze.n - 1][j])
        {
            if (flag)
            {
                flag++;
                exit2->i = maze.n - 1;
                exit2->j = j;
                return OK;
            }
            else
            {
                flag++;
                exit1->i = maze.n - 1;
                exit1->j = j;
            }
        }
    }

    return NO_EXIT;
}

list_st_t find_way_list(maze_t maze, pos_t start, pos_t end, free_mem_t *free_adr)
{
    int direct, temp_dir;
    int i;

    pos_t pos = start;

    list_st_t way;

    way = create_list(free_adr);

    // First step
    for (i = 0; i < 4; i++)
    {
        if (is_able(maze, pos, urdl[i]))
        {
            maze.a[pos.i][pos.j] = 2;
            push_list(&way, pos);
            pos = move_by(pos, urdl[i]);
            direct = (i + 2) % 4;
            break;
        }
    }
    if (direct == 4) return way; // Start in dead end

    while (!((pos.i == end.i) && (pos.j == end.j)))
    {
        maze.a[pos.i][pos.j] = 2;
        for (i = 1; i < 4; i++)
        {
            temp_dir = (direct + i) % 4;
            if (is_able(maze, pos, urdl[temp_dir]))
            {
                push_list(&way, pos);
                pos = move_by(pos, urdl[temp_dir]);
                direct = (temp_dir + 2) % 4;
                break;
            }
        }
        if (i == 4)
        {
            if (list_empty(way))
                break;
            direct = define_direct(pos, peak_list(way));
            pos = pop_list(&way);
        }
    }

    if ((pos.i == end.i) && (pos.j == end.j))
        push_list(&way, end);

    clean_maze(maze);
    return way;
}

arr_st_t find_way_arr(maze_t maze, pos_t start, pos_t end)
{
    int direct, temp_dir;
    int i;
    pos_t pos = start;

    arr_st_t way = create_arr_st();
    if (way.size == 0)
        return way;

    // First step
    for (i = 0; i < 4; i++)
    {
        if (is_able(maze, pos, urdl[i]))
        {
            maze.a[pos.i][pos.j] = 2;
            push_arr(&way, pos);
            pos = move_by(pos, urdl[i]);
            direct = (i + 2) % 4;
            break;
        }
    }
    if (direct == 4) return way; // Start in dead end

    while (!((pos.i == end.i) && (pos.j == end.j)))
    {
        maze.a[pos.i][pos.j] = 2;
        for (i = 1; i < 4; i++)
        {
            temp_dir = (direct + i) % 4;
            if (is_able(maze, pos, urdl[temp_dir]))
            {
                push_arr(&way, pos);
                pos = move_by(pos, urdl[temp_dir]);
                direct = (temp_dir + 2) % 4;
                break;
            }
        }
        if (i == 4)
        {
            if (arr_empty(way))
                break;
            direct = define_direct(pos, peak_arr(way));
            pos = pop_arr(&way);
        }
    }

    if ((pos.i == end.i) && (pos.j == end.j))
        push_arr(&way, end);

    clean_maze(maze);
    return way;
}

