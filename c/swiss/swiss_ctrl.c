#include "../include/ft_swiss.h"
#include "swiss_ctrl.h"


uint8_t ft_swiss_h2(uint64_t hash)
{
    return (uint8_t)((hash >> 57) & 0x7F);
}

size_t ft_swiss_probe_start(uint64_t hash,
                            size_t capacity)
{
    return (size_t)(hash & (capacity - 1));
}


size_t ft_swiss_probe_next(size_t pos,
                           size_t capacity)
{
    return (pos + 1) & (capacity - 1);
}


int ft_swiss_is_empty(uint8_t ctrl)
{
    return ctrl_is_empty(ctrl);
}

int ft_swiss_is_deleted(uint8_t ctrl)
{
    return ctrl_is_deleted(ctrl);
}

int ft_swiss_match(uint8_t ctrl,
                   uint8_t fingerprint)
{
    return ctrl_is_full(ctrl) && ctrl == fingerprint;
}