/*
** EPITECH PROJECT, 2021
** B-PSU-400-TLS-4-1-malloc-pauline.faure
** File description:
** my_realloc
*/

#include <string.h>
#include "malloc.h"

extern malloc_t *global;

void *check_size(malloc_t *tmp, size_t size, void *ptr)
{
    void *new = NULL;

    if (size <= tmp->size) {
        tmp->size = size;
        return (ptr);
    }
    new = malloc(size);
    if (new == NULL)
        return (NULL);
    memcpy(new, ptr, tmp->size);
    free(ptr);
    return (new);
}

void *realloc(void *ptr, size_t size)
{
    void *new = NULL;

    if (size == 0) {
        if (ptr != NULL)
            free(ptr);
        return (NULL);
    }
    if (ptr == NULL) {
        new = malloc(size);
        return (new);
    }
    for (malloc_t *tmp = global; tmp != NULL; tmp = tmp->next) {
        if (tmp->addr == ptr) {
            new = check_size(tmp, size, ptr);
            break;
        }
    }
    return (new);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (ptr == NULL) {
        ptr = malloc(size * nmemb);
        return (ptr);
    } else
        ptr = realloc(ptr, (size * nmemb));
    return (ptr);
}