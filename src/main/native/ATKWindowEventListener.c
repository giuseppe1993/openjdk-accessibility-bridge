#include "net_java_openjdk_internal_accessibility_ATKWindowEventListener.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <atk/atk.h>
#include "AtkFrame.h"

static CAtkFrame * frame = NULL;
static const char *utfdesciption;
static const char *utfname;

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkWindows
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong root)
{

    fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkWindows\n");
    if (!frame)
    	frame = c_atk_frame_new ();
    atk_object_set_parent(ATK_OBJECT(frame),ATK_OBJECT(root));
    g_object_ref (frame);
    return frame;

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_freeAtkWindows
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject)
{
	g_object_unref(frame);
	fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_freeAtkWindows\n");

}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_atkWindowOpened
	(JNIEnv *env, jclass ATKWindowEventListenerclass, jlong cObject, jstring name, jstring description)
{
	if (frame == cObject){
		fprintf(stderr, "ATKWindowEventListener_windowOpened name is:");
		if (name != NULL){
			utfname = (*env)->GetStringUTFChars(env, name, NULL);
			atk_object_set_name(ATK_OBJECT(frame),utfname);
			fprintf(stderr, "%s ", utfdesciption);
			}
		else
			fprintf(stderr, "NULL ");
		fprintf(stderr, "description is: ");
		if (description != NULL){
			utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);
			atk_object_set_description(ATK_OBJECT(frame),utfdesciption);
			fprintf(stderr, "%s\n", utfdesciption);
		}
		else
			fprintf(stderr, "NULL\n");
	}
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
