#include "bst.h"

int main(){
    BST<int,int> bst{};
    bst.insert(std::make_pair(3,1));
    bst.insert(std::make_pair(1,2));
    bst.insert(std::make_pair(5,3));
    bst.insert(std::make_pair(4,4));
    bst.insert(std::make_pair(2,5));
    bst.insert(std::make_pair(6,6));
    bst.insert(std::make_pair(8,7));
    bst.insert(std::make_pair(10,8));
    bst.insert(std::make_pair(9,9));
    bst.insert(std::make_pair(7,10));
    std::cout<<bst;
    std::cout<<"---------------"<<std::endl;
    bst.balance();
    std::cout<<"---------------"<<std::endl;
    std::cout<<"Find the node with key = 8 and print it:"<<std::endl;
    std::cout<<"("<<(*(bst.find(8))).first<<" , "<<(*(bst.find(8))).second<<")"<<std::endl;
    return 0;
}