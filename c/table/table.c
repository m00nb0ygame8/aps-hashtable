#include <stdlib.h>
#include <string.h>

#include "../include/ft_table.h"
#include "table.h"
#include "../include/ft_config.h"
#include "../include/ft_swiss.h"

ft_table* ft_table_new(void)
{
    ft_table* t = malloc(sizeof(ft_table));

    t->capacity = FT_INIT_SIZE;
    t->mask = t->capacity - 1;
    t->size = 0;

    t->ctrl = malloc(t->capacity);
    t->hashes = malloc(sizeof(uint64_t) * t->capacity);
    t->entries = malloc(sizeof(void*) * t->capacity);

    memset(t->ctrl, 0x80, t->capacity);

    return t;
}

void ft_table_destroy(ft_table* t)
{
    free(t->ctrl);
    free(t->hashes);
    free(t->entries);
    free(t);
}

size_t ft_table_size(ft_table* t)
{
    return t->size;
}