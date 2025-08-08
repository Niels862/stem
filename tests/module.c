#include "stem/stem.h"
#include "stem/builder.h"

stem_node_t *build_function(char *name) {
    return Function(name, Empty);
}

stem_node_t *build_class() {
    return Class(
        "Class",
        Empty,
        List(
            build_function("method1"),
            build_function("method2")
        )
    );
}

int main() {
    stem_init();

    stem_node_t *root = Module(
        List( build_class() ),
        Empty
    );

    stem_c_profile_t profile;
    stem_c_profile_init(&profile);

    stem_build(root, (stem_profile_t *)&profile, stdout);

    stem_node_free(root);

    return 0;
}
