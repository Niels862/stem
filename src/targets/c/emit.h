#ifndef STEM_TARGET_C_EMIT
#define STEM_TARGET_C_EMIT

#include "stem/stem.h"
#include "targets/cc/emit.h"
#include "target.h"
#include <stdio.h>

void stem_c_source_target_init(stem_target_t *target);

void stem_c_header_target_init(stem_target_t *target);

void stem_c_emit_module_source(stem_build_context_t *bctx, stem_node_t *vnode);

void stem_c_emit_module_header(stem_build_context_t *bctx, stem_node_t *vnode);

void stem_c_emit_class_declaration(stem_build_context_t *bctx, 
                                   stem_node_t *vnode);

void stem_c_emit_variable(stem_build_context_t *bctx, stem_node_t *vnode);

void stem_c_entry_source(stem_build_context_t *bctx, stem_node_t *vnode);

void stem_c_entry_header(stem_build_context_t *bctx, stem_node_t *vnode);

void stem_c_entry(stem_build_context_t *bctx, stem_node_t *vnode, char *dir);

#endif
