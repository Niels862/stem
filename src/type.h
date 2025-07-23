#ifndef STEM_TYPE_H
#define STEM_TYPE_H

typedef enum {
    STEM_TYPE_NAMED,
} stem_typekind_t;

typedef struct {
    stem_typekind_t kind;
} stem_type_t;

#endif
