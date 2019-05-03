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

import com.sun.java.accessibility.util.EventQueueMonitor;
import com.sun.java.accessibility.util.SwingEventMonitor;

public class AccessBridge {

    private static native long initATK();
    private static native void runMainLoopATK();
    private static native void stopMainLoopATK();
    private static native void freeATK();
    private static long atkRoot;
    private static Thread mainloop;

    static {
        System.loadLibrary("OpenJDKAccessBridge");
        atkRoot = initATK();
        mainloop = new Thread(new Runnable() {
            public void run(){
                runMainLoopATK();
            }
        });
        mainloop.start();
        System.err.println("the refency of the AtkRoot: "+atkRoot);
    }

    public AccessBridge() {
        EventQueueMonitor.isGUIInitialized();
        SwingEventMonitor.addWindowListener(new ATKWindowEventListener(atkRoot));
    }

    @Override
    protected void finalize() throws Throwable {
      //when the Garbage collector destroy this object destroy also the C object
      super.finalize();
      //I don't know if it is enought
      stopMainLoopATK();
      //maybe it's too much
      mainloop.stop();
      mainloop.destroy();
      freeATK();
    }
}
