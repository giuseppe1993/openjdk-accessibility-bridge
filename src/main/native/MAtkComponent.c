/*
 * demo_component.c
 *
 *  Created on: Apr 25, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <gmodule.h>
#include "MAtkComponent.h"

#define M_ATK_COMPONENT_GET_PRIVATE(o) (m_atk_component_get_istance_private (o))

typedef struct
{
    AtkRectangle *rectangle;
    AtkCoordType coord_type;
    AtkLayer layer;
} MAtkComponentPrivate;

static void m_atk_component_atk_component_init (AtkComponentIface *iface);

G_DEFINE_TYPE_WITH_CODE (MAtkComponent, m_atk_component, M_TYPE_ATK_OBJECT, { G_ADD_PRIVATE (MAtkComponent); G_IMPLEMENT_INTERFACE (atk_component_get_type(), m_atk_component_atk_component_init); })

static void
m_atk_component_get_extents (AtkComponent *component, gint *x, gint *y, gint *width, gint *height, AtkCoordType coord_type)
{
    MAtkComponentPrivate *priv = m_atk_component_get_instance_private(M_ATK_COMPONENT(component));
    *x = priv->rectangle->x;
    *y = priv->rectangle->y;
    *width = priv->rectangle->width;
    *height = priv->rectangle->height;
    coord_type = priv->coord_type;
}

static AtkLayer
m_atk_component_get_layer(AtkComponent *component)
{
    MAtkComponentPrivate *priv = m_atk_component_get_instance_private(M_ATK_COMPONENT(component));
    return priv->layer;
}

static void
m_atk_component_atk_component_init (AtkComponentIface *iface)
{
    iface->get_extents = m_atk_component_get_extents;
    iface->get_layer = m_atk_component_get_layer;
}

void
m_atk_component_set_layer (MAtkComponent *self, AtkLayer layer)
{
    g_return_if_fail (M_IS_ATK_COMPONENT (self));
    MAtkComponentPrivate *priv = m_atk_component_get_instance_private(self);
    priv->layer = layer;
}

void
m_atk_component_set_bound (MAtkComponent *self, gint x, gint y, gint width, gint height)
{
  MAtkComponentPrivate *priv = m_atk_component_get_instance_private(self);
  priv->rectangle->x = x;
  priv->rectangle->y = y;
  priv->rectangle->width = width;
  priv->rectangle->height = height;
}

void
m_atk_component_set_coord_type(MAtkComponent *self, AtkCoordType coord_type)
{
    g_return_if_fail (M_IS_ATK_COMPONENT (self));
    MAtkComponentPrivate *priv = m_atk_component_get_instance_private(self);
    priv->coord_type = coord_type;
}


static void
m_atk_component_finalize (GObject *object)
{
	g_return_if_fail (M_IS_ATK_COMPONENT(object));

	G_OBJECT_CLASS (m_atk_component_parent_class)->finalize (object);
}

static void
m_atk_component_class_init (MAtkComponentClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = m_atk_component_finalize;
}

MAtkComponent *
m_atk_component_new (void)
{
   MAtkComponent *component = g_object_new (M_TYPE_ATK_COMPONENT, NULL);
   atk_object_initialize (ATK_OBJECT(component), NULL);
   return component;
}


static void
m_atk_component_init (MAtkComponent *self)
{
  atk_object_set_role(ATK_OBJECT(self), ATK_ROLE_INVALID);
	atk_object_set_parent(ATK_OBJECT(self), NULL);
  m_atk_object_set_name(M_ATK_OBJECT(self),"M Atk Component");
  m_atk_object_set_description(M_ATK_OBJECT(self),"this is the description of the component of mediator");
  MAtkComponentPrivate *priv = m_atk_component_get_instance_private(self);
  priv->rectangle = g_new0 ( AtkRectangle, 1 );
  priv->layer = ATK_LAYER_INVALID;
}
