#ifndef STEM_BUILDER_H
#define STEM_BUILDER_H

#include "stem/node.h"

#define List(...) stem_list(__VA_ARGS__, stem_list_end)
#define Empty stem_empty()

#define Module stem_module

#define Class stem_class

#define Function stem_function

#define Variable stem_variable

#define IfElse stem_if_else

#define If stem_if

#define Bool stem_bool

#define True stem_true()
#define False stem_false()

#define Ident stem_ident

#endif
