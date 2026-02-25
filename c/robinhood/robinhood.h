#ifndef ROBINHOOD_INTERNAL_H
#define ROBINHOOD_INTERNAL_H

#include <stddef.h>
#include "../include/ft_util.h"


static inline size_t rh_distance(size_t slot, size_t ideal, size_t cap)
{
    return (slot + cap - ideal) & (cap - 1);
}

static inline int rh_swap_needed(size_t new_dist, size_t old_dist)
{
    return new_dist > old_dist;
}

#endif