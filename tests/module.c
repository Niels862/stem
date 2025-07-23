#include "stem/stem.h"

int main() {
    stem_init();

    stem_node_t *root = stem_module(
        stem_list(
            stem_class(
                "Class",
                stem_empty(),
                stem_empty()
            ),
            stem_list_end
        ),
        stem_list(
            stem_function(
                "func",
                stem_empty()
            ),
            stem_list_end
        )
    );

    stem_node_write(root, 0, stdout);
    fprintf(stdout, "\n");

    stem_c_profile_t profile;
    stem_c_profile_init(&profile);

    stem_build(root, (stem_profile_t *)&profile, stdout);

    stem_node_free(root);

    return 0;
}
