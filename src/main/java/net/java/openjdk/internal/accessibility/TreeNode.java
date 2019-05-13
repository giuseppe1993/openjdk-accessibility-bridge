package net.java.openjdk.internal.accessibility;

import java.util.ArrayList;
import java.util.List;

public class TreeNode<T>{

    private T data;
    private TreeNode<T> parent;
    private List<TreeNode<T>> children;

    public TreeNode(T data) {
       this.data = data;
       this.parent = null;
       this.children = new ArrayList<TreeNode<T>>();
   }

   public TreeNode<T> addChild(T child) {
       TreeNode<T> childNode = new TreeNode<T>(child);
       childNode.parent = this;
       this.children.add(childNode);
       return childNode;
   }

   public TreeNode<T> addChild(TreeNode<T> child) {
       child.parent = this;
       this.children.add(child);
       return child;
   }

   public void addChildren(List<TreeNode<T>> children) {
    children.forEach(each -> each.setParent(this));
    this.children.addAll(children);
    }

    public List<TreeNode<T>> getChildren() {
        return children;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    private void setParent(TreeNode<T> parent) {
        this.parent = parent;
    }

    public TreeNode<T> getParent() {
        return parent;
    }
}
