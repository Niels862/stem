#ifndef STEM_C_LIKE_EMIT_H
#define STEM_C_LIKE_EMIT_H

#include "context.h"
#include "targets/emit.h"

void stem_c_like_brace_open(stem_build_context_t *bctx);

void stem_c_like_brace_close(stem_build_context_t *bctx, 
                             bool newline, bool space);

void stem_c_like_block(stem_build_context_t *bctx, stem_node_t **block, 
                       bool newline);

void stem_c_like_paren_expr(stem_build_context_t *bctx, stem_node_t *vnode);

void stem_c_like_semicolon(stem_build_context_t *bctx);

void stem_c_like_emit_bool_lit(stem_build_context_t *bctx, stem_node_t *vnode);

void stem_c_like_emit_if_else(stem_build_context_t *bctx, stem_node_t *vnode);

#endif
