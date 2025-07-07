#ifndef STEM_TOKEN_H
#define STEM_TOKEN_H

#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    STEM_FMT_NONE           = 0x0,
    STEM_FMT_SPACE          = 0x1,
    STEM_FMT_NEWLINE        = 0x2,
} stem_format_attr_t;

typedef struct {
    stem_strview_t text;
    stem_format_attr_t left;
    stem_format_attr_t right;
} stem_token_t;

typedef struct stem_token_block_t {
    struct stem_token_block_t *next;
    size_t size;
    stem_token_t data[];
} stem_token_block_t;

#define STEM_TOKENS_BLOCKSIZE 4096
#define STEM_TOKENS_N_PER_BLOCK \
        (STEM_TOKENS_BLOCKSIZE - sizeof(stem_token_block_t)) \
            / sizeof(stem_token_t)

#define STEM_TOKENS_POOL_BLOCKSIZE 4096

/* Append to last */
typedef struct { 
    stem_token_block_t *first;
    stem_token_block_t *last;
    stem_pool_t pool;
} stem_tokenlist_t;

typedef struct {
    stem_token_block_t *block;
    size_t idx;

    stem_token_t *token;
    stem_token_t *next;
} stem_token_iter_t;

void stem_token_emit(stem_tokenlist_t *list, char *str, 
                     stem_format_attr_t left, 
                     stem_format_attr_t right);

void stem_token_write(stem_token_t *token, FILE *file);

void stem_tokenlist_init(stem_tokenlist_t *list);

void stem_tokenlist_free(stem_tokenlist_t *list);

void stem_tokenlist_write(stem_tokenlist_t *list, FILE *file);

void stem_token_iter_init(stem_token_iter_t *iter, stem_tokenlist_t *list);

void stem_token_iter_next(stem_token_iter_t *iter);

bool stem_token_iter_at_end(stem_token_iter_t *iter);

#endif
