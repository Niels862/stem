#include "pool.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>

static stem_pool_block_t *stem_pool_alloc_new_block(size_t blocksize, 
                                                    stem_pool_block_t *next) {
    size_t size = sizeof(stem_pool_block_t) + blocksize;
    stem_pool_block_t *block = stem_xmalloc(size);

    block->next = next;
    block->size = 0;

    return block;
}

void stem_pool_init(stem_pool_t *pool, size_t blocksize) {
    pool->blocksize = blocksize;
    pool->first = stem_pool_alloc_new_block(blocksize, NULL);
}

void stem_pool_free(stem_pool_t *pool) {
    stem_pool_block_t *block = pool->first;

    while (block != NULL) {
        stem_pool_block_t *next = block->next;
        free(block);

        block = next;
    }
}

void *stem_pool_alloc(stem_pool_t *pool, size_t size) {
    assert(size <= pool->blocksize);

    stem_pool_block_t *block = pool->first;

    if (block->size + size >= pool->blocksize) {
        block = stem_pool_alloc_new_block(pool->blocksize, pool->first);
        pool->first = block;
    }

    void *p = block->data + block->size;
    block->size += size;

    return p;
}
