#include "head.h"

int finput_tree_avl(char file_name[], tree_t *tree)
{
    int sc, number;
    FILE *f = fopen(file_name, "r");
    if (!f)     return WRONG_FILE;

    sc = fscanf(f, "%d", &number);
    while (sc == 1)
    {
        add_node_avl(tree, number);
        sc = fscanf(f, "%d", &number);
    }
    fclose(f);
    if (sc != EOF)  return WRONG_FORMAT;
    return OK;
}


int add_node_avl(tree_t *tree, int val)
{
    int code = OK;
    int old_bal = -2;
    tree_t new_node;

    if (!(*tree))
    {
        code = create_node(&new_node, val);
        (*tree) = new_node;
    }
    else
    {
        if (val > (*tree)->val)
        {
            if ((*tree)->right)
                old_bal = (*tree)->right->bal;

            add_node_avl(&(*tree)->right, val);

            if ((old_bal == -2) || (old_bal == 0 && (*tree)->right->bal != 0))
                (*tree)->bal += 1;
        }
        else if (val < (*tree)->val)
        {
            if ((*tree)->left)
                old_bal = (*tree)->left->bal;

            add_node_avl(&(*tree)->left, val);

            if ((old_bal == -2) || (old_bal == 0 && (*tree)->left->bal != 0))
                (*tree)->bal -= 1;
        }
        balance_node(tree);
    }
    return code;
}

int delete_node_avl(tree_t *tree, int val)
{
    int old_bal = -2, code;
    tree_t temp_node;
    tree_t* exchange;

    if (!(*tree))
        return NO_ELEMENT;

    if (val > (*tree)->val)
    {
        if ((*tree)->right)
            old_bal = (*tree)->right->bal;

        code = delete_node_avl(&(*tree)->right, val);
        if (code == NO_ELEMENT)     return code;
        if (old_bal != -2)
        {
            if (!(*tree)->right)
                (*tree)->bal -= 1;
            else if (old_bal != 0 && (*tree)->right->bal == 0)
                (*tree)->bal -= 1;
            balance_node(tree);
        }
    }
    else if (val < (*tree)->val)
    {
        if ((*tree)->left)
            old_bal = (*tree)->left->bal;

        code = delete_node_avl(&(*tree)->left, val);
        if (code == NO_ELEMENT)     return code;

        if (old_bal != -2)
        {
            if (!(*tree)->left)
                (*tree)->bal += 1;
            else if (old_bal != 0 && (*tree)->left->bal == 0)
                (*tree)->bal += 1;
            balance_node(tree);
        }
    }
    else
    {
        if ((*tree)->right && (*tree)->left)
        {
            exchange = find_exchange(tree);
            (*tree)->val = (*exchange)->val;
            old_bal = (*tree)->left->bal;

            delete_node_avl(&(*tree)->left, (*exchange)->val);

            if (old_bal != -2)
            {
                if (!(*tree)->left)
                    (*tree)->bal += 1;
                else if (old_bal != 0 && (*tree)->left->bal == 0)
                    (*tree)->bal += 1;
                balance_node(tree);
            }
        }
        else if ((*tree)->right)
        {
            temp_node = (*tree)->right;
            clean_node(tree);
            (*tree) = temp_node;
        }
        else if ((*tree)->left)
        {
            temp_node = (*tree)->left;
            clean_node(tree);
            (*tree) = temp_node;
        }
        else
            clean_node(tree);
    }

    return OK;
}

int find_depth_avl(tree_t tree)
{
    if (!tree)
        return 0;

    if (tree->bal >= 0)
        return find_depth_avl(tree->left) + tree->bal + 1;
    else
        return find_depth_avl(tree->right) - tree->bal + 1;
}



/// Ballancing functions
int balance_node(tree_t *tree)
{
    int flag = 1;
    if ((*tree)->bal >= 2)
    {
        if ((*tree)->right->bal >= 0)
            l_rotate(tree);
        else
            dl_rotate(tree);
    }
    else if ((*tree)->bal <= -2)
    {
        if ((*tree)->left->bal <= 0)
            r_rotate(tree);
        else
            dr_rotate(tree);
    }
    else
        flag = 0;

    return flag;
}

int deep_balance(tree_t *tree)
{
    if (!(*tree))
        return 0;

    int l = deep_balance(&(*tree)->left);
    int r = deep_balance(&(*tree)->right);
    int is_balanced = 0;

    (*tree)->bal = r - l;

    is_balanced = balance_node(tree);

    if (is_balanced)
        deep_balance(tree);

    return find_depth(*tree);
}

void r_rotate(tree_t *tree)
{
    tree_t root = (*tree);
    tree_t left = (*tree)->left;

    root->bal += 1 - left->bal;
    left->bal += 1;

    root->left = left->right;
    left->right = root;
    (*tree) = left;
}

void l_rotate(tree_t *tree)
{
    tree_t root = (*tree);
    tree_t right = (*tree)->right;

    root->bal -= 1 + right->bal;
    right->bal -= 1;

    root->right = right->left;
    right->left = root;
    (*tree) = right;
}

void dr_rotate(tree_t *tree)
{
    tree_t root = (*tree);
    tree_t left = (*tree)->left;
    tree_t lr = left->right;

    left->bal -= 1;
    if (lr->bal > 0)
        left->bal -= lr->bal;
    root->bal += 2;
    if (lr->bal < 0)
        root->bal -= lr->bal;

    root->left = lr->right;
    left->right = lr->left;
    lr->left = left;
    lr->right = root;
    (*tree) = lr;
    (*tree)->bal = find_depth((*tree)->right) - find_depth((*tree)->left);
}

void dl_rotate(tree_t *tree)
{
    tree_t root = (*tree);
    tree_t right = (*tree)->right;
    tree_t rl = right->left;

    right->bal += 1;
    root->bal -= 2;
    if (rl->bal < 0)
        right->bal -= rl->bal;
    else
        root->bal -= rl->bal;

    root->right = rl->left;
    right->left = rl->right;
    rl->left = root;
    rl->right = right;
    (*tree) = rl;
    (*tree)->bal = find_depth((*tree)->right) - find_depth((*tree)->left);
}
