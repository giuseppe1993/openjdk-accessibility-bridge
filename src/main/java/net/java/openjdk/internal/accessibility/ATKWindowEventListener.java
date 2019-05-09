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

    private static native long newAtkComponent (long referency);
    private static native long newAtkAction (long referency);
    private static native long newAtkActionComponent (long referency);
    private static native void setRole(long object, String role);
    private static native void setStates(long object, String states);
    private static native void setBound(long object, int x, int y, int width, int height);

    private static native void freeAtkFrame(long frameReferency);
    private static native void atkFrameOpened(long frameReferency, String name, String description);
    private static native void atkFrameClosing(long frameReferency, String description);
    private static native void atkFrameClosed(long frameReferency, String description);
    private static native void atkFrameIconified(long frameReferency, String description);
    private static native void atkFrameDeiconified(long frameReferency, String description);
    private static native void atkFrameActivated(long frameReferency, String description);
    private static native void atkFrameDeactivated(long frameReferency, String description);

    private long frameReferency;

	public ATKWindowEventListener(long root) {
        super();
        frameReferency = initAtkFrame(root);
        System.err.println("J Mediator Root referency: "+root+" Java Frame Root: "+frameReferency);
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
            AccessibleRole accessibleRole = ac.getAccessibleRole();
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
            atkFrameOpened(frameReferency, name, description);
            setRole(frameReferency,accessibleRole);
            AccessibleComponent component = null;
            if( (component = ac.getAccessibleComponent() )!= null){
                Rectangle bound = component.getBounds();
                int height = (int) bound.getHeight();
                int width = (int) bound.getWidth();
                int x = (int) bound.getX();
                int y = (int) bound.getY();
                setBound(frameReferency, x, y, width, height);
            }
            String states = ac.getAccessibleStateSet().toString();
            states = states.replace("[","");
            states = states.replace("]","");
            setStates(frameReferency, states);
        }
    }

    @Override
    public void windowClosing(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameClosing(frameReferency, description);
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
            atkFrameClosed(frameReferency, description);
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
            atkFrameIconified(frameReferency, description);
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
            atkFrameDeiconified(frameReferency, description);
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
            atkFrameActivated(frameReferency, description);
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
            atkFrameDeactivated(frameReferency, description);
            //System.err.println("deactivated: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    protected void finalize() throws Throwable {
    	//when the Garbage collector destroy this object destroy also the C object
    	super.finalize();
    	freeAtkFrame(frameReferency);
    }

}
