#include "net_java_openjdk_internal_accessibility_ATKWindowEventListener.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <atk/atk.h>
#include "mediatorAtk.h"
#include "mappingEnumerators.h"
#include "MAtkFrame.h"

static AtkObject *frame = NULL;

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkComponent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong referency)
{
    MAtkObject *father = M_ATK_OBJECT( (gpointer) referency);
    AtkObject *child = ATK_OBJECT ( m_atk_component_new () );
    m_atk_object_add_child (father, frame);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkAction (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong referency)
{
    MAtkObject *father = M_ATK_OBJECT( (gpointer) referency);
    AtkObject *child = ATK_OBJECT ( m_atk_component_new () );
    m_atk_object_add_child (father, frame);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkActionComponent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong referency)
{
    MAtkObject *father = M_ATK_OBJECT( (gpointer) referency);
    AtkObject *child = ATK_OBJECT ( m_atk_component_new () );
    m_atk_object_add_child (father, frame);
    g_object_ref (child);
    return (jlong) child;
}


JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkFrame (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong referency)
{
    MAtkObject * root = M_ATK_OBJECT( (gpointer) referency);
    fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkFrame\n");
    if (!frame)
    {
        frame = ATK_OBJECT ( m_atk_frame_new () );
        m_atk_object_add_child (root, frame);
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
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkFrameOpened (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring name, jstring description)
{
    const char *utfname = NULL;
    const char *utfdesciption = NULL;
	if ( (jlong)frame == cObject){
		fprintf(stderr, "ATKWindowEventListener_FrameOpened name is:");
		if (name != NULL){
			utfname = (*env)->GetStringUTFChars(env, name, NULL);
            atk_object_set_name (frame, utfname);
			fprintf(stderr, "%s ", utfname);
		}
		else
			fprintf(stderr, "NULL ");
		fprintf(stderr, "description is: ");
		if (description != NULL){
			utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
            atk_object_set_description (frame, utfdesciption);
			fprintf(stderr, "%s\n", utfdesciption);
		}
		else
			fprintf(stderr, "NULL\n");
	}
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setRole (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring accessibleRole)
{
    AtkObject *object = ATK_OBJECT((gpointer) refency);
    const char *utfvalue = (*env)->GetStringUTFChars(env, accessibleRole, NULL);
    AtkRole role = mapping_role_from_Java(utfvalue);
    atk_object_set_role (object, role);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setName (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring name)
{
    AtkObject *object = ATK_OBJECT((gpointer) refency);
    const gchar *utfname = (*env)->GetStringUTFChars(env, name, NULL);
    atk_object_set_name (object, utfname);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setDescription (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring description)
{
    AtkObject *object = ATK_OBJECT((gpointer) refency);
    const gchar *utfdescription = (*env)->GetStringUTFChars(env, description, NULL);
    atk_object_set_description (object, utfdescription);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setBound (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jint x, jint y, jint width, jint height)
{
    MAtkComponent *object = M_ATK_COMPONENT((gpointer) refency);
    m_atk_component_set_bound (object, x, y, width, height);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setStates (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong refency, jstring states)
{
    MAtkObject *object = M_ATK_OBJECT((gpointer) refency);
    char *utfstates = strdup( (*env)->GetStringUTFChars(env, states, NULL) );
    const char *delim = ",";
    char *ptr = strtok(utfstates, delim);
    AtkState state = ATK_STATE_INVALID;
    while(ptr != NULL)
    {
        state = mapping_state_from_Java (ptr);
        m_atk_object_add_state (object, state);
		ptr = strtok(NULL, delim);
	}
    free(utfstates);
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
