/*
 * demo_frame.h
 *
 *  Created on: Apr 10, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_FRAME_H_
#define DEMO_FRAME_H_


#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_FRAME            (c_atk_frame_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkFrame, c_atk_frame, C, ATK_FRAME, AtkObject)

struct _CAtkFrameClass
{
  AtkObjectClass parent_class;

};

CAtkFrame *c_atk_frame_new (void);

void c_atk_frame_add_child(CAtkFrame *frame, AtkObject *obj, gpointer data);

void c_atk_frame_remove_child(CAtkFrame *frame, AtkObject *obj, gpointer data);

G_END_DECLS

#endif /* DEMO_FRAME_H_ */
