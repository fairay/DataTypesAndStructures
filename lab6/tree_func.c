#include "head.h"

/// Apply functioons
void print_head(char head[])
{
    printf("   ");
    if (strlen(head))
        for (int i = 0; i < strlen(head) - 1; i++)
        {
            if (head[i] == head[i + 1])
                printf("  ");
            else
                printf("%c ", UD);
        }
}

/// Node CDIO
int create_node(tree_t *node, int val)
{
    (*node) = (tree_t)malloc(sizeof(node_t));
    if (*node)
    {
        (*node)->val = val;
        (*node)->bal = 0;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return OK;
    }
    else
        return ALLOC_FAIL;
}

void print_node(tree_t tree, char head[])
{
    if (!tree)       return;

    int depth = strlen(head);
    char l_head[depth + 2];
    char r_head[depth + 2];
    char arrow[4] = "\0";

    if (tree->right)
    {
        strcpy(r_head, head);
        strcat(r_head, "r");
        print_node(tree->right, r_head);
        print_head(r_head);
        printf("%c \n", UD);
    }

    if (depth)
    {
        if (head[depth - 1] == 'l')
            sprintf(arrow, "%c%c", UR, LR);
        else
            sprintf(arrow, "%c%c", DR, LR);
    }

    print_head(head);
    // printf("%s%d, %d\n", arrow, tree->val, tree->bal);
    printf("%s%d\n", arrow, tree->val);

    if (tree->left)
    {
        strcpy(l_head, head);
        strcat(l_head, "l");
        print_head(l_head);
        printf("%c \n", UD);
        print_node(tree->left, l_head);
    }
}

void clean_node(tree_t *node)
{
    free(*node);
    (*node) = NULL;
}

/// Tree CDIO
tree_t create_tree(void)
{
    return NULL;
}

int finput_tree(char file_name[], tree_t *tree)
{
    int sc, number;
    FILE *f = fopen(file_name, "r");
    if (!f)     return WRONG_FILE;

    sc = fscanf(f, "%d", &number);
    while (sc == 1)
    {
        add_node(tree, number);
        sc = fscanf(f, "%d", &number);
    }
    fclose(f);
    if (sc != EOF)  return WRONG_FORMAT;
    return OK;
}

void print_tree(tree_t tree)
{
    printf("\n");
    print_node(tree, "");
    printf("\n");
}

void delete_tree(tree_t *tree)
{
    if (*tree)
    {
        delete_tree(&(*tree)->left);
        delete_tree(&(*tree)->right);
        free(*tree);
        (*tree) = NULL;
    }
}

/// Tree functionds
int add_node(tree_t *tree, int val)
{
    int code = OK;
    tree_t new_node;
    if (!(*tree))
    {
        code = create_node(&new_node, val);
        if (code)      return code;
        (*tree) = new_node;
    }
    else
    {
        if (val > (*tree)->val)
            add_node(&(*tree)->right, val);
        else if (val < (*tree)->val)
            add_node(&(*tree)->left, val);
    }
    return code;
}

int delete_node(tree_t *tree, int val)
{
    tree_t* del_node = find_node(tree, val);
    tree_t* exchange;
    tree_t temp_node;

    if (!del_node)
        return NO_ELEMENT;

    if ((*del_node)->right && (*del_node)->left)
    {
        exchange = find_exchange(del_node);
        (*del_node)->val = (*exchange)->val;
        delete_node(exchange, (*exchange)->val);
    }
    else if ((*del_node)->right)
    {
        temp_node = (*del_node);
        (*del_node) = temp_node->right;
        free(temp_node);
    }
    else if ((*del_node)->left)
    {
        temp_node = (*del_node);
        (*del_node) = temp_node->left;
        free(temp_node);
    }
    else
        // Easy-pesay
    {
        free(*del_node);
        (*del_node) = NULL;
    }
    return OK;
}

/// Find functions
tree_t* find_node(tree_t* tree, int val)
{
    if (!(*tree))
        return NULL;
    else if (val > (*tree)->val)
        return find_node(&(*tree)->right, val);
    else if (val < (*tree)->val)
        return find_node(&(*tree)->left, val);
    else
        return tree;
}

tree_t* find_exchange(tree_t* tree)
{
    tree_t* temp_node = &(*tree)->left;
    while ((*temp_node)->right)
        temp_node = &(*temp_node)->right;
    return temp_node;
}

int find_cmp(tree_t tree, int val)
{
    if (!tree)
        return 0;
    else if (val > tree->val)
        return find_cmp(tree->right, val) + 1;
    else if (val < tree->val)
        return find_cmp(tree->left, val) + 1;
    else
        return 1;
}

int find_depth(tree_t tree)
{
    if (!tree)
        return 0;

    int l = find_depth(tree->left);
    int r = find_depth(tree->right);
    return MAX(l, r) + 1;
}

int tree_cmp_count(tree_t tree, int depth)
{
    if (!tree)
        return 0;
    else
        return depth +
                tree_cmp_count(tree->left, depth + 1) +
                tree_cmp_count(tree->right, depth + 1);
}

int tree_n_count(tree_t tree)
{
    if (!tree)
        return 0;
    else
        return 1 + tree_n_count(tree->left) + tree_n_count(tree->right);
}

float tree_aver_count(tree_t tree)
{
    return (float)tree_cmp_count(tree, 1) / tree_n_count(tree);
}

/// Traversals
void prefix_trav(tree_t tree)
{
    if (tree)
    {
        printf("%d ", tree->val);
        prefix_trav(tree->left);
        prefix_trav(tree->right);
    }
}

void postfix_trav(tree_t tree)
{
    if (tree)
    {
        postfix_trav(tree->left);
        postfix_trav(tree->right);
        printf("%d ", tree->val);
    }
}

void infix_trav(tree_t tree)
{
    if (tree)
    {
        infix_trav(tree->left);
        printf("%d ", tree->val);
        infix_trav(tree->right);
    }
}
