#include "targets/c/emit.h"
#include <assert.h>
#include <stdarg.h>

void stem_c_target_init(stem_target_t *target) {
    static stem_emit_dispatch_function_t dispatch[STEM_N_NODES] = {
        [STEM_NODE_MODULE]      = &stem_cc_emit_module,
        [STEM_NODE_CLASS]       = &stem_c_emit_class,
        [STEM_NODE_FUNCTION]    = &stem_cc_emit_function,
        [STEM_NODE_VARIABLE]    = NULL,
        [STEM_NODE_IF_ELSE]     = &stem_c_like_emit_if_else,
        [STEM_NODE_BOOL_LIT]    = &stem_c_like_emit_bool_lit,
    };

    target->name = "C";
    for (size_t i = 0; i < STEM_N_NODES; i++) {
        target->emit_dispatch[i] = dispatch[i];
    }
}

void stem_c_emit_class(stem_context_t *ctx, stem_node_t *vnode) {
    stem_node_class_t *node = stem_cast_class(vnode);

    stem_set_option(stem_separated(ctx, "struct"), pre, newline, true);
    stem_separated(ctx, node->name);

    stem_c_like_brace_open(ctx);
    stem_c_like_brace_close(ctx, true);
}
