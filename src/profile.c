#include "profile.h"

void stem_profile_init(stem_profile_t *profile, stem_target_id_t target) {
    profile->target = target;
    profile->indent.n = 2;
}
