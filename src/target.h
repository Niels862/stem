#ifndef STEM_TARGET_H
#define STEM_TARGET_H

#include "stem/target.h"
#include "node.h"

typedef struct stem_build_context_t stem_build_context_t;

typedef void(*stem_emit_dispatch_function_t)(stem_build_context_t *, stem_node_t *);

typedef struct {
    char *name;
    stem_emit_dispatch_function_t *emit_dispatch;
} stem_target_t;

void stem_target_init(stem_target_t *target, stem_target_id_t id);

#endif
