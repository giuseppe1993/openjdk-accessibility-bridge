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
#include <atk-bridge.h>
#include "AtkRoot.h"

static AtkObject *root = NULL;
static GMainLoop *mainloop = NULL;

static AtkObject*
get_root (void)
{
  if (!root)
    root = ATK_OBJECT(c_atk_root_new ());
  
  return root;
}

static const gchar *
get_toolkit_name (void)
{
  return strdup ("My ATK-UTIL");
}

static void
setup_atk_util (void)
{
  AtkUtilClass *klass;

  klass = g_type_class_ref (ATK_TYPE_UTIL);
  klass->get_root = get_root;
  klass->get_toolkit_name = get_toolkit_name;
  g_type_class_unref (klass);
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_AccessBridge_initATK(JNIEnv *env, jclass AccessBridgeClass)
{
  setup_atk_util();
  int init_outcome = atk_bridge_adaptor_init (NULL, NULL);
  if(init_outcome)
    if(!root)
    {
      fprintf(stderr, "Problems\n");
      root = atk_get_root(); 
    }    
  
  fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_AccessBridge_initATK\n");
  /*mainloop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (mainloop);*/
  
  /*OpenJDKAccessBridge* bridge = (OpenJDKAccessBridge*) malloc(sizeof(OpenJDKAccessBridge));
  (*env)->GetJavaVM(env, &bridge->jvm);*/
  g_object_ref (root);
  return root;
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_AccessBridge_runMainLoopATK(JNIEnv *env, jclass AccessBridgeClass)
{
  if(!mainloop){
    mainloop = g_main_loop_new (NULL, FALSE);
    mainloop = g_main_loop_ref(mainloop);
    g_main_loop_run (mainloop);
  }
  else
    if(!g_main_loop_is_running(mainloop))
      g_main_loop_run (mainloop);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_AccessBridge_stopMainLoopATK(JNIEnv *env, jclass AccessBridgeClass)
{
  if( (mainloop) && (g_main_loop_is_running(mainloop)) )
  {
    g_main_loop_unref(mainloop);
    g_main_loop_quit (mainloop);
  }
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_AccessBridge_freeATK(JNIEnv *env, jclass AccessBridgeClass)
{
  g_object_unref(root);
  atk_bridge_adaptor_cleanup();
}


