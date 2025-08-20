#include "semantics.h"
#include "node.h"
#include "type.h"
#include <stdlib.h>

static stem_type_t *stem_semantic_dispatch(stem_node_t *node);

static void stem_semantic_dispatch_list(stem_node_t **list);

static void stem_declare_variable(stem_node_t *vnode) {
    stem_node_variable_t *node = stem_node_cast_variable(vnode);

    stem_symbol_t *sym = stem_symbol_variable(node, &vnode->ctx->pool);
    stem_symboltable_add(stem_node_get_scope(vnode), node->name, sym);
}

static void stem_declare_body(stem_node_t **list) {
    for (size_t i = 0; !STEM_AT_LIST_END(list[i]); i++) {
        stem_node_t *vnode = list[i];

        switch (vnode->desc->kind) {
            case STEM_NODE_VARIABLE:    
                stem_declare_variable(vnode);
                break;

            default:
                break;
        }
    }
}

static void stem_declare_function(stem_node_t *vnode) {
    stem_node_function_t *node = stem_node_cast_function(vnode);

    stem_symboltable_link_parent(&node->syms, stem_node_get_scope(vnode));
    stem_node_enter_scope(vnode, &node->syms);

    stem_declare_body(node->body);

    stem_node_leave_scope(vnode, &node->syms);

    stem_symbol_t *sym = stem_symbol_function(node, &node->base.ctx->pool);
    stem_symboltable_add(stem_node_get_scope(vnode), node->name, sym);
}

static void stem_declare_class(stem_node_t *vnode) {
    stem_node_class_t *node = stem_node_cast_class(vnode);

    stem_symboltable_link_parent(&node->syms, stem_node_get_scope(vnode));
    stem_node_enter_scope(vnode, &node->syms);

    for (size_t i = 0; !STEM_AT_LIST_END(node->attributes[i]); i++) {
        stem_declare_variable(node->attributes[i]);
    }
    for (size_t i = 0; !STEM_AT_LIST_END(node->methods[i]); i++) {
        stem_declare_function(node->methods[i]);
    }

    stem_node_leave_scope(vnode, &node->syms);

    stem_symbol_t *sym = stem_symbol_class(node, &node->base.ctx->pool);
    stem_symboltable_add(stem_node_get_scope(vnode), node->name, sym);
}

static stem_type_t *stem_type_from_annotation(stem_node_t *vnode) {
    fprintf(stderr, "{%s %d}\n", vnode->desc->name, vnode->desc->kind);

    switch (vnode->desc->kind) {
        case STEM_NODE_IDENT: {
            stem_node_ident_t *node = stem_node_cast_ident(vnode);
            stem_symboltable_t *scope = stem_node_get_scope(vnode);

            stem_symbol_t *vsym = stem_symboltable_lookup(scope, node->name);
            stem_symbol_class_t *sym = stem_sym_cast_class(vsym);

            return sym->type;
        }

        default:
            break;
    }

    fprintf(stderr, "Error: unhandled case: '%s'\n",
            vnode->desc->name);
    abort();
}

static stem_type_t *stem_semantic_module(stem_node_t *vnode) {
    stem_node_module_t *node = stem_node_cast_module(vnode);

    stem_node_enter_scope(vnode, &node->syms);

    stem_symboltable_t *scope = stem_node_get_scope(vnode);
    stem_pool_t *pool = &vnode->ctx->pool;

    stem_symboltable_add(scope, "int", stem_symbol_class(NULL, pool));

    for (size_t i = 0; !STEM_AT_LIST_END(node->classes[i]); i++) {
        stem_declare_class(node->classes[i]);
    }
    for (size_t i = 0; !STEM_AT_LIST_END(node->functions[i]); i++) {
        stem_declare_function(node->functions[i]);
    }

    stem_semantic_dispatch_list(node->classes);
    stem_semantic_dispatch_list(node->functions);

    stem_node_leave_scope(vnode, &node->syms);

    return NULL;
}

static stem_type_t *stem_semantic_class(stem_node_t *vnode) {
    stem_node_class_t *node = stem_node_cast_class(vnode);

    stem_node_enter_scope(vnode, &node->syms);
    
    stem_semantic_dispatch_list(node->attributes);
    stem_semantic_dispatch_list(node->methods);

    stem_node_leave_scope(vnode, &node->syms);
   
    return NULL;
}

static stem_type_t *stem_semantic_function(stem_node_t *vnode) {
    stem_node_function_t *node = stem_node_cast_function(vnode);

    stem_node_enter_scope(vnode, &node->syms);

    stem_semantic_dispatch_list(node->body);

    stem_node_leave_scope(vnode, &node->syms);

    return NULL;
}

static stem_type_t *stem_semantic_variable(stem_node_t *vnode) {
    stem_node_variable_t *node = stem_node_cast_variable(vnode);

    stem_symboltable_t *scope = stem_node_get_scope(vnode);
    stem_symbol_t *vsym = stem_symboltable_lookup(scope, node->name);
    stem_symbol_variable_t *sym = stem_sym_cast_variable(vsym);
    
    sym->type = stem_type_from_annotation(node->anno);

    return NULL;
}

static stem_type_t *stem_semantic_if_else(stem_node_t *vnode) {
    (void)vnode;
    
    return NULL;
}

static stem_type_t *stem_semantic_dispatch(stem_node_t *vnode) {
    switch (vnode->desc->kind) {
        case STEM_NODE_MODULE:      return stem_semantic_module(vnode);
        case STEM_NODE_CLASS:       return stem_semantic_class(vnode);
        case STEM_NODE_FUNCTION:    return stem_semantic_function(vnode);
        case STEM_NODE_VARIABLE:    return stem_semantic_variable(vnode);
        case STEM_NODE_IF_ELSE:     return stem_semantic_if_else(vnode);

        default:
            break;
    }

    fprintf(stderr, "Error: unhandled case in semantic analysis: '%s'\n",
            vnode->desc->name);
    abort();
}

static void stem_semantic_dispatch_list(stem_node_t **list) {
    for (size_t i = 0; !STEM_AT_LIST_END(list[i]); i++) {
        stem_semantic_dispatch(list[i]);
    }
}

void stem_semantic_phase(stem_node_t *root) {
    stem_node_start_traversal(root, "semantic-phase");

    stem_semantic_dispatch(root);
    
    stem_node_end_traversal(root);
}
