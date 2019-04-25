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

import java.awt.Point;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.accessibility.Accessible;
import javax.accessibility.AccessibleContext;
import javax.accessibility.AccessibleRole;
import javax.accessibility.AccessibleStateSet;

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
    
    private long cObject;
	
	public ATKWindowEventListener(long root) {
        super();
        cObject= initAtkFrame(root);
        System.err.println("the refency of the AtkRoot: "+root+" the referecy of the AtkWindows: "+cObject);
    }

    void printInformation(AccessibleContext ac){
        AccessibleStateSet states = ac.getAccessibleStateSet();
        int nchild = ac.getAccessibleChildrenCount();
        AccessibleRole accessibleRole = ac.getAccessibleRole();
        AccessibleRole fatherAccessibleRole= ac.getAccessibleParent().getAccessibleContext().getAccessibleRole();
        System.err.println("The child of: '"+fatherAccessibleRole.toString()+"' have this role: "+accessibleRole.toString()+"\nthis states: ["+
        states.toString()+"]\nand this numeber of child: "+nchild+"\n");
        if (nchild>0){
            for (int i =0; i<nchild;i++){
                AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                printInformation(child);
            }
        }
    }


    @Override
    public void windowOpened(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;

            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            Point position = ac.getAccessibleComponent().getLocation();
            AccessibleStateSet states = ac.getAccessibleStateSet();
            int nchild = ac.getAccessibleChildrenCount();
            AccessibleRole accessibleRole = ac.getAccessibleRole();
            System.err.println("Java Root role: "+accessibleRole.toString()+"\nhave this states: ["+
            states.toString()+"] the position is: [x="+position.getX()+" y="+
            position.getY()+"]\nthe numeber of child is:"+nchild+"\n");

            for (int i =0; i<nchild;i++){
                AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                printInformation(child);
            }
            
            //TODO take all Accessibility content. 
            // I think is better to do a independent method because for every override method you need to extract the informations
            String name = ac.getAccessibleName();
            String description = ac.getAccessibleDescription();
            //TODO push all in C Object
            atkFrameOpened(cObject, name, description);
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
