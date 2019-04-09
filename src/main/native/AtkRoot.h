/*
 * AtkRoot.h
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe
 */

#ifndef _C_ATK_ROOT_H_
#define _C_ATK_ROOT_H_

#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_ROOT            (c_atk_root_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkRoot, c_atk_root, C, ATK_ROOT, AtkObject)

struct _CAtkRootClass
{
  AtkObjectClass parent_class;
};

CAtkRoot *c_atk_root_new (void);

void c_atk_root_add_child(CAtkRoot *root, AtkObject *obj, gpointer data);

void c_atk_root_remove_child(CAtkRoot *root, AtkObject *obj, gpointer data);

G_END_DECLS

#endif /* ATKROOT_H_ */
