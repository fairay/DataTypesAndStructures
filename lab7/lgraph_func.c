#include "head.h"

/// Edge list CDIO
edge_t* create_edge(int node, int dist, int cost)
{
    edge_t* edge = (edge_t*)malloc(sizeof(edge_t));
    if (edge)
    {
        edge->node = node;
        edge->dist = dist;
        edge->cost = cost;
    }
    return edge;
}

void delete_edge(edge_t** edge)
{
    free(*edge);
    (*edge) = NULL;
}


/// Edge list CDIO
ledge_t create_ledge(void)
{
    return NULL;
}

int insert_ledge(ledge_t* list, edge_t* edge)
{
    ledge_t temp = *list;
    if (!temp || temp->node > edge->node)
    {
        edge->next = (*list);
        (*list) = edge;
        return OK;
    }

    while (temp->next && temp->next->node < edge->node)
        temp = temp->next;

    if (temp->node == edge->node)
        return DOUBLE_EDGE;

    edge->next = temp->next;
    temp->next = edge;
    return OK;
}

void delete_ledge(ledge_t* list)
{
    ledge_t temp = *list;
    while (temp != NULL)
    {
        (*list) = (*list)->next;
        delete_edge(&temp);
        temp = (*list);
    }
}


/// Node CDIO
node_t create_node(char name[])
{
    node_t node;
    strcpy(node.name, name);
    node.list = create_ledge();
    return node;
}

void delete_node(node_t* node)
{
    delete_ledge(&(node->list));
}


/// List graph CDIO

lgraph_t create_lgraph(void)
{
    lgraph_t graph = {
        .node_arr = NULL,
        .size = 0,
    };
    return graph;
}

int finput_lgraph(char file_name[], lgraph_t *graph)
{
    int sc = 0;
    char city1[MAX_STR + 1];
    char city2[MAX_STR + 1];
    int dist;
    int cost;
    edge_t *edge;

    FILE* f = fopen(file_name, "r");
    if (!f)
        return WRONG_FILE;

    sc = fscanf(f, "%s", city1);

    while (sc != EOF)
    {
        sc += fscanf(f, "%s", city2);
        sc += fscanf(f, "%d%d", &dist, &cost);
        if (sc != 4)
        {
            fclose(f);
            return WRONG_FILE;
        }
        if (dist < 0 || cost < 0)
        {
            fclose(f);
            return NEGATIVE_VAL;
        }

        sc = add_node(graph, city1);
        sc = add_node(graph, city2);

        sc = fscanf(f, "%s", city1);
    }
    if (!graph->size)
    {
        fclose(f);
        return EMPTY_FILE;
    }

    fseek(f, 0, SEEK_SET);

    sc = fscanf(f, "%s", city1);
    while (sc != EOF)
    {
        sc += fscanf(f, "%s", city2);
        sc += fscanf(f, "%d%d", &dist, &cost);

        sc = add_edge(graph, city1, city2, dist, cost);
        if (sc != OK)
        {
            fclose(f);
            return sc;
        }

        sc = fscanf(f, "%s", city1);
    }

    printf("Scaned info:\n");
    for (int i = 0; i < graph->size; i++)
    {
        printf("%d) %s - ", i, graph->node_arr[i].name);
        edge = graph->node_arr[i].list;
        while (edge)
        {
            printf("%d ", edge->node);
            edge = edge->next;
        }
        printf("\n");
    }

    fclose(f);
    return OK;
}

