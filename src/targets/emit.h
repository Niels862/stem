#ifndef STEM_EMIT_H
#define STEM_EMIT_H

#include "context.h"
#include "nodes.h"

#define stem_set_option(token, side, opt, value) \
        stem_set_format_option(&(token)->side.opt, value, true)

void stem_set_format_option(stem_format_option_t *opt, bool emit, bool force);

/* Token with soft space on both sides. */
stem_token_t *stem_separated(stem_context_t *ctx, char *text);

/* Token with hard no-space on both sides */
stem_token_t *stem_separator(stem_context_t *ctx, char *text);

stem_token_t *stem_indent(stem_context_t *ctx);

stem_token_t *stem_dedent(stem_context_t *ctx);

void stem_dispatch(stem_context_t *ctx, stem_node_t *node);

#endif
