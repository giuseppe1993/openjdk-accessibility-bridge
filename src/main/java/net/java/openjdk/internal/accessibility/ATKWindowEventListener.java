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

import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.accessibility.Accessible;
import javax.accessibility.AccessibleContext;

public class ATKWindowEventListener implements WindowListener {
	
	private static native long initAtkWindows();
	private static native void freeAtkWindows(long cObject);
	private static native void atkWindowOpened(long cObject, String description);
	private static native void atkWindowClosing(long cObject, String description);
	private static native void atkWindowClosed(long cObject, String description);
	private static native void atkWindowIconified(long cObject, String description);
	private static native void atkWindowDeiconified(long cObject, String description);
	private static native void atkWindowActivated(long cObject, String description);
	private static native void atkWindowDeactivated(long cObject, String description);
	
	private long cObject;
	
	public ATKWindowEventListener() {
		super();
		//TODO I don't know how create new ATKWindows 
		
		cObject= initAtkWindows();
	}

    @Override
    public void windowOpened(WindowEvent e) {
        Object window = e.getSource();
        if (window instanceof Accessible) {
            Accessible accessibleWindow = (Accessible) window;
            AccessibleContext ac = accessibleWindow.getAccessibleContext();
            //TODO take all Accessibility content. 
            // I think is better to do a independent method because for every override method you need to extract the informations
            String description= ac.getAccessibleDescription();
            //TODO push all in C Object
            atkWindowOpened(cObject, description);
        }
    }

    @Override
    public void windowClosing(WindowEvent e) {
        Object window = e.getSource();
        if (window instanceof Accessible) {
            Accessible accessibleWindow = (Accessible) window;
            AccessibleContext ac = accessibleWindow.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkWindowClosing(cObject, description);
            //System.err.println("closing: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowClosed(WindowEvent e) {
    	Object window = e.getSource();
        if (window instanceof Accessible) {
            Accessible accessibleWindow = (Accessible) window;
            AccessibleContext ac = accessibleWindow.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkWindowClosed(cObject, description);
            //System.err.println("closed: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowIconified(WindowEvent e) {
    	Object window = e.getSource();
        if (window instanceof Accessible) {
            Accessible accessibleWindow = (Accessible) window;
            AccessibleContext ac = accessibleWindow.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkWindowIconified(cObject, description);
            //System.err.println("iconified: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowDeiconified(WindowEvent e) {
    	Object window = e.getSource();
        if (window instanceof Accessible) {
            Accessible accessibleWindow = (Accessible) window;
            AccessibleContext ac = accessibleWindow.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkWindowDeiconified(cObject, description);
            //System.err.println("Deiconified: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowActivated(WindowEvent e) {
    	Object window = e.getSource();
        if (window instanceof Accessible) {
            Accessible accessibleWindow = (Accessible) window;
            AccessibleContext ac = accessibleWindow.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkWindowActivated(cObject, description);
            //System.err.println("activated: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }

    @Override
    public void windowDeactivated(WindowEvent e) {
    	Object window = e.getSource();
        if (window instanceof Accessible) {
            Accessible accessibleWindow = (Accessible) window;
            AccessibleContext ac = accessibleWindow.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkWindowDeactivated(cObject, description);
            //System.err.println("deactivated: " + ac.getAccessibleDescription() + " - " + ac);
        }
    }
    
    @Override
    protected void finalize() throws Throwable {
    	//when the Garbage collector destroy this object destroy also the C object
    	super.finalize();
    	freeAtkWindows(cObject);
    }

}
