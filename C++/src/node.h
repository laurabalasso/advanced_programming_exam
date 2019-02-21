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
    template <class t, class u>
    friend std::ostream& operator<<(std::ostream& os, const Node<t,u>* node);
    ~Node(){};
};

template <class t, class u>
/**
 overloading the operator<< in order to print key:value of a node
 */
std::ostream& operator<<(std::ostream& os, const Node<t,u>* node){
    
    os<<"( key: "<<node->node_pair.first<<", value: "<<node->node_pair.second<<" )";
    return os;
}


#endif
