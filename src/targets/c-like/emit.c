#include "targets/c-like/emit.h"

void stem_c_like_brace_open(stem_build_context_t *bctx) {
    stem_token_t *brace = stem_separator(bctx, "{");
    stem_set_option(brace, pre, space, true);
    stem_indent(bctx);
}

void stem_c_like_brace_close(stem_build_context_t *bctx, bool newline) {
    stem_token_t *dedent = stem_dedent(bctx);
    stem_set_option(dedent, pre, emptyline, false);

    stem_token_t *close = stem_separator(bctx, "}");
    stem_set_option(close, post, space, true);
    stem_set_option(close, post, newline, newline);
    stem_set_option_soft(close, post, emptyline, newline);
}

void stem_c_like_block(stem_build_context_t *bctx, stem_node_t **block, bool newline) {
    stem_c_like_brace_open(bctx);

    for (size_t i = 0; !STEM_AT_LIST_END(block[i]); i++) {
        stem_dispatch(bctx, block[i]);
    }

    stem_c_like_brace_close(bctx, newline);
}

void stem_c_like_paren_expr(stem_build_context_t *bctx, stem_node_t *vnode) {    
    stem_set_option(stem_separator(bctx, "("), pre, space, true);
    stem_dispatch(bctx, vnode);
    stem_set_option(stem_separator(bctx, ")"), post, space, true);
}

void stem_c_like_semicolon(stem_build_context_t *bctx) {
    stem_set_option(stem_separator(bctx, ";"), post, newline, true);
}

void stem_c_like_emit_bool_lit(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_bool_lit_t *node = stem_node_cast_bool_lit(vnode);
    if (node->value) {
        stem_separated(bctx, "true");
    } else {
        stem_separated(bctx, "false");
    }
}

void stem_c_like_emit_if_else(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_if_else_t *node = stem_node_cast_if_else(vnode);

    stem_separated(bctx, "if");
    stem_c_like_paren_expr(bctx, node->cond);

    if (stem_list_is_empty(node->else_body)) {
        stem_c_like_block(bctx, node->then_body, true);
    } else {
        stem_c_like_block(bctx, node->then_body, false);
        stem_separated(bctx, "else");
        stem_c_like_block(bctx, node->else_body, true);
    }
}
