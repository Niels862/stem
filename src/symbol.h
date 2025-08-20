#ifndef STEM_SYMBOL_H
#define STEM_SYMBOL_H

#include "node-forward.h"
#include "type.h"
#include "pool.h"
#include "strmap.h"
#include <stdio.h>

typedef struct stem_symboltable_t {
    stem_strmap_t map;
    struct stem_symboltable_t *parent;
} stem_symboltable_t;

typedef enum {
    STEM_SYM_CLASS,
    STEM_SYM_FUNCTION,
    STEM_SYM_VARIABLE,
} stem_symbolkind_t;

struct stem_symbol_t {
    stem_symbolkind_t kind;
    char *name; /* Set after the symbol is added to the symbol-table 
                   (linked to a symbol name) */
};

struct stem_symbol_class_t {
    stem_symbol_t base;
    stem_node_class_t *node;
    stem_type_t *type;
};

struct stem_symbol_function_t {
    stem_symbol_t base;
    stem_node_function_t *node;
};

struct stem_symbol_variable_t {
    stem_symbol_t base;
    stem_node_variable_t *node;
    stem_type_t *type;
};

void stem_symboltable_init(stem_symboltable_t *table);

void stem_symboltable_destruct(stem_symboltable_t *table);

void stem_symboltable_link_parent(stem_symboltable_t *table, 
                                  stem_symboltable_t *parent);

void stem_symboltable_write_oneline(stem_symboltable_t *table, FILE *file);

void stem_symboltable_add(stem_symboltable_t *table, 
                          char *name, stem_symbol_t *sym);

stem_symbol_t *stem_symboltable_lookup(stem_symboltable_t *table, char *name);

char *stem_symbolkind_name(stem_symbolkind_t kind);

stem_symbol_t *stem_symbol_class(stem_node_class_t *node, 
                                 stem_pool_t *pool);

stem_symbol_t *stem_symbol_function(stem_node_function_t *node, 
                                    stem_pool_t *pool);

stem_symbol_t *stem_symbol_variable(stem_node_variable_t *node,
                                    stem_pool_t *pool);

void stem_symbol_write(stem_symbol_t *sym, FILE *file);

#define STEM_SYM_TYPE(t) stem_symbol_##t##_t

#define STEM_SYM_SOURCE(e, t) \
    STEM_SYM_TYPE(t) *stem_sym_cast_##t(stem_symbol_t *sym) { \
        assert(sym != NULL); \
        assert(sym->kind == e); \
        return (STEM_SYM_TYPE(t) *)sym; \
    }

#define STEM_SYM_HEADER(e, t) \
    STEM_SYM_TYPE(t) *stem_sym_cast_##t(stem_symbol_t *sym);

STEM_SYM_HEADER(STEM_SYM_CLASS, class)
STEM_SYM_HEADER(STEM_SYM_FUNCTION, function)
STEM_SYM_HEADER(STEM_SYM_VARIABLE, variable)

#endif
