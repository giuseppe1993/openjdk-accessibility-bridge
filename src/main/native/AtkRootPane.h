
#ifndef ATK_ROOT_PANE_H_
#define ATK_ROOT_PANE_H_

#include <atk/atk.h>
#include "AtkActor.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_ROOT_PANE            (c_atk_root_pane_get_type ())

G_DECLARE_DERIVABLE_TYPE (CAtkRootPane, c_atk_root_pane, C, ATK_ROOT_PANE, CAtkActor)

struct _CAtkRootPaneClass
{
  CAtkActorClass parent_class;
};

CAtkRootPane *c_atk_root_pane_new (void);

#endif 