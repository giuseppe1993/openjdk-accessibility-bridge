/*
 * AtkRoot.h
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe
 */

#ifndef ATK_ROOT_H_
#define ATK_ROOT_H_

#include <atk/atk.h>
#include "AtkActor.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_ROOT            (c_atk_root_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkRoot, c_atk_root, C, ATK_ROOT, CAtkActor)

struct _CAtkRootClass
{
  CAtkActorClass parent_class;
};

CAtkRoot *c_atk_root_new (void);

G_END_DECLS

#endif 