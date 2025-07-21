#ifndef STEM_CONTEXT_H
#define STEM_CONTEXT_H

#include "token.h"
#include "target.h"
#include "targets/profile.h"

struct stem_context_t {
    stem_tokenlist_t *tokens;
    stem_target_t *target;
    stem_profile_t *profile;
};

#endif
