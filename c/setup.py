from setuptools import setup, Extension

module = Extension(
    "hashtable",
    sources=[
        "py_hashtable.c",

        "xxh3/xxh3.c",
        "xxh3/xxh3_tiny.c",
        "xxh3/xxh3_small.c",
        "xxh3/xxh3_medium.c",
        "xxh3/xxh3_large.c",
        "xxh3/xxh3_accumulate.c",
        "xxh3/xxh3_finalize.c",
        "xxh3/xxh3_secrets.c",

        "swiss/swiss_ctrl.c",

        "robinhood/robinhood.c",

        "table/table.c",
        "table/table_insert.c",
        "table/table_lookup.c",
        "table/table_remove.c",
        "table/table_resize.c",
    ],
    include_dirs=[
        "include",
        "xxh3",
        "swiss",
        "robinhood",
        "table",
    ],
    extra_compile_args=[
        "-O3",
        "-std=c11",
    ],
)

setup(
    name="hashtable",
    version="0.1",
    ext_modules=[module],
)
