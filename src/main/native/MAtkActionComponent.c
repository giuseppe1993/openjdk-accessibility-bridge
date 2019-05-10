/*
 * matkactioncomponent.c
 *
 *  Mreated on: May 3, 2019
 *      Author: giuseppe
 */
 #include <gmodule.h>
 #include "MAtkActionComponent.h"

 #define M_ATK_ACTION_COMPONENT_GET_PRIVATE(o) (m_atk_action_component_get_istance_private (o))

 typedef struct
 {
     AtkRectangle *rectangle;
     AtkCoordType coord_type;
     AtkLayer layer;
 } MAtkActionComponentPrivate;

 static void m_atk_action_component_atk_action_component_init (AtkComponentIface *iface);

 G_DEFINE_TYPE_WITH_CODE (MAtkActionComponent, m_atk_action_component, M_TYPE_ATK_ACTION, { G_ADD_PRIVATE (MAtkActionComponent); G_IMPLEMENT_INTERFACE (atk_component_get_type(), m_atk_action_component_atk_action_component_init); })

 static void
 m_atk_action_component_get_extents (AtkComponent *component, gint *x, gint *y, gint *width, gint *height, AtkCoordType coord_type)
 {
     MAtkActionComponentPrivate *priv = m_atk_action_component_get_instance_private(M_ATK_ACTION_COMPONENT(component));
     *x = priv->rectangle->x;
     *y = priv->rectangle->y;
     *width = priv->rectangle->width;
     *height = priv->rectangle->height;
     coord_type = priv->coord_type;
 }

 static AtkLayer
 m_atk_action_component_get_layer(AtkComponent *component)
 {
     MAtkActionComponentPrivate *priv = m_atk_action_component_get_instance_private(M_ATK_ACTION_COMPONENT(component));
     return priv->layer;
 }

 static void
 m_atk_action_component_atk_action_component_init (AtkComponentIface *iface)
 {
     iface->get_extents = m_atk_action_component_get_extents;
     iface->get_layer = m_atk_action_component_get_layer;
 }

 MAtkActionComponent *
 m_atk_action_component_new (void)
 {
    MAtkActionComponent *actioncomponent = g_object_new (M_TYPE_ATK_ACTION_COMPONENT, NULL);
    atk_object_initialize (ATK_OBJECT(actioncomponent), NULL);
    return actioncomponent;
 }

 void
 m_atk_action_component_set_layer (MAtkActionComponent *self, AtkLayer layer)
 {
     MAtkActionComponentPrivate *priv = m_atk_action_component_get_instance_private(self);
     priv->layer = layer;
 }

 void
 m_atk_action_component_set_bound (MAtkActionComponent *self, gint x, gint y, gint width, gint height)
 {
     MAtkActionComponentPrivate *priv = m_atk_action_component_get_instance_private(self);
     priv->rectangle->x = x;
     priv->rectangle->y = y;
     priv->rectangle->width = width;
     priv->rectangle->height = height;
 }

 void
 m_atk_action_component_set_coord_type(MAtkActionComponent *self, AtkCoordType coord_type)
 {
     MAtkActionComponentPrivate *priv = m_atk_action_component_get_instance_private(self);
     priv->coord_type = coord_type;
 }


 static void
 m_atk_action_component_finalize (GObject *object)
 {
 	g_return_if_fail (M_IS_ATK_ACTION_COMPONENT(object));

 	G_OBJECT_CLASS (m_atk_action_component_parent_class)->finalize (object);
 }

 static void
 m_atk_action_component_class_init (MAtkActionComponentClass *klass)
 {
   GObjectClass *object_class = G_OBJECT_CLASS (klass);

   object_class->finalize = m_atk_action_component_finalize;
 }

 static void
 m_atk_action_component_init (MAtkActionComponent *self)
 {
     atk_object_set_name(ATK_OBJECT(self),"M Atk Action Component");
     atk_object_set_description(ATK_OBJECT(self),"this is the description of the Action Component of mediator");
     MAtkActionComponentPrivate *priv = m_atk_action_component_get_instance_private(self);
     priv->rectangle = g_new0 ( AtkRectangle, 1 );
     priv->layer = ATK_LAYER_INVALID;
     priv->coord_type = ATK_XY_WINDOW;

 }
