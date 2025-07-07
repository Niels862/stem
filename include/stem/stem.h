#ifndef STEM_STEM_H
#define STEM_STEM_H

typedef enum {
    STEM_NODE_CLASS,
    STEM_NODE_VARIABLE,
    STEM_NODE_IDENTIFIER,
} stem_nodekind_t;

typedef struct {
    stem_nodekind_t kind;
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
    stem_node_t *type;
} stem_node_variable_t;

typedef struct {
    stem_node_t base;
    char *name;
} stem_node_identifier_t;

#define STEM_FOR_EACH(arr, id) \
        for (stem_node_t **_##id = arr, *id = *_##id; \
              *_##id != NULL; \
             _##id++, id = *_##id)

void stem_init();

stem_node_t *stem_class(char *name, stem_node_t **attributes, 
                        stem_node_t **methods);

stem_node_t *stem_variable(char *name, stem_node_t *type);

stem_node_t *stem_identifier(char *name);

stem_node_t **stem_empty();

stem_node_t **stem_list(stem_node_t *node, ...);

void stem_free_node(stem_node_t *node);

#endif
