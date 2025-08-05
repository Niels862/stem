#include "targets/c-like/emit.h"

void stem_c_like_block(stem_context_t *ctx, stem_node_t **block, bool newline) {
    stem_token_t *open = stem_separator(ctx, "{");
    stem_set_option(open, pre, space, true);

    stem_indent(ctx);

    for (size_t i = 0; !STEM_AT_LIST_END(block[i]); i++) {
        stem_dispatch(ctx, block[i]);
    }

    stem_token_t *dedent = stem_dedent(ctx);
    stem_set_option(dedent, pre, emptyline, false);

    stem_token_t *close = stem_separator(ctx, "}");
    stem_set_option(close, post, space, true);
    stem_set_option(close, post, newline, newline);
    stem_set_option_soft(close, post, emptyline, newline);
}

void stem_c_like_paren_expr(stem_context_t *ctx, stem_node_t *vnode) {    
    stem_set_option(stem_separator(ctx, "("), pre, space, true);
    stem_dispatch(ctx, vnode);
    stem_set_option(stem_separator(ctx, ")"), post, space, true);
}

void stem_c_like_bool_lit(stem_context_t *ctx, stem_node_t *vnode) {
    stem_node_bool_lit_t *node = stem_cast_bool_lit(vnode);
    if (node->value) {
        stem_separated(ctx, "true");
    } else {
        stem_separated(ctx, "false");
    }
}

void stem_c_like_emit_if_else(stem_context_t *ctx, stem_node_t *vnode) {
    stem_node_if_else_t *node = stem_cast_if_else(vnode);

    stem_separated(ctx, "if");
    stem_c_like_paren_expr(ctx, node->cond);

    if (stem_list_is_empty(node->else_body)) {
        stem_c_like_block(ctx, node->then_body, true);
    } else {
        stem_c_like_block(ctx, node->then_body, false);
        stem_separated(ctx, "else");
        stem_c_like_block(ctx, node->else_body, true);
    }
}
