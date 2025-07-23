#include "node.h"
#include "renderer.h"
#include "util.h"
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

static stem_node_t stem_node_sentinel;

stem_node_t *stem_list_end = &stem_node_sentinel;

stem_node_t *stem_module(stem_node_t **classes, stem_node_t **functions) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_MODULE,
        .name = "module",
        .attrs = {
            { offsetof(stem_node_module_t, classes), STEM_ATTR_LIST },
            { offsetof(stem_node_module_t, functions), STEM_ATTR_LIST },
        }
    };

    stem_node_module_t *node = stem_xmalloc(sizeof(stem_node_module_t));

    node->base.desc = &desc;
    node->classes = classes;
    node->functions = functions;

    return &node->base;
}

stem_node_t *stem_class(char *name, stem_node_t **attributes, 
                        stem_node_t **methods) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_CLASS,
        .name = "class",
        .attrs = {
            { offsetof(stem_node_class_t, name), ATEM_ATTR_STRV },
            { offsetof(stem_node_class_t, methods), STEM_ATTR_LIST },
            { offsetof(stem_node_class_t, attributes), STEM_ATTR_LIST },
        }
    };

    stem_node_class_t *node = stem_xmalloc(sizeof(stem_node_class_t));

    node->base.desc = &desc;
    node->name = name;
    node->attributes = attributes;
    node->methods = methods;

    return &node->base;
}

stem_node_t *stem_function(char *name, stem_node_t **body) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_FUNCTION,
        .name = "function",
        .attrs = {
            { offsetof(stem_node_function_t, name), ATEM_ATTR_STRV },
            { offsetof(stem_node_function_t, body), STEM_ATTR_LIST },
        }
    };

    stem_node_function_t *node = stem_xmalloc(sizeof(stem_node_function_t));

    node->base.desc = &desc;
    node->name = name;
    node->body = body;
    
    return &node->base;
}

stem_node_t *stem_variable(char *name, stem_node_t *type) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_VARIABLE,
        .name = "variable",
        .attrs = {
            { offsetof(stem_node_variable_t, name), ATEM_ATTR_STRV },
        }
    };

    stem_node_variable_t *node = stem_xmalloc(sizeof(stem_node_variable_t));

    node->base.desc = &desc;
    node->name = name;
    node->type = type;

    return &node->base;
}

stem_node_t *stem_if_else(stem_node_t *cond, 
                          stem_node_t **then_body, stem_node_t **else_body) {
    static stem_node_descriptor_t desc = {
        .kind = STEM_NODE_IF_ELSE,
        .name = "if-else",
        .attrs = {
            { offsetof(stem_node_if_else_t, cond), STEM_ATTR_NODE },
            { offsetof(stem_node_if_else_t, then_body), STEM_ATTR_LIST },
            { offsetof(stem_node_if_else_t, else_body), STEM_ATTR_LIST },
        }
    };

    stem_node_if_else_t *node = stem_xmalloc(sizeof(stem_node_if_else_t));

    node->base.desc = &desc;
    node->cond = cond;
    node->then_body = then_body;
    node->else_body = else_body;

    return &node->base;
}

stem_node_t *stem_if(stem_node_t *cond, stem_node_t **body) {
    return stem_if_else(cond, body, stem_empty());
}

stem_node_t **stem_empty() {
    stem_node_t **list = stem_xmalloc(sizeof(stem_node_t *));

    list[0] = stem_list_end;

    return list;
}

stem_node_t **stem_list(stem_node_t *node, ...) {
    va_list args;
    size_t count = 0;

    va_start(args, node);
    stem_node_t *arg = node;
    while (!STEM_AT_LIST_END(arg)) {
        if (count >= 256) {
            fprintf(stderr, "Fatal error: missing list terminator "
                    "after %ld entries\n", count);
            abort();
        }

        count++;
        arg = va_arg(args, stem_node_t *);
    }
    va_end(args);

    stem_node_t **list = stem_xmalloc((count + 1) * sizeof(void *));

    va_start(args, node);
    for (size_t i = 0; i < count; ++i) {
        list[i] = (i == 0) ? node : va_arg(args, void *);
    }
    list[count] = stem_list_end;
    va_end(args);

    return list;
}

static void stem_node_list_write(stem_node_t **list, size_t indent, 
                                 FILE *file) {
    if (stem_list_is_empty(list)) {
        stem_write_n_chars(' ', indent, file);
        fprintf(file, "[]");
        return;
    }
    
    stem_write_n_chars(' ', indent, file);
    fprintf(file, "[\n");

    for (size_t i = 0; !STEM_AT_LIST_END(list[i]); i++) {
        stem_node_write(list[i], indent + 1, file);
        fprintf(file, ",\n");
    }

    stem_write_n_chars(' ', indent, file);
    fprintf(file, "]");
}

bool stem_list_is_empty(stem_node_t **list) {
    return STEM_AT_LIST_END(list[0]);
}

void stem_node_write(stem_node_t *node, size_t indent, FILE *file) {
    if (node == NULL) {
        stem_write_n_chars(' ', indent, file);
        fprintf(file, "(null)");
        return;
    }

    stem_node_descriptor_t *desc = node->desc;
    assert(desc != NULL);

    stem_write_n_chars(' ', indent, file);
    fprintf(file, "%s {\n", desc->name);

    for (size_t i = 0; i < STEM_NODE_MAX_ATTRS; i++) {
        stem_node_attribute_t *attr = &desc->attrs[i];
        void *p = *(void **)((char *)node + attr->offset);

        switch (attr->type) {
            case STEM_ATTR_NONE:
                break;

            case STEM_ATTR_NODE:
                stem_node_write(p, indent + 1, file);
                fprintf(file, ",\n");
                break;

            case STEM_ATTR_LIST:
                stem_node_list_write(p, indent + 1, file);
                fprintf(file, ",\n");
                break;

            case ATEM_ATTR_STRV:
                stem_write_n_chars(' ', indent + 1, file);
                fprintf(file, "%s,\n", (char *)p);
                break;
        }
    }

    stem_write_n_chars(' ', indent, file);
    fprintf(file, "}");
}

static void stem_node_list_free(stem_node_t **list) {
    for (size_t i = 0; !STEM_AT_LIST_END(list[i]); i++) {
        stem_node_free(list[i]);
    }
    free(list);
}

void stem_node_free(stem_node_t *node) {
    if (node == NULL) {
        return;
    }

    stem_node_descriptor_t *desc = node->desc;
    assert(desc != NULL);

    for (size_t i = 0; i < STEM_NODE_MAX_ATTRS; i++) {
        stem_node_attribute_t *attr = &desc->attrs[i];
        void *p = *(void **)((char *)node + attr->offset);

        switch (attr->type) {
            case STEM_ATTR_NONE:
            case ATEM_ATTR_STRV:
                break;

            case STEM_ATTR_NODE:
                stem_node_free(p);
                break;

            case STEM_ATTR_LIST:
                stem_node_list_free(p);
                break;
        }
    }

    free(node);
}
