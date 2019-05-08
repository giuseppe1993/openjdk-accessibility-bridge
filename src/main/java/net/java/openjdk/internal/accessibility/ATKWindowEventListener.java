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
import java.util.HashMap;

import javax.accessibility.*;

public class ATKWindowEventListener implements WindowListener {

    //devo togliere anche questi
    private static native long initAtkFrame(long root);
    private static native void freeAtkFrame(long referency);
    //lo devo togliere e usare sempre new component
    private static native void atkFrameOpened(long referency, String name, String description);
    private static native void atkFrameClosing(long referency, String description);
    private static native void atkFrameClosed(long referency, String description);
    private static native void atkFrameIconified(long referency, String description);
    private static native void atkFrameDeiconified(long referency, String description);
    private static native void atkFrameActivated(long referency, String description);
    private static native void atkFrameDeactivated(long referency, String description);

    //setting of C object
    private static native long newAtkComponent(long father);
    private static native long newAtkActionComponent(long father);
    private static native long newAtkAction(long father);
    private static native void setName(long referency, String name);
    private static native void setDescription(long referency, String description);
    private static native void setRole(long referency, String role);
    private static native void setStates(long referency, String states);
    private static native void setBound(long referency, int x, int y, int width, int height);
    private static native void setActionBound(long referency, int x, int y, int width, int height);
    private static native void setActionDescription(long refency, String description);

//hashmap chiave oggetto java valore nodo dell'albero al cui interno ci sta il riferimento C
    private TreeNode<Long> hierarchical = null;
    private long referency = 0;
    private HashMap<AccessibleContext,TreeNode> hashReferency = null;

	public ATKWindowEventListener(long root) {
        super();
        hierarchical = new TreeNode<Long> (newAtkComponent(root));
        referency = hierarchical.getData().longValue();
        hashReferency = new HashMap<AccessibleContext,TreeNode> ();
        System.err.println("the refency of the AtkRoot: "+root+" the referency of the AtkWindows: "+referency);
    }

    void createChildren(AccessibleContext ac, TreeNode<Long> father){
        TreeNode<Long> child = null;
        long childReferency = 0;
        long fatherReferency = father.getData().longValue();
        String name = ac.getAccessibleName();
        String description = ac.getAccessibleDescription();
        String accessibleRole = ac.getAccessibleRole().toString();
        String states = ac.getAccessibleStateSet().toString();
        states = states.replace("[","");
        states = states.replace("]","");
        int nchild = ac.getAccessibleChildrenCount();

        AccessibleAction action = null;
        if ( (action = ac.getAccessibleAction()) != null ){
            AccessibleComponent component = null;
            if( (component = ac.getAccessibleComponent() )!= null ){
                //ActionComponent
                childReferency = newAtkActionComponent(fatherReferency);
                Rectangle bound = component.getBounds();
                int height = (int) bound.getHeight();
                int width = (int) bound.getWidth();
                int x = (int) bound.getX();
                int y = (int) bound.getY();
                setActionBound(childReferency, x, y, width, height);
            }
            else{//Action
                childReferency = newAtkAction(fatherReferency);
            }
            int count = action.getAccessibleActionCount();
            for ( int i = 0; i < count; i++ ) {
                String actionDescription = action.getAccessibleActionDescription(i);
                setActionDescription(childReferency, actionDescription);
            }
        }
        AccessibleComponent component = null;
        if( (component = ac.getAccessibleComponent() )!= null){
            //Component
            childReferency = newAtkComponent(fatherReferency);
            Rectangle bound = component.getBounds();
            int height = (int) bound.getHeight();
            int width = (int) bound.getWidth();
            int x = (int) bound.getX();
            int y = (int) bound.getY();
            setBound(childReferency, x, y, width, height);
        }
        child = father.addChild(new Long(childReferency));
        /*
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
        }*/
        hashReferency.put(ac,child);
        if ( nchild > 0 ){
            for ( int i =0; i < nchild ;i++ ){
                AccessibleContext childContext = ac.getAccessibleChild(i).getAccessibleContext();
                createChildren(childContext, child);
            }
        }
    }

    @Override
    public void windowOpened(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            hashReferency.put(ac,hierarchical);
            int nchild = ac.getAccessibleChildrenCount();
            String name = ac.getAccessibleName();
            String description = ac.getAccessibleDescription();
            String accessibleRole = ac.getAccessibleRole().toString();
            atkFrameOpened(referency, name, description);
            setRole(referency,accessibleRole);
            AccessibleComponent component = null;
            if( (component = ac.getAccessibleComponent() )!= null){
                Rectangle bound = component.getBounds();
                int height = (int) bound.getHeight();
                int width = (int) bound.getWidth();
                int x = (int) bound.getX();
                int y = (int) bound.getY();
                setBound(referency, x, y, width, height);
            }
            String states = ac.getAccessibleStateSet().toString();
            states = states.replace("[","");
            states = states.replace("]","");
            setStates(referency, states);
            for (int i =0; i<nchild;i++){
                AccessibleContext childContext = ac.getAccessibleChild(i).getAccessibleContext();
                createChildren(childContext, hierarchical);
            }

        }
    }

    @Override
    public void windowClosing(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            //search and extract the information
            String description= ac.getAccessibleDescription();
            atkFrameClosing(referency, description);
        }
    }

    @Override
    public void windowClosed(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameClosed(referency, description);
        }
    }

    @Override
    public void windowIconified(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameIconified(referency, description);
        }
    }

    @Override
    public void windowDeiconified(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameDeiconified(referency, description);
        }
    }

    @Override
    public void windowActivated(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameActivated(referency, description);
        }
    }

    @Override
    public void windowDeactivated(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameDeactivated(referency, description);
        }
    }

    @Override
    protected void finalize() throws Throwable {
    	//when the Garbage collector destroy this object destroy also the C object
    	super.finalize();
    	freeAtkFrame(referency);
    }
}
