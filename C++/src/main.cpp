/**
 main.cpp
 object: main that creates some binary search trees and performs some test on it.
 */

#include "bst.h"



template <typename T1, typename T2>
/**
 method that test the clear function, given a binary search tree.
 */
void clearTest(BST<T1,T2> binary_tree){
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Binary search tree clear test"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    
    binary_tree.clear();
    
    std::cout<<"Print the binary tree that has been cleared(), so I expect an empty tree:"<<std::endl;
    binary_tree.print();
    std::cout<<"----------------------"<<std::endl;
    
    binary_tree.insert(8,1);
    binary_tree.insert(3,2);
    binary_tree.insert(10,3);
    binary_tree.insert(6,4);
    binary_tree.insert(14,5);
    binary_tree.insert(1,6);
    binary_tree.insert(13,7);
    
    std::cout<<"Print the binary tree, after adding the same nodes that has been removed:"<<std::endl;
    binary_tree.print();
    binary_tree.clear();
    
}


template <typename T1, typename T2>
/**
 method that tests the copy and move sematic of the binary search tree class.
 */
void semanticTest(BST<T1,T2> binary_tree){
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Binary search tree copy and move semantic test"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    
    BST<int,int> binary_tree2 = binary_tree;
    binary_tree2.insert(15,10);
    std::cout<<"Print the second tree, a deep copy of the first with a new node, build from the copy assignment"<<std::endl;
    binary_tree2.print();
    
    std::cout<<" ----------------------"<<std::endl;
    std::cout<<"Print first tree:"<<std::endl;
    binary_tree.print();
    
    std::cout<<" ----------------------"<<std::endl;
    std::cout<<"Print third tree, a deep copy of the second, using the copy constructor"<<std::endl;
    BST<int,int> binary_tree3(binary_tree2);
    binary_tree3.print();
    
    std::cout<<" ----------------------"<<std::endl;
    std::cout<<"Print the fourth tree, using the move constructor from the first tree"<<std::endl;
    BST<int,int> binary_tree4(std::move(binary_tree));
    binary_tree4.print();
    
    std::cout<<" ----------------------"<<std::endl;
    std::cout<<"Print the first tree: I expect no print"<<std::endl;
    binary_tree.print();
    
    std::cout<<" ----------------------"<<std::endl;
    std::cout<<"Print the fifth tree, using the move assignment from the second tree"<<std::endl;
    BST<int,int> binary_tree5 = std::move(binary_tree2);
    binary_tree5.print();
    
    binary_tree.clear();
    binary_tree2.clear();
    binary_tree3.clear();
    binary_tree4.clear();
    binary_tree5.clear();
}

int main(){
    
    return 0;
}
