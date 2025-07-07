#include "util.h"
#include <stdlib.h>
#include <stdio.h>

void *stem_xmalloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        perror("malloc");
        abort();
    }

    return p;
}
