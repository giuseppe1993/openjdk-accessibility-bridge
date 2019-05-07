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

package net.java.openjdk.internal.accessibility;

import java.awt.Rectangle;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.accessibility.*;

public class ATKWindowEventListener implements WindowListener {

    private static native long initAtkFrame(long root);
    private static native void freeAtkFrame(long cObject);
    private static native void atkFrameOpened(long cObject, String name, String description);
    private static native void atkFrameClosing(long cObject, String description);
    private static native void atkFrameClosed(long cObject, String description);
    private static native void atkFrameIconified(long cObject, String description);
    private static native void atkFrameDeiconified(long cObject, String description);
    private static native void atkFrameActivated(long cObject, String description);
    private static native void atkFrameDeactivated(long cObject, String description);

    //setting of C object
    private static native long newAtkComponent(long father);
    private static native void setRole(long object, String role);
    private static native void setStates(long object, String states);
    private static native void setBound(long object, int x, int y, int width, int height);

    private long cObject;

	public ATKWindowEventListener(long root) {
        super();
        cObject = initAtkFrame(root);
        System.err.println("the refency of the AtkRoot: "+root+" the referecy of the AtkWindows: "+cObject);
    }

    void createChildren(AccessibleContext ac){
        AccessibleStateSet states = ac.getAccessibleStateSet();
        int nchild = ac.getAccessibleChildrenCount();
        AccessibleRole accessibleRole = ac.getAccessibleRole();
        AccessibleRole fatherAccessibleRole= ac.getAccessibleParent().getAccessibleContext().getAccessibleRole();
        System.err.println("\nThe child of: '"+fatherAccessibleRole.toString()+"' have this role: "+accessibleRole.toString()+
        "\nthis states: ["+states.toString()+"]\nand this numeber of child: "+nchild);
        AccessibleAction action = null;
        if ( (action = ac.getAccessibleAction()) != null ){
          int count = action.getAccessibleActionCount();
          System.err.println("Implement Java Action and have "+count+" actions:[");
          for ( int i = 0; i < count; i++ ) {
            String description = action.getAccessibleActionDescription(i);
            System.err.println("\tAction n. "+i+" description: "+description);
          }
          System.err.println("]");
        }
        AccessibleComponent component = null;
        if( (component = ac.getAccessibleComponent() )!= null){
            Rectangle bound = component.getBounds();
            System.err.println("Implement Java Compontent and have this dimension : "+bound.toString());
        }
        if( ac.getAccessibleEditableText() != null ){
          System.err.println("Implement Java Editable Text interface");
        }
        AccessibleSelection selection = null;
        if( ( selection = ac.getAccessibleSelection() ) != null ){
          int count = selection.getAccessibleSelectionCount();
          System.err.println("Implement Java Selection interface and have n. "+count+" child");
        }
        AccessibleRelationSet relationSet = null;
        if( (relationSet = ac.getAccessibleRelationSet() ) != null ){
          System.err.println("Have Java Relation Set and have this toString() method :["+relationSet.toString()+"]");
        }
        if( ac.getAccessibleTable() != null ){
          System.err.println("Implement Java Table interface");
        }
        if( ac.getAccessibleText() != null ){
          System.err.println("Implement Java Text interface");
        }
        if( ac.getAccessibleValue() != null ){
          System.err.println("Implement Java Value interface");
        }
        if ( nchild > 0 ){
            for ( int i =0; i < nchild ;i++ ){
                AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                createChildren(child);
            }
        }
    }

    @Override
    public void windowOpened(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
/*
            AccessibleStateSet states = ac.getAccessibleStateSet();
            int nchild = ac.getAccessibleChildrenCount();
            System.err.println("\nJava Root name is :'"+ac.getAccessibleName()+"' have this description:'"+
            ac.getAccessibleDescription()+"'\nhave this role: "+
            accessibleRole.toString()+"\nhave this states: ["+
            states.toString()+"]\nthe numeber of child is:"+nchild);
            AccessibleAction action = null;
            if ( (action = ac.getAccessibleAction()) != null ){
              int count = action.getAccessibleActionCount();
              System.err.println("Implement Java Action and have "+count+" actions:[");
              for ( int i = 0; i < count; i++ ) {
                String description = action.getAccessibleActionDescription(i);
              System.err.println("\tAction n. "+i+" description: "+description);
              }
              System.err.println("]");
            }
            AccessibleComponent component = null;
            if( (component = ac.getAccessibleComponent() )!= null){
                Rectangle bound = component.getBounds();
                System.err.println("Implement Java Compontent and have this dimension :"+bound.toString());
            }
            if( ac.getAccessibleEditableText() != null ){
              System.err.println("Implement Java Editable Text interface");
            }
            AccessibleSelection selection = null;
            if( ( selection = ac.getAccessibleSelection() ) != null ){
              int count = selection.getAccessibleSelectionCount();
              System.err.println("Implement Java Selection interface and have n. "+count+" child");
            }
            AccessibleRelationSet relationSet = null;
            if( (relationSet = ac.getAccessibleRelationSet() ) != null ){
              System.err.println("Have Java Relation Set and have this toString() method :["+relationSet.toString()+"]");
            }
            if( ac.getAccessibleTable() != null ){
              System.err.println("Implement Java Table interface");
            }
            if( ac.getAccessibleText() != null ){
              System.err.println("Implement Java Text interface");
            }
            if( ac.getAccessibleValue() != null ){
              System.err.println("Implement Java Value interface");
            }

            for (int i =0; i<nchild;i++){
                AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                printInformation(child);
            }
*/
            String name = ac.getAccessibleName();
            String description = ac.getAccessibleDescription();
            String accessibleRole = ac.getAccessibleRole().toString();
            //TODO push all in C Object
            atkFrameOpened(cObject, name, description);
            setRole(cObject,accessibleRole);
            AccessibleComponent component = null;
            if( (component = ac.getAccessibleComponent() )!= null){
                Rectangle bound = component.getBounds();
                int height = (int) bound.getHeight();
                int width = (int) bound.getWidth();
                int x = (int) bound.getX();
                int y = (int) bound.getY();
                setBound(cObject, x, y, width, height);
            }
            String states = ac.getAccessibleStateSet().toString();
            states = states.replace("[","");
            states = states.replace("]","");
            setStates(cObject, states);

        }
    }

    @Override
    public void windowClosing(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameClosing(cObject, description);
            //System.err.println("closing: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowClosed(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameClosed(cObject, description);
            //System.err.println("closed: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowIconified(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameIconified(cObject, description);
            //System.err.println("iconified: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowDeiconified(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameDeiconified(cObject, description);
            //System.err.println("Deiconified: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowActivated(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameActivated(cObject, description);
            //System.err.println("activated: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowDeactivated(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameDeactivated(cObject, description);
            //System.err.println("deactivated: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    protected void finalize() throws Throwable {
    	//when the Garbage collector destroy this object destroy also the C object
    	super.finalize();
    	freeAtkFrame(cObject);
    }
}
