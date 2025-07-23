#include "semantics.h"
#include "node.h"
#include "type.h"
#include <stdlib.h>

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
    (void)root;

    stem_semantic_dispatch(root);
}
