/*
 * AtkRoot.h
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe
 */

#ifndef _C_ATK_ROOT_H_
#define _C_ATK_ROOT_H_

#include <atk/atk.h>

G_BEGIN_DECLS

#define C_ATK_TYPE_ROOT            (c_atk_root_get_type ())

/* Work around the fact that Atk does not define the auto pointer cleanup.
 * Add a check using ATK_CHECK_VERSION once fixed in Atk upstream. */
G_DEFINE_AUTOPTR_CLEANUP_FUNC(AtkObject, g_object_unref)

G_DECLARE_DERIVABLE_TYPE(CAtkRoot, c_atk_root, C, ATK_ROOT, AtkObject)

struct _CAtkRootClass
{
  AtkObjectClass parent_class;

};

CAtkRoot *c_atk_root_new (void);

G_END_DECLS

#endif /* ATKROOT_H_ */
