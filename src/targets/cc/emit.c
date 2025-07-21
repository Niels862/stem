#include "targets/cc/emit.h"
#include "nodes.h"

void stem_cc_emit_function(stem_context_t *ctx, void *p) {
    stem_node_function_t *node = p;

    stem_separated(ctx, "void");
    stem_separated(ctx, node->name);
    stem_separator(ctx, "(");
    stem_separator(ctx, ")");

    stem_c_like_block(ctx, node->body, true);
}
