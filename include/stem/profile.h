#ifndef STEM_INCLUDE_PROFILE_H
#define STEM_INCLUDE_PROFILE_H

#include "stem/target.h"
#include <stddef.h>

typedef struct {
    size_t n;
} stem_indent_profile_t;

typedef struct {
    stem_indent_profile_t indent;
} stem_profile_t;

typedef struct {
    stem_profile_t base;
} stem_c_like_profile_t;

typedef struct {
    stem_c_like_profile_t c_like;
} stem_cc_profile_t;

typedef struct {
    stem_cc_profile_t cc;
} stem_c_profile_t;

void stem_c_profile_init(stem_c_profile_t *profile);

#endif
