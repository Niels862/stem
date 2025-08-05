#ifndef STEM_TARGET_C_EMIT
#define STEM_TARGET_C_EMIT

#include "stem/stem.h"
#include "targets/cc/emit.h"
#include "target.h"
#include <stdio.h>

void stem_c_target_init(stem_target_t *target);

void stem_c_emit_class(stem_context_t *ctx, stem_node_t *vnode);

#endif
