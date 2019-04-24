/*
 * AtkWindow.h
 *
 *  Created on: Apr 4, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_WINDOW_H_
#define DEMO_WINDOW_H_

#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_WINDOW            (c_atk_window_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkWindow, c_atk_window, C, ATK_WINDOW, AtkObject)

struct _CAtkWindowClass
{
  AtkObjectClass parent_class;

};

CAtkWindow *c_atk_window_new (void);

void c_atk_window_add_child(CAtkWindow *window, AtkObject *obj);

void c_atk_window_remove_child(CAtkWindow *window, AtkObject *obj);

G_END_DECLS

#endif /* DEMO_WINDOW_H_ */
