#include "strutil.h"
#include <string.h>

void stem_strview_pool_init(stem_strview_t *str, 
                            stem_pool_t *pool, char *data) {    
    size_t size = strlen(data);
    
    str->start = stem_pool_alloc(pool, size);
    str->end = str->start + size;
}
