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
    JavaVM *jvm;
    jmethodID action_method;
    jobject java_action;
} MAtkActionPrivate;

struct _RealAction {
    const char* description;
    const char* name;
    const char* keybinding;
    const char* localizedname;
 };

static void m_atk_action_atk_action_init (AtkActionIface *iface);

G_DEFINE_TYPE_WITH_CODE (MAtkAction, m_atk_action, M_TYPE_ATK_OBJECT, { G_ADD_PRIVATE (MAtkAction); G_IMPLEMENT_INTERFACE (atk_action_get_type(), m_atk_action_atk_action_init); })

static gboolean
m_atk_action_do_action(AtkAction *action, int index)
{
    g_return_val_if_fail (M_IS_ATK_ACTION(action), FALSE);
    MAtkActionPrivate *priv = m_atk_action_get_instance_private (M_ATK_ACTION(action));
    JNIEnv *env;
    (*priv->jvm)->GetEnv (priv->jvm, (void **)&env, JNI_VERSION_1_6);
    (*priv->jvm)->AttachCurrentThread (priv->jvm, (void **)&env, NULL);
    //add other check on priv->env and priv->java_action
    jboolean java_result = (*env)->CallBooleanMethod (env, priv->java_action, priv->action_method, index);
    (*priv->jvm)->DetachCurrentThread (priv->jvm);
    return java_result;
}

static gint
m_atk_action_get_n_actions(AtkAction *action)
{
    g_return_val_if_fail (M_IS_ATK_ACTION(action), -1);
    MAtkActionPrivate *priv = m_atk_action_get_instance_private (M_ATK_ACTION(action));
    return g_list_length(priv->accessibleActions);
}

static const gchar*
m_atk_action_get_description(AtkAction *action, gint i)
{
    g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
    MAtkActionPrivate *priv = m_atk_action_get_instance_private (M_ATK_ACTION(action));
    RealAction *data = g_list_nth_data (priv->accessibleActions, i);
    g_return_val_if_fail (data, NULL);
    return strdup(data->description);
}

static const gchar*
m_atk_action_get_name(AtkAction *action, gint i)
{
    g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
    MAtkActionPrivate *priv = m_atk_action_get_instance_private (M_ATK_ACTION(action));
    RealAction *data = g_list_nth_data (priv->accessibleActions, i);
    g_return_val_if_fail (data, NULL);
    return data->name;
}

static const gchar*
m_atk_action_get_keybinding(AtkAction *action, gint i)
{
    g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
    MAtkActionPrivate *priv = m_atk_action_get_instance_private (M_ATK_ACTION(action));
    RealAction *data = g_list_nth_data (priv->accessibleActions, i);
    g_return_val_if_fail (data, NULL);
    return data->keybinding;
}

static const gchar*
m_atk_action_get_localized_name(AtkAction *action, gint i)
{
    g_return_val_if_fail (M_IS_ATK_ACTION(action), NULL);
    MAtkActionPrivate *priv = m_atk_action_get_instance_private (M_ATK_ACTION(action));
    RealAction *data = g_list_nth_data (priv->accessibleActions, i);
    g_return_val_if_fail (data, NULL);
    return data->localizedname;
}

 static void
 m_atk_action_atk_action_init (AtkActionIface *iface)
 {
     iface->do_action = m_atk_action_do_action;
     iface->get_n_actions = m_atk_action_get_n_actions;
     iface->get_description = m_atk_action_get_description;
     iface->get_name = m_atk_action_get_name;
     iface->get_keybinding = m_atk_action_get_keybinding;
     iface->get_localized_name = m_atk_action_get_localized_name;
 }

 MAtkAction *
 m_atk_action_new (void)
 {
     MAtkAction *action = g_object_new (M_TYPE_ATK_ACTION, NULL);
     atk_object_initialize (ATK_OBJECT(action), NULL);
     return action;
 }

 void
 m_atk_action_save_java_reference(MAtkAction *self, JavaVM *jvm, jmethodID method, jobject obj)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     priv->jvm = jvm;
     priv->action_method = method;
     priv->java_action = obj;
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
     priv->jvm = NULL;
     priv->java_action = NULL;
     priv->action_method = NULL;
     G_OBJECT_CLASS (m_atk_action_parent_class)->finalize (object);
 }

 static void
 m_atk_action_class_init (MAtkActionClass *klass)
 {
     GObjectClass *object_class = G_OBJECT_CLASS (klass);
     object_class->finalize = m_atk_action_finalize;
 }

 int m_atk_action_add_action (MAtkAction *self, const char *name, const char *description, const char *keybinding, const char *localizedname)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     RealAction *action = g_new0 (RealAction, 1);
     action->name = name;
     action->description = description;
     action->keybinding = keybinding;
     action->localizedname = localizedname;
     priv->accessibleActions = g_list_append (priv->accessibleActions, action);
     return (int) g_list_index (priv->accessibleActions, action);
 }

 gboolean m_atk_action_remove_action(MAtkAction *self, int index)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     g_return_val_if_fail ( (index<0), FALSE);
     GList *data = g_list_nth (priv->accessibleActions, (guint) index);
     g_return_val_if_fail (data, FALSE);
     RealAction *action = (RealAction*) data->data;
     priv->accessibleActions = g_list_remove (priv->accessibleActions, action);
     return TRUE;
 }

 gboolean m_atk_action_set_name(MAtkAction *self, int index, const char *name)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     g_return_val_if_fail ( (index<0), FALSE);
     GList *data = g_list_nth (priv->accessibleActions, (guint) index);
     g_return_val_if_fail (data, FALSE);
     RealAction *realaction = (RealAction*) data->data;
     g_free ( (void*)realaction->name );
     realaction->name = name;
     return TRUE;
 }
 gboolean m_atk_action_set_keybinding(MAtkAction *self, int index, const char *keybinding)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     g_return_val_if_fail ( (index<0), FALSE);
     GList *data = g_list_nth (priv->accessibleActions, (guint) index);
     g_return_val_if_fail (data, FALSE);
     RealAction *realaction = (RealAction*) data->data;
     g_free ( (void*)realaction->keybinding );
     realaction->keybinding = keybinding;
     return TRUE;
 }

 gboolean m_atk_action_set_localized_name(MAtkAction *self, int index, const char *localizedname)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     g_return_val_if_fail ( (index<0), FALSE);
     GList *data = g_list_nth (priv->accessibleActions, (guint) index);
     g_return_val_if_fail (data, FALSE);
     RealAction *realaction = (RealAction*) data->data;
     g_free ( (void*)realaction->localizedname );
     realaction->localizedname = localizedname;
     return TRUE;
 }

 static void
 m_atk_action_init (MAtkAction *self)
 {
     MAtkActionPrivate *priv = m_atk_action_get_instance_private(self);
     priv->accessibleActions = NULL;
     priv->jvm = NULL;
     priv->java_action = NULL;
     priv->action_method = NULL;
 }
