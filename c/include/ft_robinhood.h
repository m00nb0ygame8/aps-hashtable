#ifndef FT_ROBINHOOD_H
#define FT_ROBINHOOD_H

#include <stddef.h>

size_t ft_rh_probe_distance(size_t slot, size_t ideal, size_t capacity);

int ft_rh_should_swap(size_t newcomer_dist, size_t resident_dist);
#endif