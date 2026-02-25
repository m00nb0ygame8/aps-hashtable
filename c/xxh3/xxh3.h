#ifndef XXH3_INTERNAL_H
#define XXH3_INTERNAL_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define PRIME64_1 0x9E3779B185EBCA87ULL
#define PRIME64_2 0xC2B2AE3D27D4EB4FULL
//Folding
static inline uint64_t
xxh3_mul128_fold(uint64_t lhs, uint64_t rhs)
{
#if defined(_MSC_VER) && defined(_M_X64)
    unsigned __int64 hi;
    unsigned __int64 lo = _umul128(lhs, rhs, &hi);
    return hi ^ lo;
#else
    __uint128_t product = (__uint128_t)lhs * (__uint128_t)rhs;
    return (uint64_t)(product >> 64) ^ (uint64_t)product;
#endif
}
//Avalanche
static inline uint64_t
xxh3_avalanche(uint64_t h)
{
    h ^= h >> 37;
    h *= 0x165667919E3779F9ULL;
    h ^= h >> 32;
    return h;
}
//Read Helpers
//TODO change to __builtin_memcpy
static inline uint32_t xxh3_read32(const void* ptr)
{
    uint32_t val;
    memcpy(&val, ptr, sizeof(val));
    return val;
}
static inline uint64_t xxh3_read64(const void* ptr)
{
    uint64_t val;
    memcpy(&val, ptr, sizeof(val));
    return val;
}
//Medium
static inline void xxh3_mix16B_acc(uint64_t* acc,
                const uint8_t* data,
                const uint8_t* secret)
{
    uint64_t lo = xxh3_read64(data);
    uint64_t hi = xxh3_read64(data + 8);

    uint64_t key_lo = xxh3_read64(secret);
    uint64_t key_hi = xxh3_read64(secret + 8);

    *acc += xxh3_mul128_fold(lo ^ key_lo,
                             hi ^ key_hi);
}
//Large
static void
xxh3_accumulate_64B(
    uint64_t* acc,
    const uint8_t* data,
    const uint8_t* secret)
{
    for (int i = 0; i < 8; i++) {

        uint64_t d = xxh3_read64(data + 8*i);
        uint64_t key = xxh3_read64(secret + 8*i);

        uint64_t x = d ^ key;

        acc[i] += d;
        acc[i] += xxh3_mul128_fold(x, 0x9E3779B185EBCA87ULL);
    }
}
static void
xxh3_scramble_acc(uint64_t* acc, const uint8_t* secret)
{
    for (int i = 0; i < 8; i++) {
        uint64_t key = xxh3_read64(secret + 8*i);

        uint64_t x = acc[i];
        x ^= x >> 47;
        x ^= key;
        x *= 0x9E3779B185EBCA87ULL;

        acc[i] = x;
    }
}
static uint64_t
xxh3_merge_accs(uint64_t* acc, size_t len)
{
    uint64_t result = len * 0x9E3779B185EBCA87ULL;

    for (int i = 0; i < 8; i++) {
        result += xxh3_mul128_fold(
            acc[i],
            0xC2B2AE3D27D4EB4FULL
        );
    }

    return xxh3_avalanche(result);
}
//dispatchers
uint64_t xxh3_len_0to16(const uint8_t* data, size_t len);
uint64_t xxh3_len_17to128(const uint8_t* data, size_t len);
uint64_t xxh3_len_129to240(const uint8_t* data, size_t len);
uint64_t xxh3_hash_large(const uint8_t* data, size_t len);

//SECRET
#if defined(_MSC_VER)
extern __declspec(align(64)) const uint8_t XXH3_kSecret[192];
#else
extern const uint8_t XXH3_kSecret[192] __attribute__((aligned(64)));
#endif
extern const uint8_t XXH3_kSecret[192];
//XXH3_INIT_ACC
#if defined(_MSC_VER)
extern __declspec(align(64)) const uint64_t XXH3_INIT_ACC[8];
#else
extern const uint64_t XXH3_INIT_ACC[8] __attribute__((aligned(64)));
#endif
extern const uint64_t XXH3_INIT_ACC[8];

#endif
