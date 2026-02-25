#ifndef FT_TABLE_H
#define FT_TABLE_H

#include <stdint.h>
#include <stddef.h>

typedef struct ft_table ft_table;

ft_table* ft_table_new(void);
void ft_table_destroy(ft_table* t);

int ft_table_insert(ft_table* t, void* entry, uint64_t hash);

int ft_table_contains(ft_table* t, void* entry, uint64_t hash);

int ft_table_remove(ft_table* t, void* entry, uint64_t hash);

void ft_table_resize(ft_table* t);

size_t ft_table_size(ft_table* t);

#endif