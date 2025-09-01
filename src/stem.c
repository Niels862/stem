#include "stem/stem.h"
#include "targets/emit.h"
#include "context.h"
#include "token.h"
#include "target.h"
#include "renderer.h"
#include "util.h"
#include <stdlib.h>

static void debug_info_pre(stem_node_t *root, stem_target_t *target) {
    stem_node_module_t *node = stem_node_cast_module(root);

    fprintf(stderr, "Writing Module '%s' as target '%s'...\n\n", 
            node->name, target->name);
}

static void debug_info_post() {
    fprintf(stderr, "\n");
}

void stem_init() {
    
}

void stem_build(stem_node_t *root, stem_profile_t *profile, 
                stem_target_id_t tid, FILE *file) {
    stem_target_t target;
    stem_target_init(&target, tid);

    stem_tokenlist_t tokens;
    stem_tokenlist_init(&tokens);

    stem_build_context_t bctx = {
        .tokens = &tokens,
        .target = &target,
        .profile = profile,
    };

    debug_info_pre(root, &target);

    stem_emission_phase(&bctx, root);
    stem_render_phase(&bctx, file);

    debug_info_post();

    stem_tokenlist_free(&tokens);
}
