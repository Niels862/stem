#include "stem/stem.h"
#include "stem/builder.h"
#include <stdio.h>

stem_node_t *build_tree_class() {
    return Class(
        "Node",
        List(
            Variable("left", ClassType("Node", STEM_STORE_REFERENCE)),
            Variable("right", ClassType("Node", STEM_STORE_REFERENCE))
        ),
        Empty
    );
}

int main() {
    stem_init();

    stem_node_t *root = Module(
        "Tree",
        List( build_tree_class() ),
        Empty
    );

    stem_c_profile_t profile;
    stem_c_profile_init(&profile);

    stem_build(root, (stem_profile_t *)&profile, STEM_TARGET_C_SOURCE, stdout);
    stem_build(root, (stem_profile_t *)&profile, STEM_TARGET_C_HEADER, stdout);

    stem_node_free(root);

    return 0;
}
