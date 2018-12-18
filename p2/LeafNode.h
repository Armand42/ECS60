#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left, BTreeNode *right);
  LeafNode* Sort();
  int getMinimum() const;
  int getMaximum() const;
  LeafNode* insert(int value); // returns pointer to new Leaf if splits
  // else NULL
  void print(Queue <BTreeNode*> &queue);




//new functions
  void orderedInsertion(int number);
  void orderLeftSibling();
  void orderRightSibling();

  LeafNode* newSplitNode(int number);


}; //LeafNode class

#endif
