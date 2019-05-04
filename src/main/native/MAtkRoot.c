/*
 * catkroot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include <gmodule.h>
#include "MAtkRoot.h"

#define M_ATK_ROOT_GET_PRIVATE(o) (m_atk_root_get_istance_private (o))

typedef struct
{
  gint pad1;

} MAtkRootPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (MAtkRoot, m_atk_root, M_TYPE_ATK_OBJECT)

MAtkRoot *
m_atk_root_new (void)
{
   MAtkRoot *root = g_object_new (M_TYPE_ATK_ROOT, NULL);
   atk_object_initialize (ATK_OBJECT(root), NULL);
   return root;
}

static void
m_atk_root_initialize (AtkObject *self, gpointer null)
{
}

static void
m_atk_root_finalize (GObject *object)
{
	g_return_if_fail (M_IS_ATK_ROOT(object));
  G_OBJECT_CLASS (m_atk_root_parent_class)->finalize (object);
}

static void
m_atk_root_class_init (MAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_CLASS(klass);

  atk_class->initialize = m_atk_root_initialize;

  object_class->finalize = m_atk_root_finalize;
}

static void
m_atk_root_init (MAtkRoot *self)
{
  atk_object_set_role(ATK_OBJECT(self), ATK_ROLE_APPLICATION);
	atk_object_set_parent(ATK_OBJECT(self), NULL);
  m_atk_object_set_name(M_ATK_OBJECT(self),"Atk Root");
  m_atk_object_set_description(M_ATK_OBJECT(self),"this is the description of the root component");
}
