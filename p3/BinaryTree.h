#include <iostream>
#include <iomanip>
using namespace std;

template <class Object>
class BSTNode {
    string binaryArray;
    int value;      // frequency
    char data;      // characters
    BSTNode* parent;
    BSTNode* leftChild;
    BSTNode* rightChild;
    void printTree();      
                          // need to operator overload Comparable class
    void makeLeafNode(value);
    void inOrderTraversal(BSTNode* ptr);
  // void insert(*Node head, int value);
  bool binaryTreePtr<T>::operator<(const binaryTreePtr<T>&)

};

template <class Comparable>
void BinaryHeap<Comparable>::insert(const Comparable & x ) {

}

//array[i]->value = frequencyArray[i];

    // fix template definition
 BSTNode::BSTNode* BSTNode::makeLeafNode(value) {
     BSTNode* node = new BSTNode;
     node->leftChild = NULL;
     node->rightChild = NULL;
     node->value = frequencyArray[i];
     node->data = input[i];
     return node;
 }

 void BSTNode::inOrderTraversal(BSTNode* ptr) {
     if (parent != NULL) {          // because we want to keep print left values
         if (ptr->leftChild != NULL) {  // because we want to keep print left values
         node->binaryArray.append('0');
         //somehwere here print current tree and the string of 000111 in traversal
         printTree();
         }
         cout << ptr->value;
     }
 }

// NEED BOTH THE DEFINITION AND IMPLEMENTATION OF THE BINARYTREE template
// IMPLEMENT A public printTree() method - that will be called from main()
void BSTNode::printTree() {
    string binaryArray;
    for (int i = 0; i < binaryArray.length(); i++) {
        binaryArray[i] = 0;

        

    }
}