#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
    T data;
    // this holds the actual value stored in the node
    // for polynomials this is a Term
    // for general bst this can be anything

    Node<T> *left;
    // pointer to left child
    // everything smaller goes here

    Node<T> *right;
    // pointer to right child
    // everything bigger goes here

public:
    Node();
    Node(T data);
    // constructor sets data and nulls children

    T &getData();
    // return reference to data so caller can modify the real stored value
    // needed for polynomial merging and updates

    Node<T> *&getLeft();
    // return reference to left pointer so bst insert and remove can rewire it

    Node<T> *&getRight();
    // return reference to right pointer same reason as above

    void setLeft(Node<T> *left);
    // set left child pointer

    void setRight(Node<T> *right);
    // set right child pointer
};
template <typename T>
Node<T>::Node()
{
    left = nullptr;
    right = nullptr;
}

template <typename T>
Node<T>::Node(T data)
{
    this->data = data;
    // store the value passed in

    this->left = nullptr;
    // no left child yet

    this->right = nullptr;
    // no right child yet
}

template <typename T>
T &Node<T>::getData()
{
    // return actual data not a copy
    // this lets caller change the stored value directly
    return data;
}

template <typename T>
Node<T> *&Node<T>::getLeft()
{
    // return reference to left pointer
    // bst insert needs this to attach new nodes
    return left;
}

template <typename T>
Node<T> *&Node<T>::getRight()
{
    // return reference to right pointer
    // same reason as getLeft
    return right;
}

template <typename T>
void Node<T>::setLeft(Node<T> *left)
{
    // assign left child pointer
    this->left = left;
}

template <typename T>
void Node<T>::setRight(Node<T> *right)
{
    // assign right child pointer
    this->right = right;
}

#endif
