/*
 * demo_frame.h
 *
 *  Created on: Apr 10, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_FRAME_H_
#define DEMO_FRAME_H_

#include <atk/atk.h>
#include "AtkActor.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_FRAME            (c_atk_frame_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkFrame, c_atk_frame, C, ATK_FRAME, CAtkActor)

struct _CAtkFrameClass
{
  CAtkActorClass parent_class;
};

CAtkFrame *c_atk_frame_new (void);

G_END_DECLS

#endif /* DEMO_FRAME_H_ */
