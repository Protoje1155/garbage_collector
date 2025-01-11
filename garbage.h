#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct s_garbage_node t_garbage_node;
typedef struct s_garbage t_garbage;

typedef struct s_garbage_node
{
    void *to_free;
    size_t size;
    t_garbage_node *next;
} t_garbage_node;

typedef struct s_garbage
{
    t_garbage_node *head;
    t_garbage_node *tail;
} t_garbage;

void free_garbage(t_garbage *garb);
void *better_malloc(t_garbage *garb, size_t size);
void init_garbage(t_garbage *garb);

#endif
