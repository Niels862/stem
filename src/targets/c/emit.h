#ifndef STEM_TARGET_C_EMIT
#define STEM_TARGET_C_EMIT

#include "stem/stem.h"
#include "targets/cc/emit.h"
#include "target.h"
#include <stdio.h>

void stem_c_target_init(stem_target_t *target);

void stem_emit_c(stem_node_t *root, FILE *file);

#endif
