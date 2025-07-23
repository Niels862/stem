#include "semantics.h"
#include "node.h"
#include "type.h"
#include <stdlib.h>

static void stem_declare_function(void *vnode, stem_symboltable_t *syms) {
    stem_node_function_t *node = vnode;
    stem_symbol_t *sym = stem_symbol_function(node);
    stem_symbol_declare(syms, node->name, sym);
}

static void stem_declare_class(void *vnode, stem_symboltable_t *syms) {
    // todo check node type
    stem_node_class_t *node = vnode;

    for (size_t i = 0; !STEM_AT_LIST_END(node->methods[i]); i++) {
        stem_declare_function(node->methods[i], &node->syms);
    }

    stem_symbol_t *sym = stem_symbol_class(node);
    stem_symbol_declare(syms, node->name, sym);
}

static stem_type_t *stem_semantic_module(stem_node_module_t *node) {
    for (size_t i = 0; !STEM_AT_LIST_END(node->classes[i]); i++) {
        stem_declare_class(node->classes[i], &node->syms);
    }

    for (size_t i = 0; !STEM_AT_LIST_END(node->functions[i]); i++) {
        stem_declare_function(node->functions[i], &node->syms);
    }

    return NULL;
}

static stem_type_t *stem_semantic_class(stem_node_class_t *node) {
    (void)node;

    return NULL;
}

static stem_type_t *stem_semantic_function(stem_node_function_t *node) {
    (void)node;

    return NULL;
}

static stem_type_t *stem_semantic_variable(stem_node_variable_t *node) {
    (void)node;

    return NULL;
}

static stem_type_t *stem_semantic_if_else(stem_node_variable_t *node) {
    (void)node;
    
    return NULL;
}

stem_type_t *stem_semantic_dispatch(stem_node_t *root) {
    void *node = root;

    switch (root->desc->kind) {
        case STEM_NODE_MODULE:      return stem_semantic_module(node);
        case STEM_NODE_CLASS:       return stem_semantic_class(node);
        case STEM_NODE_FUNCTION:    return stem_semantic_function(node);
        case STEM_NODE_VARIABLE:    return stem_semantic_variable(node);
        case STEM_NODE_IF_ELSE:     return stem_semantic_if_else(node);

        default:
            break;
    }

    fprintf(stderr, "Error: unhandled case in semantic analysis: '%s'\n",
            root->desc->name);
    abort();
}

void stem_semantic_analysis(stem_node_t *root) {
    stem_semantic_dispatch(root);
}
