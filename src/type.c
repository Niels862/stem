#include "type.h"
#include "symbol.h"
#include <assert.h>

static void stem_type_base_init(stem_type_t *type, stem_typekind_t kind) {
    type->kind = kind;
}

stem_type_t *stem_type_class(stem_symbol_t *sym, stem_pool_t *pool) {
    stem_type_class_t *type = stem_pool_alloc(pool, sizeof(stem_type_class_t));

    stem_type_base_init(&type->base, STEM_TYPE_CLASS);
    type->sym = sym;

    return &type->base;
}

void stem_type_write(stem_type_t *vtype, FILE *file) {
    switch (vtype->kind) {
        case STEM_TYPE_CLASS: {
            stem_type_class_t *type = stem_type_cast_class(vtype);
            fprintf(file, "%s", type->sym->name);
            break;
        }

        default:
            break;
    }
}

STEM_TYPE_SOURCE(STEM_TYPE_CLASS, class)