void foutput_lgraph(lgraph_t *graph, path_t path)
{
    edge_t* temp_edge;
    FILE *f = fopen(OUT_FILE, "w");

    fprintf(f, "graph Citys { \n");
    fprintf(f, "\tgraph [ dpi = %d ]; \n", GRAPHICS_SIZE);

    fprintf(f, "\tnode [shape=ellipse];");
    for (int i = 0; i < graph->size; i++)
        fprintf(f, " %s;", graph->node_arr[i].name);
    fprintf(f, "\n\n");

    for (int i = 0; i < graph->size; i++)
    {
        temp_edge = graph->node_arr[i].list;
        while (temp_edge && temp_edge->node < i)
        {
            fprintf(f, "\t%s -- %s [label = \"%d %d p.\" %s];\n",
                    graph->node_arr[i].name, graph->node_arr[temp_edge->node].name,
                    temp_edge->dist, temp_edge->cost,
                    is_in_path(path, i, temp_edge->node) ? "color = red" : " ");
            temp_edge = temp_edge->next;
        }
    }

    if (path.len)
        fprintf(f, "\tlabel = \"\n\n %s distance = %d coast = %d \";",
                "Path ", path_dist(graph, path), path_cost(graph, path));
    else
        fprintf(f, "\tlabel = \"\n\n %s \";",
                "Path not exist");

    fprintf(f,"\tfontsize=20;");
    fprintf(f, "\n}\n");

    fclose(f);
    system(OUT_FILE);
}

void delete_lgraph(lgraph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
        delete_node(&(graph->node_arr[i]));

    free(graph->node_arr);
    graph->node_arr = NULL;
    graph->size = 0;
}

int resize_lgraph(lgraph_t *graph, int new_size)
{
    node_arr_t new_arr = (node_arr_t)realloc(graph->node_arr, new_size * sizeof(node_t));
    if (new_arr)
    {
        graph->node_arr = new_arr;
        new_arr = NULL;
        graph->size = new_size;
        return OK;
    }
    else
        return ALLOC_FAIL;
}


/// List graph functions
path_t bfs(lgraph_t *graph, int st, int fin)
{
    path_t path = create_path(graph->size);
    aqueue_t queue = create_aque();
    array_t from;
    array_t s_p;
    int temp_node;
    edge_t* temp_edge;

    create_array(&from, graph->size);
    create_array(&s_p, graph->size);
    for (int i = 0; i < graph->size; i++)
        from[i] = -1;

    s_p[fin] = 0;
    push_aque(&queue, fin);
    while (!aque_empty(queue))
    {
        temp_node = pop_aque(&queue);
        temp_edge = graph->node_arr[temp_node].list;
        while (temp_edge)
        {
            if ((temp_edge->node != fin) && (from[temp_edge->node] == -1 ||
                    (s_p[temp_edge->node] > s_p[temp_node] + temp_edge->dist + temp_edge->cost)))
            {
                from[temp_edge->node] = temp_node;
                s_p[temp_edge->node] = s_p[temp_node] + temp_edge->dist + temp_edge->cost;
                push_aque(&queue, temp_edge->node);
            }
            temp_edge = temp_edge->next;
        }
    }


    if (fin == st)
        add_node_path(&path, st);
    else if (from[st] != -1)
    {
        temp_node = st;
        while (temp_node != -1)
        {
            add_node_path(&path, temp_node);
            temp_node = from[temp_node];
        }
    }
    resize_path(&path, path.len);
    delete_array(&from);
    delete_array(&s_p);
    return path;
}

int find_node(lgraph_t *graph, char name[])
{
    for (int i = 0; i < graph->size; i++)
        if (!strcmp(graph->node_arr[i].name, name))
            return i;
    return -1;
}

int add_node(lgraph_t *graph, char name[])
{
    int code;
    if (find_node(graph, name) != -1)
        return OK;

    code = resize_lgraph(graph, graph->size + 1);
    if (code != OK)     return code;

    graph->node_arr[graph->size - 1] = create_node(name);
    return OK;
}

int add_edge(lgraph_t *graph,
             char city1[], char city2[],
             int dist, int cost)
{
    int code;
    int node1 = find_node(graph, city1);
    int node2 = find_node(graph, city2);
    if (node1 == -1 || node2 == -1 || node1 == node2)
        return WRONG_FORMAT;

    edge_t* edge1 = create_edge(node1, dist, cost);
    edge_t* edge2 = create_edge(node2, dist, cost);

    if (!edge1 || !edge2)
        return ALLOC_FAIL;

    code = insert_ledge(&graph->node_arr[node1].list, edge2);
    code = insert_ledge(&graph->node_arr[node2].list, edge1);

    return code;
}
