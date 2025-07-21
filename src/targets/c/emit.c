#include "targets/c/emit.h"
#include <assert.h>
#include <stdarg.h>

void stem_c_target_init(stem_target_t *target) {
    static emit_dispatch_function_t dispatch[STEM_N_NODES] = {
        [STEM_NODE_CLASS]       = NULL,
        [STEM_NODE_FUNCTION]    = &stem_cc_emit_function,
        [STEM_NODE_VARIABLE]    = NULL,
        [STEM_NODE_IF_ELSE]     = &stem_c_like_emit_if_else,
    };

    target->name = "C";
    for (size_t i = 0; i < STEM_N_NODES; i++) {
        target->emit_dispatch[i] = dispatch[i];
    }
}

void stem_emit_c(stem_node_t *root, FILE *file) {
    (void)root, (void)file;
}
