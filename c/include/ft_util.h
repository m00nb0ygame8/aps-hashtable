#if defined(__GNUC__)
#define FT_LIKELY(x)   __builtin_expect(!!(x), 1)
#define FT_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define FT_LIKELY(x) (x)
#define FT_UNLIKELY(x) (x)
#endif