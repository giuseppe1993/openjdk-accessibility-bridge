#include "net_java_openjdk_internal_accessibility_ATKWindowEventListener.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "MAtkComponent.h"
#include "MAtkActionComponent.h"
#include "MAtkAction.h"
#include "mappingEnumeretors.h"

static MAtkObject *frame = NULL;

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setRole (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring accessibleRole)
{
    MAtkObject *object = M_ATK_OBJECT((gpointer) refency);
    char *utfvalue = strdup( (*env)->GetStringUTFChars(env, accessibleRole, NULL));
    AtkRole role = mapping_role_from_Java(utfvalue);
    m_atk_object_set_role (object, role);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setBound (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jint x, jint y, jint width, jint height)
{
  MAtkComponent *object = M_ATK_COMPONENT((gpointer) refency);
  m_atk_component_set_bound (object, x, y, width, height);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setActionBound (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jint x, jint y, jint width, jint height)
{
  MAtkActionComponent *object = M_ATK_ACTION_COMPONENT((gpointer) refency);
  m_atk_action_component_set_bound (object, x, y, width, height);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setActionDescription (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring description)
{
    MAtkAction *object = M_ATK_ACTION( (gpointer)refency );
    char *utfdesciption;
    if (description != NULL){
        RealAction *action = g_new0 (RealAction, 1);
        m_atk_action_add_action (object, action);
        m_atk_action_set_name (object, action, "");
        m_atk_action_set_keybinding (object, action, "");
        m_atk_action_set_localized_name (object, action, "");
        utfdesciption = strdup( (*env)->GetStringUTFChars(env, description, NULL) );
        m_atk_action_set_description (object, action, utfdesciption);
    }
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setStates (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring states)
{
    MAtkObject *object = M_ATK_OBJECT((gpointer) refency);
    char *utfstates = strdup( (*env)->GetStringUTFChars(env, states, NULL) );
    const char *delim = ",";
    char *ptr = strtok(utfstates, delim);
    AtkState state = ATK_STATE_INVALID;
    while(ptr != NULL){
        state = mapping_state_from_Java (ptr);
        m_atk_object_add_state (object, state);
        ptr = strtok(NULL, delim);
    }
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setName (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring name)
{
    char *utfname;
    if (name != NULL){
        utfname = strdup( (*env)->GetStringUTFChars(env, name, NULL) );
        m_atk_object_set_name(frame, utfname);
    }
    else
        m_atk_object_set_name(frame, "");
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setDescription (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring description)
{
    char *utfdesciption;
    if (description != NULL){
        utfdesciption = strdup( (*env)->GetStringUTFChars(env, description, NULL) );
        m_atk_object_set_description(frame, utfdesciption);
    }
    else
        m_atk_object_set_description(frame, "");
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkActionComponent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency)
{
    MAtkObject *father = M_ATK_OBJECT((gpointer) refency);
    AtkObject *child= ATK_OBJECT( m_atk_action_component_new() );
    m_atk_object_add_child (father, child);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkAction (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency)
{
    MAtkObject *father = M_ATK_OBJECT((gpointer) refency);
    AtkObject *child= ATK_OBJECT( m_atk_action_new() );
    m_atk_object_add_child (father, child);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkComponent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency)
{
  MAtkObject *father = M_ATK_OBJECT((gpointer) refency);
  AtkObject *child= ATK_OBJECT( m_atk_component_new() );
  if (!frame)
    frame = M_ATK_OBJECT(child);
  m_atk_object_add_child (father, child);
  g_object_ref (child);
  return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkFrame (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency)
{
    MAtkObject *root = M_ATK_OBJECT((gpointer) refency);
    fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkFrame\n");
    if (!frame)
    {
      frame = M_ATK_OBJECT (m_atk_component_new());
      m_atk_object_add_child (root, ATK_OBJECT(frame));
      g_object_ref (frame);
    }
    return (jlong) frame;

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_freeAtkFrame (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject)
{
	g_object_unref(frame);
	fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_freeAtkFrame\n");
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameOpened (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring name, jstring description)
{
    char *utfdesciption;
    char *utfname;
    MAtkObject *object = M_ATK_OBJECT ((gpointer) refency);
    if (frame == object){
        fprintf(stderr, "ATKWindowEventListener_FrameOpened name is:");
		if (name != NULL){
			utfname = strdup( (*env)->GetStringUTFChars(env, name, NULL) );
            m_atk_object_set_name(frame, utfname);
            fprintf(stderr, "%s ", utfname);
		}
		else
			fprintf(stderr, "NULL ");
		fprintf(stderr, "description is: ");
		if (description != NULL){
			utfdesciption = strdup( (*env)->GetStringUTFChars(env, description, NULL) );
            m_atk_object_set_description(frame, utfdesciption);
			fprintf(stderr, "%s\n", utfdesciption);
		}
		else
			fprintf(stderr, "NULL\n");
	}
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameClosing (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{

    fprintf(stderr, "ATKWindowEventListener_FrameClosing description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameClosed
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{
    fprintf(stderr, "ATKWindowEventListener_FrameClosed description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameIconified (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{
    fprintf(stderr, "ATKWindowEventListener_FrameIconified description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameDeiconified
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{
    fprintf(stderr, "ATKWindowEventListener_FrameDeiconified description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameActivated (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{
    fprintf(stderr, "ATKWindowEventListener_FrameActivated description is: ");
	if (description != NULL){
		const char *utfdesciption;
		utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
		fprintf(stderr, "%s\n", utfdesciption);
	}
	else
		fprintf(stderr, "NULL\n");
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameDeactivated (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{
    fprintf(stderr, "ATKWindowEventListener_FrameDeactivated description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");
}
