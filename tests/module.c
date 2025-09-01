#include "stem/stem.h"
#include "stem/builder.h"

stem_node_t *build_function(char *name) {
    return Function(name, List(
        Variable("var1", Ident("int"))
    ));
}

stem_node_t *build_class() {
    return Class(
        "Class",
        List(
            Variable("x", Ident("int")),
            Variable("y", Ident("int"))
        ),
        List(
            build_function("method1"),
            build_function("method2")
        )
    );
}

int main() {
    stem_init();

    stem_node_t *root = Module(
        "Module",
        List( build_class() ),
        Empty
    );

    stem_node_context_t *nctx = stem_node_context_new(root);
    stem_finalize_tree(root);

    stem_c_profile_t profile;
    stem_c_profile_init(&profile);

    stem_build(root, (stem_profile_t *)&profile, STEM_TARGET_C_SOURCE, stdout);
    stem_build(root, (stem_profile_t *)&profile, STEM_TARGET_C_HEADER, stdout);

    stem_node_context_free(nctx, root);
    stem_node_free(root);

    return 0;
}
