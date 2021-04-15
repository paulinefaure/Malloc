/*
** EPITECH PROJECT, 2021
** B-PSU-400-TLS-4-1-malloc-pauline.faure
** File description:
** malloc
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

typedef struct malloc_s
{
    size_t size;
    bool is_free;
    void *addr;
    struct malloc_s *next;
} malloc_t;

#define POWER(x) ((( (x) - 1) >> 2) << 2) + 4

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif /* !MALLOC_H_ */
