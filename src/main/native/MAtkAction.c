/*
 * MAtkAction.c
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
 #include <gmodule.h>
 #include "MAtkAction.h"

 #define M_ATK_ACTION_GET_PRIVATE(o) (m_atk_action_get_istance_private (o))

 typedef struct
 {
     GList *accessibleActions;
 } MAtkActionPrivate;

 static void m_atk_action_atk_action_init (AtkActionIface *iface);

 G_DEFINE_TYPE_WITH_CODE (MAtkAction, m_atk_action, M_TYPE_ATK_OBJECT, { G_ADD_PRIVATE (MAtkAction); G_IMPLEMENT_INTERFACE (atk_action_get_type(), m_atk_action_atk_action_init); })

static gint
m_atk_action_get_n_actions(AtkAction *action)
{
  g_return_val_if_fail (M_IS_ATK_ACTION(action), -1);
  MAtkActionPrivate *priv = m_atk_action_get_instance_private(M_ATK_ACTION(action));
  return g_list_length(priv->accessibleActions);
}

static const gchar*
m_atk_action_get_description(AtkAction *action, gint i)
{
  g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
  MAtkActionPrivate *priv = m_atk_action_get_instance_private(M_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return strdup(data->description);
}

static const gchar*
m_atk_action_get_name(AtkAction *action, gint i)
{
  g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
  MAtkActionPrivate *priv = m_atk_action_get_instance_private(M_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return data->name;
}

static const gchar*
m_atk_action_get_keybinding(AtkAction *action, gint i)
{
  g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
  MAtkActionPrivate *priv = m_atk_action_get_instance_private(M_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return data->keybinding;
}

static const gchar*
m_atk_action_get_localized_name(AtkAction *action, gint i)
{
  g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
  MAtkActionPrivate *priv = m_atk_action_get_instance_private(M_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return data->localizedname;
}

 static void
 m_atk_action_atk_action_init (AtkActionIface *iface)
 {
     iface->get_n_actions = m_atk_action_get_n_actions;
     iface->get_description = m_atk_action_get_description;
     iface->get_name = m_atk_action_get_name;
     iface->get_keybinding = m_atk_action_get_keybinding;
     iface->get_localized_name = m_atk_action_get_localized_name;
 }

 static void
 m_atk_action_finalize (GObject *object)
 {
 	g_return_if_fail (M_IS_ATK_ACTION(object));
  MAtkActionPrivate *priv = m_atk_action_get_instance_private(M_ATK_ACTION(object));
  if (priv->accessibleActions)
	{
	  g_list_free (priv->accessibleActions);
	  priv->accessibleActions = NULL;
	}

 	G_OBJECT_CLASS (m_atk_action_parent_class)->finalize (object);
 }

 static void
 m_atk_action_class_init (MAtkActionClass *klass)
 {
   GObjectClass *object_class = G_OBJECT_CLASS (klass);
   object_class->finalize = m_atk_action_finalize;
 }

 void m_atk_action_add_action (MAtkAction *self, RealAction *action)
 {
   MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
   priv->accessibleActions = g_list_append (priv->accessibleActions, action);
 }

 void m_atk_action_remove_action (MAtkAction *self, RealAction *action)
 {
   MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
   priv->accessibleActions = g_list_remove (priv->accessibleActions, action);
 }

 void m_atk_action_set_name (MAtkAction *self, RealAction *action, gchar *name)
 {
   MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
   GList *data = g_list_find(priv->accessibleActions, action);
   RealAction *realaction = (RealAction*) data->data;
   g_return_if_fail (realaction);
   g_free((void*)realaction->name);
   realaction->name = name;
 }

 void m_atk_action_set_description (MAtkAction *self, RealAction *action, gchar *description)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     GList *data = g_list_find(priv->accessibleActions, action);
     RealAction *realaction = (RealAction*) data->data;
     g_return_if_fail (realaction);
     g_free((void*)realaction->description);
     realaction->description = description;
 }

 void m_atk_action_set_keybinding (MAtkAction *self, RealAction *action, gchar *keybinding)
 {
   MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
   GList *data = g_list_find(priv->accessibleActions, action);
   RealAction *realaction = (RealAction*) data->data;
   g_return_if_fail (realaction);
   g_free((void*)realaction->keybinding);
   realaction->keybinding = keybinding;
 }

 void m_atk_action_set_localized_name(MAtkAction *self, RealAction *action, gchar *localizedname)
 {
   MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
   GList *data = g_list_find(priv->accessibleActions, action);
   RealAction *realaction = (RealAction*) data->data;
   g_return_if_fail (realaction);
   g_free((void*)realaction->localizedname);
   realaction->localizedname = localizedname;
 }

 MAtkAction *
 m_atk_action_new (void)
 {
    MAtkAction *action = g_object_new (M_TYPE_ATK_ACTION, NULL);
    atk_object_initialize (ATK_OBJECT(action), NULL);
    return action;
 }

 static void
 m_atk_action_init (MAtkAction *self)
 {
   atk_object_set_role(ATK_OBJECT(self), ATK_ROLE_INVALID);
   atk_object_set_parent(ATK_OBJECT(self), NULL);
   m_atk_object_set_name(M_ATK_OBJECT(self),"M Atk Action");
   m_atk_object_set_description(M_ATK_OBJECT(self),"this is the description of the Action component of mediator");
   MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
   priv->accessibleActions = NULL;
 }
