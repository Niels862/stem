#include "target.h"
#include "targets/c/emit.h"

void stem_target_init(stem_target_t *target, stem_target_id_t id) {
    switch (id) {
        case STEM_TARGET_C: 
            stem_c_target_init(target);
            break;

        default:
            break;
    }
}
