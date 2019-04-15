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
	GList *accessibleObjects;

} CAtkRootPanePrivate;


G_DEFINE_TYPE_WITH_PRIVATE (CAtkRootPane, c_atk_root_pane, ATK_TYPE_OBJECT)

void c_atk_root_pane_add_child(CAtkRootPane *root_pane, AtkObject *obj)
{
	CAtkRootPanePrivate *priv = c_atk_root_pane_get_instance_private(root_pane);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (root_pane));

	priv->accessibleObjects = g_list_append (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);
	g_signal_emit_by_name (root_pane, "children-changed::add", index, obj, NULL);

}

void c_atk_root_pane_remove_child(CAtkRootPane *root_pane, AtkObject *obj)
{
	CAtkRootPanePrivate *priv = c_atk_root_pane_get_instance_private(root_pane);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (root_pane));

	priv->accessibleObjects = g_list_remove (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);

	g_signal_emit_by_name (root_pane, "children-changed::remove", index, obj, NULL);
}

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
	atk_object_set_role(self,ATK_ROLE_ROOT_PANE);
	atk_object_set_parent(self,NULL);
}

static gint
c_atk_root_pane_get_n_children (AtkObject *obj)
{
  CAtkRootPanePrivate *priv = c_atk_root_pane_get_instance_private(C_ATK_ROOT_PANE(obj));
  return g_list_length (priv->accessibleObjects);
}

static AtkObject*
c_atk_root_pane_ref_child (AtkObject *obj, gint i)
{
  GList *obj_list = NULL;
  gint num = 0;
  AtkObject *item = NULL;

  CAtkRootPanePrivate *priv = c_atk_root_pane_get_instance_private(C_ATK_ROOT_PANE(obj));

  obj_list = priv->accessibleObjects;

  num = g_list_length (obj_list);

  g_return_val_if_fail ((i < num)&&(i >= 0), NULL);

  item = g_list_nth_data (obj_list, i);
  if (!item)
      return NULL;

  g_object_ref (item);

  return item;
}



static void
c_atk_root_pane_finalize (GObject *object)
{
	CAtkRootPane *root_pane = C_ATK_ROOT_PANE(object);

	g_return_if_fail (C_IS_ATK_ROOT_PANE(object));

	CAtkRootPanePrivate *priv = c_atk_root_pane_get_instance_private(root_pane);

	if (priv->accessibleObjects)
	{
	  g_list_free (priv->accessibleObjects);
	  priv->accessibleObjects = NULL;
	}

	G_OBJECT_CLASS (c_atk_root_pane_parent_class)->finalize (object);
}


static void
c_atk_root_pane_class_init (CAtkRootPaneClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_root_pane_initialize;
  atk_class->get_n_children = c_atk_root_pane_get_n_children;
  atk_class->ref_child = c_atk_root_pane_ref_child;
	atk_class->get_name = c_atk_root_pane_get_name;
  atk_class->get_description = c_atk_root_pane_get_description;

  object_class->finalize = c_atk_root_pane_finalize;
}

static void
c_atk_root_pane_init (CAtkRootPane *self)
{
	CAtkRootPanePrivate *priv = c_atk_root_pane_get_instance_private(self);
	priv->accessibleObjects = NULL;
}



