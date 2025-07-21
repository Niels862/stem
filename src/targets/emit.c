#include "targets/emit.h"

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
