#include "xxh3.h"

uint64_t xxh3_len_129to240(const uint8_t* data, size_t len)
{
    uint64_t acc = (uint64_t)len * PRIME64_1;

    size_t i = 0;
    size_t secret_offset = 0;

    for (; i + 16 <= len; i += 16) {

        xxh3_mix16B_acc(
            &acc,
            data + i,
            XXH3_kSecret + (secret_offset % (192 - 16))
        );

        secret_offset += 16;
    }

    acc ^= acc >> 29;
    acc *= PRIME64_2;
    acc ^= acc >> 32;

    return xxh3_avalanche(acc);
}
