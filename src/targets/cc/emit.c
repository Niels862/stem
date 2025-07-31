#include "targets/cc/emit.h"
#include "node.h"

void stem_cc_emit_module(stem_context_t *ctx, stem_node_t *vnode) {
    stem_node_module_t *node = stem_cast_module(vnode);

    for (size_t i = 0; !STEM_AT_LIST_END(node->classes[i]); i++) {
        stem_dispatch(ctx, node->classes[i]);
    }
}

void stem_cc_emit_function(stem_context_t *ctx, stem_node_t *vnode) {
    stem_node_function_t *node = stem_cast_function(vnode);

    stem_separated(ctx, "void");
    stem_separated(ctx, node->name);
    stem_separator(ctx, "(");
    stem_separator(ctx, ")");

    stem_c_like_block(ctx, node->body, true);
}
