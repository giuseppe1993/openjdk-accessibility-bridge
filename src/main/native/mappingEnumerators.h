#ifndef MEDIATOR_MAPPING_ENUMERATORS_H_
#define MEDIATOR_MAPPING_ENUMERATORS_H_

#include <atk/atk.h>

AtkRole mapping_role_from_Java (const char * role);
AtkState mapping_state_from_Java (const char *state);
AtkLayer mapping_layer_from_Java_role (const char * role);

#endif
