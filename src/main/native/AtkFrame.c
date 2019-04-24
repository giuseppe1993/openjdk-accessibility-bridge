/*
 * demo_frame.c
 *
 *  Created on: Apr 10, 2019
 *      Author: giuseppe
 */
#include <stdio.h>

#include <gmodule.h>
#include "AtkFrame.h"

#define C_ATK_FRAME_GET_PRIVATE(o) (c_atk_frame_get_istance_private (o))

typedef struct
{
	GList *accessibleObjects;
	AtkStateSet *states;
	AtkAttributeSet *attributes;

} CAtkFramePrivate;


G_DEFINE_TYPE_WITH_PRIVATE (CAtkFrame, c_atk_frame, ATK_TYPE_OBJECT)

void
c_atk_frame_add_child(CAtkFrame *frame, AtkObject *obj)
{
	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(frame);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (frame));

	priv->accessibleObjects = g_list_append (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);
	g_signal_emit_by_name (frame, "children-changed::add", index, obj, NULL);
}

void
c_atk_frame_remove_child(CAtkFrame *frame, AtkObject *obj)
{
	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(frame);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (frame));

	priv->accessibleObjects = g_list_remove (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);

	g_signal_emit_by_name (frame, "children-changed::remove", index, obj, NULL);
}

void
c_atk_frame_add_state(CAtkFrame *frame, AtkStateType state)
{
	CAtkFramePrivate *priv = c_atk_frame_get_instance_private (frame);

	atk_state_set_add_state (priv->states, state);

	atk_object_notify_state_change (ATK_OBJECT(frame), state, TRUE);
}

void c_atk_frame_remove_state(CAtkFrame *frame, AtkStateType state){

	CAtkFramePrivate *priv = c_atk_frame_get_instance_private (frame);

	atk_state_set_remove_state(priv->states, state);

	atk_object_notify_state_change( ATK_OBJECT(frame), state, FALSE);
}


CAtkFrame *
c_atk_frame_new (void)
{
   CAtkFrame *frame = g_object_new (C_TYPE_ATK_FRAME, NULL);

   atk_object_initialize(ATK_OBJECT(frame), NULL);

   return frame;
}

static const char*
c_atk_frame_get_name (AtkObject *obj)
{
   return "Atk Frame";
}

static const char*
c_atk_frame_get_description()
{
	return "this is the description of the frame component";
}


static void
c_atk_frame_initialize (AtkObject *self, gpointer null)
{
	atk_object_set_role(self,ATK_ROLE_FRAME);
	atk_object_set_parent(self,NULL);
}

static AtkStateSet*
c_atk_frame_ref_state_set(AtkObject *obj)
{
	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(C_ATK_FRAME(obj));
	return g_object_ref(priv->states);
}

static gint
c_atk_frame_get_n_children (AtkObject *obj)
{
  CAtkFramePrivate *priv = c_atk_frame_get_instance_private(C_ATK_FRAME(obj));
  return g_list_length (priv->accessibleObjects);
}

static AtkObject*
c_atk_frame_ref_child (AtkObject *obj, gint i)
{
  GList *obj_list = NULL;
  gint num = 0;
  AtkObject *item = NULL;

  CAtkFramePrivate *priv = c_atk_frame_get_instance_private(C_ATK_FRAME(obj));

  obj_list = priv->accessibleObjects;

  num = g_list_length (obj_list);

  g_return_val_if_fail ((i < num)&&(i >= 0), NULL);

  item = g_list_nth_data (obj_list, i);
  if (!item)
      return NULL;

  g_object_ref (item);

  return item;
}

static AtkAttributeSet*
c_atk_frame_get_attributes(AtkObject *obj)
{
	AtkAttributeSet *atr_list = NULL;
	gint num = 0;

	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(C_ATK_FRAME(obj));

	atr_list = priv->attributes;

	num = g_slist_length (atr_list);

	if (!num)
	  return NULL;

	g_object_ref (atr_list);

	return atr_list;
}

void c_atk_frame_add_attribute (CAtkFrame *frame, AtkAttribute *attribute)
{
	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(C_ATK_FRAME(frame));
	if(g_slist_find(priv->attributes, attribute))
	{
		priv->attributes = g_slist_append(priv->attributes, attribute);
	}
}

void c_atk_frame_remove_attribute (CAtkFrame *frame, AtkAttribute *attribute)
{
	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(C_ATK_FRAME(frame));
	if(!g_slist_find(priv->attributes, attribute))
	{
		priv->attributes = g_slist_remove(priv->attributes, attribute);
	}
}

static void
c_atk_frame_finalize (GObject *object)
{
	CAtkFrame *frame = C_ATK_FRAME(object);

	g_return_if_fail (C_IS_ATK_FRAME(object));

	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(frame);

	if (priv->accessibleObjects)
	{
	  g_list_free (priv->accessibleObjects);
	  priv->accessibleObjects = NULL;
	}

	atk_attribute_set_free(priv->attributes);

	g_clear_object(&priv->states);

	G_OBJECT_CLASS (c_atk_frame_parent_class)->finalize (object);
}


static void
c_atk_frame_class_init (CAtkFrameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_frame_initialize;
  atk_class->get_n_children = c_atk_frame_get_n_children;
  atk_class->ref_child = c_atk_frame_ref_child;
  atk_class->get_name = c_atk_frame_get_name;
  atk_class->get_description = c_atk_frame_get_description;
  atk_class->ref_state_set = c_atk_frame_ref_state_set;
  atk_class->get_attributes = c_atk_frame_get_attributes;

  object_class->finalize = c_atk_frame_finalize;
}

static void
c_atk_frame_init (CAtkFrame *self)
{
	CAtkFramePrivate *priv = c_atk_frame_get_instance_private(self);
	priv->accessibleObjects = NULL;
	priv->states = atk_state_set_new();
	priv->attributes = NULL;
}

