#include "stem/stem.h"
#include <stdio.h>

int main() {
    stem_init();

    stem_node_t *root = stem_class(
        "book", 
        stem_list(
            stem_variable("pages", NULL), NULL
        ), 
        stem_empty()
    );

    stem_free_node(root);

    return 0;
}
