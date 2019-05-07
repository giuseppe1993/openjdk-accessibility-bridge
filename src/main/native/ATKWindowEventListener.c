#include "net_java_openjdk_internal_accessibility_ATKWindowEventListener.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <atk/atk.h>
#include "MAtkComponent.h"

#define SWITCH(S) char *_S = S; if (0)
#define CASE(S) } else if (strcmp(_S, S) == 0) {switch(1) { case 1
#define BREAK }
#define DEFAULT } else {switch(1) { case 1


static MAtkObject *frame = NULL;
static const char *utfdesciption;
static const char *utfname;

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setRole (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong object, jstring accessibleRole)
{
    /*jmethodID envelopeGetValueMethod = (*env)->GetMethodID(env, (*env)->FindClass(env, "javax/accessibility/AccessibleRole"), "toString", "()Ljava/lang/String;");
    jobject string = (*env)->CallObjectMethod(env, AccessibleRole, envelopeGetValueMethod);*/
    char *utfvalue = (*env)->GetStringUTFChars(env, accessibleRole, NULL);
    //fprintf(stderr, "%s\n", utfvalue);
    SWITCH (utfvalue) {
        CASE ("frame"):
            atk_object_set_role(object, ATK_ROLE_FRAME);
            BREAK;
        CASE ("root pane"):
            atk_object_set_role(object, ATK_ROLE_ROOT_PANE);
            BREAK;
        CASE ("layered pane"):
            atk_object_set_role(object, ATK_ROLE_LAYERED_PANE);
            BREAK;
        CASE ("panel"):
            atk_object_set_role(object, ATK_ROLE_PANEL);
            BREAK;
        CASE ("menu bar"):
            atk_object_set_role(object, ATK_ROLE_MENU_BAR);
            BREAK;
        CASE ("menu"):
            atk_object_set_role(object, ATK_ROLE_MENU);
            BREAK;
        CASE ("menu item"):
            atk_object_set_role(object, ATK_ROLE_MENU_ITEM);
            BREAK;
        CASE ("check box"):
            atk_object_set_role(object, ATK_ROLE_CHECK_BOX);
            BREAK;
        CASE ("separator"):
            atk_object_set_role(object, ATK_ROLE_SEPARATOR);
            BREAK;
        CASE ("page tab list"):
            atk_object_set_role(object, ATK_ROLE_PAGE_TAB_LIST);
            BREAK;
        CASE ("page tab"):
            atk_object_set_role(object, ATK_ROLE_PAGE_TAB);
            BREAK;
            /*
        CASE ("ghijkl"):
            printf ("C1!\n");
            BREAK;*/
        DEFAULT:
            printf ("problem!\n");
            BREAK;
    }
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setBound (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong object, jint x, jint y, jint width, jint height)
{
  m_atk_component_set_bound (object, x, y, width, height);
}

JNIEXPORT void JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_setStates (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong object, jstring states)
{
  char *utfstates = (*env)->GetStringUTFChars(env, states, NULL);
  const char *delim = ",";
  fprintf(stderr, "%s\n", utfstates);
  char *ptr = strtok(utfstates, delim);
  fprintf(stderr, "%s\n", ptr);
	while(ptr != NULL)
	{
		SWITCH (utfstates){
      CASE ("enabled"):
          m_atk_object_add_state (object, ATK_STATE_ENABLED);
          BREAK;
      CASE ("focusable"):
          m_atk_object_add_state (object, ATK_STATE_FOCUSABLE);
          BREAK;
      CASE ("visible"):
          m_atk_object_add_state (object, ATK_STATE_VISIBLE);
          BREAK;
      CASE ("showing"):
          m_atk_object_add_state (object, ATK_STATE_SHOWING);
          BREAK;
      CASE ("resizable"):
          m_atk_object_add_state (object, ATK_STATE_RESIZABLE);
          BREAK;
      CASE ("opaque"):
          m_atk_object_add_state (object, ATK_STATE_OPAQUE);
          BREAK;
      CASE ("selectable"):
          m_atk_object_add_state (object, ATK_STATE_SELECTABLE);
          BREAK;
      CASE ("checked"):
          m_atk_object_add_state (object, ATK_STATE_CHECKED);
          BREAK;
      DEFAULT:
          printf ("problem!\n");
          BREAK;
    }
		ptr = strtok(NULL, delim);
    fprintf(stderr, "%s\n", ptr);
	}

}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_newAtkComponent (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong father)
{
  AtkObject *child= ATK_OBJECT( m_atk_component_new() );
  m_atk_object_add_child (father, child);
  g_object_ref (child);
  return child;
}

JNIEXPORT jlong JNICALL
Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkFrame (JNIEnv *env, jclass ATKWindowEventListenerclass, jlong root)
{
    fprintf(stderr, "Java_net_java_openjdk_internal_accessibility_ATKWindowEventListener_initAtkFrame\n");
    if (!frame)
    {
      frame = M_ATK_OBJECT (m_atk_component_new());
      m_atk_object_add_child (root, ATK_OBJECT(frame));
      g_object_ref (frame);
    }
    return frame;

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
	if (frame == cObject){
		fprintf(stderr, "ATKWindowEventListener_FrameOpened name is:");
		if (name != NULL){
			utfname = (*env)->GetStringUTFChars(env, name, NULL);
      m_atk_object_set_name(frame, utfname);
      /*AtkPropertyValues signalstuff = g_new0(AtkPropertyValues, 1);
      signalstuff->property_name = "accessible-name";
      signalstuff->old_value = atk_object_get_name(ATK_OBJECT(frame));
      signalstuff->new_value = utfname;
      atk_object_set_name(ATK_OBJECT(frame),utfname);
      g_signal_emit_by_name (object, signalstuff, NULL);*/
			fprintf(stderr, "%s ", utfname);
		}
		else
			fprintf(stderr, "NULL ");
		fprintf(stderr, "description is: ");
		if (description != NULL){
			utfdesciption = (*env)->GetStringUTFChars(env, description, NULL);

      m_atk_object_set_description(frame, utfdesciption);
      /*AtkPropertyValues signalstuff = g_new0(AtkPropertyValues, 1);
      signalstuff->property_name = "accessible-name";
      signalstuff->old_value = atk_object_get_description(ATK_OBJECT(frame));
      signalstuff->new_value = utfname;
      atk_object_set_description(ATK_OBJECT(frame),utfname);*/
      //atk_object_set_description(ATK_OBJECT(frame),utfdesciption);
			fprintf(stderr, "%s\n", utfdesciption);
		}
		else
			fprintf(stderr, "NULL\n");

    //m_atk_component_set_bound (M_ATK_COMPONENT(frame), 10, 10, 10, 10);
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
