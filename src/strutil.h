#ifndef STEM_STRUTIL_H
#define STEM_STRUTIL_H

#include "pool.h"

typedef struct {
    char *start;
    char *end;
} stem_strview_t;

void stem_strview_pool_init(stem_strview_t *str, 
                            stem_pool_t *pool, char *data);

#endif
