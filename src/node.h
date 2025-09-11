#ifndef STEM_NODE_H
#define STEM_NODE_H

#include "stem/stem.h"
#include "node-forward.h"
#include "pool.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

typedef enum {
    STEM_NODE_NONE,

    STEM_NODE_MODULE,
    STEM_NODE_CLASS,
    STEM_NODE_FUNCTION,
    STEM_NODE_VARIABLE,
    STEM_NODE_IF_ELSE,

    STEM_NODE_BOOL_LIT,

    STEM_NODE_IDENT,

    STEM_NODE_CLASSTYPE,

    STEM_N_NODES,
} stem_nodekind_t;

typedef enum {
    STEM_ATTR_NONE,
    STEM_ATTR_NODE,
    STEM_ATTR_LIST,
    STEM_ATTR_STRVIEW,
    STEM_ATTR_BOOL,
    STEM_ATTR_INT,
    STEM_ATTR_FLOAT,
} stem_node_attribute_type_t;

typedef struct {
    size_t offset;
    stem_node_attribute_type_t type;
} stem_node_attribute_t;

#define STEM_NODE_MAX_ATTRS 4

typedef struct {
    stem_nodekind_t kind;
    char *name;
    stem_node_attribute_t attrs[STEM_NODE_MAX_ATTRS];
} stem_node_descriptor_t;

struct stem_node_t {
    stem_node_descriptor_t *desc;
};

struct stem_node_module_t {
    stem_node_t base;
    char *name;
    stem_node_t **classes;
    stem_node_t **functions;
};

struct stem_node_class_t {
    stem_node_t base;
    char *name;
    stem_node_t **attributes;
    stem_node_t **methods;
};

struct stem_node_function_t {
    stem_node_t base;
    char *name;
    stem_node_t **body;
};

struct stem_node_variable_t {
    stem_node_t base;
    char *name;
    stem_node_t *anno;
};

struct stem_node_if_else_t {
    stem_node_t base;
    stem_node_t *cond;
    stem_node_t **then_body;
    stem_node_t **else_body;
};

struct stem_node_bool_lit_t {
    stem_node_t base;
    bool value;
};

struct stem_node_ident_t {
    stem_node_t base;
    char *name;
};

struct stem_node_classtype_t {
    stem_node_t base;
    char *name;
    stem_storagetype_t store;
};

#define STEM_NODE_TYPE(t) stem_node_##t##_t

#define STEM_NODE_HEADER(e, t) \
    STEM_NODE_TYPE(t) *stem_node_cast_##t(stem_node_t *node);

#define STEM_NODE_SOURCE(e, t) \
    STEM_NODE_TYPE(t) *stem_node_cast_##t(stem_node_t *node) { \
        assert(node != NULL); \
        assert(node->desc->kind == e); \
        return (STEM_NODE_TYPE(t) *)node; \
    }

STEM_NODE_HEADER(STEM_NODE_MODULE, module)
STEM_NODE_HEADER(STEM_NODE_CLASS, class)
STEM_NODE_HEADER(STEM_NODE_FUNCTION, function)
STEM_NODE_HEADER(STEM_NODE_VARIABLE, variable)
STEM_NODE_HEADER(STEM_NODE_IF_ELSE, if_else)
STEM_NODE_HEADER(STEM_NODE_BOOL_LIT, bool_lit)
STEM_NODE_HEADER(STEM_NODE_IDENT, ident)
STEM_NODE_HEADER(STEM_NODE_CLASSTYPE, classtype)

void stem_node_visit(stem_node_t *node, void *ctx, 
                     void(*func)(stem_node_t *, void *));

#endif
