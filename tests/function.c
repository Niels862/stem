#include "stem/stem.h"
#include <stdio.h>

int main() {
    stem_init();

    stem_node_t *root = stem_function(
        "func"
    );

    stem_free_node(root);

    return 0;
}
