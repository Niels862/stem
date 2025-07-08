#include "emitter.h"

static bool stem_insert(stem_format_attr_t right, stem_format_attr_t left,
                        stem_format_attr_t yes, stem_format_attr_t no, 
                        stem_format_attr_t force) {
    if (right & force || left & force) {
        return true;
    }

    if (right & no || left & no) {
        return false;
    }

    return right & yes || left & yes;
}
 
static bool stem_insert_space(stem_format_attr_t right, 
                              stem_format_attr_t left) {
    return stem_insert(right, left, STEM_FMT_SPACE, STEM_FMT_NO_SPACE, 
                       STEM_FMT_FORCE_SPACE);
}

static bool stem_insert_newline(stem_format_attr_t right,
                                stem_format_attr_t left) {
    return stem_insert(right, left, STEM_FMT_NEWLINE, STEM_FMT_NO_NEWLINE,
                       STEM_FMT_FORCE_NEWLINE);
}

static void stem_emit_token(stem_token_t *token, stem_token_t *next, 
                            FILE *file) {
    stem_strview_write(&token->text, file);

    bool space = stem_insert_space(token->right, next->left);
    bool newline = stem_insert_newline(token->right, next->left);
    int i = 5;

    if (newline) {
        fprintf(file, "\n");
    } else if (space) {
        fprintf(file, " ");
    }
}

void stem_emit(stem_tokenlist_t *tokens, FILE *file) {
    stem_token_iter_t iter;
    stem_token_iter_init(&iter, tokens);

    stem_token_t *token = stem_token_empty();
    stem_token_t *next  = iter.token;

    do {
        stem_token_iter_next(&iter);
        token = next;
        next  = iter.token;

        stem_emit_token(token, next, file);
    } while (token != next);

    fprintf(file, "\n");
}
