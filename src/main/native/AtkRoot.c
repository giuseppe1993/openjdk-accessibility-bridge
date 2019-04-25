/*
 * AtkRoot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include "AtkRoot.h"
#include <gmodule.h>

#define C_ATK_ROOT_GET_PRIVATE(o) (c_atk_root_get_istance_private (o))

typedef struct
{
  gint pad1;

} CAtkRootPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRoot, c_atk_root, C_TYPE_ATK_ACTOR)

CAtkRoot *
c_atk_root_new (void)
{
   CAtkRoot *root = g_object_new (C_TYPE_ATK_ROOT, NULL);

   atk_object_initialize (ATK_OBJECT(root), NULL);

   return root;
}

static void
c_atk_root_initialize (AtkObject *self, gpointer null)
{

	atk_object_set_role(self, ATK_ROLE_APPLICATION);
	atk_object_set_parent(self, NULL);

}

static void
c_atk_root_finalize (GObject *object)
{
	g_return_if_fail (C_IS_ATK_ROOT(object));

  G_OBJECT_CLASS (c_atk_root_parent_class)->finalize (object);
}

static const char*
c_atk_root_get_name (AtkObject *obj)
{
   return "Atk Root";
}

static const char*
c_atk_root_get_description()
{
	return "this is the description of the root component";
}

static void
c_atk_root_class_init (CAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_CLASS(klass);

  atk_class->initialize = c_atk_root_initialize;
  atk_class->get_name = c_atk_root_get_name;
  atk_class->get_description = c_atk_root_get_description;

  object_class->finalize = c_atk_root_finalize;
}

static void
c_atk_root_init (CAtkRoot *self)
{
}