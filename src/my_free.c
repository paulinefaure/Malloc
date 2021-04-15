/*
** EPITECH PROJECT, 2021
** B-PSU-400-TLS-4-1-malloc-pauline.faure
** File description:
** my_free
*/

#include "malloc.h"

extern malloc_t *global;
extern void *mem_break;

void free_page(void)
{
    malloc_t *first_elem_free = NULL;
    malloc_t *last_elem_free = NULL;
    int result = 0;
    void *free_page = NULL;

    for (malloc_t *tmp = global; tmp != NULL; tmp = tmp->next) {
        if (tmp->is_free == true)
            last_elem_free = tmp;
        if (tmp->is_free == false)
            first_elem_free = tmp;
    }
    result = (last_elem_free - first_elem_free->next) / getpagesize();
    while (result) {
        free_page = sbrk(-getpagesize());
        if (free_page != (void *) -1)
            mem_break = free_page - getpagesize();
        result--;
    }
    first_elem_free->next = NULL;
}

void unalloc(void)
{
    malloc_t *begin = NULL;
    malloc_t *last = NULL;
    malloc_t *tmp = NULL;

    for (tmp = global; tmp != NULL; tmp = tmp->next) {
        if (tmp->is_free == true && begin == NULL)
            begin = tmp;
        if (tmp->is_free == false) {
            begin = NULL;
            last = tmp;
        }
    }
    if (last == NULL && brk(global) != -1) {
        global = NULL;
        mem_break = NULL;
        return;
    }
    free_page();
}

void free(void *ptr)
{
    malloc_t *tmp = NULL;

    for (tmp = global; tmp != NULL && tmp->addr != ptr; tmp = tmp->next);
    if (tmp == NULL )
        return;
    tmp->is_free = true;
    if (tmp->next == NULL)
        unalloc();
}