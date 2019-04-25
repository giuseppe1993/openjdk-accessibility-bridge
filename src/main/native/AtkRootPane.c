/*
 * demo_root_pane.c
 *
 *  Created on: Apr 11, 2019
 *      Author: giuseppe
 */

#include <gmodule.h>
#include "AtkRootPane.h"

#define C_ATK_ROOT_PANE_GET_PRIVATE(o) (c_atk_root_pane_get_istance_private (o))

typedef struct
{
	gint pad1;
} CAtkRootPanePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRootPane, c_atk_root_pane, C_TYPE_ATK_ACTOR)

CAtkRootPane *
c_atk_root_pane_new (void)
{
  CAtkRootPane *root_pane = g_object_new (C_TYPE_ATK_ROOT_PANE, NULL);
  atk_object_initialize(ATK_OBJECT(root_pane), NULL);
  return root_pane;
}

static const char*
c_atk_root_pane_get_name (AtkObject *obj)
{
  return "Atk Root Pane";
}

static const char*
c_atk_root_pane_get_description()
{
	return "this is the description of the root pane component";
}

static void
c_atk_root_pane_initialize (AtkObject *self, gpointer null)
{
}

static void
c_atk_root_pane_finalize (GObject *object)
{
	g_return_if_fail (C_IS_ATK_ROOT_PANE(object));

	G_OBJECT_CLASS (c_atk_root_pane_parent_class)->finalize (object);
}


static void
c_atk_root_pane_class_init (CAtkRootPaneClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_root_pane_initialize;
	atk_class->get_name = c_atk_root_pane_get_name;
  atk_class->get_description = c_atk_root_pane_get_description;

  object_class->finalize = c_atk_root_pane_finalize;
}

static void
c_atk_root_pane_init (CAtkRootPane *self)
{
  atk_object_set_role(ATK_OBJECT(self),ATK_ROLE_ROOT_PANE);
	atk_object_set_parent(ATK_OBJECT(self),NULL);
} 
