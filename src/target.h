#ifndef STEM_TARGET_H
#define STEM_TARGET_H

#include "node.h"

typedef struct stem_context_t stem_context_t;

typedef void(*emit_dispatch_function_t)(stem_context_t *, void *);

typedef struct {
    char *name;
    emit_dispatch_function_t emit_dispatch[STEM_N_NODES];
} stem_target_t;

#endif
