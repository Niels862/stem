#include "stem/stem.h"
#include <stdio.h>

static stem_node_t *build_function() {
    return stem_function(
        "func",
        stem_list(
            stem_if_else(
                NULL,
                stem_empty(),
                stem_list(
                    stem_if(
                        NULL,
                        stem_empty()
                    ),
                    stem_list_end
                )
            ),
            stem_if(
                NULL,
                stem_empty()
            ),
            stem_list_end
        )
    );
}

int main() {
    stem_init();

    stem_node_t *root = stem_module(
        stem_empty(),
        stem_list(
            build_function(),
            stem_list_end
        )
    );

    stem_c_profile_t profile;
    stem_c_profile_init(&profile);

    stem_build(root, (stem_profile_t *)&profile, stdout);
    
    stem_node_free(root);

    return 0;
}
