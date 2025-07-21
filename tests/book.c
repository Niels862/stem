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

    stem_node_write(root, 0, stdout);
    fprintf(stdout, "\n");

    stem_node_free(root);

    return 0;
}
