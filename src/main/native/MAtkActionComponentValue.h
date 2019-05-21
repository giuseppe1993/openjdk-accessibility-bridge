/*
 * MAtkActionComponentValue.h
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
#ifndef MEDIATOR_ACTION_COMPONENT_VALUE_H_
#define MEDIATOR_ACTION_COMPONENT_VALUE_H_

#include <atk/atk.h>
#include "MAtkActionComponent.h"

G_BEGIN_DECLS

#define M_TYPE_ATK_ACTION_COMPONENT_VALUE            (m_atk_action_component_value_get_type ())

G_DECLARE_DERIVABLE_TYPE(MAtkActionComponentValue, m_atk_action_component_value, M, ATK_ACTION_COMPONENT_VALUE, MAtkActionComponent)

struct _MAtkActionComponentValueClass
{
    MAtkActionComponentClass parent_class;
};

MAtkActionComponentValue *m_atk_action_component_value_new (void);
void m_atk_action_component_value_set_current (MAtkActionComponentValue *self, const gdouble current);
void m_atk_action_component_value_set_max (MAtkActionComponentValue *self, const gdouble max);
void m_atk_action_component_value_set_min (MAtkActionComponentValue *self, const gdouble min);

G_END_DECLS

#endif
