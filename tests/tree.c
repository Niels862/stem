#include "stem/stem.h"
#include "stem/builder.h"
#include <stdio.h>

stem_node_t *build_tree_class() {
    return Class(
        "Node",
        List(
            Variable("left", Ident("Node")),
            Variable("right", Ident("Node"))
        ),
        Empty
    );
}

int main() {
    stem_init();

    stem_node_t *root = Module(
        List( build_tree_class() ),
        Empty
    );

    stem_c_profile_t profile;
    stem_c_profile_init(&profile);

    stem_build(root, (stem_profile_t *)&profile, stdout, STEM_TARGET_C);

    stem_node_free(root);

    return 0;
}
