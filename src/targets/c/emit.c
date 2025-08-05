#include "targets/c/emit.h"
#include <assert.h>
#include <stdarg.h>

void stem_c_target_init(stem_target_t *target) {
    static stem_emit_dispatch_function_t dispatch[STEM_N_NODES] = {
        [STEM_NODE_MODULE]      = &stem_cc_emit_module,
        [STEM_NODE_CLASS]       = NULL,
        [STEM_NODE_FUNCTION]    = &stem_cc_emit_function,
        [STEM_NODE_VARIABLE]    = NULL,
        [STEM_NODE_IF_ELSE]     = &stem_c_like_emit_if_else,
        [STEM_NODE_BOOL_LIT]    = &stem_c_like_bool_lit,
    };

    target->name = "C";
    for (size_t i = 0; i < STEM_N_NODES; i++) {
        target->emit_dispatch[i] = dispatch[i];
    }
}

