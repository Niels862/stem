#ifndef STEM_UTIL_H
#define STEM_UTIL_H

#include <stdio.h>
#include <stddef.h>

void *stem_xmalloc(size_t size);

void stem_write_n_chars(char c, int n, FILE *file);

#endif
