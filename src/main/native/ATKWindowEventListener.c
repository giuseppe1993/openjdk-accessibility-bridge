#include "net_java_openjdk_internal_accessibility_ATKWindowEventListener.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <atk/atk.h>
#include "AtkWindow.h"

static CAtkWindow * window = NULL;

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkWindows
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong root)
{

    fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkWindows\n");
    if (!window)
    	window = c_atk_window_new ();
    atk_object_set_parent(ATK_OBJECT(window),ATK_OBJECT(root));
    return window;

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_freeAtkWindows
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject)
{
	fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_freeAtkWindows\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowOpened
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{
    fprintf(stderr, "ATKWindowEventListener_windowOpened description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowClosing
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{

    fprintf(stderr, "ATKWindowEventListener_windowClosing description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowClosed
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{

    fprintf(stderr, "ATKWindowEventListener_windowClosed description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowIconified
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{

    fprintf(stderr, "ATKWindowEventListener_windowIconified description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowDeiconified
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{

    fprintf(stderr, "ATKWindowEventListener_windowDeiconified description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowActivated
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{

    fprintf(stderr, "ATKWindowEventListener_windowActivated description is: ");
	if (description != NULL){
		const char *utfdesciption;
		utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
		fprintf(stderr, "%s\n", utfdesciption);
	}
	else
		fprintf(stderr, "NULL\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowDeactivated
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring description)
{

    fprintf(stderr, "ATKWindowEventListener_windowDeactivated description is: ");
    if (description != NULL){
    	const char *utfdesciption;
    	utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
    	fprintf(stderr, "%s\n", utfdesciption);
    }
    else
    	fprintf(stderr, "NULL\n");

}
