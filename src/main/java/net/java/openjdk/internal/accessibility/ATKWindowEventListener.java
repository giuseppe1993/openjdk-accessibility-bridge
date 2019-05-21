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

import java.awt.Dimension;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import java.util.HashMap;
import java.lang.Number;

import javax.accessibility.Accessible;
import javax.accessibility.AccessibleContext;
import javax.accessibility.AccessibleAction;
import javax.accessibility.AccessibleComponent;
import javax.accessibility.AccessibleValue;
import javax.accessibility.AccessibleSelection;
import javax.accessibility.AccessibleRelationSet;
import javax.accessibility.AccessibleStateSet;
import javax.accessibility.AccessibleRole;


public class ATKWindowEventListener implements WindowListener {

    private static native long newAtkComponent (long father);
    private static native long newAtkAction (long father);
    private static native long newAtkActionComponent (long father);
    private static native long newAtkActionComponentValue (long father);
    private static native void setRole (long object, String role);
    private static native void setName (long object, String name);
    private static native void setDescription (long object, String description);
    private static native void setStates (long object, String states);
    private static native void setBound (long object, int x, int y, int width, int height);
    private static native void setActionBound (long object, int x, int y, int width, int height);
    private static native void setLayer(long object, String role);
    private static native void setActionLayer(long object, String role);
    private static native void saveCallReference(long object, AccessibleAction action);
    private static native int addAction (long object, String name, String description, String keybinding, String localizedname);
    private static native void setMax (long object, double max);
    private static native void setMin (long object, double min);
    private static native void setCurrent (long object, double current);

    private static native void atkFrameClosing(long frameReference, String description);
    private static native void atkFrameClosed(long frameReference, String description);
    private static native void atkFrameIconified(long frameReference, String description);
    private static native void atkFrameDeiconified(long frameReference, String description);
    private static native void atkFrameActivated(long frameReference, String description);
    private static native void atkFrameDeactivated(long frameReference, String description);

    private long frameReference, rootReferecy;
    TreeNode<Long> JavaRoot = null;
    HashMap<AccessibleContext,TreeNode> status = null;

	public ATKWindowEventListener(long root) {
        super();
        rootReferecy = root;
        frameReference = newAtkComponent(root);
        JavaRoot = new TreeNode<Long>(frameReference);
        status = new HashMap<AccessibleContext,TreeNode>();
        System.err.println("J Mediator Root reference: "+root+" Java Frame Root: "+frameReference);
    }

    @Override
    public void windowOpened(WindowEvent e) {
        Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            int nchild = ac.getAccessibleChildrenCount();

            if (status.containsKey(ac)){
                TreeNode<Long> position = status.get(ac);
                System.err.println("J already contains: "+position.getData().longValue());
                if ( nchild > 0 ){
                    for ( int i =0; i < nchild ;i++ ){
                        AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                        createChildren(child, position);
                    }
                }
            }
            else{
                Accessible father = ac.getAccessibleParent();
                if (father == null){
                    status.put(ac,JavaRoot);
                    String name = ac.getAccessibleName();
                    String description = ac.getAccessibleDescription();
                    String accessibleRole = ac.getAccessibleRole().toString();
                    setRole (frameReference, accessibleRole);
                    setName (frameReference, name);
                    setDescription (frameReference, description);
                    setName (rootReferecy, name);
                    setDescription (rootReferecy, description);
                    AccessibleComponent component = null;
                    if( (component = ac.getAccessibleComponent() )!= null){
                        Point position = component.getLocationOnScreen();
                        int x = (int) position.getX();
                        int y = (int) position.getY();
                        Dimension dim = component.getSize();
                        int height = (int) dim.getHeight();
                        int width = (int) dim.getWidth();
                        setBound (frameReference, x, y, width, height);
                        setLayer (frameReference, accessibleRole);
                    }
                    String states = ac.getAccessibleStateSet().toString();
                    states = states.replace("[","");
                    states = states.replace("]","");
                    setStates (frameReference, states);

                    if ( nchild > 0 ){
                        for ( int i =0; i < nchild ;i++ ){
                            AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                            createChildren(child, JavaRoot);
                        }
                    }
                }
                else{
                    AccessibleContext fatherContext = father.getAccessibleContext();
                    TreeNode<Long> fatherReference = status.get(fatherContext);
                    System.err.println("J ac toString(): "+ac.toString());
                    createChildren(ac, fatherReference);
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
            atkFrameClosing(frameReference, description);
        }
    }

    @Override
    public void windowClosed(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameClosed(frameReference, description);
        }
    }

