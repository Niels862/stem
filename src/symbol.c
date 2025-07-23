#include "symbol.h"

void stem_symboltable_init(stem_symboltable_t *table) {
    stem_strmap_init(table);
}

void stem_symboltable_destruct(stem_symboltable_t *table) {
    stem_strmap_destruct(table);
}

void stem_symboltable_write(stem_symboltable_t *table, FILE *file) {
    (void)table, (void)file;
}
