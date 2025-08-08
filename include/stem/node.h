#ifndef STEM_INCLUDE_NODE_H
#define STEM_INCLUDE_NODE_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct stem_node_t stem_node_t;

stem_node_t *stem_module(stem_node_t **classes, stem_node_t **functions);

stem_node_t *stem_class(char *name, stem_node_t **attributes, 
                        stem_node_t **methods);

stem_node_t *stem_function(char *name, stem_node_t **body);

stem_node_t *stem_variable(char *name, stem_node_t *type);

stem_node_t *stem_if_else(stem_node_t *cond, 
                          stem_node_t **then_body, stem_node_t **else_body);

stem_node_t *stem_if(stem_node_t *cond, stem_node_t **body);

stem_node_t *stem_bool(bool value);

stem_node_t *stem_true();

stem_node_t *stem_false();

stem_node_t *stem_ident(char *name);

stem_node_t **stem_empty();

stem_node_t **stem_list(stem_node_t *node, ...);

bool stem_list_is_empty(stem_node_t **list);

void stem_node_write(stem_node_t *node, size_t indent, FILE *file);

void stem_node_free(stem_node_t *node);

extern stem_node_t *stem_list_end;

#define STEM_AT_LIST_END(e) ((e) == stem_list_end)

#endif
