#ifndef FT_SWISS_H
#define FT_SWISS_H

#include <stdint.h>
#include <stddef.h>

#define FT_EMPTY   ((uint8_t)0x80)
#define FT_DELETED ((uint8_t)0xFE)

uint8_t ft_swiss_h2(uint64_t hash);
size_t  ft_swiss_probe_start(uint64_t hash, size_t capacity);
size_t  ft_swiss_probe_next(size_t pos, size_t capacity);

int ft_swiss_is_empty(uint8_t ctrl);
int ft_swiss_is_deleted(uint8_t ctrl);
int ft_swiss_match(uint8_t ctrl, uint8_t fingerprint);

#endif