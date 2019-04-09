/*
 * fixAtk.h
 *
 *  Created on: Apr 4, 2019
 *      Author: giuseppe
 */

#pragma once

/* Work around the fact that Atk does not define the auto pointer cleanup.
 * Add a check using ATK_CHECK_VERSION once fixed in Atk upstream. */
G_DEFINE_AUTOPTR_CLEANUP_FUNC(AtkObject, g_object_unref)

