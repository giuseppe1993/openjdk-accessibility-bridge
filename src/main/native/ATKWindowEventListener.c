#include "net_java_openjdk_internal_accessibility_ATKWindowEventListener.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <atk/atk.h>
#include "mediatorAtk.h"

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkComponent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference)
{
    MAtkObject *father = M_ATK_OBJECT( (gpointer) reference);
    AtkObject *child = ATK_OBJECT ( m_atk_component_new() );
    m_atk_object_add_child (father, child);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkAction (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference)
{
    MAtkObject *father = M_ATK_OBJECT( (gpointer) reference);
    AtkObject *child = ATK_OBJECT ( m_atk_action_new () );
    m_atk_object_add_child (father, child);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkActionComponent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference)
{
    MAtkObject *father = M_ATK_OBJECT( (gpointer) reference);
    AtkObject *child = ATK_OBJECT ( m_atk_action_component_new() );
    m_atk_object_add_child (father, child);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkActionComponentValue (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference)
{
    MAtkObject *father = M_ATK_OBJECT( (gpointer) reference);
    AtkObject *child = ATK_OBJECT ( m_atk_action_component_value_new() );
    m_atk_object_add_child (father, child);
    g_object_ref (child);
    return (jlong) child;
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setRole (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jstring accessibleRole)
{
    AtkObject *object = ATK_OBJECT((gpointer) reference);
    const char *utfRole = (*env)->GetStringUTFChars(env, accessibleRole, NULL);
    AtkRole role = mapping_role_from_Java(utfRole);
    atk_object_set_role (object, role);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setName (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jstring name)
{
    AtkObject *object = ATK_OBJECT((gpointer) reference);
    const gchar *utfname = (*env)->GetStringUTFChars(env, name, NULL);
    atk_object_set_name (object, utfname);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setDescription (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jstring description)
{
    AtkObject *object = ATK_OBJECT((gpointer) reference);
    const gchar *utfdescription = (*env)->GetStringUTFChars(env, description, NULL);
    atk_object_set_description (object, utfdescription);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setBound (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jint x, jint y, jint width, jint height)
{
    MAtkComponent *object = M_ATK_COMPONENT((gpointer) reference);
    m_atk_component_set_bound (object, x, y, width, height);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setActionBound (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jint x, jint y, jint width, jint height)
{
    MAtkActionComponent *object = M_ATK_ACTION_COMPONENT((gpointer) reference);
    m_atk_action_component_set_bound (object, x, y, width, height);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setStates (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jstring states)
{
    MAtkObject *object = M_ATK_OBJECT((gpointer) reference);
    g_auto(GStrv) strsplit = NULL;
    gchar **strstates;
    AtkState state = ATK_STATE_INVALID;
    strsplit = g_strsplit( (*env)->GetStringUTFChars(env, states, NULL), ",",-1);
    for ( strstates = strsplit; *strstates; strstates++)
    {
        state = mapping_state_from_Java ( (const char*) *strstates );
        m_atk_object_add_state (object, state);
    }
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setLayer (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jstring accessibleRole)
{
    MAtkComponent *object = M_ATK_COMPONENT((gpointer) reference);
    const char *utfRole = (*env)->GetStringUTFChars (env, accessibleRole, NULL);
    AtkLayer atklayer = mapping_layer_from_Java_role (utfRole);
    m_atk_component_set_layer (object, atklayer);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setActionLayer (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jstring accessibleRole)
{
    MAtkActionComponent *object = M_ATK_ACTION_COMPONENT((gpointer) reference);
    const char *utfRole = (*env)->GetStringUTFChars (env, accessibleRole, NULL);
    AtkLayer atklayer = mapping_layer_from_Java_role (utfRole);
    m_atk_action_component_set_layer (object, atklayer);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_saveCallReference (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jobject java_action)
{
    MAtkAction *object = M_ATK_ACTION((gpointer) reference);
    jobject g_java_action = (*env)->NewGlobalRef (env, java_action);
    JavaVM *jvm;
    (*env)->GetJavaVM (env, &jvm);
    jclass gActionClass = (*env)->GetObjectClass(env, g_java_action);
    jmethodID g_mid = (*env)->GetMethodID(env, gActionClass, "doAccessibleAction", "(I)Z");
    m_atk_action_save_java_reference (object, jvm, g_mid, g_java_action);
}

JNIEXPORT jint JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_addAction (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jstring name, jstring description, jstring keybinding, jstring localizedname)
{
    MAtkAction *object = M_ATK_ACTION((gpointer) reference);
    const char *utfname = (*env)->GetStringUTFChars(env, name, NULL);
    const char *utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    const char *utfkeybinding = (*env)->GetStringUTFChars(env, keybinding, NULL);
    const char *utflocalizedname = (*env)->GetStringUTFChars(env, localizedname, NULL);
    return m_atk_action_add_action(object, utfname, utfdesciption, utfkeybinding, utflocalizedname);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setMax (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jdouble max)
{
    MAtkActionComponentValue *object = M_ATK_ACTION_COMPONENT_VALUE((gpointer) reference);
    m_atk_action_component_value_set_max (object, max);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setMin (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jdouble min)
{
    MAtkActionComponentValue *object = M_ATK_ACTION_COMPONENT_VALUE((gpointer) reference);
    m_atk_action_component_value_set_min (object, min);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setCurrent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong reference, jdouble current)
{
    MAtkActionComponentValue *object = M_ATK_ACTION_COMPONENT_VALUE((gpointer) reference);
    m_atk_action_component_value_set_current (object, current);
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
