#include <iostream>
#include "InternalNode.h"

using namespace std;


InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0; 
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{
  if (InternalNode::getCount() == leafsize || InternalNode::getCount() == internalsize)
  // students must write this
  // internal size represents number of leafnodes it can contain 
  // have value and check last childs keys insert for the child at the end of the loop
  // insert value into the child first because it doesnt matter if it is full
  children[index]->insert(value);
  if (count < internalSize) {

  }

  if (rightSibling < internalSize) {
    
  }
  else {

  }
  children->getMinimum(); // keys
   // if NEED to check if a child has room
   // if there is also room for a value
// if its full u dont need to split yet, u only need to split when u cant put the leafnode left or right
// the logic for the leafnode should be identical to the internal node
   // if left sibling < internalsize
   // if right sibling < internalsize

   // else both of them are full


// values is children and keys
// when u make space for value and move everything down, then insert 


// keys represents the minimum of children in leafnode but children is values
// inserting nodes into children and ints into values
// children->getMinimum is keys



  
  return NULL;                            // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ 
  BTreeNode* newRoot = new InternalNode;
  newRoot->insert(oldRoot, leafptr);
  root = newRoot; 
  
  
  
  
  // Node must be the root, and node1
  // students must write this
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  // students may write this
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


