#ifndef STEM_STRUTIL_H
#define STEM_STRUTIL_H

#include "pool.h"
#include <stdio.h>

typedef struct {
    char *start;
    char *end;
} stem_strview_t;

void stem_strview_init(stem_strview_t *str, char *start, char *end);

void stem_strview_init_in_pool(stem_strview_t *str, 
                               stem_pool_t *pool, char *data);

void stem_strview_write_literal(stem_strview_t *str, FILE *file);

void stem_strview_write(stem_strview_t *str, FILE *file);

void stem_str_write_literal(char *str, int len, FILE *file);

#endif
