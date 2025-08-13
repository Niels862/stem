#include "targets/emit.h"
#include <stdlib.h>

void stem_set_format_option(stem_format_option_t *opt, bool emit, bool force) {
    opt->emit = emit;
    opt->force = force;
}

stem_token_t *stem_separated(stem_context_t *ctx, char *text) {
    stem_token_t *token = stem_token_emit(ctx->tokens, STEM_TOKEN_TEXT, text);

    stem_set_format_option(&token->pre.space, true, false);
    stem_set_format_option(&token->post.space, true, false);

    return token;
}

stem_token_t *stem_separator(stem_context_t *ctx, char *text) {
    stem_token_t *token = stem_token_emit(ctx->tokens, STEM_TOKEN_TEXT, text);

    stem_set_format_option(&token->pre.space, false, true);
    stem_set_format_option(&token->post.space, false, true);

    return token;
}

stem_token_t *stem_indent(stem_context_t *ctx) {
    stem_token_t *token = stem_token_emit(ctx->tokens, STEM_TOKEN_INDENT, NULL);

    stem_set_format_option(&token->pre.newline, true, true);
    stem_set_format_option(&token->post.newline, false, true);

    return token;
}

stem_token_t *stem_dedent(stem_context_t *ctx) {
    stem_token_t *token = stem_token_emit(ctx->tokens, STEM_TOKEN_DEDENT, NULL);

    stem_set_format_option(&token->pre.newline, true, true);
    stem_set_format_option(&token->post.newline, false, true);

    return token;
}

void stem_dispatch(stem_context_t *ctx, stem_node_t *node) {
    stem_node_descriptor_t *desc = node->desc;

    stem_emit_dispatch_function_t func = ctx->target->emit_dispatch[desc->kind];
    if (func == NULL) {
        fprintf(stderr, "Fatal error: target '%s' does not implement '%s'\n", 
                ctx->target->name, desc->name);
        abort();
    }

    func(ctx, node);
}

void stem_emission_phase(stem_context_t *ctx, stem_node_t *root) {
    stem_node_start_traversal(root, "emission-phase");

    stem_dispatch(ctx, root);

    stem_node_end_traversal(root);
}
