#include "nodes.h"
#include "renderer.h"
#include "util.h"
#include <stdlib.h>
#include <stdarg.h>

void stem_init() {}

stem_node_t *stem_class(char *name, stem_node_t **attributes, 
                        stem_node_t **methods) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_CLASS
    };

    stem_node_class_t *node = stem_xmalloc(sizeof(stem_node_class_t));

    node->base.desc = &desc;
    node->name = name;
    node->attributes = attributes;
    node->methods = methods;

    return &node->base;
}

stem_node_t *stem_function(char *name) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_FUNCTION
    };

    stem_node_function_t *node = stem_xmalloc(sizeof(stem_node_function_t));

    node->base.desc = &desc;
    node->name = name;

    return &node->base;
}

stem_node_t *stem_variable(char *name, stem_node_t *type) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_VARIABLE
    };

    stem_node_variable_t *node = stem_xmalloc(sizeof(stem_node_variable_t));

    node->base.desc = &desc;
    node->name = name;
    node->type = type;

    return &node->base;
}

stem_node_t *stem_identifier(char *name) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_IDENTIFIER
    };

    stem_node_identifier_t *node = stem_xmalloc(sizeof(stem_node_identifier_t));

    node->base.desc = &desc;
    node->name = name;

    return &node->base;
}

stem_node_t **stem_empty() {
    stem_node_t **list = stem_xmalloc(sizeof(void *));

    list[0] = NULL;

    return list;
}

stem_node_t **stem_list(stem_node_t *node, ...) {
    va_list args;
    size_t count = 0;

    va_start(args, node);
    void *arg = node;
    while (arg != NULL) {
        count++;
        arg = va_arg(args, void *);
    }
    va_end(args);

    stem_node_t **list = stem_xmalloc((count + 1) * sizeof(void *));

    va_start(args, node);
    for (size_t i = 0; i < count; ++i) {
        list[i] = (i == 0) ? node : va_arg(args, void *);
    }
    list[count] = NULL;
    va_end(args);

    return list;
}

void stem_free_list(stem_node_t **list) {
    for (size_t i = 0; list[i] != NULL; i++) {
        stem_free_node(list[i]);
    }
}

void stem_free_node(stem_node_t *node) {
    (void)node;
}
