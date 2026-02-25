#ifndef FT_XXH3_H
#define FT_XXH3_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t ft_xxh3_64(const void* data, size_t len);

#define FT_XXH3_SECRET_SIZE 192 // 192 bytes
#define FT_XXH3_STRIPE_LEN 64 // 64 bytes
#define FT_XXH3_ACC_NB 8 // 8 Parallel Accumulators


#ifdef __cplusplus
}
#endif

#endif