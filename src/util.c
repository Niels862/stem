#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *stem_xmalloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        perror("malloc");
        abort();
    }

    return p;
}

void *stem_xrealloc(void *p, size_t size) {
    void *pn = realloc(p, size);
    if (pn == NULL) {
        perror("realloc");
        abort();
    }

    return pn;
}

#define STEM_WRITE_CHAR_BUFFER_SIZE 256

void stem_write_n_chars(char c, int n, FILE *file) {
    static char buffer[STEM_WRITE_CHAR_BUFFER_SIZE];

    memset(buffer, c, STEM_WRITE_CHAR_BUFFER_SIZE);

    while (n > 0) {
        int block = STEM_WRITE_CHAR_BUFFER_SIZE;
        if (block > n) {
            block = n;
        }

        fprintf(file, "%.*s", block, buffer);

        n -= block;
    }
}
