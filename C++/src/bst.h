/**
    bst.h
    object: define a BST class that allows to create and manage a binary search tree, 
            in which a single node is a struct Node.
*/
#ifndef __bst__
#define __bst__

#include "node.h"
#include <vector>



template <typename T1, typename T2>

class BST{
    private:
    
    Node<T1,T2>* root;
    const Node<T1,T2>* head;
    Node<T1,T2>* tail;
    int n_nodes;
    int height;

    public:

    BST();
    BST(BST &&bst) noexcept;
    ~BST() noexcept;
    BST<T1,T2>& operator=(const BST<T1,T2>&& bst) noexcept;

    Node<T1,T2>*  end();
    const Node<T1,T2>* cend();

};

template <typename T1, typename T2>
/**
    default constructor that creates an empty binary search tree
*/
BST<T1,T2>::BST(){

    if constexpr (std::is_same<T2,std::string>::value){     //if the value is a string
        root = nullptr;
        head = new Node<T1,T2>{std::make_pair(NULL,""),root,root};
    }
    else{                                                  //if the value is not a string
        root = nullptr;
        head = new Node<T1,T2>{std::make_pair(NULL,NULL),root,root};
    }
    tail = root;
    n_nodes = 0;
    height= 0;
} 

template <typename T1, typename T2>
/**
    move constructor 
*/
BST<T1,T2>::BST(BST &&bst)  noexcept
        :root(bst.root),
        head(bst.head),
        tail(bst.tail),
        n_nodes(bst.n_nodes),
        height(bst.height)
{
    bst.head = nullptr;
    bst.root = nullptr;
    bst.tail = nullptr; 
}

template <typename T1, typename T2>
/**
    custom destructor that delete the head node when the BST goes out of scope.
*/
BST<T1,T2>::~BST()noexcept{
    
    delete(head);
}

template <typename T1, typename T2>
/**
    overloading the operator= to allow move assignment
*/
BST<T1,T2>& BST<T1,T2>::operator=(const BST<T1,T2>&& bst) noexcept { 
    
    if(&bst == this) return *this;
    clear(); 
    n_nodes = 0;
    height = 0;
    root = bst.root;
    head = bst.head;
    tail = bst.tail;
    n_nodes = bst.n_nodes;
    bst.head = nullptr;
    bst.root = nullptr;
    bst.tail = nullptr;
    return *this;
}

template <typename T1, typename T2>
/**
    function that returns a pointer to the deepest node of the tree
*/
Node<T1,T2>* BST<T1,T2>::end(){
        return tail;
}

template <typename T1, typename T2>
/**
    function that returns a const pointer to the deepest node of the tree
*/
const Node<T1,T2>* BST<T1,T2>::cend(){
        return(const_cast<const Node<T1,T2>*>(tail));
}

#endif
