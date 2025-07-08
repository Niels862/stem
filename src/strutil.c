#include "strutil.h"
#include <string.h>
#include <ctype.h>

void stem_strview_init_in_pool(stem_strview_t *str, 
                               stem_pool_t *pool, char *data) {    
    size_t size = strlen(data);
    
    str->start = stem_pool_alloc(pool, size);
    str->end = str->start + size;

    memcpy(str->start, data, size);
}

void stem_strview_write_literal(stem_strview_t *str, FILE *file) {
    fprintf(file, "\"");

    for (char *s = str->start; s != str->end; s++) {

        switch (*s) {
            case '\n':
                fprintf(file, "\\n");
                break;

            case '\r':
                fprintf(file, "\\r");
                break;

            case '\t':
                fprintf(file, "\\t");
                break;

            case '\\':
                fprintf(file, "\\");
                break;

            default:
                if (isprint(*s)) {
                    fprintf(file, "%c", *s);
                } else if (*s < 10) {
                    fprintf(file, "\\%d", *s);
                } else {
                    fprintf(file, "\\x%02X", *s);
                }
                break;
        }
    }

    fprintf(file, "\"");
}

void stem_strview_write(stem_strview_t *str, FILE *file) {
    fprintf(file, "%.*s", (int)(str->end - str->start), str->start);
}
