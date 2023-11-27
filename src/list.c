#include "list.h"
#include <stddef.h>
#include <stdlib.h>

// Libera los datos utilizados por un nodo de la lista
void freeeee(int_ll_t *node)
{
    node->data = 0;
    node->next = NULL;
    node->prev = NULL;
}

// Init list structure
int init_list(int_ll_t *list)
{
    list = malloc(sizeof(int_ll_t));
    list->data = 0;
    list->next = NULL;
    list->prev = NULL;
    return 0;
}

// Free list structure
int free_list(int_ll_t *list)
{
    if (list == NULL)
        return 1;
    int_ll_t *current = list;
    while (current != NULL)
    {
        int_ll_t *next = current->next;
        freeeee(current);
        current = next;
    }
    return 0;
}

// Get list size
int size_list(int_ll_t *list)
{
    int count = 0;
    int_ll_t *current = list;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

// Get element at index
int index_list(int_ll_t *list, int index, int *out_value)
{
    int_ll_t *current = list;
    if (list == NULL)
        return 1;
    if (index <= 0)
    {
        out_value = current->data;
        return 0;
    }
    int count = 0;
    while (current != NULL)
    {
        out_value = current->data;
        if (count == index)
            break;
        count++;
        current = current->next;
    }
    return 0;
}

// Insert element at index
int insert_list(int_ll_t *list, int index, int value)
{
    int_ll_t *new_node = malloc(sizeof(int_ll_t));
    new_node->data = value;
    if (list == NULL)
    {
        list = new_node;
        return 0;
    }

    if (index <= 0)
    {
        new_node->next = list;
        list->prev = new_node;
    }

    int_ll_t *current = list;
    int count = 0;
    while (current != NULL)
    {
        if (index == count)
        {
            if (current->prev != NULL)
            {
                int_ll_t *previous = current->prev;
                previous->next = new_node;
                new_node->prev = previous;
            }

            new_node->next = current;
            current->prev = new_node;
            return 0;
        }

        if (current->next == NULL) // legue al final de la lista asi que iserto new_node ahi
        {
            current->next = new_node;
            new_node->prev = current;
            return 0;
        }

        count++;
        current = current->next;
    }
    // si el indice es mayor o igual que el tamanno de la lista lo inserto en la ultima posicion
    int_ll_t *previous = current->prev;
    previous->next = new_node;
    new_node->prev = previous;
    return 0;
}

// Remove element at index
int remove_list(int_ll_t *list, int index, int *out_value)
{
    if (list == NULL)
        return 1;

    if (index <= 0)
    {
        out_value = list->data;
        int_ll_t *next = list->next;
        next->prev = NULL;
        freeeee(list);
        return 0;
    }

    int_ll_t *current = list;
    int count = 0;
    while (current != NULL)
    {
        if (count == index)
        {
            out_value = current->data;
            if (current->prev != NULL)
            {
                int_ll_t *previous = current->prev;
                previous->next = NULL;
            }
            if (current->next != NULL)
            {
                int_ll_t *next = current->next;
                next->prev = NULL;
            }
            free(current);
            return 0;
        }
        if (current->next == NULL)
        {
            out_value = current->data;
            int_ll_t *previous = current->prev;
            previous->next = NULL;
            free(current);
            return 0;
        }

        count++;
        current = current->next;
    }
    return 0;
}


