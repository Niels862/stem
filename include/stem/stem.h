#ifndef STEM_STEM_H
#define STEM_STEM_H

#include <stdio.h>
#include <stddef.h>

typedef enum {
    STEM_NODE_NONE,

    STEM_NODE_CLASS,
    STEM_NODE_FUNCTION,
    STEM_NODE_VARIABLE,

    STEM_N_NODES,
} stem_nodekind_t;

typedef enum {
    STEM_ATTR_NONE,
    STEM_ATTR_NODE,
    STEM_ATTR_LIST,
    ATEM_ATTR_STRV,
} stem_node_attribute_type_t;

typedef struct {
    size_t offset;
    stem_node_attribute_type_t type;
} stem_node_attribute_t;

#define STEM_NODE_MAX_ATTRS 4

typedef struct {
    stem_nodekind_t kind;
    char *name;
    stem_node_attribute_t attrs[STEM_NODE_MAX_ATTRS];
} stem_node_descriptor_t;

typedef struct {
    stem_node_descriptor_t *desc;
} stem_node_t;

typedef struct {
    stem_node_t base;
    char *name;
    stem_node_t **attributes;
    stem_node_t **methods;
} stem_node_class_t;

typedef struct {
    stem_node_t base;
    char *name;
} stem_node_function_t;

typedef struct {
    stem_node_t base;
    char *name;
    stem_node_t *type;
} stem_node_variable_t;

void stem_init();

stem_node_t *stem_class(char *name, stem_node_t **attributes, 
                        stem_node_t **methods);

stem_node_t *stem_function(char *name);

stem_node_t *stem_variable(char *name, stem_node_t *type);

stem_node_t **stem_empty();

stem_node_t **stem_list(stem_node_t *node, ...);

void stem_node_write(stem_node_t *node, size_t indent, FILE *file);

void stem_node_free(stem_node_t *node);

#endif
