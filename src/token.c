#include "token.h"
#include "util.h"
#include <stdlib.h>

static char stem_empty_str = '\0';

static stem_token_t stem_empty_token = {
    .left = STEM_FMT_NONE, 
    .right = STEM_FMT_NONE,
    .text = {
        .start = &stem_empty_str,
        .end = &stem_empty_str,
    },
};

static stem_token_block_t *stem_token_block_alloc() {
    stem_token_block_t *block = stem_xmalloc(STEM_TOKENS_BLOCKSIZE);

    block->next = NULL;
    block->size = 0;

    return block;
}

void stem_token_emit(stem_tokenlist_t *list, char *str, 
                     stem_format_attr_t left, 
                     stem_format_attr_t right) {
    stem_token_block_t *block = list->last;

    if (block->size + 1 >= STEM_TOKENS_N_PER_BLOCK) {
        list->last = block = block->next = stem_token_block_alloc();
    }

    stem_token_t *token = &block->data[block->size];

    stem_strview_init_in_pool(&token->text, &list->pool, str);
    token->left = left;
    token->right = right;

    block->size++;
}

void stem_token_write(stem_token_t *token, FILE *file) {
    stem_strview_write_literal(&token->text, file);
}

void stem_tokenlist_init(stem_tokenlist_t *list) {
    list->first = list->last = stem_token_block_alloc();
    stem_pool_init(&list->pool, STEM_TOKENS_POOL_BLOCKSIZE);
}

void stem_tokenlist_free(stem_tokenlist_t *list) {
    stem_token_block_t *block = list->first;

    while (block != NULL) {
        stem_token_block_t *next = block->next;
        free(block);

        block = next;
    }

    stem_pool_free(&list->pool);
}

void stem_tokenlist_write(stem_tokenlist_t *list, FILE *file) {
    stem_token_block_t *block = list->first;

    fprintf(file, "{\n");

    while (block != NULL) {
        for (size_t i = 0; i < block->size; i++) {
            fprintf(file, "  ");
            stem_token_write(&block->data[i], file);
            fprintf(file, ",\n");
        }

        block = block->next;
    }

    fprintf(file, "}\n");
}

static stem_token_t *stem_token_at_block_idx(stem_token_block_t *block, 
                                             size_t idx) {
    while (idx > block->size) {
        if (block->next == NULL) {
            return &stem_empty_token;
        }
        idx -= block->size;
        block = block->next;
    }

    return &block->data[idx];
}

void stem_token_iter_init(stem_token_iter_t *iter, stem_tokenlist_t *list) { 
    iter->block = list->first;
    iter->idx = 0;
    iter->token = stem_token_at_block_idx(iter->block, iter->idx);
    iter->next = stem_token_at_block_idx(iter->block, iter->idx + 1);
}

void stem_token_iter_next(stem_token_iter_t *iter) {
    if (!stem_token_iter_at_end(iter)) {
        iter->idx++;

        if (iter->idx >= iter->block->size) {

        }
    }

    iter->token = iter->next;
}

bool stem_token_iter_at_end(stem_token_iter_t *iter) {
    (void)iter;
    return false;
}
