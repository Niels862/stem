#ifndef STEM_TYPE_H
#define STEM_TYPE_H

#include <stdio.h>

typedef enum {
    STEM_TYPE_NAMED,
} stem_typekind_t;

typedef struct {
    stem_typekind_t kind;
} stem_type_t;

typedef struct {
    stem_type_t base;
    char *name;
} stem_type_named_t;

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

STEM_TYPE_HEADER(STEM_TYPE_NAMED, named)

#endif
