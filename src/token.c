#include "token.h"
#include "util.h"
#include <stdlib.h>

static stem_token_block_t *stem_token_block_alloc() {
    stem_token_block_t *block = stem_xmalloc(STEM_TOKENS_BLOCKSIZE);

    block->next = NULL;
    block->size = 0;

    return block;
}

stem_token_t *stem_token_empty() {
    static char empty_str = '\0';

    static stem_token_t empty_token = {
        .left = STEM_FMT_NONE,
        .right = STEM_FMT_NONE,
        .text = {
            .start = &empty_str, .end = &empty_str
        },
    };

    return &empty_token;
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
    stem_token_iter_t iter;
    stem_token_iter_init(&iter, list);

    fprintf(file, "{\n");

    while (!stem_token_iter_at_end(&iter)) {
        fprintf(file, "  ");
        stem_token_write(iter.token, file);
        fprintf(file, ",\n");

        stem_token_iter_next(&iter);
    }

    fprintf(file, "}\n");
}

void stem_token_iter_init(stem_token_iter_t *iter, stem_tokenlist_t *list) { 
    iter->block = list->first;
    iter->idx = 0;

    if (iter->block != NULL && iter->block->size > 0) {
        iter->token = &iter->block->data[iter->idx];
    } else {
        iter->token = stem_token_empty();
    }
}

void stem_token_iter_next(stem_token_iter_t *iter) {
    if (stem_token_iter_at_end(iter)) {
        return;
    }

    iter->idx++;
    if (iter->idx >= iter->block->size) {
        iter->block = iter->block->next;
        iter->idx = 0;
    }

    if (iter->block == NULL || iter->idx >= iter->block->size) {
        iter->token = stem_token_empty();
    } else {
        iter->token = &iter->block->data[iter->idx];
    }
}

bool stem_token_iter_at_end(stem_token_iter_t *iter) {
    return iter->token == stem_token_empty();
}
