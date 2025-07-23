#include "symbol.h"

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
        fprintf(file, "%s", iter.key);

        stem_strmap_iter_next(&iter);
    }

    fprintf(file, " }}");
}

void stem_symboltable_insert(stem_symboltable_t *table, char *sym) {
    stem_strmap_insert(table, sym, NULL);
}
