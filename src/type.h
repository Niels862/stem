#ifndef STEM_TYPE_H
#define STEM_TYPE_H

#include "symbol-forward.h"
#include "pool.h"
#include <stdio.h>

typedef enum {
    STEM_TYPE_CLASS,
} stem_typekind_t;

typedef struct {
    stem_typekind_t kind;
} stem_type_t;

typedef struct {
    stem_type_t base;
    stem_symbol_t *sym; /* FIXME: initialize */
} stem_type_class_t;

stem_type_t *stem_type_class(stem_symbol_t *sym, stem_pool_t *pool);

void stem_type_write(stem_type_t *vtype, FILE *file);

#define STEM_TYPE_TYPE(t) stem_type_##t##_t

#define STEM_TYPE_HEADER(e, t) \
    STEM_TYPE_TYPE(t) *stem_type_cast_##t(stem_type_t *type);

#define STEM_TYPE_SOURCE(e, t) \
    STEM_TYPE_TYPE(t) *stem_type_cast_##t(stem_type_t *type) { \
        assert(type != NULL); \
        assert(type->kind == e); \
        return (STEM_TYPE_TYPE(t) *)type; \
    }

STEM_TYPE_HEADER(STEM_TYPE_CLASS, class)

#endif
