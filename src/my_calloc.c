/*
** EPITECH PROJECT, 2021
** B-PSU-400-TLS-4-1-malloc-pauline.faure
** File description:
** my_calloc
*/

#include <string.h>
#include "malloc.h"

void *calloc(size_t nmemb, size_t size)
{
    void *ptr = NULL;

    ptr = malloc(size * nmemb);
    if (ptr == NULL)
        return (NULL);
    memset(ptr, 0, size *nmemb);
    return (ptr);
}