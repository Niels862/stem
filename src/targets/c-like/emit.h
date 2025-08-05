#ifndef STEM_C_LIKE_EMIT_H
#define STEM_C_LIKE_EMIT_H

#include "context.h"
#include "targets/emit.h"

void stem_c_like_block(stem_context_t *ctx, stem_node_t **block, bool newline);

void stem_c_like_paren_expr(stem_context_t *ctx, stem_node_t *vnode);

void stem_c_like_bool_lit(stem_context_t *ctx, stem_node_t *vnode);

void stem_c_like_emit_if_else(stem_context_t *ctx, stem_node_t *vnode);

#endif
