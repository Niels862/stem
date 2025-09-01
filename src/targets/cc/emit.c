#include "targets/cc/emit.h"
#include "node.h"

void stem_cc_emit_module(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_module_t *node = stem_node_cast_module(vnode);

    for (size_t i = 0; !STEM_AT_LIST_END(node->classes[i]); i++) {
        stem_dispatch(bctx, node->classes[i]);
    }

    for (size_t i = 0; !STEM_AT_LIST_END(node->functions[i]); i++) {
        stem_dispatch(bctx, node->functions[i]);
    }
}

void stem_cc_emit_function(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_function_t *node = stem_node_cast_function(vnode);

    stem_separated(bctx, "void");
    stem_separated(bctx, node->name);
    stem_separator(bctx, "(");
    stem_separator(bctx, ")");

    stem_c_like_block(bctx, node->body, true);
}
