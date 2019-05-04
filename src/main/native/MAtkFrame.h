/*
 * demo_frame.h
 *
 *  Created on: Apr 10, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_FRAME_H_
#define DEMO_FRAME_H_

#include <atk/atk.h>
#include "MAtkComponent.h"

G_BEGIN_DECLS

#define M_TYPE_ATK_FRAME            (m_atk_frame_get_type ())

G_DECLARE_DERIVABLE_TYPE(MAtkFrame, m_atk_frame, M, ATK_FRAME, MAtkComponent)

struct _MAtkFrameClass
{
  MAtkComponentClass parent_class;
};

MAtkFrame *m_atk_frame_new (void);

G_END_DECLS

#endif /* DEMO_FRAME_H_ */
