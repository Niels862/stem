#include "renderer.h"
#include "util.h"

typedef struct {
    FILE *file;
    size_t indent;
    bool clean_line;
} stem_render_context_t;

static void stem_render_context_init(stem_render_context_t *rctx, FILE *file) {
    rctx->file = file;
    rctx->indent = 0;
    rctx->clean_line = true;
}

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

static void stem_render_token(stem_build_context_t *bctx, 
                              stem_render_context_t *rctx, 
                              stem_token_t *token, stem_token_t *next) {
    bool emptyline = false, newline = false, space = false;

    if (stem_use_format_option(token->post.emptyline, next->pre.emptyline)) {
        emptyline = true;
    } else if (stem_use_format_option(token->post.newline, next->pre.newline)) {
        newline = true;
    } else if (stem_use_format_option(token->post.space, next->pre.space)) {
        space = true;
    }

    switch (token->type) {
        case STEM_TOKEN_TEXT:
            if (rctx->clean_line) {
                stem_write_n_chars(' ', rctx->indent, rctx->file);
            }
            stem_strview_write(&token->text, rctx->file);
            rctx->clean_line = false;
            break;

        case STEM_TOKEN_INDENT:
            rctx->indent += bctx->profile->indent.n;
            break;

        case STEM_TOKEN_DEDENT:
            rctx->indent -= bctx->profile->indent.n;
            break;
    }

    if (emptyline) {
        fprintf(rctx->file, "\n\n");
        rctx->clean_line = true;
    } else if (newline) {
        fprintf(rctx->file, "\n");
        rctx->clean_line = true;
    } else if (space && !rctx->clean_line) {
        fprintf(rctx->file, " ");
    }
}

void stem_render_phase(stem_build_context_t *bctx, FILE *file) {
    stem_render_context_t rctx;
    stem_render_context_init(&rctx, file);

    stem_token_iter_t iter;
    stem_token_iter_init(&iter, bctx->tokens);

    stem_token_t *token = stem_token_empty();
    stem_token_t *next  = iter.token;

    do {
        stem_token_iter_next(&iter);
        token = next;
        next  = iter.token;

        stem_render_token(bctx, &rctx, token, next);
    } while (token != next);
}
