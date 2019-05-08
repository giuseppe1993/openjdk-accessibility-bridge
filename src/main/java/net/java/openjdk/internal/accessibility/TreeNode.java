package net.java.openjdk.internal.accessibility;

import java.util.ArrayList;
import java.util.List;

public class TreeNode<T> {

    private T data = null;
    private TreeNode parent = null;
    private List<TreeNode<T>> children = new ArrayList<>();

    public TreeNode(T data){
        this.data = data;
    }

    public TreeNode<T> addChild(T data) {
        TreeNode<T> child = new TreeNode(data);
        child.setParent(this);
        this.children.add(child);
        return child;
    }

    public void addChildren(List<TreeNode<T>> children) {
        children.forEach(each -> each.setParent(this));
        this.children.addAll(children);
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
