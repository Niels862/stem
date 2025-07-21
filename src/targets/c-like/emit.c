#include "targets/c-like/emit.h"

void stem_c_like_open_block(stem_context_t *ctx) {
    stem_set_option(stem_separator(ctx, "{"), pre, space, true);
    stem_indent(ctx);
}

void stem_c_like_close_block(stem_context_t *ctx) {
    stem_dedent(ctx);
    stem_set_option(stem_separator(ctx, "}"), post, newline, true);
}