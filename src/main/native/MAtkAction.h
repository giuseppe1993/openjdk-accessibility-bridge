/*
 * catkaction.h
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
 #ifndef DEMO_ACTION_H_
 #define DEMO_ACTION_H_

 #include <atk/atk.h>
 #include "MAtkObject.h"

 G_BEGIN_DECLS

 #define M_TYPE_ATK_ACTION            (m_atk_action_get_type ())

 G_DECLARE_DERIVABLE_TYPE(MAtkAction, m_atk_action, M, ATK_ACTION, MAtkObject)

 struct _MAtkActionClass
 {
   MAtkObjectClass parent_class;
 };

 typedef struct _RealAction RealAction;

 struct _RealAction {
    const char* description;
    const char* name;
    const char* keybinding;
    const char* localizedname;
  };

 MAtkAction *m_atk_action_new (void);
 void m_atk_action_add_action(MAtkAction *self, RealAction *action);
 void m_atk_action_remove_action(MAtkAction *self, RealAction *action);
 void m_atk_action_set_name(MAtkAction *self, RealAction *action, gchar *name);
 void m_atk_action_set_keybinding(MAtkAction *self, RealAction *action, gchar *keybinding);
 void m_atk_action_set_localized_name(MAtkAction *self, RealAction *action, gchar *localizedname);


 G_END_DECLS

 #endif
