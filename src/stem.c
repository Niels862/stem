#include "stem/stem.h"
#include "emitter.h"
#include "util.h"
#include <stdlib.h>
#include <stdarg.h>

void stem_init() {
    stem_tokenlist_t tokens;
    stem_tokenlist_init(&tokens);

    stem_token_emit(&tokens, "struct", STEM_FMT_SPACE, STEM_FMT_SPACE);
    stem_token_emit(&tokens, "test_t", STEM_FMT_SPACE, STEM_FMT_SPACE);
    stem_token_emit(&tokens, "{", STEM_FMT_SPACE, STEM_FMT_NEWLINE);
    stem_token_emit(&tokens, "int", STEM_FMT_SPACE, STEM_FMT_SPACE);
    stem_token_emit(&tokens, "i", STEM_FMT_SPACE, STEM_FMT_SPACE);
    stem_token_emit(&tokens, ";", STEM_FMT_NO_SPACE, STEM_FMT_NEWLINE);
    stem_token_emit(&tokens, "}", STEM_FMT_NONE, STEM_FMT_NONE);

    stem_tokenlist_write(&tokens, stderr);

    stem_emit(&tokens, stderr);

    stem_tokenlist_free(&tokens);
}

stem_node_t *stem_class(char *name, stem_node_t **attributes, 
                        stem_node_t **methods) {
    stem_node_class_t *node = stem_xmalloc(sizeof(stem_node_class_t));

    node->base.kind = STEM_NODE_CLASS;
    node->name = name;
    node->attributes = attributes;
    node->methods = methods;

    return &node->base;
}

stem_node_t *stem_variable(char *name, stem_node_t *type) {
    stem_node_variable_t *node = stem_xmalloc(sizeof(stem_node_variable_t));

    node->base.kind = STEM_NODE_VARIABLE;
    node->name = name;
    node->type = type;

    return &node->base;
}

stem_node_t *stem_identifier(char *name) {
    stem_node_identifier_t *node = stem_xmalloc(sizeof(stem_node_identifier_t));

    node->base.kind = STEM_NODE_IDENTIFIER;
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

void stem_free_node(stem_node_t *node) {
    (void)node;
}
