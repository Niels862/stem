#include "strmap.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STEM_STRMAP_INIT_CAP 8

// https://stackoverflow.com/a/7666577
static uint32_t stem_strhash(char *str) {
    uint32_t hash = 5381;

    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

static void stem_strmap_lookup_internal(stem_strmap_t *map, char *key,
                                        uint32_t *hash, size_t *idx, 
                                        stem_strmap_entry_t ***pentry) {
    *hash = stem_strhash(key);
    *idx = map->cap % *hash;

    *pentry = &map->entries[*idx];
    stem_strmap_entry_t *entry = **pentry;

    while (entry != NULL) {
        if (entry->hash == *hash && strcmp(entry->key, key) == 0) {
            return;
        }
        *pentry = &entry->next;
        entry = **pentry;
    }

    *pentry = NULL;
}

void stem_strmap_init(stem_strmap_t *map) {
    map->cap = STEM_STRMAP_INIT_CAP;
    map->n = 0;
    
    map->entries = stem_xmalloc(map->cap * sizeof(stem_strmap_entry_t *));
    for (size_t i = 0; i < map->cap; i++) {
        map->entries[i] = NULL;
    }
}

void stem_strmap_destruct(stem_strmap_t *map) {
    for (size_t i = 0; i < map->cap; i++) {
        stem_strmap_entry_t *entry = map->entries[i];

        while (entry != NULL) {
            stem_strmap_entry_t *next = entry->next;
            free(entry);
            entry = next;
        }
    }

    free(map->entries);
}

void *stem_strmap_insert(stem_strmap_t *map, char *key, void *value) {
    size_t idx;
    uint32_t hash;
    stem_strmap_entry_t **pentry;
    stem_strmap_lookup_internal(map, key, &hash, &idx, &pentry);

    if (pentry != NULL) {
        return (*pentry)->value;
    }
    
    stem_strmap_entry_t *new = stem_xmalloc(sizeof(stem_strmap_entry_t));

    new->key = key;
    new->value = value;
    new->hash = hash;
    new->next = map->entries[idx];

    map->entries[idx] = new;
    map->n++;

    return NULL;
}

void *stem_strmap_delete(stem_strmap_t *map, char *key) {
    size_t idx;
    uint32_t hash;
    stem_strmap_entry_t **pentry;
    stem_strmap_lookup_internal(map, key, &hash, &idx, &pentry);

    if (pentry == NULL) {
        return NULL;
    }

    stem_strmap_entry_t *entry = *pentry;
    void *value = entry->value;
    *pentry = entry->next;
    free(entry);

    map->n--;

    return value;
}

void *stem_strmap_lookup(stem_strmap_t *map, char *key) {
    size_t idx;
    uint32_t hash;
    stem_strmap_entry_t **pentry;
    stem_strmap_lookup_internal(map, key, &hash, &idx, &pentry);

    if (pentry == NULL) {
        return NULL;
    } else {
        return (*pentry)->value;
    }
}

static bool stem_strmap_iter_valid(stem_strmap_iter_t *iter) {
    return iter->pentry != NULL;
}

static void stem_strmap_iter_fill_entry(stem_strmap_iter_t *iter, 
                                        stem_strmap_entry_t **pentry, 
                                        size_t idx) {
    iter->key = (*pentry)->key;
    iter->value = (*pentry)->value;
    iter->pentry = pentry;
    iter->pnext = &(*pentry)->next;
    iter->idx = idx;
}

static void stem_strmap_iter_find_next_entry(stem_strmap_iter_t *iter,
                                             size_t idx_start) {
    stem_strmap_t *map = iter->map;

    for (size_t i = idx_start; i < map->cap; i++) {
        stem_strmap_entry_t **pentry = &map->entries[i];

        if (*pentry != NULL) {
            stem_strmap_iter_fill_entry(iter, pentry, i);
            return;
        }
    }

    iter->key = NULL;
    iter->value = NULL;
    iter->pentry = NULL;
    iter->pnext = NULL;
    iter->idx = 0;
}

void stem_strmap_iter_init(stem_strmap_iter_t *iter, stem_strmap_t *map) {
    iter->map = map;
    stem_strmap_iter_find_next_entry(iter, 0);
}

void stem_strmap_iter_next(stem_strmap_iter_t *iter) {
    if (stem_strmap_iter_at_end(iter)) {
        return;
    }

    if (*iter->pnext == NULL) {
        stem_strmap_iter_find_next_entry(iter, iter->idx + 1);
    } else {
        stem_strmap_iter_fill_entry(iter, iter->pnext, iter->idx);
    }
}

void stem_strmap_iter_delete(stem_strmap_iter_t *iter) {
    assert(!stem_strmap_iter_at_end(iter));
    assert(stem_strmap_iter_valid(iter));

    *iter->pentry = (*iter->pentry)->next;  
    iter->pnext = iter->pentry;
    iter->pentry = NULL;  
}

bool stem_strmap_iter_at_end(stem_strmap_iter_t *iter) {
    return iter->key == NULL;
}
