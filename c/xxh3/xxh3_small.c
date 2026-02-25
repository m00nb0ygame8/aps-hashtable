#include "xxh3.h"



uint64_t xxh3_len_17to128(const uint8_t* data, size_t len)
{
    uint64_t acc = (uint64_t)len * PRIME64_1;

    xxh3_mix16B_acc(&acc, data, XXH3_kSecret + 0);
    xxh3_mix16B_acc(&acc, data + len - 16, XXH3_kSecret + 16);

    if (len > 32) {
        xxh3_mix16B_acc(&acc, data + 16, XXH3_kSecret + 32);
        xxh3_mix16B_acc(&acc, data + len - 32, XXH3_kSecret + 48);
    }

    if (len > 64) {
        xxh3_mix16B_acc(&acc, data + 32, XXH3_kSecret + 64);
        xxh3_mix16B_acc(&acc, data + len - 48, XXH3_kSecret + 80);
    }

    if (len > 96) {
        xxh3_mix16B_acc(&acc, data + 48, XXH3_kSecret + 96);
        xxh3_mix16B_acc(&acc, data + len - 64, XXH3_kSecret + 112);
    }

    return xxh3_avalanche(acc);
}
