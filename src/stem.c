#include "stem/stem.h"
#include "targets/emit.h"
#include "semantics.h"
#include "context.h"
#include "token.h"
#include "target.h"
#include "renderer.h"

void stem_init() {
    
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

    stem_semantic_analysis(root);

    stem_node_write(root, 0, stdout);
    fprintf(stdout, "\n");

    stem_dispatch(&ctx, root);

    stem_render(&ctx, file);

    stem_tokenlist_free(&tokens);
}
