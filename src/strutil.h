#ifndef STEM_STRUTIL_H
#define STEM_STRUTIL_H

#include "pool.h"
#include <stdio.h>

typedef struct {
    char *start;
    char *end;
} stem_strview_t;

typedef struct {
    char *buf;
    size_t cap;
    size_t len;
} stem_strbuilder_t;

void stem_strview_init(stem_strview_t *str, char *start, char *end);

void stem_strview_init_in_pool(stem_strview_t *str, 
                               stem_pool_t *pool, char *data);

void stem_strview_write_literal(stem_strview_t *str, FILE *file);

void stem_strview_write(stem_strview_t *str, FILE *file);

void stem_strbuilder_init(stem_strbuilder_t *sb, size_t size);

void stem_strbuilder_destruct(stem_strbuilder_t *sb);

void stem_strbuilder_clear(stem_strbuilder_t *sb);

void stem_strbuilder_append(stem_strbuilder_t *sb, char *s);

void stem_str_write_literal(char *str, int len, FILE *file);

#endif
