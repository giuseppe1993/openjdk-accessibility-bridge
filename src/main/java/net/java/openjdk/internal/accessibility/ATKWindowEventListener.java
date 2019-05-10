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

    private static native long newAtkComponent (long referency);
    private static native long newAtkAction (long referency);
    private static native long newAtkActionComponent (long referency);
    private static native void setRole (long object, String role);
    private static native void setName (long object, String name);
    private static native void setDescription (long object, String description);
    private static native void setStates (long object, String states);
    private static native void setBound (long object, int x, int y, int width, int height);
    private static native void setActionBound (long object, int x, int y, int width, int height);

    private static native void atkFrameClosing(long frameReferency, String description);
    private static native void atkFrameClosed(long frameReferency, String description);
    private static native void atkFrameIconified(long frameReferency, String description);
    private static native void atkFrameDeiconified(long frameReferency, String description);
    private static native void atkFrameActivated(long frameReferency, String description);
    private static native void atkFrameDeactivated(long frameReferency, String description);


    private long frameReferency, rootReferecy;

	public ATKWindowEventListener(long root) {
        super();
        rootReferecy = root;
        frameReferency = newAtkComponent(root);
        System.err.println("J Mediator Root referency: "+root+" Java Frame Root: "+frameReferency);
    }

    @Override
    public void windowOpened(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String name = ac.getAccessibleName();
            String description = ac.getAccessibleDescription();
            int nchild = ac.getAccessibleChildrenCount();
            String accessibleRole = ac.getAccessibleRole().toString();
            setRole (frameReferency, accessibleRole);
            setName (frameReferency, name);
            setDescription (frameReferency, description);
            setName (rootReferecy, name);
            setDescription (rootReferecy, description);
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

            if ( nchild > 0 ){
                for ( int i =0; i < nchild ;i++ ){
                    AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                    createChildren(child, frameReferency);
                }
            }
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
        }
    }

    void createChildren (AccessibleContext ac, long father){
        String name = ac.getAccessibleName();
        if (name == null)
            name="";
        String description = ac.getAccessibleDescription();
        if (description == null)
            description = "";
        String accessibleRole = ac.getAccessibleRole().toString();
        int nchild = ac.getAccessibleChildrenCount();
        String states = ac.getAccessibleStateSet().toString();
        states = states.replace("[","");
        states = states.replace("]","");
        long childReferency = bindingAtkInterfaces (ac ,father);
        setRole (childReferency, accessibleRole);
        setName (childReferency, name);
        setDescription (childReferency, description);
        setStates (childReferency, states);
        if ( nchild > 0 ){
            for ( int i =0; i < nchild ;i++ ){
                AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                createChildren(child ,childReferency);
            }
        }
    }

    private long bindingAtkInterfaces (AccessibleContext ac, long father){
        long referency = 0;
        AccessibleAction action = null;
        AccessibleComponent component = null;
        AccessibleSelection selection = null;
        AccessibleRelationSet relationSet = null;
        if ( (action = ac.getAccessibleAction()) != null ){
            if( (component = ac.getAccessibleComponent() )!= null){
                referency = newAtkActionComponent(father);
                Rectangle bound = component.getBounds();
                int height = (int) bound.getHeight();
                int width = (int) bound.getWidth();
                int x = (int) bound.getX();
                int y = (int) bound.getY();
                setActionBound (referency, x, y, width, height);
            }
            else
                referency = newAtkAction(father);

            int count = action.getAccessibleActionCount();
            for ( int i = 0; i < count; i++ ) {
                String description = action.getAccessibleActionDescription(i);
                System.err.println("Action n. "+i+" description: "+description);
            }
        }
        else
            if( (component = ac.getAccessibleComponent() )!= null){
                referency = newAtkComponent(father);
                Rectangle bound = component.getBounds();
                int height = (int) bound.getHeight();
                int width = (int) bound.getWidth();
                int x = (int) bound.getX();
                int y = (int) bound.getY();
                setBound (referency, x, y, width, height);
            }
        return referency;
    }

}
