#include <stdlib.h>
#include <string.h>

#include "../include/ft_table.h"
#include "table.h"

#include "../include/ft_config.h"
#include "../include/ft_swiss.h"
#include "../include/ft_table.h"

/* forward declaration */
int ft_table_insert(ft_table*, void*, uint64_t);

static void ft_table_rehash(ft_table* newt, ft_table* oldt)
{
    for (size_t i = 0; i < oldt->capacity; i++)
    {
        if (!ft_swiss_is_empty(oldt->ctrl[i]))
        {
            ft_table_insert(newt,
                            oldt->entries[i],
                            oldt->hashes[i]);
        }
    }
}

void ft_table_resize(ft_table* t)
{
    size_t new_capacity =
        t->capacity * FT_GROWTH_FACTOR;

    ft_table newt;

    newt.capacity = new_capacity;
    newt.mask = new_capacity - 1;
    newt.size = 0;

    newt.ctrl = malloc(new_capacity);
    newt.hashes = malloc(sizeof(uint64_t) * new_capacity);
    newt.entries = malloc(sizeof(void*) * new_capacity);

    memset(newt.ctrl, 0x80, new_capacity);

    ft_table_rehash(&newt, t);

    free(t->ctrl);
    free(t->hashes);
    free(t->entries);

    *t = newt;
}