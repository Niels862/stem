#ifndef STEM_EMIT_H
#define STEM_EMIT_H

#include "context.h"

static void stem_set_format_option(stem_format_option_t *opt, 
                                   bool emit, bool force) {
    opt->emit = emit;
    opt->force = force;
}

#define stem_set_option(token, side, opt, value) \
        stem_set_format_option(&(token)->side.opt, value, true)

/* Token with soft space on both sides. */
stem_token_t *stem_separated(stem_context_t *ctx, char *text);

/* Token with hard no-space on both sides */
stem_token_t *stem_separator(stem_context_t *ctx, char *text);

stem_token_t *stem_indent(stem_context_t *ctx);

stem_token_t *stem_dedent(stem_context_t *ctx);

#endif
