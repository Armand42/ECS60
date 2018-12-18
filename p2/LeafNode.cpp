#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

int ceilres(int a){
	if (a % 2 == 0){
		return a;
	}
	else{
		return (a/2) + 1;
	}
}

LeafNode* LeafNode::Sort(){
	for(int k = 1; k<count; k++){
		for(int l=1; l < (count-k+1);l++){
			if(values[l]>values[l+1]){
				cout << "values to be swapped = " << values[l]<< " and " << values[l+1] << endl;
				int temp = values[l];
				values[l] = values[l+1];
				values[l+1] = temp;
			}
		}
	}
	return 0;
}

//ADDED
int LeafNode::getMaximum()const
{
	if(count>0)
		return values[count-1];
	else
		return 0;
}

int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()

LeafNode* LeafNode::insert(int value)
{
  // students must write this
  if(LeafNode::getCount() < leafSize){
	  for (int pos = 0; pos < count; pos++) {
			if (value < values[i]) {
				DO SHIT
			}
		}
	  //cout << "count = " << count << " value = " << value << endl;
	  values[count] = value;												// does original values change?
	  //cout << "inserted value " << values[count] << endl;
	  count++;																// does the original value of count inside the class change?
	  //cout << "inserted value " << values[count-1] << endl;
	  //LeafNode::Sort();
	  
	  return NULL;
  }
  else if(LeafNode::getCount() == leafSize){
	  //cout << "2222" << endl;
	  if(LeafNode::getLeftSibling()->getCount() < leafSize){				// does this consider non-existence of leftsibling?
		  /*getLeftSibling ->insert(values[0]);
			for (int pos = 0; pos <= count; pos++) {
				values[i + 1] = values[i];
				count = count - 1;
			}*/



			if(value > LeafNode::getMinimum()){
			  LeafNode::getLeftSibling()->insert(LeafNode::getMinimum());
			  values[count] = value;
			  //LeafNode::Sort();
		  }
		  else
			  LeafNode::getLeftSibling()->insert(value);
		  return NULL;
	  }
	  else if(LeafNode::getRightSibling()->getCount() < leafSize){
		  if(value>LeafNode::getMaximum())

			  LeafNode::getRightSibling()->insert(value);
		  else{
			  LeafNode::getRightSibling()->insert(LeafNode::getMaximum());
			  values[count] = value;
			  //LeafNode::Sort();
		  }
		  return NULL;
	  }
	  else{
		  LeafNode* newleaf = new LeafNode(leafSize, NULL, NULL, NULL);
		  newleaf->count = 0;
		  
		  for(int i = 1; i < ceilres(leafSize); i++){
			  if(LeafNode::getMaximum() > value){
				  count--;
				  newleaf->insert(LeafNode::getMaximum());
				  values[count + 1] = NULL;		
			  }
			  else{
				  newleaf->insert(value);
			  }
		  }
		  return newleaf;
	  }
  }
  //return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()





















/*#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p, BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode() 


int LeafNode::getMinimum() const                 // takes the minimum value in the array
{
  if(count > 0)              // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


// NEW FUNCTION
void LeafNode::orderedInsertion(int number) {
  // Fix this part of the function
  for (int pos = count - 1; pos = 0; pos--) {
    values[pos + 1] = values[pos];
  }

}


void LeafNode::orderLeftSibling() {
  for (int pos = count - 1; pos = 0; p--) {
    values[pos + 1] = values[pos];    // might need to fix this
    return NULL;
  }


}

void LeafNode::orderRightSibling() {

}



LeafNode* LeafNode newSplitNode(int number) {

  LeafNode* newsplitNode;

}




int LeafNode::getMaximum(){


}


/////////////////////////////////////////////////////////////////////////////////////

LeafNode* LeafNode::insert(int value)
{
  bool isFull == 1;
  // students must write this
  if (LeafNode->getCount() < leafsize) {     // if it isn't full, insert a value while still having the list sorted
   *values = value;
                          
                          // insert (keeping it sorted) 
  return NULL;

  }
            // For if regular node is full so hand it off

  else {    
        if (getLeftSibling() < leafsize ){   // checking to see if we can insert a value into a left sibling
          
           if (getLeftSibling() < leafsize[i]) {    // must fix ar[i+1] = ar[i]
             getLeftSibling()->insert(value);

           }
         }
         // getLeftSibling()->insert(values[0]);                          // inserting at the initial position so that we can sort after
         // orderLeftSibling();
        }                // if it is full, split or give up a value for - do this for left and right child


        else {
          if (getRightSibling() < leafsize) { // checking to see if we can insert a value into a right sibling

            //orderRightSibling();


          }
          else {
            return newSplitNode(value);      // for if we are unable to look left or look right <- Sean's rule
          }



        }

  }




  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()

*/


