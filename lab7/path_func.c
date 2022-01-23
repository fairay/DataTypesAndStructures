#include "head.h"
/// Path CDIO
path_t create_path(int size)
{
    int code;
    path_t path;
    path.len = 0;
    code = create_array(&path.node_arr, size);
    if (code == OK)
        path.size = size;
    else
        path.size = 0;
    return path;
}

void delete_path(path_t *path)
{
    delete_array(&path->node_arr);
    path->size = 0;
    path->len = 0;
}

void print_path(lgraph_t *graph, path_t path)
{
    if (!path.len)
        printf("Error: no path\n");
    else
    {
        printf("Path: ");
        printf("%s", graph->node_arr[path.node_arr[0]].name);
        for (int i = 1; i < path.len; i++)
            printf(" -> %s", graph->node_arr[path.node_arr[i]].name);
        printf("\n");
    }
}

int resize_path(path_t *path, int new_size)
{
    int code = OK;
    if (new_size)
        code = resize_array(&path->node_arr, new_size);
    else
        delete_path(path);

    if (code == OK)
        path->size = new_size;
    return code;
}


/// Path functions
void add_node_path(path_t *path, int node)
{
    path->node_arr[path->len] = node;
    path->len++;
}

int is_in_path(path_t path, int node1, int node2)
{
    for (int i = 0; i < path.len - 1; i++)
    {
        if ((path.node_arr[i] == node1 && path.node_arr[i+1] == node2) ||
                (path.node_arr[i] == node2 && path.node_arr[i+1] == node1))
            return 1;
    }
    return 0;
}

int path_dist(lgraph_t *graph, path_t path)
{
    int dist = 0;
    edge_t *edge;

    for (int i = 0; i < path.len - 1; i++)
    {
        edge = graph->node_arr[path.node_arr[i]].list;
        while (edge && edge->node != path.node_arr[i + 1])
            edge = edge->next;
        dist += edge->dist;
    }
    return dist;
}

int path_cost(lgraph_t *graph, path_t path)
{
    int cost = 0;
    edge_t *edge;
    for (int i = 0; i < path.len - 1; i++)
    {
        edge = graph->node_arr[path.node_arr[i]].list;
        while (edge && edge->node != path.node_arr[i + 1])
            edge = edge->next;
        cost += edge->cost;
    }
    return cost;
}
