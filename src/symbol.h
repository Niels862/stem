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

typedef struct {
    stem_symbolkind_t kind;
} stem_symbol_t;

typedef struct {
    stem_symbol_t base;
    stem_node_class_t *node;
} stem_symbol_class_t;

typedef struct {
    stem_symbol_t base;
    stem_node_function_t *node;
} stem_symbol_function_t;

typedef struct {
    stem_symbol_t base;
    stem_node_variable_t *node;
    stem_type_t *type;
} stem_symbol_variable_t;

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

#endif
