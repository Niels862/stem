#ifndef STEM_NODE_H
#define STEM_NODE_H

#include "stem/stem.h"
#include "node-forward.h"
#include "symbol.h"
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

    STEM_N_NODES,
} stem_nodekind_t;

typedef enum {
    STEM_ATTR_NONE,
    STEM_ATTR_NODE,
    STEM_ATTR_LIST,
    STEM_ATTR_STRVIEW,
    STEM_ATTR_SYMTABLE,
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

struct stem_node_context_t {
    /* Owns objects that are only valid during the `build` phase: 
       types and symbols */
    stem_pool_t pool;
 
    /* The current symbol table of the current node in the AST _traversal. */
    stem_symboltable_t *_curr;

    /* Stores a traversal name set by start_traversal. Soft-locks the context 
       to a single traversal at a time. */
    char *_traversal;
};

struct stem_node_t {
    stem_node_descriptor_t *desc;
    stem_node_context_t *ctx;
};

struct stem_node_module_t {
    stem_node_t base;
    char *name;
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

void stem_node_visit(stem_node_t *node, void *ctx, 
                     void(*func)(stem_node_t *, void *));

void stem_node_start_traversal(stem_node_t *node, char *name);

void stem_node_end_traversal(stem_node_t *node);

stem_symboltable_t *stem_node_get_scope(stem_node_t *node);

void stem_node_enter_scope(stem_node_t *node, stem_symboltable_t *table);

void stem_node_leave_scope(stem_node_t *node, stem_symboltable_t *table);

#endif
