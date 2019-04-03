/*
 * AtkRoot.h
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe
 */

#ifndef _C_ATK_ROOT_H_
#define _C_ATK_ROOT_H_

#include <atk/atk.h>

G_BEGIN_DECLS

#define C_ATK_TYPE_ROOT            (c_atk_root_get_type ())
#define C_ATK_ROOT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), C_ATK_TYPE_ROOT, CallyRoot))
#define C_ATK_ROOT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), C_ATK_TYPE_ROOT, CallyRootClass))
#define C_ATK_IS_ROOT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), C_ATK_TYPE_ROOT))
#define C_ATK_IS_ROOT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), C_ATK_TYPE_ROOT))
#define C_ATK_ROOT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), C_ATK_TYPE_ROOT, CallyRootClass))

typedef struct _CAtkRoot        CAtkRoot;
typedef struct _CAtkRootClass   CAtkRootClass;
typedef struct _CAtkRootPrivate CAtkRootPrivate;

struct _CAtkRoot {
  AtkObject parent;

  CAtkRootPrivate *priv;
};

struct _CAtkRootClass
{
  AtkObjectClass parent_class;

};

GType     c_atk_root_get_type ();
CAtkRoot *c_atk_root_new (void);

G_END_DECLS

#endif /* ATKROOT_H_ */
