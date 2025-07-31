#include "stem/stem.h"
#include "targets/emit.h"
#include "semantics.h"
#include "context.h"
#include "token.h"
#include "target.h"
#include "renderer.h"

void stem_init() {
    
}

static void stem_node_context_init(stem_node_context_t *nctx) {
    stem_pool_init(&nctx->typepool, 256);
}

static void stem_node_context_destruct(stem_node_context_t *nctx) {
    stem_pool_destruct(&nctx->typepool);
}

static void stem_visitor_set_context(stem_node_t *node, void *nctx) {
    node->ctx = nctx;
}

void stem_build(stem_node_t *root, stem_profile_t *profile, FILE *file) {
    stem_target_t target;
    stem_target_init(&target, profile->target);

    stem_tokenlist_t tokens;
    stem_tokenlist_init(&tokens);

    stem_context_t ctx = {
        .tokens = &tokens,
        .target = &target,
        .profile = profile,
    };

    stem_node_context_t nctx;
    stem_node_context_init(&nctx);
    stem_node_visit(root, &nctx, stem_visitor_set_context);

    stem_semantic_analysis(root);

    stem_node_write(root, 0, stdout);
    fprintf(stdout, "\n");

    stem_dispatch(&ctx, root);

    stem_render(&ctx, file);

    stem_tokenlist_free(&tokens);

    stem_node_visit(root, NULL, stem_visitor_set_context);
    stem_node_context_destruct(&nctx);
}
