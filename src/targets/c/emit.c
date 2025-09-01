#include "targets/c/emit.h"
#include <assert.h>
#include <stdarg.h>

void stem_c_source_target_init(stem_target_t *target) {
    static stem_emit_dispatch_function_t dispatch[STEM_N_NODES] = {
        [STEM_NODE_MODULE]      = &stem_cc_emit_module,
        [STEM_NODE_CLASS]       = &stem_c_emit_class,
        [STEM_NODE_FUNCTION]    = &stem_cc_emit_function,
        [STEM_NODE_VARIABLE]    = &stem_c_emit_variable,
        [STEM_NODE_IF_ELSE]     = &stem_c_like_emit_if_else,
        [STEM_NODE_BOOL_LIT]    = &stem_c_like_emit_bool_lit,
    };

    target->name = "C-Source";
    target->emit_dispatch = dispatch;
}

void stem_c_header_target_init(stem_target_t *target) {
    static stem_emit_dispatch_function_t dispatch[STEM_N_NODES] = {
        [STEM_NODE_MODULE] = NULL
    };

    target->name = "C-Header";
    target->emit_dispatch = dispatch;
}

static void stem_c_type_annotation(stem_build_context_t *bctx, 
                                        stem_node_t *vnode) {
    switch (vnode->desc->kind) {
        case STEM_NODE_IDENT: {
            stem_node_ident_t *node = stem_node_cast_ident(vnode);
            stem_separated(bctx, node->name);
            break;
        }

        default:
            assert(1); // TODO: ERROR
    }
}

void stem_c_emit_class(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_class_t *node = stem_node_cast_class(vnode);

    stem_set_option(stem_separated(bctx, "struct"), pre, newline, true);
    stem_separated(bctx, node->name);

    stem_c_like_brace_open(bctx);

    for (size_t i = 0; !STEM_AT_LIST_END(node->attributes[i]); i++) {
        stem_dispatch(bctx, node->attributes[i]);
    }

    stem_c_like_brace_close(bctx, false, false);
    stem_c_like_semicolon(bctx);
}

void stem_c_emit_variable(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_variable_t *node = stem_node_cast_variable(vnode);

    stem_c_type_annotation(bctx, node->anno);
    stem_separated(bctx, node->name);
    stem_c_like_semicolon(bctx);
}
