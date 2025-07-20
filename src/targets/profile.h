#ifndef STEM_PROFILE_H
#define STEM_PROFILE_H

#include <stddef.h>

typedef struct {
    size_t n;
} stem_indent_profile_t;

typedef struct {
    stem_indent_profile_t indent;
} stem_profile_t;

#endif
