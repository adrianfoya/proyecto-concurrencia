#include "list.h"

// Init list structure
int init_list(int_ll_t *list)
{
    list->head = NULL;
    list->size = 0;
    pthread_mutex_init(&list->mutex, NULL);
    return 0;
}
// Free list structure
int free_list(int_ll_t *list)
{
    pthread_mutex_lock(&list->mutex);
    node *current = list->head;
    while (current != NULL)
    {
        node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    free(list);
    pthread_mutex_unlock(&list->mutex);

    return 0;
}

// Get list size
int size_list(int_ll_t *list)
{
    pthread_mutex_lock(&list->mutex);
    int size = list->size;
    pthread_mutex_unlock(&list->mutex);
    return size;
}

// Get element at index
int index_list(int_ll_t *list, int index, int *out_value)
{
    pthread_mutex_lock(&list->mutex);

    if(list->head==NULL)
    {
        pthread_mutex_unlock(&list->mutex);
        return 1;
    }

    if (index <= 0)
    {
        *out_value = list->head->data;
        pthread_mutex_unlock(&list->mutex);
        return 0;
    }
    
    int i = 0;
    node *current = list->head;
    while (current->next != NULL)
    {
        if(i==index)
        {
            *out_value = current->data;
            pthread_mutex_unlock(&list->mutex);
            return 0;
        }
        current = current->next;
        i++;
    }

    *out_value = current->data;
    pthread_mutex_unlock(&list->mutex);
    return 0;
}

// Insert element at index
int insert_list(int_ll_t *list, int index, int value)
{
    pthread_mutex_lock(&list->mutex);

    node *new_node = (node*)malloc(sizeof(node));

    if(index<=0)  
    {
        new_node->next = list->head;
        list->head = new_node;
        list->size ++;
        pthread_mutex_unlock(&list->mutex);
        return 0;
    }

    if(index > list->size)
    {
        node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
        list->size ++;
        pthread_mutex_unlock(&list->mutex);
        return 0;
    }
    
    node *current = list->head;
    for(int i = 0; i < index-1; i++)
    {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    list->size ++;
    pthread_mutex_unlock(&list->mutex);
    return 0;   
}

// Remove element at index
int remove_list(int_ll_t *list, int index, int *out_value)
{
    pthread_mutex_lock(&list->mutex);

    if(list->head == NULL) 
    {
        pthread_mutex_unlock(&list->mutex);
        return 1;
    }

    if(list->size==1)
    {
        *out_value = list->head->data;
        free(list->head);
        list->size --;
        pthread_mutex_unlock(&list->mutex);
        return 0; 
    }
    
    node *current = list->head;
    node *previous = NULL;

    if(index <= 0)
    {
        list->head = current->next;
        *out_value = current->data;
        free(current);
        list->size --;
        pthread_mutex_unlock(&list->mutex);
        return 0;
    }

    if(index >= list->size)
    {
        while (current->next != NULL)
        {
            previous = current;
            current = current->next;
        }
        *out_value = current->data;
        previous->next = NULL;
        free(current);
        list->size --;
        pthread_mutex_unlock(&list->mutex);
        return 0;
    }

    for (int i = 0; i < index - 1; i++)
    {
        current = current->next;
    }

    node *del = current->next;
    current->next = del->next;
    *out_value = del->data;
    free(del);
    list->size --;
    pthread_mutex_unlock(&list->mutex);
    return 0; 
}
