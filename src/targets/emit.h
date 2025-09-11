#ifndef STEM_EMIT_H
#define STEM_EMIT_H

#include "context.h"
#include "node.h"

#define stem_set_option(token, side, opt, value) \
        stem_set_format_option(&(token)->side.opt, value, true)

#define stem_set_option_soft(token, side, opt, value) \
        stem_set_format_option(&(token)->side.opt, value, false)

void stem_set_format_option(stem_format_option_t *opt, bool emit, bool force);

/* Token with soft space on both sides. */
stem_token_t *stem_separated(stem_build_context_t *bctx, char *text);

/* Token with hard no-space on both sides */
stem_token_t *stem_separator(stem_build_context_t *bctx, char *text);

stem_token_t *stem_indent(stem_build_context_t *bctx);

stem_token_t *stem_dedent(stem_build_context_t *bctx);

void stem_dispatch(stem_build_context_t *bctx, stem_node_t *node);

void stem_dispatch_list(stem_build_context_t *bctx, stem_node_t **list);

void stem_emission_phase(stem_build_context_t *bctx, stem_node_t *root);

#endif
