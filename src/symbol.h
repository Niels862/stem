#ifndef STEM_SYMBOL_H
#define STEM_SYMBOL_H

#include "strmap.h"
#include <stdio.h>

typedef stem_strmap_t stem_symboltable_t;

void stem_symboltable_init(stem_symboltable_t *table);

void stem_symboltable_destruct(stem_symboltable_t *table);

void stem_symboltable_write(stem_symboltable_t *table, FILE *file);

#endif
