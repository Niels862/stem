#ifndef STEM_SYMBOL_H
#define STEM_SYMBOL_H

#include "node-forward.h"
#include "strmap.h"
#include <stdio.h>

typedef stem_strmap_t stem_symboltable_t;

typedef enum {
    STEM_SYM_CLASS,
    STEM_SYM_FUNCTION,
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

void stem_symboltable_init(stem_symboltable_t *table);

void stem_symboltable_destruct(stem_symboltable_t *table);

void stem_symboltable_write_oneline(stem_symboltable_t *table, FILE *file);

void symboltable_add(stem_symboltable_t *table, 
                     char *name, stem_symbol_t *sym);

stem_symbol_t *stem_symbol_class(stem_node_class_t *node);

stem_symbol_t *stem_symbol_function(stem_node_function_t *node);

#endif
