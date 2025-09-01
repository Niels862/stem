#include "profile.h"

void stem_c_profile_init(stem_c_profile_t *profile) {
    stem_profile_init(&profile->cc.c_like.base);
}
