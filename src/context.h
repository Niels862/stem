#ifndef STEM_CONTEXT_H
#define STEM_CONTEXT_H

#include "token.h"
#include "targets/profile.h"

typedef struct {
    stem_tokenlist_t *tokens;
    stem_profile_t *profile;
} stem_context_t;

#endif
