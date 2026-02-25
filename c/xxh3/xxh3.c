#include "xxh3.h"

uint64_t ft_xxh3_64(const void* data, size_t len)
{
    const uint8_t* p = (const uint8_t*)data;

    if (len <= 16)
        return xxh3_len_0to16(p, len);

    if (len <= 128)
        return xxh3_len_17to128(p, len);

    if (len <= 240)
        return xxh3_len_129to240(p, len);

    return xxh3_hash_large(p, len);
}