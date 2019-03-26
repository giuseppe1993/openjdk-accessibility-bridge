/*
 * Copyright (c) 2018, Red Hat, Inc.
 * Copyright (c) 2018, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#include "net_java_openjdk_internal_accessibility_AccessBridge.h"

#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <atk/atk.h>
#include <atk-bridge.h>
#include "AccessBridge.h"

static void
set_root (void){
	static GObject *groot=NULL;
	static AtkObject *root=NULL;

	if(!groot){
		groot=g_object_new (ATK_TYPE_GOBJECT_ACCESSIBLE, NULL);
		root =atk_gobject_accessible_for_object(groot);
		atk_object_initialize (root, NULL);
	}
}

JNIEXPORT jboolean JNICALL
Java_net_java_openjdk_internal_accessibility_AccessBridge_initATK(JNIEnv *env,
        jclass AccessBridgeClass)
{
	set_root;

	gboolean initATK = atk_bridge_adaptor_init (NULL, NULL);

	if(initATK)
		fprintf(stderr,"Initialized\n");
	else
		fprintf(stderr,"Not Initialized\n");

    fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_AccessBridge_initATK\n");

    OpenJDKAccessBridge* bridge = (OpenJDKAccessBridge*) malloc(sizeof(OpenJDKAccessBridge));
    (*env)->GetJavaVM(env, &bridge->jvm);

    return initATK;

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_AccessBridge_freeATK(JNIEnv *env, jclass AccessBridgeClass)
{
	atk_bridge_adaptor_cleanup();
}