    @Override
    public void windowIconified(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            /*Point position = ac.getAccessibleComponent().getLocation();
            AccessibleStateSet states = ac.getAccessibleStateSet();
            int nchild = ac.getAccessibleChildrenCount();
            AccessibleRole accessibleRole = ac.getAccessibleRole();
            System.err.println("Java Root role: "+accessibleRole.toString()+"\nhave this states: ["+
            states.toString()+"] the position is: [x="+position.getX()+" y="+
            position.getY()+"]\nthe numeber of child is:"+nchild+"\n");
            System.err.println("\nJava Root name is :'"+ac.getAccessibleName()+"' have this description:'"+
            ac.getAccessibleDescription()+"'\nhave this role: "+
            accessibleRole.toString()+"\nhave this states: ["+
            states.toString()+"]\nthe numeber of child is:"+nchild);
            AccessibleAction action = null;
            if ( (action = ac.getAccessibleAction()) != null ){
             int count = action.getAccessibleActionCount();
             System.err.println("Implement Java Action and have "+count+" actions:[");
             for ( int i = 0; i < count; i++ ) {
               String actionDescription = action.getAccessibleActionDescription(i);
             System.err.println("\tAction n. "+i+" description: "+actionDescription);
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
             System.err.println("Implement Java Relation Set interface and have this toString() method :["+relationSet.toString()+"]");
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
           }*/
            atkFrameIconified(frameReference, description);
        }
    }

    @Override
    public void windowDeiconified(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameDeiconified(frameReference, description);
        }
    }

    @Override
    public void windowActivated(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameActivated(frameReference, description);
        }
    }

    @Override
    public void windowDeactivated(WindowEvent e) {
    	Object frame = e.getSource();
        if (frame instanceof Accessible) {
            Accessible accessibleFrame = (Accessible) frame;
            AccessibleContext ac = accessibleFrame.getAccessibleContext();
            String description= ac.getAccessibleDescription();
            atkFrameDeactivated(frameReference, description);
        }
    }

    void createChildren (AccessibleContext ac, TreeNode<Long> father){
        String name = ac.getAccessibleName();
        if (name == null || name.equals(""))
            name=ac.getClass().getSimpleName();
        String description = ac.getAccessibleDescription();
        if (description == null)
            description = "";
        String accessibleRole = ac.getAccessibleRole().toString();
        int nchild = ac.getAccessibleChildrenCount();
        String states = ac.getAccessibleStateSet().toString();
        states = states.replace("[","");
        states = states.replace("]","");
        TreeNode<Long> reference = bindingAtkInterfaces (ac ,father, accessibleRole);
        long childReference = reference.getData().longValue();
        status.put(ac, reference);
        setRole (childReference, accessibleRole);
        setName (childReference, name);
        setDescription (childReference, description);
        setStates (childReference, states);
        if ( nchild > 0 ){
            for ( int i =0; i < nchild ;i++ ){
                AccessibleContext child = ac.getAccessibleChild(i).getAccessibleContext();
                createChildren(child ,reference);
            }
        }
    }

    private TreeNode<Long> bindingAtkInterfaces (AccessibleContext ac, TreeNode<Long> fatherReference, String role){
        long reference = 0;
        long father = fatherReference.getData().longValue();
        TreeNode<Long> nodeReference = null;
        AccessibleAction action = null;
        AccessibleComponent component = null;
        AccessibleValue value = null;
        AccessibleRelationSet relationSet = null;
        if ( (action = ac.getAccessibleAction()) != null ){

            if ( (component = ac.getAccessibleComponent() )!= null){

                if ( (value = ac.getAccessibleValue() ) != null){
                    reference = newAtkActionComponentValue(father);
                    Number currentValue = value.getCurrentAccessibleValue();
                    Number maxValue = value.getMaximumAccessibleValue();
                    Number minValue = value.getMinimumAccessibleValue();
                    setMax (reference, maxValue.doubleValue());
                    setMin (reference, minValue.doubleValue());
                    setCurrent (reference, currentValue.doubleValue());
                }
                else
                    reference = newAtkActionComponent(father);

                int x = 0;
                int y = 0;
                int height = 0;
                int width = 0;
                Point position = component.getLocationOnScreen();
                if (position != null){
                    x = (int) position.getX();
                    y = (int) position.getY();
                    Dimension dim = component.getSize();
                    if (dim != null){
                        height = (int) dim.getHeight();
                        width = (int) dim.getWidth();
                    }
                }
                setActionBound (reference, x, y, width, height);
                setActionLayer (reference, role);
            }
            else
                reference = newAtkAction(father);

            int count = action.getAccessibleActionCount();
            saveCallReference (reference, action);
            for ( int i = 0; i < count; i++ ) {
                String description = action.getAccessibleActionDescription(i);
                addAction (reference, "", description, "", "");
            }
        }
        else
            if( (component = ac.getAccessibleComponent() )!= null){
                reference = newAtkComponent(father);
                int x = 0;
                int y = 0;
                int height = 0;
                int width = 0;
                Point position = component.getLocationOnScreen();
                if (position != null){
                    x = (int) position.getX();
                    y = (int) position.getY();
                    Dimension dim = component.getSize();
                    if (dim != null){
                        height = (int) dim.getHeight();
                        width = (int) dim.getWidth();
                    }
                }
                setBound (reference, x, y, width, height);
                setLayer (reference, role);
            }
        nodeReference = new TreeNode<Long> (reference);
        return nodeReference;
    }

    void printInformation(AccessibleContext ac){
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
          System.err.println("Implement Java Relation Set interface and have this toString() method :["+relationSet.toString()+"]");
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
                printInformation(child);
            }
        }
    }

}
