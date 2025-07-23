#ifndef STEM_STRMAP_H
#define STEM_STRMAP_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct stem_strmap_entry_t {
    char *key;
    void *value;
    uint32_t hash;
    struct stem_strmap_entry_t *next;
} stem_strmap_entry_t;

typedef struct {
    stem_strmap_entry_t **entries;
    size_t n;
    size_t cap;
} stem_strmap_t;

typedef struct {
    /* Exposed key-value pair. Value of key exclusively determines if iter is 
       at_end. */
    char *key;
    void *value;

    stem_strmap_t *map;

    /* NULL if at_end or iter invalid (after deletion) */
    stem_strmap_entry_t **pentry;

    /* Only indicates (ref to) next in bucket, can be NULL but not at_end */
    stem_strmap_entry_t **pnext;
    size_t idx;
} stem_strmap_iter_t;

void stem_strmap_init(stem_strmap_t *map);

void stem_strmap_destruct(stem_strmap_t *map);

void stem_strmap_write(stem_strmap_t *map, FILE *file);

/* If key exists: does not insert and returns value. 
 * Otherwise: returns NULL. 
 */
void *stem_strmap_insert(stem_strmap_t *map, char *key, void *value);

/* Delete entry and returns value if key exists.
 * Otherwise: returns NULL.
 */
void *stem_strmap_delete(stem_strmap_t *map, char *key);

void *stem_strmap_lookup(stem_strmap_t *map, char *key);

void stem_strmap_iter_init(stem_strmap_iter_t *iter, stem_strmap_t *map);

void stem_strmap_iter_next(stem_strmap_iter_t *iter);

void stem_strmap_iter_delete(stem_strmap_iter_t *iter);

bool stem_strmap_iter_at_end(stem_strmap_iter_t *iter);

#endif
