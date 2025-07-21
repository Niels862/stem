#include "targets/cc/emit.h"
#include "targets/emit.h"
#include "nodes.h"

void stem_cc_emit_function(stem_context_t *ctx, void *p) {
    stem_node_function_t *node = p;

    stem_separated(ctx, "void");
    stem_separated(ctx, node->name);
    stem_separator(ctx, "(");
    stem_separator(ctx, ")");

    stem_set_option(stem_separator(ctx, "{"), pre, space, true);
    stem_indent(ctx);

    stem_separated(ctx, "(text)");

    stem_dedent(ctx);
    stem_set_option(stem_separator(ctx, "}"), post, newline, true);
}
