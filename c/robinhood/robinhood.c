#include "robinhood.h"
#include "../include/ft_robinhood.h"

size_t ft_rh_probe_distance(size_t slot, size_t ideal, size_t capacity)
{
    return rh_distance(slot, ideal, capacity);
}

int ft_rh_should_swap(size_t newcomer_dist, size_t resident_dist)
{
    return rh_swap_needed(newcomer_dist, resident_dist);
}