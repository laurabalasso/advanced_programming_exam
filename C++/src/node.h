/**
    node.h
    object: define a Node struct that represents a single node of a binary search tree
*/

#ifndef __node__
#define __node__

#include <utility>

template <typename T1, typename T2>
 
struct Node{
    std::pair<T1,T2> node_pair;
    Node<T1,T2>* left;
    Node<T1,T2>* right;
    ~Node(){};
};
 
#endif