#ifndef STEM_CC_EMIT_H
#define STEM_CC_EMIT_H

#include "context.h"
#include "targets/c-like/emit.h"

void stem_cc_emit_module(stem_build_context_t *ctx, stem_node_t *node);

void stem_cc_emit_function(stem_build_context_t *ctx, stem_node_t *node);

#endif
