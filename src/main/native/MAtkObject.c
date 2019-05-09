/*
 * demo_object.c
 *
 *  Created on: Apr 14, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <gmodule.h>
#include "MAtkObject.h"

#define M_ATK_OBJECT_GET_PRIVATE(o) (m_atk_object_get_istance_private (o))

typedef struct
{
	GList *accessibleObjects;
	AtkStateSet *states;
	AtkRelationSet *relations;
	AtkAttributeSet *attributes;
} MAtkObjectPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (MAtkObject, m_atk_object, ATK_TYPE_OBJECT)

MAtkObject *
m_atk_object_new (void)
{
   MAtkObject *object = g_object_new (ATK_TYPE_OBJECT, NULL);
   atk_object_initialize (ATK_OBJECT(object), NULL);
   return object;
}

void
m_atk_object_add_child(MAtkObject *object, AtkObject *obj)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(object);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (object));
	priv->accessibleObjects = g_list_append (priv->accessibleObjects, obj);
	index = g_list_index (priv->accessibleObjects, obj);
	g_signal_emit_by_name (object, "children-changed::add", index, obj, NULL);
}

void
m_atk_object_remove_child(MAtkObject *object, AtkObject *obj)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(object);
	gint index = -1;

	index = g_list_index (priv->accessibleObjects, obj);
	priv->accessibleObjects = g_list_remove (priv->accessibleObjects, obj);
	if (index != -1)
		g_signal_emit_by_name (object, "children-changed::remove", index, obj, NULL);
}

void
m_atk_object_add_state(MAtkObject *object, AtkStateType state)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private (object);
	atk_state_set_add_state(priv->states, state);
	atk_object_notify_state_change( ATK_OBJECT(object), state, TRUE);
}

void m_atk_object_remove_state(MAtkObject *object, AtkStateType state)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private (object);
	atk_state_set_remove_state(priv->states, state);

	atk_object_notify_state_change( ATK_OBJECT(object), state, FALSE);
}

static AtkRelationSet*
m_atk_object_ref_relation_set(AtkObject *obj)
{
	g_return_val_if_fail (M_IS_ATK_OBJECT(obj), NULL);
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	return g_object_ref(priv->relations);
}

static AtkStateSet*
m_atk_object_ref_state_set(AtkObject *obj)
{
	g_return_val_if_fail (M_IS_ATK_OBJECT(obj), NULL);
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	return g_object_ref(priv->states);
}

static gint
m_atk_object_get_n_children (AtkObject *obj)
{
	g_return_val_if_fail (M_IS_ATK_OBJECT(obj), 0);
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	return g_list_length (priv->accessibleObjects);
}

static AtkObject*
m_atk_object_ref_child (AtkObject *obj, gint i)
{
	g_return_val_if_fail (M_IS_ATK_OBJECT(obj), NULL);

	GList *obj_list = NULL;
	gint num = 0;
	AtkObject *item = NULL;

	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	obj_list = priv->accessibleObjects;
	num = g_list_length (obj_list);

	g_return_val_if_fail ((i < num)&&(i >= 0), NULL);
	item = g_list_nth_data (obj_list, i);
	if (!item)
		return NULL;
	g_object_ref (item);
	return item;
}

static void*
copy_attribute(const void *origin, gpointer null)
{
	AtkAttribute *attribute = (AtkAttribute *) origin;
	AtkAttribute *copy = g_new0 ( AtkAttribute, 1 );

	copy->name = g_strdup (attribute->name);
	copy->value = g_strdup (attribute -> value);

	return copy;
}

static AtkAttributeSet*
m_atk_object_get_attributes(AtkObject *obj)
{
	AtkAttributeSet *atr_list = NULL;
	int num = 0;

	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	num = g_slist_length (priv->attributes);

	if (!num)
	  return NULL;

	atr_list = (AtkAttributeSet *) g_list_copy_deep( (GList *) priv->attributes, copy_attribute, NULL);

	return atr_list;
}

void m_atk_object_add_attribute (MAtkObject *object, gchar *name, gchar *value)
{
	AtkAttribute *attribute = g_new0(AtkAttribute,1);
	attribute->name = name;
	attribute->value = value;
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(object));
	if(!g_slist_find(priv->attributes, attribute))
		priv->attributes = g_slist_append(priv->attributes, attribute);

}

void m_atk_object_remove_attribute (MAtkObject *object, gchar *name, gchar *value)
{
	AtkAttribute *attribute = g_new0(AtkAttribute,1);
	attribute->name = name;
	attribute->value = value;
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(object));
	if(!g_slist_find(priv->attributes, attribute))
		priv->attributes = g_slist_remove(priv->attributes, attribute);

}

AtkRelationSet* m_atk_object_get_relation_set(MAtkObject *object)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(object);
	return priv->relations;
}

void m_atk_object_set_relation_set(MAtkObject *object, AtkRelationSet* relations)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(object);
	g_free(priv->relations);
	priv->relations = relations;
}

static void
m_atk_object_finalize (GObject *obj)
{
	MAtkObject *object = M_ATK_OBJECT(obj);

	g_return_if_fail (M_IS_ATK_OBJECT(obj));

	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(object);

	if (priv->accessibleObjects)
	{
	  g_list_free (priv->accessibleObjects);
	  priv->accessibleObjects = NULL;
	}

	atk_attribute_set_free(priv->attributes);
	g_free(priv->relations);

	g_clear_object(&priv->states);

	G_OBJECT_CLASS (m_atk_object_parent_class)->finalize (obj);
}


static void
m_atk_object_class_init (MAtkObjectClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  	atk_class->get_n_children = m_atk_object_get_n_children;
  	atk_class->ref_child = m_atk_object_ref_child;
  	atk_class->ref_state_set = m_atk_object_ref_state_set;
	atk_class->ref_relation_set = m_atk_object_ref_relation_set;
  	atk_class->get_attributes = m_atk_object_get_attributes;

  	object_class->finalize = m_atk_object_finalize;
}

static void
m_atk_object_init (MAtkObject *self)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(self);
	priv->accessibleObjects = NULL;
	priv->states = atk_state_set_new();
	priv->relations = atk_relation_set_new();
	priv->attributes = NULL;
}
