#include "stem/stem.h"
#include "stem/builder.h"
#include <stdio.h>

static stem_node_t *build_function() {
    return Function(
        "func",
        List(
            IfElse(
                False,
                Empty,
                List(
                    If(
                        True,
                        Empty
                    )
                )
            )
        )
    );
}

int main() {
    stem_init();

    stem_node_t *root = Module(
        "Module",
        Empty,
        List(
            build_function()
        )
    );

    stem_node_context_t *nctx = stem_node_context_new(root);
    stem_finalize_tree(root);

    stem_c_profile_t profile;
    stem_c_profile_init(&profile);

    stem_build(root, (stem_profile_t *)&profile, STEM_TARGET_C_SOURCE, stdout);
    
    stem_node_context_free(nctx, root);
    stem_node_free(root);

    return 0;
}
