/*
 * AtkRoot.h
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe
 */

#ifndef _C_ATK_ROOT_H_
#define _C_ATK_ROOT_H_

#include <atk/atk.h>
#include "MAtkObject.h"

G_BEGIN_DECLS

#define M_TYPE_ATK_ROOT            (m_atk_root_get_type ())

G_DECLARE_DERIVABLE_TYPE(MAtkRoot, m_atk_root, M, ATK_ROOT, MAtkObject)

struct _MAtkRootClass
{
  MAtkObjectClass parent_class;
};

MAtkRoot *m_atk_root_new (void);

G_END_DECLS

#endif /* ATKROOT_H_ */
