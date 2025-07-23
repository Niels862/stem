#include "symbol.h"
#include "util.h"
#include "strutil.h"
#include <string.h>

void stem_symboltable_init(stem_symboltable_t *table) {
    stem_strmap_init(table);
}

void stem_symboltable_destruct(stem_symboltable_t *table) {
    stem_strmap_iter_t iter;
    stem_strmap_iter_init(&iter, table);

    while (!stem_strmap_iter_at_end(&iter)) {
        stem_strmap_iter_delete(&iter);
        stem_strmap_iter_next(&iter);
    }

    stem_strmap_destruct(table);
}

void stem_symboltable_write_oneline(stem_symboltable_t *table, FILE *file) {
    fprintf(file, "{{ ");

    stem_strmap_iter_t iter;
    stem_strmap_iter_init(&iter, table);

    bool first = true;
    while (!stem_strmap_iter_at_end(&iter)) {
        if (!first) {
            fprintf(file, ", ");
        } else {
            first = false;
        }
        stem_str_write_literal(iter.key, strlen(iter.key), file);

        stem_strmap_iter_next(&iter);
    }

    fprintf(file, " }}");
}

void stem_symbol_declare(stem_symboltable_t *table, 
                         char *name, stem_symbol_t *sym) {
    stem_symbol_t *old = stem_strmap_insert(table, name, sym);
    (void)old;
}

stem_symbol_t *stem_symbol_class(stem_node_class_t *node) {
    stem_symbol_class_t *sym = stem_xmalloc(sizeof(stem_symbol_class_t));

    sym->base.kind = STEM_SYM_CLASS;
    sym->node = node;

    return &sym->base;
}

stem_symbol_t *stem_symbol_function(stem_node_function_t *node) {
    stem_symbol_function_t *sym = stem_xmalloc(sizeof(stem_symbol_function_t));

    sym->base.kind = STEM_SYM_FUNCTION;
    sym->node = node;

    return &sym->base;
}
