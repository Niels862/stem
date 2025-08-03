#ifndef STEM_BUILDER_H
#define STEM_BUILDER_H

#include "stem/node.h"

#define List(...) stem_list(__VA_ARGS__, stem_list_end)
#define Empty stem_empty()

#define Module(...) stem_module(__VA_ARGS__)

#define Class(...) stem_class(__VA_ARGS__)

#define Function(...) stem_function(__VA_ARGS__)

#define Variable(...) stem_variable(__VA_ARGS__)

#define IfElse(...) stem_if_else(__VA_ARGS__)

#define If(...) stem_if(__VA_ARGS__)

#define Bool(...) stem_bool(__VA_ARGS__)

#define True stem_true()
#define False stem_false()

#endif
