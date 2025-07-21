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

    stem_profile_t profile = {
        .indent.n = 2,
    };

    stem_context_t ctx = {
        .tokens = &tokens,
        .profile = &profile,
    };

    stem_cc_emit_function(&ctx, root);
    stem_render(&ctx, stdout);

    stem_tokenlist_free(&tokens);
    stem_node_free(root);

    return 0;
}
