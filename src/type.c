#include "type.h"
#include <assert.h>

void stem_type_write(stem_type_t *vtype, FILE *file) {
    switch (vtype->kind) {
        case STEM_TYPE_NAMED:
            fprintf(file, "%s", stem_type_cast_named(vtype)->name);
            break;

        default:
            break;
    }
}

STEM_TYPE_SOURCE(STEM_TYPE_NAMED, named)
