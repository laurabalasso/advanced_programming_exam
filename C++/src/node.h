#include <iostream>
#include <utility>
#include <memory>

template <class T1, class T2>

struct Node{

    std::pair<const T1,T2> np;
    std::unique_ptr<Node<T1,T2>> left;
    std::unique_ptr<Node<T1,T2>> right;
    Node* parent;

    Node(const std::pair<T1,T2>& pair, Node* p):
    np{pair},
    left{nullptr},
    right{nullptr},
    parent{p}{}
    Node(const std::pair<T1,T2>& pair):
    np{pair},
    left{nullptr},
    right{nullptr},
    parent{nullptr}{}
    Node(const std::pair<T1,T2>& pair,Node* l,Node* r,Node* p):
    np{pair},
    left{l},
    right{r},
    parent{p}{}
    
    ~Node() noexcept = default;

};
