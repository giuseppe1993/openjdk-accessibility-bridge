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
	AtkRole role;
	char *name;
	char *description;
	AtkStateSet *states;
	AtkRelationSet *relations;
	AtkAttributeSet *attributes;
} MAtkObjectPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (MAtkObject, m_atk_object, ATK_TYPE_OBJECT)

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
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	return g_object_ref(priv->relations);
}

static AtkStateSet*
m_atk_object_ref_state_set(AtkObject *obj)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	return g_object_ref(priv->states);
}

static gint
m_atk_object_get_n_children (AtkObject *obj)
{
  MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
  return g_list_length (priv->accessibleObjects);
}

static AtkObject*
m_atk_object_ref_child (AtkObject *obj, gint i)
{
  GList *obj_list = NULL;
  gint num = 0;
  AtkObject *item = NULL;

  MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
  obj_list = priv->accessibleObjects;
  num = g_list_length (obj_list);
	//fprintf(stderr, "num:%u i:%u\n", &num, &i);
  g_return_val_if_fail ( (i < num) && (i >= 0) , NULL);

  item = g_list_nth_data (obj_list, i);
  if (!item)
      return NULL;

  g_object_ref (item);
  return item;
}

void
m_atk_object_set_role (MAtkObject *object, AtkRole role)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(object);
	AtkPropertyValues *signalstuff = g_new0(AtkPropertyValues, 1);
	g_value_init (&signalstuff->old_value, ATK_TYPE_ROLE);
	g_value_init (&signalstuff->new_value, ATK_TYPE_ROLE);
	g_value_set_enum (&signalstuff->old_value, priv->role);
	g_value_set_enum (&signalstuff->new_value, role);
	signalstuff->property_name = "accessible-role";
	priv->role = role;
	g_signal_emit_by_name (object, "property-change", signalstuff, NULL);
}

AtkRole
m_atk_object_get_role (AtkObject *obj)
{
	g_return_val_if_fail (M_IS_ATK_OBJECT(obj), ATK_ROLE_INVALID);
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	return priv->role;
}

void
m_atk_object_set_name (MAtkObject *object, char *name)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(object);
	AtkPropertyValues *signalstuff = g_new0(AtkPropertyValues, 1);
	g_value_init (&signalstuff->old_value, G_TYPE_STRING);
	g_value_init (&signalstuff->new_value, G_TYPE_STRING);
	g_value_set_string (&signalstuff->old_value, priv->name);
	g_value_set_string (&signalstuff->new_value, name);
	signalstuff->property_name = "accessible-name";
	priv->name = name;
	g_signal_emit_by_name (object, "property-change", signalstuff, NULL);
}

static const char*
m_atk_object_get_name(AtkObject *obj)
{
	g_return_val_if_fail (M_IS_ATK_OBJECT(obj), NULL);
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	//fprintf(stderr, "%s\n", priv->name);
	return strdup(priv->name);
}

void
m_atk_object_set_description(MAtkObject *object, char *description)
{
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private (object);
	AtkPropertyValues *signalstuff = g_new0 (AtkPropertyValues, 1);
	g_value_init (&signalstuff->old_value, G_TYPE_STRING);
	g_value_init (&signalstuff->new_value, G_TYPE_STRING);
	g_value_set_string (&signalstuff->old_value, priv->description);
	g_value_set_string (&signalstuff->new_value, description);
	signalstuff->property_name = "accessible-description";
	priv->description = description;
	g_signal_emit_by_name (object, "property-change", signalstuff, NULL);
}

static const char*
m_atk_object_get_description(AtkObject *obj)
{
	g_return_val_if_fail (M_IS_ATK_OBJECT(obj), NULL);
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(M_ATK_OBJECT(obj));
	return strdup(priv->description);
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
	atk_class->get_role = m_atk_object_get_role;
	atk_class->get_name = m_atk_object_get_name;
	atk_class->get_description = m_atk_object_get_description;
	atk_class->ref_state_set = m_atk_object_ref_state_set;
	atk_class->ref_relation_set = m_atk_object_ref_relation_set;
	atk_class->get_attributes = m_atk_object_get_attributes;

  object_class->finalize = m_atk_object_finalize;
}

MAtkObject *
m_atk_object_new (void)
{
   MAtkObject *object = g_object_new (M_TYPE_ATK_OBJECT, NULL);
   atk_object_initialize (ATK_OBJECT(object), NULL);
   return object;
}

static void
m_atk_object_init (MAtkObject *self)
{
	m_atk_object_set_role(self, ATK_ROLE_INVALID);
	atk_object_set_parent(ATK_OBJECT(self), NULL);
  	m_atk_object_set_name(self,"M Atk Object");
  	m_atk_object_set_description(self,"this is the description of the object component of mediator");
	MAtkObjectPrivate *priv = m_atk_object_get_instance_private(self);
	priv->accessibleObjects = NULL;
	priv->states = atk_state_set_new();
	priv->relations = atk_relation_set_new();
	priv->attributes = NULL;
}
