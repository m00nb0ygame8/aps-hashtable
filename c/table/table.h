#ifndef TABLE_INTERNAL_H
#define TABLE_INTERNAL_H

#include <stdint.h>
#include <stddef.h>

struct ft_table {
    size_t capacity;
    size_t mask;
    size_t size;

    uint8_t  *ctrl;
    uint64_t *hashes;
    void    **entries;
};

#endif