#include "node.h"
#include <vector>

template <class T1,class T2>

class BST{

    public:

    class Iterator;
    class ConstIterator;
    

    private:

    std::unique_ptr<Node<T1,T2>> root;
    void insert(const std::pair<T1,T2>& p,Node<T1,T2>* leaf);
    void recursiveInsert(std::unique_ptr<Node<T1, T2>>& node);
    Iterator find(const T1& key , Node<T1, T2>* node) const noexcept;

    public:
    

    BST() = default;
    ~BST() noexcept = default;
    BST(BST& bst){recursiveInsert(bst.root);}
    BST(BST&& bst) noexcept
    :root{std::move(bst.root)}{std::cout<<"Move constructor called"<<std::endl;};
    BST& operator=(const BST& bst){
        clear();
        recursiveInsert(bst.root);
        return *this;
    }
    BST& operator=(BST&& bst) noexcept{
        std::cout<<"Move assignment called"<<std::endl;
        root = std::move(bst.root);
        return *this;
    }
    void clear() noexcept;
    void insert(const std::pair<T1,T2>& p);
    void balance();
    void balance(std::vector<std::pair<const T1,T2>>& cmd,size_t start,size_t end);
    Iterator find(const T1& key) const noexcept;
    Iterator begin();
    Iterator begin() const;
    Iterator end(){return Iterator{};};
    Iterator end() const {return Iterator{};};
    
    ConstIterator cbegin() const;
    ConstIterator cend() const{return ConstIterator{};};

};
template <class T1, class T2>
class BST<T1,T2>::Iterator{
    
    private:

    Node<T1,T2>* current;
    
    public:

    Iterator(Node<T1,T2>* c): current{c}{}
    Iterator(): current{nullptr}{}
    std::pair<const T1,T2>& operator*() const {return current->np;}
    Iterator& operator++(){
        if(current->right!=nullptr){
            current = current->right.get();
            while(current->left!=nullptr){
                current = current->left.get();
            }
        }
        else{
            const T1 key = current->np.first;
            while(current!=nullptr && key >= current->np.first){
                current = current->parent;
            }
        }
        return *this;
    }
    bool operator==(const Iterator& cmd){return current==cmd.current;}
    bool operator!=(const Iterator& cmd){return !(current==cmd.current);}
};

template <class T1, class T2>
class BST<T1,T2>::ConstIterator : public BST<T1,T2>::Iterator{
    public:
    
    const std::pair<const T1,T2>& operator*() const {return BST<T1,T2>::Iterator::operator*();}
};


template <typename T1,typename T2>
void BST<T1,T2>::recursiveInsert(std::unique_ptr<Node<T1, T2>>& node){
    if(node){
        insert(node->np);
        recursiveInsert(node->left);
        insert(node->np);
        recursiveInsert(node->right);
    }
}


template <typename T1,typename T2>
typename BST<T1,T2>::Iterator  BST<T1,T2>::begin(){
    if(root == nullptr) return root.get();
    Node<T1,T2>* p = root.get();
    while(p->left!=nullptr){
        p = p->left.get();
    }
    return(Iterator{p});
}
template <typename T1,typename T2>
typename BST<T1,T2>::Iterator  BST<T1,T2>::begin() const{
    if(root == nullptr) return root.get();
    Node<T1,T2>* p = root.get();
    while(p->left!=nullptr){
        p = p->left.get();
    }
    return(Iterator{p});
}
template <class T1,class T2>
typename BST<T1,T2>::ConstIterator BST<T1,T2>::cbegin() const{
    if(root = nullptr) return root.get();
    auto p = root.get();
    while(p->left!=nullptr){
        p = p->left.get();
    }
    return(ConstIterator{p});
}
template <class T1,class T2>
void BST<T1,T2>::clear() noexcept{
    std::cout<<"All the nodes inside the BST will be cleared"<<std::endl;
    root.reset();
}
template <class T1,class T2>
void BST<T1,T2>::insert(const std::pair<T1,T2>& p,Node<T1,T2>* leaf){
    if(p.first < leaf->np.first){     //if the key is smaller than then the key of the actual node
        
        if(leaf->left!=nullptr){        //if the actual node has a left child
            insert(p,leaf->left.get());
        }
        else{                           //if the actual node doesn't have a left child
            leaf->left.reset(new Node<T1,T2>{p,nullptr,nullptr,leaf});
            return;
        }
    }
    else if(p.first > leaf->np.first){     //if the key is bigger than then the key of the actual node
        
        if(leaf->right!=nullptr){           //if the actual node has a right child
            insert(p,leaf->right.get());
        }
        else{                               //if the actual node doesn't have a right child
            leaf->right.reset(new Node<T1,T2>{p,nullptr,nullptr,leaf});
            return;
        }
    }
}
template <class T1,class T2>
void BST<T1,T2>::insert(const std::pair<T1,T2>& p){
    if(!root){
        root.reset(new Node<T1,T2>{p,nullptr,nullptr,nullptr});
    }
    else insert(p,root.get());
}
template <class T1,class T2>
void BST<T1,T2>::balance(){
    if(!root) {
        std::cout<<"The tree is empty, you cannot balance it"<<std::endl;
        return;
    }
    std::cout<<"The tree will be balanced"<<std::endl;
    std::vector<std::pair<const T1,T2>> cmd;
    Iterator it{begin()};
    for(;it != end();++it)
        cmd.push_back(*it);
    clear();
    balance(cmd,0,cmd.size());
    std::cout<<"Tree correctly balanced"<<std::endl;

}
template <class T1,class T2>
void BST<T1,T2>::balance(std::vector<std::pair<const T1,T2>>& cmd, size_t begin, size_t end){
    if(end - begin < 1) return;
    size_t mid =(begin+end)/2;
    insert(cmd[mid]);
    balance(cmd,begin,mid);
    balance(cmd,mid+1,end);
}

template <typename T1,typename T2>
typename BST<T1,T2>::Iterator BST<T1,T2>::find(const T1& key , Node<T1, T2>* node) const noexcept{
    if(node == nullptr){return Iterator{nullptr};}
    else if(node->np.first == key){
        return Iterator{node};
    }
    else if(node->np.first < key){
        return find(key, node->right.get());
    }
    else{
        return find(key, node->left.get());
    }
    
}

template <typename T1,typename T2>
typename BST<T1,T2>::Iterator BST<T1, T2>::find(const T1& key) const noexcept{

    return find(key, root.get());
}


template <class T1,class T2>
std::ostream& operator<<(std::ostream& os, const BST<T1,T2>& bst){
    for( const auto &x:bst){
        os<<x.first<<" : "<<x.second<<std::endl; 
    }
    return os;
}



