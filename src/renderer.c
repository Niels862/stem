#include "renderer.h"

static bool stem_use_format_option(stem_format_option_t post, 
                                   stem_format_option_t pre) {
    if (post.force > pre.force) {
        return post.emit;
    } 
    if (post.force < pre.force) {
        return pre.emit;
    }
    return post.emit || pre.emit;
}

static void stem_render_token(stem_token_t *token, stem_token_t *next, 
                            FILE *file) {
    bool emptyline = false, newline = false, space = false;

    if (stem_use_format_option(token->post.emptyline, next->pre.emptyline)) {
        emptyline = true;
    } else if (stem_use_format_option(token->post.newline, next->pre.newline)) {
        newline = true;
    } else if (stem_use_format_option(token->post.space, next->pre.space)) {
        space = true;
    }

    stem_strview_write(&token->text, file);

    if (emptyline) {
        fprintf(file, "\n\n");
    } else if (newline) {
        fprintf(file, "\n");
    } else if (space) {
        fprintf(file, " ");
    }
}

void stem_render(stem_tokenlist_t *tokens, FILE *file) {
    stem_token_iter_t iter;
    stem_token_iter_init(&iter, tokens);

    stem_token_t *token = stem_token_empty();
    stem_token_t *next  = iter.token;

    do {
        stem_token_iter_next(&iter);
        token = next;
        next  = iter.token;

        stem_render_token(token, next, file);
    } while (token != next);

    fprintf(file, "\n");
}
