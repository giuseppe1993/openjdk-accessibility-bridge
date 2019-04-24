/*
 * demo_root_pane.h
 *
 *  Created on: Apr 11, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_ROOT_PANE_H_
#define DEMO_ROOT_PANE_H_

#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_ROOT_PANE            (c_atk_root_pane_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkRootPane, c_atk_root_pane, C, ATK_ROOT_PANE, AtkObject)

struct _CAtkRootPaneClass
{
  AtkObjectClass parent_class;

};

CAtkRootPane *c_atk_root_pane_new (void);

void c_atk_root_pane_add_child (CAtkRootPane *root_pane, AtkObject *obj);

void c_atk_root_pane_remove_child (CAtkRootPane *root_pane, AtkObject *obj);

void c_atk_root_pane_add_state (CAtkRootPane *root_pane, AtkStateType state);

void c_atk_root_pane_remove_state (CAtkRootPane *root_pane, AtkStateType state);

void c_atk_root_pane_add_attribute (CAtkRootPane *root_pane, AtkAttribute *attribute);

void c_atk_root_pane_remove_attribute (CAtkRootPane *root_pane, AtkAttribute *attribute);

#endif /* DEMO_ROOT_PANE_H_ */
