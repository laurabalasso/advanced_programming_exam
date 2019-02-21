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

    void insert(T1 key, T2 value,Node<T1,T2>* leaf,int level);
    void recursiveInsert(Node<T1,T2>* leaf);
    void print(Node<T1,T2>* leaf);
    
    public:

    BST();
    BST(BST &&bst) noexcept;
    ~BST() noexcept;
    BST<T1,T2>& operator=(const BST<T1,T2>&& bst) noexcept;

    
    Node<T1,T2>*  begin();
    const Node<T1,T2>* cbegin();
    Node<T1,T2>*  end();
    const Node<T1,T2>* cend();
    void insert(T1 key,T2 value);
    void print();

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
 function that returns the pointer to the first node
 */
Node<T1,T2>* BST<T1,T2>::begin(){
    return root;
}

template <typename T1, typename T2>
/**
 function that reutrn a const pointer to the first node
 */
const Node<T1,T2>* BST<T1,T2>::cbegin(){
    return(const_cast<const Node<T1,T2>*>(root));
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

template <typename T1, typename T2>
/**
 method that allows you to insert a node inside a binary search tree in a recursive way
 */
void BST<T1,T2>::insert(T1 key, T2 value,Node<T1,T2>* leaf, int level){
    
    if(key< leaf->node_pair.first){     //if the key is smaller than then the key of the actual node
        
        if(leaf->left!=nullptr){        //if the actual node has a left child
            level++;
            insert(key,value,(leaf->left),level);
        }
        else{                           //if the actual node doesn't have a left child
            leaf->left=new Node<T1,T2>;
            leaf->left->node_pair.first=key;
            leaf->left->node_pair.second=value;
            leaf->left->left=nullptr;
            leaf->left->right=nullptr;
            n_nodes++;
            if(level>=height){
                height=level;
                tail = leaf->left;
            }
        }
    }
    else if(key>leaf->node_pair.first){     //if the key is bigger than then the key of the actual node
        
        if(leaf->right!=nullptr){           //if the actual node has a right child
            level++;
            insert(key,value,leaf->right,level);
        }
        else{                               //if the actual node doesn't have a right child
            leaf->right=new Node<T1,T2>;
            leaf->right->node_pair.first=key;
            leaf->right->node_pair.second=value;
            leaf->right->left=nullptr;
            leaf->right->right=nullptr;
            n_nodes++;
            if(level>=height){
                level=height;
                tail = leaf->right;
            }
        }
    }
}
template <typename T1, typename T2>
/**
 overloading of the insert method, in order to pass only two parameters to it: key and value of the new node.
 */
void BST<T1,T2>::insert(T1 key,T2 value){
    
    if(root == nullptr){           //if the tree is empty
        root = new Node<T1,T2>{std::make_pair(key,value),nullptr,nullptr};
        n_nodes++;
        height++;
    }
    else{                          //if the tree is not empty
        insert(key,value, begin(),this->height);
    }
    
    
}

template <typename T1, typename T2>
/**
 method used to implement the copy semantic, that exploits the insert function.
 */
void BST<T1,T2>::recursiveInsert(Node<T1,T2>* leaf){
    
    if(leaf != nullptr){
        insert(leaf->node_pair.first,leaf->node_pair.second);
        recursiveInsert(leaf->left);
        insert(leaf->node_pair.first,leaf->node_pair.second);
        recursiveInsert(leaf->right);
    }
}

template <typename T1, typename T2>
/**
 recursive method that prints the tree in-order
 */
void BST<T1,T2>::print(Node<T1,T2>* leaf){
    
    if(n_nodes==0){             //if the tree is empty
        std::cout<<"empty tree"<<std::endl;
    }
    else if(leaf!=nullptr){     //if the tree is not empty
        print(leaf->left);
        std::cout<< leaf<<std::endl;
        print(leaf->right);
    }
}

template <typename T1, typename T2>
/**
 overloading of print method
 */
void BST<T1,T2>::print(){
    
    print(begin());
}

#endif
