// dal153159
// Osagbewonrue Ugiagbe
#ifndef BST_H
#define BST_H

#include <vector>
#include "Node.h"
#include <iostream>
#include <algorithm>

template <typename T>
class Bst
{
private:
    Node<T> *root;
    // root of the whole tree
    // null means tree is empty
    // everything starts from here

    void insert(Node<T> *&curr, const T &newT);
    // recursive insert
    // pass pointer by reference so i can actually change it
    // this is how new nodes get attached to the tree
    Node<T> *remove(const T &other);
    // public remove
    // returns new root after deletion
    Node<T> *remove(Node<T> *curr, const T &other);
    // recursive remove
    // walks down the tree and fixes links on the way back up

    T *find(Node<T> *curr, const T &other);
    // recursive find
    // standard bst search using < and ==

    T findMin(Node<T> *curr);
    // helper to get smallest value
    // go all the way left

    T findMax(Node<T> *curr);
    // helper to get biggest value
    // go all the way right

    void revInOrder(Node<T> *curr);
    // right node left
    // prints in descending order

    void InOrder(Node<T> *curr);
    // left node right
    // prints in ascending order

    void preOrder(Node<T> *curr);
    // node left right
    // good for copying structure

    void postOrder(Node<T> *curr);
    // left right node
    // good for deleting

    int findHeight(Node<T> *curr);
    // height of subtree
    // used to get height of whole tree

    void toVector(Node<T> *curr, std::vector<T> &out);
    // dump tree into vector
    // uses rev inorder so biggest first
    void deleteBst(Node<T> *&curr);
    // delete whole tree recursively
    // used by destructor

public:
    Bst();
    // constructor
    // start with empty tree

    ~Bst();
    // destructor
    // delete everything from heap
    Bst(int ignore);
    T *find(const T &other);
    // public find
    // user calls this instead of touching root

    T findMin();
    // public min
    // throws if tree empty
    void mainremove(const T &other);

    T findMax();
    // public max
    // throws if tree empty

    int findHeight();
    // public height
    // height of whole tree

    void insert(const T &newT) { insert(root, newT); }
    // public insert
    // always starts at root
    void preOrder();
    void postOrder();
    void InOrder();
    void revInOrder();
    // public traversal wrappers
    // just call the private ones starting at root

    std::vector<T> toVector();
    // convert whole tree to vector
    // used for polynomial printing
};

template <typename T>
Bst<T>::Bst()
{
    this->root = nullptr;
    // tree starts empty
}

template <typename T>
Bst<T>::~Bst()
{
    deleteBst(root);
    // free all nodes
}

template <typename T>
Bst<T>::Bst(int ignore)
{
    this->root = nullptr;
}
template <typename T>
std::vector<T> Bst<T>::toVector()
{
    std::vector<T> out;
    // empty vector to fill

    toVector(root, out);
    // fill vector from tree

    return out;
}

template <typename T>
void Bst<T>::insert(Node<T> *&curr, const T &newT)
{
    if (curr == nullptr)
    {
        // found null spot
        // this is where new node goes
        curr = new Node<T>(newT);
        return;
    }

    if (newT == curr->getData())
    {
        // generic bst no duplicates
        // for polynomials i handle combining outside
        return;
    }
    else if (newT < curr->getData())
    {
        // go left side
        insert(curr->getLeft(), newT);
    }
    else
    {
        // go right side
        insert(curr->getRight(), newT);
    }
}
template <typename T>
void Bst<T>::mainremove(const T &other)
{
    remove(other);
}
template <typename T>
Node<T> *Bst<T>::remove(const T &other)
{
    // wrapper so user does not pass root directly
    root = remove(root, other);
    // root might change after deletion
    return root;
}

template <typename T>
Node<T> *Bst<T>::remove(Node<T> *curr, const T &other)
{
    if (!curr)
    {
        // not found
        // nothing to delete
        return nullptr;
    }

    if (other < curr->getData())
    {
        // target is smaller
        // search left subtree
        curr->getLeft() = remove(curr->getLeft(), other);
        return curr;
    }

    if (other > curr->getData())
    {
        // target is bigger
        // search right subtree
        curr->getRight() = remove(curr->getRight(), other);
        return curr;
    }

    // if we reach here we found the node to delete

    if (curr->getRight() == nullptr && curr->getLeft() == nullptr)
    {
        // case leaf node
        // no children just delete
        delete curr;
        return nullptr;
    }

    if (curr->getRight() == nullptr)
    {
        // only left child
        // promote left child
        Node<T> *tmp = curr->getLeft();
        delete curr;
        return tmp;
    }

    if (curr->getLeft() == nullptr)
    {
        // only right child
        // promote right child
        Node<T> *tmp = curr->getRight();
        delete curr;
        return tmp;
    }

    // two children case
    // use inorder successor from right subtree
    Node<T> *successor = curr->getRight();
    while (successor->getLeft() != nullptr)
    {
        // go all the way left in right subtree
        successor = successor->getLeft();
    }

    // copy successor data into current node
    curr->getData() = successor->getData();

    // now delete successor node from right subtree
    curr->getRight() = remove(curr->getRight(), successor->getData());

    return curr;
}

