/*
 * demo_component.h
 *
 *  Created on: Apr 25, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_COMPONENT_H_
#define DEMO_COMPONENT_H_

#include <atk/atk.h>
#include "MAtkObject.h"

G_BEGIN_DECLS

#define M_TYPE_ATK_COMPONENT            (m_atk_component_get_type ())

G_DECLARE_DERIVABLE_TYPE(MAtkComponent, m_atk_component, M, ATK_COMPONENT, MAtkObject)

struct _MAtkComponentClass
{
  MAtkObjectClass parent_class;
};

//protected
void m_atk_component_set_layer (MAtkComponent *self, AtkLayer layer);
void m_atk_component_set_bound (MAtkComponent *self, gint x, gint y, gint width, gint height);
void m_atk_component_set_coord_type (MAtkComponent *self, AtkCoordType coord_type);

G_END_DECLS

#endif /* DEMO_COMPONENT_H_ */
