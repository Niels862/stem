#include "symbol.h"
#include "util.h"
#include "strutil.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void stem_symboltable_init(stem_symboltable_t *table) {
    stem_strmap_init(&table->map);
    table->parent = NULL;
}

void stem_symboltable_destruct(stem_symboltable_t *table) {
    stem_strmap_destruct(&table->map);
}

void stem_symboltable_link_parent(stem_symboltable_t *table, 
                                  stem_symboltable_t *parent) {
    assert(table->parent == NULL);
    assert(table != parent);
    assert(parent != NULL);

    table->parent = parent;
}

void stem_symboltable_write_oneline(stem_symboltable_t *table, FILE *file) {
    fprintf(file, "{{ ");

    stem_strmap_iter_t iter;
    stem_strmap_iter_init(&iter, &table->map);

    bool first = true;
    while (!stem_strmap_iter_at_end(&iter)) {
        if (!first) {
            fprintf(file, ", ");
        } else {
            first = false;
        }
        
        stem_symbol_write(iter.value, file);

        stem_strmap_iter_next(&iter);
    }

    fprintf(file, " }}");
}

void stem_symboltable_add(stem_symboltable_t *table, 
                          char *name, stem_symbol_t *sym) {
    stem_symbol_t *old = stem_strmap_insert(&table->map, name, sym);

    if (old != NULL) {
        fprintf(stderr, 
                "Fatal error: `%s` already defined in this scope\n", name);
        abort();
    }

    sym->name = name;
}

stem_symbol_t *stem_symboltable_lookup(stem_symboltable_t *table, char *name) {
    stem_symbol_t *symbol = stem_strmap_lookup(&table->map, name);
    
    if (symbol != NULL) {
        return symbol;
    }

    if (table->parent == NULL) {
        return NULL;
    }

    return stem_symboltable_lookup(table->parent, name);
}

char *stem_symbolkind_name(stem_symbolkind_t kind) {
    switch (kind) {
        case STEM_SYM_CLASS:    return "class";
        case STEM_SYM_FUNCTION: return "function";
        case STEM_SYM_VARIABLE: return "variable";
    }

    return "";
}

static void stem_symbol_base_init(stem_symbol_t *sym, stem_symbolkind_t kind) {
    sym->kind = kind;
    sym->name = NULL;
}

stem_symbol_t *stem_symbol_class(stem_node_class_t *node,
                                 stem_pool_t *pool) {
    stem_symbol_class_t *sym = 
            stem_pool_alloc(pool, sizeof(stem_symbol_class_t));

    stem_symbol_base_init(&sym->base, STEM_SYM_CLASS);
    sym->node = node;
    sym->type = stem_type_class(&sym->base, pool);

    return &sym->base;
}

stem_symbol_t *stem_symbol_function(stem_node_function_t *node, 
                                    stem_pool_t *pool) {
    stem_symbol_function_t *sym = 
            stem_pool_alloc(pool, sizeof(stem_symbol_function_t));

    stem_symbol_base_init(&sym->base, STEM_SYM_FUNCTION);
    sym->node = node;

    return &sym->base;
}

stem_symbol_t *stem_symbol_variable(stem_node_variable_t *node,
                                    stem_pool_t *pool) {
    stem_symbol_variable_t *sym =
            stem_pool_alloc(pool, sizeof(stem_symbol_variable_t));

    stem_symbol_base_init(&sym->base, STEM_SYM_VARIABLE);
    sym->node = node;
    sym->type = NULL;

    return &sym->base;
}

void stem_symbol_write(stem_symbol_t *vsym, FILE *file) {
    stem_str_write_literal(vsym->name, strlen(vsym->name), file);
    fprintf(file, ": <%s>", stem_symbolkind_name(vsym->kind));

    switch (vsym->kind) {
        case STEM_SYM_VARIABLE: {
            stem_symbol_variable_t *sym = stem_sym_cast_variable(vsym);

            fprintf(file, " (= ");
            stem_type_write(sym->type, file);
            fprintf(file, ")");

            break;
        }

        default:
            break;
    }
}

STEM_SYM_SOURCE(STEM_SYM_CLASS, class)
STEM_SYM_SOURCE(STEM_SYM_FUNCTION, function)
STEM_SYM_SOURCE(STEM_SYM_VARIABLE, variable)
