/*
 * demo_frame.c
 *
 *  Created on: Apr 10, 2019
 *      Author: giuseppe
 */
#include <gmodule.h>
#include "MAtkFrame.h"

#define M_ATK_FRAME_GET_PRIVATE(o) (m_atk_frame_get_istance_private (o))

typedef struct
{
	gint pad1;

} MAtkFramePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (MAtkFrame, m_atk_frame, M_TYPE_ATK_COMPONENT)

MAtkFrame *
m_atk_frame_new (void)
{
   MAtkFrame *frame = g_object_new (M_TYPE_ATK_FRAME, NULL);
   atk_object_initialize(ATK_OBJECT(frame), NULL);
   return frame;
}

static void
m_atk_frame_initialize (AtkObject *self, gpointer null)
{
}

static void
m_atk_frame_finalize (GObject *object)
{
	g_return_if_fail (M_IS_ATK_FRAME(object));
	G_OBJECT_CLASS (m_atk_frame_parent_class)->finalize (object);
}

static void
m_atk_frame_class_init (MAtkFrameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = m_atk_frame_initialize;

  object_class->finalize = m_atk_frame_finalize;
}

static void
m_atk_frame_init (MAtkFrame *self)
{
	atk_object_set_role (ATK_OBJECT(self), ATK_ROLE_FRAME);
	atk_object_set_parent (ATK_OBJECT(self), NULL);
	m_atk_object_set_name(M_ATK_OBJECT(self),"Atk Frame");
  m_atk_object_set_description(M_ATK_OBJECT(self),"this is the description of the frame component");
	m_atk_component_set_layer (M_ATK_COMPONENT(self), ATK_LAYER_WINDOW);
	m_atk_component_set_coord_type (M_ATK_COMPONENT(self), ATK_XY_SCREEN);
}
