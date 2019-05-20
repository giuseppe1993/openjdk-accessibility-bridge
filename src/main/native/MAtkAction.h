/*
 * catkaction.h
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
#ifndef DEMO_ACTION_H_
#define DEMO_ACTION_H_

#include <atk/atk.h>
#include <jni.h>
#include "MAtkObject.h"

G_BEGIN_DECLS

#define M_TYPE_ATK_ACTION            (m_atk_action_get_type ())

G_DECLARE_DERIVABLE_TYPE(MAtkAction, m_atk_action, M, ATK_ACTION, MAtkObject)

struct _MAtkActionClass
{
    MAtkObjectClass parent_class;
};

typedef struct _RealAction RealAction;

MAtkAction *m_atk_action_new (void);
void m_atk_action_save_java_reference (MAtkAction *self, JavaVM *jvm, jmethodID method, jobject obj);
int m_atk_action_add_action (MAtkAction *self, const char *name, const char *description, const char *keybinding, const char *localizedname);
gboolean m_atk_action_remove_action (MAtkAction *self, int index);
gboolean m_atk_action_set_name (MAtkAction *self, int index, const char *name);
gboolean m_atk_action_set_keybinding (MAtkAction *self, int index, const char *keybinding);
gboolean m_atk_action_set_localized_name (MAtkAction *self, int index, const char *localizedname);

G_END_DECLS
#endif
