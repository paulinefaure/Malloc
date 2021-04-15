/*
** EPITECH PROJECT, 2021
** B-PSU-400-TLS-4-1-malloc-pauline.faure
** File description:
** my_malloc
*/

#include <stdio.h>
#include "malloc.h"

malloc_t *global = NULL;
void *mem_break = NULL;

void add_to_list(malloc_t *init)
{
    malloc_t *tmp = NULL;

    if (global == NULL) {
        global = init;
        return;
    }
    for (tmp = global; tmp->next != NULL; tmp = tmp->next);
    tmp->next = init;
    return;
}

void *move_brk(size_t size, malloc_t *elem)
{
    void *page = NULL;

    if (elem != NULL) {
        elem += sizeof(malloc_t) + elem->size;
    }
    while (mem_break < (void *) (elem + sizeof(malloc_t) + size)) {
        page = sbrk(getpagesize());
        if (page != (void *) -1) {
            mem_break = page;
            if (elem == NULL)
                elem = mem_break;
        } else
            return (NULL);
    }
    return (elem);
}

void *malloc(size_t size)
{
    malloc_t *init = NULL;
    malloc_t *tmp = NULL;

    if (size == 0)
        return (NULL);
    size = POWER(size);
    for (tmp = global; tmp != NULL && tmp->next != NULL; tmp = tmp->next);
    init = move_brk(size, tmp);
    if (init == NULL)
        return (NULL);
    init->size = size;
    init->is_free = false;
    init->addr = init + sizeof(malloc_t);
    init->next = NULL;
    add_to_list(init);
    return (init->addr);
}