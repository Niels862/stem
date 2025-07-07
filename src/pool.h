#ifndef STEM_POOL_H
#define STEM_POOL_H

#include <stddef.h>

typedef struct stem_pool_block_t {
    struct stem_pool_block_t *next;
    size_t size;
    char data[];
} stem_pool_block_t;

typedef struct {
    size_t blocksize;
    stem_pool_block_t *first;
} stem_pool_t;

void stem_pool_init(stem_pool_t *pool, size_t blocksize);

void stem_pool_free(stem_pool_t *pool);

void *stem_pool_alloc(stem_pool_t *pool, size_t size);

#endif
