#include "targets/emit.h"
#include <stdlib.h>

void stem_set_format_option(stem_format_option_t *opt, bool emit, bool force) {
    opt->emit = emit;
    opt->force = force;
}

stem_token_t *stem_separated(stem_build_context_t *bctx, char *text) {
    stem_token_t *token = stem_token_emit(bctx->tokens, STEM_TOKEN_TEXT, text);

    stem_set_format_option(&token->pre.space, true, false);
    stem_set_format_option(&token->post.space, true, false);

    return token;
}

stem_token_t *stem_separator(stem_build_context_t *bctx, char *text) {
    stem_token_t *token = stem_token_emit(bctx->tokens, STEM_TOKEN_TEXT, text);

    stem_set_format_option(&token->pre.space, false, true);
    stem_set_format_option(&token->post.space, false, true);

    return token;
}

stem_token_t *stem_indent(stem_build_context_t *bctx) {
    stem_token_t *token = stem_token_emit(bctx->tokens, STEM_TOKEN_INDENT, NULL);

    stem_set_format_option(&token->pre.newline, true, true);
    stem_set_format_option(&token->post.newline, false, true);

    return token;
}

stem_token_t *stem_dedent(stem_build_context_t *bctx) {
    stem_token_t *token = stem_token_emit(bctx->tokens, STEM_TOKEN_DEDENT, NULL);

    stem_set_format_option(&token->pre.newline, true, true);
    stem_set_format_option(&token->post.newline, false, true);

    return token;
}

void stem_dispatch(stem_build_context_t *bctx, stem_node_t *node) {
    stem_node_descriptor_t *desc = node->desc;

    stem_emit_dispatch_function_t func = bctx->target->emit_dispatch[desc->kind];
    if (func == NULL) {
        fprintf(stderr, "Fatal error: target '%s' does not implement '%s'\n", 
                bctx->target->name, desc->name);
        abort();
    }

    func(bctx, node);
}

void stem_dispatch_list(stem_build_context_t *bctx, stem_node_t **list) {
    for (size_t i = 0; !STEM_AT_LIST_END(list[i]); i++) {
        stem_dispatch(bctx, list[i]);
    }
}

void stem_emission_phase(stem_build_context_t *bctx, stem_node_t *root) {
    stem_dispatch(bctx, root);
}
