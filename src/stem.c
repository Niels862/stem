#include "stem/stem.h"
#include "targets/emit.h"
#include "semantics.h"
#include "context.h"
#include "token.h"
#include "target.h"
#include "renderer.h"
#include "util.h"
#include <stdlib.h>

void stem_init() {
    
}

static void stem_visitor_set_context(stem_node_t *node, void *nctx) {
    node->ctx = nctx;
}

stem_node_context_t *stem_node_context_new(stem_node_t *root) {
    stem_node_context_t *nctx = stem_xmalloc(sizeof(stem_node_context_t));
    
    stem_pool_init(&nctx->pool, 256);
    nctx->_curr = NULL;
    nctx->_traversal = NULL;

    stem_node_visit(root, nctx, stem_visitor_set_context);

    return nctx;
}

void stem_node_context_free(stem_node_context_t *nctx,
                            stem_node_t *root) {
    stem_node_visit(root, NULL, stem_visitor_set_context);

    stem_pool_destruct(&nctx->pool);
    free(nctx);
}

void stem_build(stem_node_t *root, stem_profile_t *profile, FILE *file, stem_target_id_t tid) {
    stem_target_t target;
    stem_target_init(&target, tid);

    stem_tokenlist_t tokens;
    stem_tokenlist_init(&tokens);

    stem_build_context_t bctx = {
        .tokens = &tokens,
        .target = &target,
        .profile = profile,
    };

    stem_node_context_t *nctx = stem_node_context_new(root);

    stem_semantic_phase(root);
    stem_emission_phase(&bctx, root);
    stem_render_phase(&bctx, file);

    stem_node_write(root, 0, stderr);
    fprintf(stderr, "\n");

    stem_tokenlist_free(&tokens);

    stem_node_context_free(nctx, root);
}
