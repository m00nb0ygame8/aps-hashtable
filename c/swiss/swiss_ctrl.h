#ifndef SWISS_CTRL_H
#define SWISS_CTRL_H

#include <stdint.h>
#include "../include/ft_util.h"


static inline int ctrl_is_empty(uint8_t c)
{
    return c == FT_EMPTY;
}

static inline int ctrl_is_deleted(uint8_t c)
{
    return c == FT_DELETED;
}

static inline int ctrl_is_full(uint8_t c)
{
    return c < 0x80;
}

#endif