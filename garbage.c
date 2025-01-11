#include "garbage.h"

static void handle_error(t_garbage *garb, const char *message)
{
    free_garbage(garb);
    perror(message);
    exit(EXIT_FAILURE);
}
void free_garbage(t_garbage *garb)
{
    t_garbage_node *head;
    t_garbage_node *tmp;

    head = garb->head;
    while (head != NULL)
    {
        tmp = head;
        free(tmp->to_free);
        head = head->next;
        free(tmp);
    }
    garb->head = NULL;
    garb->tail = NULL;
}

static t_garbage_node *create_garb_node(t_garbage *garb)
{
    t_garbage_node *new;

    if (!garb)
    {
        fprintf(stderr, "Garbage isn't initialized!\n");
        exit(EXIT_FAILURE);
    }
    new = malloc(sizeof(t_garbage_node));
    if (!new) 
        handle_error(garb, "Failed to add garbage node!");
    new->to_free = NULL;
    new->size = 0;
    new->next = NULL;
    return (new);
}

void *better_malloc(t_garbage *garb, size_t size)
{
    void *ret;
    t_garbage_node *new;

    new = create_garb_node(garb);
    if (garb->head == NULL)
        garb->head = new;
    else
        garb->tail->next = new;
    garb->tail = new;
    ret = malloc(size);
    if (!ret)
        handle_error(garb, "Memory allocation failed!");
    new->size = size;
    new->to_free = ret;
    return (ret);
}

void init_garbage(t_garbage *garb)
{
    garb->head = NULL;
    garb->tail = NULL;
}