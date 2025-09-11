#include "strutil.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void stem_strview_init(stem_strview_t *str, char *start, char *end) {
    str->start = start;
    str->end = end;
}

void stem_strview_init_in_pool(stem_strview_t *str, 
                               stem_pool_t *pool, char *data) {    
    size_t size = strlen(data);
    
    str->start = stem_pool_alloc(pool, size);
    str->end = str->start + size;

    memcpy(str->start, data, size);
}

void stem_strview_write_literal(stem_strview_t *str, FILE *file) {
    if (str->start == NULL) {
        fprintf(file, "(null)");
        return;
    }
    
    stem_str_write_literal(str->start, (int)(str->end - str->start), file);
}

void stem_strview_write(stem_strview_t *str, FILE *file) {
    fprintf(file, "%.*s", (int)(str->end - str->start), str->start);
}

static void stem_strbuilder_realloc(stem_strbuilder_t *sb, size_t len) {
    while (sb->cap < len) {
        sb->cap *= 2;
    }
    sb->buf = stem_xrealloc(sb->buf, sb->cap);
}

void stem_strbuilder_init(stem_strbuilder_t *sb, size_t size) {
    sb->cap = size;
    sb->buf = stem_xmalloc(sb->cap);
    sb->len = 0;
}

void stem_strbuilder_destruct(stem_strbuilder_t *sb) {
    free(sb->buf);
}

void stem_strbuilder_clear(stem_strbuilder_t *sb) {
    sb->len = 0;
}

void stem_strbuilder_append(stem_strbuilder_t *sb, char *s) {
    int len = strlen(s);
    if (sb->len + len > sb->cap) {
        stem_strbuilder_realloc(sb, len);
    }
    
    memcpy(sb->buf + sb->len, s, len);
    sb->len += len;
}

void stem_str_write_literal(char *str, int len, FILE *file) {
    fprintf(file, "\"");

    for (int i = 0; i < len; i++) {
        char c = str[i];
        
        switch (c) {
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
                if (isprint(c)) {
                    fprintf(file, "%c", c);
                } else if (c < 10) {
                    fprintf(file, "\\%d", c);
                } else {
                    fprintf(file, "\\x%02X", c);
                }
                break;
        }
    }

    fprintf(file, "\"");
}