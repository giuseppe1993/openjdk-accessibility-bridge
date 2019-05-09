/*
 * demo_object.h
 *
 *  Created on: Apr 14, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_OBJECT_H_
#define DEMO_OBJECT_H_

#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define M_TYPE_ATK_OBJECT            (m_atk_object_get_type ())

G_DECLARE_DERIVABLE_TYPE(MAtkObject, m_atk_object, M, ATK_OBJECT, AtkObject)

struct _MAtkObjectClass
{
  AtkObjectClass parent_class;
};

void m_atk_object_add_child (MAtkObject *object, AtkObject *obj);
void m_atk_object_remove_child (MAtkObject *object, AtkObject *obj);
void m_atk_object_add_state (MAtkObject *object, AtkStateType state);
void m_atk_object_remove_state (MAtkObject *object, AtkStateType state);
void m_atk_object_add_attribute (MAtkObject *object, gchar *name, gchar *value);
void m_atk_object_remove_attribute (MAtkObject *object,  gchar *name, gchar *value);
AtkRelationSet* m_atk_object_get_relation_set(MAtkObject *object);
void m_atk_object_set_relation_set(MAtkObject *object, AtkRelationSet* relations);

G_END_DECLS

#endif /* DEMO_OBJECT_H_ */