template <typename T>
void Bst<T>::preOrder()
{
    // public wrapper
    preOrder(root);
}

template <typename T>
void Bst<T>::postOrder()
{
    // public wrapper
    postOrder(root);
}

template <typename T>
void Bst<T>::postOrder(Node<T> *curr)
{
    // left right node
    if (!curr)
        return;

    postOrder(curr->getLeft());
    postOrder(curr->getRight());
    std::cout << curr->getData() << std::endl;
}

template <typename T>
void Bst<T>::preOrder(Node<T> *curr)
{
    // node left right
    if (!curr)
        return;

    std::cout << curr->getData() << std::endl;
    preOrder(curr->getLeft());
    preOrder(curr->getRight());
}

template <typename T>
int Bst<T>::findHeight()
{
    // height of whole tree
    return findHeight(root);
}

template <typename T>
int Bst<T>::findHeight(Node<T> *curr)
{
    if (!curr)
    {
        // empty subtree
        // height is -1 by convention
        return -1;
    }

    int leftH = findHeight(curr->getLeft());
    // height of left side

    int rightH = findHeight(curr->getRight());
    // height of right side

    return 1 + std::max(leftH, rightH);
    // height is 1 plus max of children
}

template <typename T>
T Bst<T>::findMin(Node<T> *curr)
{
    if (!curr)
    {
        // no nodes
        std::cout << "tree is empty" << std::endl;
        return T();
    }

    // keep going left until we cannot
    while (curr->getLeft() != nullptr)
    {
        curr = curr->getLeft();
    }
    return curr->getData();
}

template <typename T>
T Bst<T>::findMin()
{
    // public wrapper
    return findMin(root);
}

template <typename T>
T Bst<T>::findMax(Node<T> *curr)
{
    if (!curr)
    {
        // no nodes
        std::cout << "tree is empty" << std::endl;
        return T();
    }

    // keep going right until we cannot
    while (curr->getRight() != nullptr)
    {
        curr = curr->getRight();
    }
    return curr->getData();
}

template <typename T>
T Bst<T>::findMax()
{
    // public wrapper
    return findMax(root);
}

template <typename T>
T *Bst<T>::find(const T &other)
{
    // public wrapper
    return find(root, other);
}

template <typename T>
T *Bst<T>::find(Node<T> *curr, const T &other)
{
    if (!curr)
    {
        // hit null
        // not found
        return nullptr;
    }
    else if (curr->getData() == other)
    {
        // found match
        return &curr->getData();
    }
    else if (other < curr->getData())
    {
        // search left
        return find(curr->getLeft(), other);
    }
    else
    {
        // search right
        return find(curr->getRight(), other);
    }
}

template <typename T>
void Bst<T>::deleteBst(Node<T> *&curr)
{
    // post order delete
    // delete children before node
    if (curr == nullptr)
        return;

    deleteBst(curr->getLeft());
    deleteBst(curr->getRight());
    delete curr;
    curr = nullptr;
}

template <typename T>
void Bst<T>::toVector(Node<T> *curr, std::vector<T> &out)
{
    if (!curr)
        return;

    // right first so biggest values go first
    toVector(curr->getRight(), out);

    // push current node data
    out.push_back(curr->getData());

    // then left side
    toVector(curr->getLeft(), out);
}

template <typename T>
void Bst<T>::InOrder()
{
    // public wrapper
    InOrder(root);
}

template <typename T>
void Bst<T>::InOrder(Node<T> *curr)
{
    if (!curr)
        return;

    // left node right
    InOrder(curr->getLeft());
    std::cout << curr->getData() << std::endl;
    InOrder(curr->getRight());
}

template <typename T>
void Bst<T>::revInOrder()
{
    // public wrapper
    revInOrder(root);
}

template <typename T>
void Bst<T>::revInOrder(Node<T> *curr)
{
    if (!curr)
        return;

    // right node left
    revInOrder(curr->getRight());
    std::cout << curr->getData() << std::endl;
    revInOrder(curr->getLeft());
}

#endif
