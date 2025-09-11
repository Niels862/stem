#include "targets/c/emit.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

void stem_c_source_target_init(stem_target_t *target) {
    static stem_emit_dispatch_function_t dispatch[STEM_N_NODES] = {
        [STEM_NODE_MODULE]      = &stem_c_emit_module_source,
        [STEM_NODE_CLASS]       = NULL,
        [STEM_NODE_FUNCTION]    = &stem_cc_emit_function,
        [STEM_NODE_VARIABLE]    = &stem_c_emit_variable,
        [STEM_NODE_IF_ELSE]     = &stem_c_like_emit_if_else,
        [STEM_NODE_BOOL_LIT]    = &stem_c_like_emit_bool_lit,
        [STEM_NODE_CLASSTYPE]   = &stem_c_emit_classtype,
    };

    target->name = "C-Source";
    target->emit_dispatch = dispatch;
}

void stem_c_header_target_init(stem_target_t *target) {
    static stem_emit_dispatch_function_t dispatch[STEM_N_NODES] = {
        [STEM_NODE_MODULE]      = &stem_c_emit_module_header,
        [STEM_NODE_CLASS]       = &stem_c_emit_class_declaration,
        [STEM_NODE_FUNCTION]    = NULL,
        [STEM_NODE_VARIABLE]    = &stem_c_emit_variable,
        [STEM_NODE_CLASSTYPE]   = &stem_c_emit_classtype,
    };

    target->name = "C-Header";
    target->emit_dispatch = dispatch;
}

void stem_c_emit_module_source(stem_build_context_t *bctx, stem_node_t *vnode) {
    (void)bctx, (void)vnode;
}

void stem_c_emit_module_header(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_module_t *module = stem_node_cast_module(vnode);
    stem_dispatch_list(bctx, module->classes);
    stem_dispatch_list(bctx, module->functions);
}

void stem_c_emit_class_declaration(stem_build_context_t *bctx, 
                                   stem_node_t *vnode) {
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

    stem_dispatch(bctx, node->anno);
    stem_separated(bctx, node->name);
    stem_c_like_semicolon(bctx);
}

void stem_c_emit_classtype(stem_build_context_t *bctx, stem_node_t *vnode) {
    stem_node_classtype_t *node = stem_node_cast_classtype(vnode);

    stem_separated(bctx, node->name);

    switch (node->store) {
        case STEM_STORE_REFERENCE: {
            stem_token_t *token = stem_separator(bctx, "*");
            stem_set_option_soft(token, pre, space, true);
            stem_set_option(token, post, space, false);
        }
            
            break;

        case STEM_STORE_VALUE:
            break;
    }
}

void stem_c_entry_source(stem_build_context_t *bctx, stem_node_t *vnode) {
    (void)bctx, (void)vnode;
}

void stem_c_entry_header(stem_build_context_t *bctx, stem_node_t *vnode) {
    (void)bctx, (void)vnode;
}

void stem_c_entry(stem_build_context_t *bctx, stem_node_t *vnode, char *dir) {
    stem_strbuilder_t sb;
    stem_strbuilder_init(&sb, 256);

    stem_node_module_t *module = stem_node_cast_module(vnode);

    stem_strbuilder_append(&sb, dir);
    stem_strbuilder_append(&sb, "/");
    stem_strbuilder_append(&sb, module->name);
    stem_strbuilder_append(&sb, ".c");

    fprintf(stderr, "[%s]\n", sb.buf);

    (void)bctx;
}
