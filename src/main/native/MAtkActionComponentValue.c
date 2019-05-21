/*
 * MAtkActionComponentValue.c
 *
 *  Mreated on: May 21, 2019
 *      Author: giuseppe
 */
#include <gmodule.h>
#include "MAtkActionComponentValue.h"

#define M_ATK_ACTION_COMPONENT_VALUE_GET_PRIVATE(o) (m_atk_action_component_value_get_istance_private (o))

typedef struct
{
    gdouble current;
    gdouble max;
    gdouble min;
} MAtkActionComponentValuePrivate;

static void m_atk_action_component_value_atk_action_component_value_init (AtkValueIface *iface);

G_DEFINE_TYPE_WITH_CODE (MAtkActionComponentValue, m_atk_action_component_value, M_TYPE_ATK_ACTION_COMPONENT, { G_ADD_PRIVATE (MAtkActionComponentValue); G_IMPLEMENT_INTERFACE (atk_value_get_type(), m_atk_action_component_value_atk_action_component_value_init); })

static void
m_atk_action_component_value_get_value_and_text (AtkValue *obj, gdouble *value, gchar  **text)
{
    g_return_if_fail (M_IS_ATK_ACTION_COMPONENT_VALUE(obj));
    MAtkActionComponentValuePrivate *priv = m_atk_action_component_value_get_instance_private(M_ATK_ACTION_COMPONENT_VALUE(obj));
    *value = priv->current;
}

static AtkRange*
m_atk_action_component_value_get_range (AtkValue *obj)
{
    g_return_val_if_fail (M_IS_ATK_ACTION_COMPONENT_VALUE(obj), NULL);
    MAtkActionComponentValuePrivate *priv = m_atk_action_component_value_get_instance_private(M_ATK_ACTION_COMPONENT_VALUE(obj));
    return atk_range_new (priv->min, priv->max, NULL);
}
/*
static gdouble
m_atk_action_component_value_get_increment (AtkValue *obj)
{
    //i don't know
}

static GSList*
m_atk_action_component_value_get_sub_ranges (AtkValue *obj)
{

}*/

static void
m_atk_action_component_value_set_value (AtkValue *obj, const gdouble new_value)
{
    g_return_if_fail (M_IS_ATK_ACTION_COMPONENT_VALUE(obj));
    MAtkActionComponentValuePrivate *priv = m_atk_action_component_value_get_instance_private(M_ATK_ACTION_COMPONENT_VALUE(obj));
    g_return_if_fail ( (priv->min <= new_value) && (new_value <= priv->max) );
    //change the value in the Java object
    priv->current = new_value;
    g_signal_emit_by_name (obj, "value-changed", new_value, NULL, NULL);
}

static void
m_atk_action_component_value_atk_action_component_value_init (AtkValueIface *iface)
{
    iface->get_value_and_text = m_atk_action_component_value_get_value_and_text;
    iface->get_range = m_atk_action_component_value_get_range;
    //iface->get_increment = m_atk_action_component_value_get_increment;
    //iface->get_sub_ranges = m_atk_action_component_value_get_sub_ranges;
    iface->set_value = m_atk_action_component_value_set_value;
}

MAtkActionComponentValue *
m_atk_action_component_value_new (void)
{
    MAtkActionComponentValue *value = g_object_new (M_TYPE_ATK_ACTION_COMPONENT_VALUE, NULL);
    atk_object_initialize (ATK_OBJECT(value), NULL);
    return value;
}

void
m_atk_action_component_value_set_current (MAtkActionComponentValue *self, const gdouble current)
{
    MAtkActionComponentValuePrivate *priv = m_atk_action_component_value_get_instance_private(self);
    g_return_if_fail ( (priv->min <= current) && (current <= priv->max) );
    priv->current = current;
}

void
m_atk_action_component_value_set_max (MAtkActionComponentValue *self, const gdouble max)
{
    MAtkActionComponentValuePrivate *priv = m_atk_action_component_value_get_instance_private(self);
    g_return_if_fail (max < priv->min);
    priv->max = max;
}

void
m_atk_action_component_value_set_min (MAtkActionComponentValue *self, const gdouble min)
{
    MAtkActionComponentValuePrivate *priv = m_atk_action_component_value_get_instance_private(self);
    g_return_if_fail(min < priv->max);
    priv->min = min;
}

static void
m_atk_action_component_value_finalize (GObject *object)
{
    g_return_if_fail (M_IS_ATK_ACTION_COMPONENT_VALUE(object));
 	G_OBJECT_CLASS (m_atk_action_component_value_parent_class)->finalize (object);
}

static void
m_atk_action_component_value_class_init (MAtkActionComponentValueClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    object_class->finalize = m_atk_action_component_value_finalize;
}

static void
m_atk_action_component_value_init (MAtkActionComponentValue *self)
{
    atk_object_set_name(ATK_OBJECT(self),"M Atk Action Component Value");
    atk_object_set_description(ATK_OBJECT(self),"this is the description of the Action Component Value of mediator");
    MAtkActionComponentValuePrivate *priv = m_atk_action_component_value_get_instance_private(self);
    priv->current = 0;
    priv->min = G_MAXDOUBLE;
    priv->max = G_MINDOUBLE;
}
