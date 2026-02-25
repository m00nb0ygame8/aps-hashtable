#include "xxh3.h"

uint64_t xxh3_hash_large(const uint8_t* data, size_t len)
{
    uint64_t acc[8];

    for (int i = 0; i < 8; i++)
        acc[i] = XXH3_INIT_ACC[i];

    size_t stripe;

    for (stripe = 0; stripe + 64 <= len; stripe += 64) {
        xxh3_accumulate_64B(
            acc,
            data + stripe,
            XXH3_kSecret + (stripe % (192 - 64))
        );
    }

    xxh3_scramble_acc(acc, XXH3_kSecret);

    return xxh3_merge_accs(acc, len);
}

