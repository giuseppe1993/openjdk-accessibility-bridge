/*
 * AtkWindow.c
 *
 *  Created on: Apr 4, 2019
 *      Author: giuseppe
 */

#include <gmodule.h>
#include "AtkWindow.h"

#define C_ATK_WINDOW_GET_PRIVATE(o) (c_atk_window_get_istance_private (o))

typedef struct
{
	GList *accessibleObjects;

} CAtkWindowPrivate;


G_DEFINE_TYPE_WITH_PRIVATE (CAtkWindow, c_atk_window, ATK_TYPE_OBJECT)

void c_atk_window_add_child(CAtkWindow *window, AtkObject *obj)
{
	CAtkWindowPrivate *priv = c_atk_window_get_instance_private(window);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (window));

	priv->accessibleObjects = g_list_append (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);
	g_signal_emit_by_name (window, "children-changed::add", index, obj, NULL);

}

void c_atk_window_remove_child(CAtkWindow *window, AtkObject *obj)
{
	CAtkWindowPrivate *priv = c_atk_window_get_instance_private(window);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (window));

	priv->accessibleObjects = g_list_remove (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);

	g_signal_emit_by_name (window, "children-changed::remove", index, obj, NULL);
}

CAtkWindow *
c_atk_window_new (void)
{
   CAtkWindow *window = g_object_new (C_TYPE_ATK_WINDOW, NULL);

   atk_object_initialize(ATK_OBJECT(window), NULL);

   return window;
}

static void
c_atk_window_initialize (AtkObject *self, gpointer null)
{
	atk_object_set_role(self,ATK_ROLE_WINDOW);
	atk_object_set_parent(self,NULL);
}

static gint
c_atk_window_get_n_children (AtkObject *obj)
{
  CAtkWindowPrivate *priv = c_atk_window_get_instance_private(C_ATK_WINDOW(obj));
  return g_list_length (priv->accessibleObjects);
}

static AtkObject*
c_atk_window_ref_child (AtkObject *obj, gint i)
{
  GList *obj_list = NULL;
  gint num = 0;
  AtkObject *item = NULL;

  CAtkWindowPrivate *priv = c_atk_window_get_instance_private(C_ATK_WINDOW(obj));

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
c_atk_window_finalize (GObject *object)
{
	CAtkWindow *window = C_ATK_WINDOW(object);

	g_return_if_fail (C_IS_ATK_WINDOW(object));

	CAtkWindowPrivate *priv = c_atk_window_get_instance_private(window);

	if (priv->accessibleObjects)
	{
	  g_list_free (priv->accessibleObjects);
	  priv->accessibleObjects = NULL;
	}

	G_OBJECT_CLASS (c_atk_window_parent_class)->finalize (object);
}


static void
c_atk_window_class_init (CAtkWindowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_window_initialize;
  atk_class->get_n_children = c_atk_window_get_n_children;
  atk_class->ref_child = c_atk_window_ref_child;

  object_class->finalize = c_atk_window_finalize;
}

static void
c_atk_window_init (CAtkWindow *self)
{
	CAtkWindowPrivate *priv = c_atk_window_get_instance_private(self);
	priv->accessibleObjects = NULL;
}


