#include "xxh3.h"

#if defined(_MSC_VER)
__declspec(align(64))
#else
__attribute__((aligned(64)))
#endif
const uint64_t XXH3_INIT_ACC[8] = {
    0x9E3779B185EBCA87ULL,
    0xC2B2AE3D27D4EB4FULL,
    0x165667B19E3779F9ULL,
    0x85EBCA77C2B2AE63ULL,
    0x27D4EB2F165667C5ULL,
    0x9E3779B97F4A7C15ULL,
    0xD2B74407B1CE6E93ULL,
    0xCA5A826395121157ULL
};
