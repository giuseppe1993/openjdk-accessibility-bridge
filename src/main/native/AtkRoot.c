/*
 * AtkRoot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include "AtkRoot.h"

struct _CAtkRootPrivate
{
   /* g_type_add_instance_private requires private_size > 0 */
   gint pad;
};

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRoot, c_atk_root, ATK_TYPE_OBJECT)


/**
 * atkroot_new:
 *
 * Create a new #AtkRoot.
 *
 * Returns: (transfer full): a newly created #AtkRoot
 */
CAtkRoot *
c_atk_root_new (void)
{
   CAtkRoot *root = g_object_new (C_ATK_TYPE_ROOT, NULL);

   atk_object_initialize(ATK_OBJECT(root), NULL);

   return root;
}

static void
atk_root_initialize(AtkObject *self, gpointer null)
{
	atk_object_set_role(self, ATK_ROLE_APPLICATION);
}


static void
atk_root_finalize (GObject *object)
{
  /* CAtkRoot *self = (CAtkRoot *)object; */
  /* CAtkRootPrivate *priv = c_atk_root_get_instance_private (self); */

  G_OBJECT_CLASS (c_atk_root_parent_class)->finalize (object);
}

static const char*
c_atk_root_get_name (AtkObject *obj)
{
   return "ATK DEMO FOR THE WIN!!";
}

static void
c_atk_root_class_init (CAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_CLASS(klass);

  atk_class->initialize = atk_root_initialize;
  atk_class->get_name = c_atk_root_get_name;
  object_class->finalize = atk_root_finalize;
}

static void
c_atk_root_init (CAtkRoot *self)
{
}

