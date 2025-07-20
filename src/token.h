#ifndef STEM_TOKEN_H
#define STEM_TOKEN_H

#include "strutil.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool emit;
    bool force;
} stem_format_option_t;

typedef struct {
    stem_strview_t text;
    struct {
        stem_format_option_t space;
        stem_format_option_t newline;
        stem_format_option_t emptyline;
    } pre;
    struct {
        stem_format_option_t space;
        stem_format_option_t newline;
        stem_format_option_t emptyline;
    } post;
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
} stem_token_iter_t;

stem_token_t *stem_token_empty();

stem_token_t *stem_token_emit(stem_tokenlist_t *list, char *str);

void stem_token_write(stem_token_t *token, FILE *file);

void stem_tokenlist_init(stem_tokenlist_t *list);

void stem_tokenlist_free(stem_tokenlist_t *list);

void stem_tokenlist_write(stem_tokenlist_t *list, FILE *file);

void stem_token_iter_init(stem_token_iter_t *iter, stem_tokenlist_t *list);

void stem_token_iter_next(stem_token_iter_t *iter);

bool stem_token_iter_at_end(stem_token_iter_t *iter);

#endif
