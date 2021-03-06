/*
 * MAtkActionComponent.h
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
#ifndef MEDIATOR_ACTION_COMPONENT_H_
#define MEDIATOR_ACTION_COMPONENT_H_

#include <atk/atk.h>
#include "MAtkAction.h"

G_BEGIN_DECLS

#define M_TYPE_ATK_ACTION_COMPONENT            (m_atk_action_component_get_type ())

G_DECLARE_DERIVABLE_TYPE(MAtkActionComponent, m_atk_action_component, M, ATK_ACTION_COMPONENT, MAtkAction)

struct _MAtkActionComponentClass
{
    MAtkActionClass parent_class;
};

MAtkActionComponent *m_atk_action_component_new (void);
void m_atk_action_component_set_layer (MAtkActionComponent *self, AtkLayer layer);
void m_atk_action_component_set_bound (MAtkActionComponent *self, gint x, gint y, gint width, gint height);
void m_atk_action_component_set_coord_type (MAtkActionComponent *self, AtkCoordType coord_type);

G_END_DECLS

#endif
