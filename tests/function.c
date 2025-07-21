#include "stem/stem-test-all.h"
#include <stdio.h>

int main() {
    stem_init();

    stem_node_t *root = stem_function(
        "func"
    );

    stem_node_write(root, 0, stdout);
    fprintf(stdout, "\n");

    stem_tokenlist_t tokens;
    stem_tokenlist_init(&tokens);

    stem_target_t target;
    stem_c_target_init(&target);

    stem_profile_t profile = {
        .indent.n = 2,
    };

    stem_context_t ctx = {
        .tokens = &tokens,
        .target = &target,
        .profile = &profile,
    };

    stem_dispatch(&ctx, root);
    stem_render(&ctx, stdout);

    stem_tokenlist_free(&tokens);
    stem_node_free(root);

    return 0;
}
