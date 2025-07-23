#ifndef STEM_INCLUDE_STEM_H
#define STEM_INCLUDE_STEM_H

#include "stem/node.h"
#include "stem/profile.h"
#include "stem/target.h"
#include <stdio.h>

void stem_init();

void stem_build(stem_node_t *root, stem_profile_t *profile, FILE *file);

#endif
