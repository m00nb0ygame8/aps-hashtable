#include <string.h>
#include "xxh3.h"

uint64_t xxh3_len_0to16(const uint8_t* data, size_t len)
{
    if (len == 0)
        return xxh3_avalanche(PRIME64_1);

    if (len <= 3) {
        uint32_t c1 = data[0];
        uint32_t c2 = data[len >> 1];
        uint32_t c3 = data[len - 1];

        uint32_t combined =
            (c1 << 16) |
            (c2 << 24) |
            (c3 << 0)  |
            ((uint32_t)len << 8);

        uint64_t bitflip = 0x9E3779B185EBCA87ULL;
        return xxh3_avalanche((uint64_t)combined ^ bitflip);
    }

    if (len <= 8) {
        uint64_t input =
            xxh3_read32(data) |
            ((uint64_t)xxh3_read32(data + len - 4) << 32);

        uint64_t bitflip = 0xC2B2AE3D27D4EB4FULL;
        uint64_t keyed = input ^ bitflip;

        return xxh3_avalanche(
            xxh3_mul128_fold(keyed, PRIME64_1 ^ len)
        );
    }

    uint64_t input_lo = xxh3_read64(data);
    uint64_t input_hi = xxh3_read64(data + len - 8);

    uint64_t bitflip1 = PRIME64_1;
    uint64_t bitflip2 = PRIME64_2;

    uint64_t acc =
        len +
        xxh3_mul128_fold(input_lo ^ bitflip1,
                         input_hi ^ bitflip2);

    return xxh3_avalanche(acc);
}
