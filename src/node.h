#ifndef STEM_NODE_H
#define STEM_NODE_H

#include "stem/stem.h"
#include "node-forward.h"
#include "symbol.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    STEM_NODE_NONE,

    STEM_NODE_MODULE,
    STEM_NODE_CLASS,
    STEM_NODE_FUNCTION,
    STEM_NODE_VARIABLE,
    STEM_NODE_IF_ELSE,

    STEM_N_NODES,
} stem_nodekind_t;

typedef enum {
    STEM_ATTR_NONE,
    STEM_ATTR_NODE,
    STEM_ATTR_LIST,
    STEM_ATTR_STRVIEW,
    STEM_ATTR_SYMTABLE,
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
    stem_node_t **classes;
    stem_node_t **functions;
    stem_symboltable_t syms;
};

struct stem_node_class_t {
    stem_node_t base;
    char *name;
    stem_node_t **attributes;
    stem_node_t **methods;
    stem_symboltable_t syms;
};

struct stem_node_function_t {
    stem_node_t base;
    char *name;
    stem_node_t **body;
    stem_symboltable_t syms;
};

struct stem_node_variable_t {
    stem_node_t base;
    char *name;
    stem_node_t *type;
};

struct stem_node_if_else_t {
    stem_node_t base;
    stem_node_t *cond;
    stem_node_t **then_body;
    stem_node_t **else_body;
};

#endif
