/**
 main.cpp
 object: main that creates some binary search trees and performs some test on it.
 */

#include "bst.h"
#include <ctime>
#include <map>
#include <algorithm>

template <typename T1, typename T2>
/**
    method that tests the balance function, printing the root and the tail of a given binary search before and after
    balancing it.
*/
void balanceTest(BST<T1,T2> binary_tree){

    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Binary search balance test"<<std::endl;
    std::cout<<"----------------------"<<std::endl;

    std::cout<<"Print the begin and the end of the NOT-balanced tree:"<<std::endl;
    std::cout<<"begin: "<<binary_tree.begin()<<std::endl;
    std::cout<<"end: "<<binary_tree.end()<<std::endl;
    std::cout<<" ----------------------"<<std::endl;

    binary_tree.balance();

    std::cout<<"Print the root and the tail of the balanced tree:"<<std::endl;
    std::cout<<"begin: "<<binary_tree.begin()<<std::endl;
    std::cout<<"end: "<< binary_tree.end()<<std::endl;
    binary_tree.clear();

}

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
template <typename T1,typename T2>
/**
    method that tests the find function, given a binary search tree and a key used to find the nodes inside the tree.
*/
void findTest(BST<T1,T2> binary_tree, T1 key){

    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Binary search tree find test"<<std::endl;
    std::cout<<"----------------------"<<std::endl;

    std::cout<<"search for node with key equal to "<<key<<": "<<binary_tree.find(key)<<std::endl;
    std::cout<<"search for node with a key that is not present in the tree: "<<binary_tree.find(-1)<<std::endl;
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
/**
    method that compares the performance between our implementation of a binary search tree, not-balanced and balanced,
    and a std::map, calculating the average time to find a single node. The parameter N is the number of the nodes that
    will be inserted and the parameter num_attemps is thenumber of times the test is repeated, in order to achieve 
    robustness and reproducibility of results.

    This method can be adapted to the case of double-type keys,adapting the templates types and substituting the 
    for loop that generates the random intgeres with the following one:

    for(int i =0;i<N;i++){
            double f = (double)rand() / RAND_MAX;
            testVector.push_back(1 + f * (2*N));
    }
*/

void performanceTest(int N,int num_attempts){
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Binary search tree performance test"<<std::endl;
    std::cout<<"Number of nodes choosen to run the test: "<<N<<std::endl;
    std::cout<<"Number of attempts choosen to run the test: "<<num_attempts<<std::endl;
    std::cout<<"----------------------"<<std::endl;
  
    double sumDiffNotBal=0;
    double sumDiffBal=0;
    double sumDiffMap=0;
    std::vector<int> testVector;
    BST<int,int> bst_test{};
    std::map<int,int> test_map;
    srand((unsigned)time(0));
    clock_t begin;
    clock_t end;
    for(int j=0;j<num_attempts;j++){
       
       for(int i=0;i<N; i++){
        int a = rand()%(2*N)+1;
        testVector.push_back(a);
        }
       
        for(int i=0;i<N; i++){
        bst_test.insert(testVector[i],i+1);
        test_map.insert(std::pair<int,int>(testVector[i],i+1));
        }

        std::random_shuffle(testVector.begin(),testVector.end());
    /**    
    //  Another version version of this test could be the following one, in which, instead of using std::random_shuffle,
    //  we clear the testVector and we push into it other random values. This leads to an higher medium time to find a 
    //  single node, because most of the generated numbers aren't present in the tree so the find function traverse the 
    //  whole tree more times than than the other method.
    
        testVector.clear();

        for(int i=0;i<N; i++){
        int b = rand()%(2*N)+1;
        testVector.push_back(b);
        }
    */
        begin = std::clock();
        for(int i=0;i<N;i++){
            bst_test.find(testVector[i]);
        }
        end = std::clock();
        double diff = (double)(end - begin)/ CLOCKS_PER_SEC;
        sumDiffNotBal += diff;

        bst_test.balance();

        begin = std::clock();
        for(int i=0;i<N;i++){
            bst_test.find(testVector[i]);
        }
        end = std::clock();
        diff = (double)(end - begin)/ CLOCKS_PER_SEC;
        sumDiffBal += diff;

        begin = std::clock();
        for(int i=0;i<N;i++){
            test_map.find(testVector[i]);
        }
        end = std::clock();
        diff = (double)(end - begin)/ CLOCKS_PER_SEC;
        sumDiffMap += diff;

        testVector.clear();
        test_map.clear();
        bst_test.clear();
    }
    std::cout<<"Mean time to find a single node in a not-balanced BST: "<<(sumDiffNotBal/num_attempts)/N<<std::endl;
    std::cout<<"---------------------------- "<<std::endl;
    std::cout<<"Mean time to find a single node in a balanced BST: "<<(sumDiffBal/num_attempts)/N<<std::endl;
    std::cout<<"---------------------------- "<<std::endl;
    std::cout<<"Mean time to find a single node in a std::map: "<<(sumDiffMap/num_attempts)/N<<std::endl;
    std::cout<<"---------------------------- "<<std::endl;
    
}

int main(){
    
    BST<int,int> binary_tree{};
    binary_tree.insert(60,1);
    binary_tree.insert(41,2);
    binary_tree.insert(74,3);
    binary_tree.insert(16,4);
    binary_tree.insert(53,5);
    binary_tree.insert(65,6);
    binary_tree.insert(25,7);
    binary_tree.insert(46,8);
    binary_tree.insert(55,9);
    binary_tree.insert(63,10);
    binary_tree.insert(70,11);
    binary_tree.insert(42,12);
    binary_tree.insert(62,13);
    binary_tree.insert(64,14);
    std::cout<<"Print the tree in order: "<<std::endl;
    binary_tree.print();
    balanceTest(binary_tree);
    clearTest(binary_tree);
    findTest(binary_tree,42);
    semanticTest(binary_tree);
    performanceTest(1000,10);
    binary_tree.clear();
    
    return 0;
}
