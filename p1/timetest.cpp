#include <iostream>
#include "CPUTimer.h"
#include "dsexceptions.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"
#include <fstream>

using namespace std;

vector<CursorNode <int> > cursorSpace(500001);          //compiles the cursorlist function
// function prototypes
void RunList(string file);
void RunCursorlist(string file);
void RunStackAr(string file);
void RunStackLi(string file);
void RunQueueAr(string file);
void RunSkipList(string file);
int getChoice();                // returns choice of ADT Menu

int main() {
    int choice;
    string filename;
    cout << "Filename >> ";
   
    cin >> filename;
    cout << "\n";
    CPUTimer ct;
    

do {


   choice = getChoice();
   ct.reset();
    switch(choice) {
        case 1: RunList(filename); break;
        case 2: RunCursorlist(filename); break;
        case 3: RunStackAr(filename); break;
        case 4: RunStackLi(filename); break;
        case 5: RunQueueAr(filename); break;
        case 6: RunSkipList(filename); break;

    }
    cout << "CPU time: " << ct.cur_CPUTime() << endl;

} while (choice > 0);


    return 0;
}



int getChoice() {
    
    int choice;
cout <<"      ADT Menu\n" << "0. Quit\n" << "1. LinkedList\n" << "2. CursorList\n" << "3. StackAr\n" 
    << "4. StackLi\n" << "5. QueueAr\n" << "6. SkipList\n";
    cout << "Your choice >> ";
    cin >> choice;
// this part is not needed it is in the do while loop commented out
    
    return choice;
}

//

// ADT Function 1
void RunList(string filename) {
    List <int> linkedList;
    ListItr <int> iterator = linkedList.zeroth(); 
    ifstream fin;       // to read in data from the file
    fin.open(filename);     // opens file
    char letter;        // to catch i value
    char firstLine[512]; // to get rid of first line of code
    int number;         // to catch number
    fin.getline(firstLine, 512); // to extract the first line of the character array, does nothing with it
    while (fin >> letter >> number) {       // while loop used to keep inserting or deleting data
        //cout << letter << " " << number << endl;
        if(letter == 'i') {
            linkedList.insert(number, iterator);
            
        }
        else if(letter == 'd') {
            linkedList.remove(number);
        }
      

    }
    fin.close();


}

// ADT Function 2
void RunCursorlist(string filename) {
    CursorList <int> cursorList(cursorSpace);
    CursorListItr <int> iterator = cursorList.zeroth();

    ifstream fin;
    fin.open(filename);
    char letter;
    char firstLine[512];
    int number;

    fin.getline(firstLine, 512);

    while(fin >> letter >> number) {
        if(letter == 'i') {
            cursorList.insert(number,iterator);
        }
        else if(letter == 'd') {
            cursorList.remove(number);
        }
    }
    fin.close();

}

// ADT Function 3
void RunStackAr(string filename) {
    ifstream fin;
    StackAr <int> stackFrame(500001);
    fin.open(filename);
    char letter;
    char firstLine[512];
    int number;

    fin.getline(firstLine, 512);

    while (fin >> letter >> number) {
        if (letter == 'i') {
            stackFrame.push(number);
        }
        else if (letter == 'd') {
            stackFrame.pop();
        }
    }
    fin.close();


}
// ADT Function 4
void RunStackLi(string filename) {
    ifstream fin;
    StackLi <int> liStack;

    fin.open(filename);
    char letter;
    char firstLine[512];
    int number;

    fin.getline(firstLine, 512);
    while (fin >> letter >> number) {
        if (letter == 'i') {
            liStack.push(number);
        }
        else if(letter == 'd') {
            liStack.pop();
        }
    }
    fin.close();
}

// ADT Function 5

void RunQueueAr(string filename) {

    ifstream fin;
    Queue <int> queueData(500001);
    fin.open(filename);
    char letter;
    char firstLine[512];
    int number;
    fin.getline(firstLine, 512);

    while (fin >> letter >> number) {
        if (letter == 'i') {
            queueData.enqueue(number);
        }
        else if (letter == 'd') {
            queueData.dequeue();
        }
    }
    fin.close();
}

// ADT Function 6

void RunSkipList(string filename) {
    ifstream fin;
    SkipList <int> skip(0, 250000);
    fin.open(filename);
    char letter;
    char firstLine[512];
    int number;
    fin.getline(firstLine, 512);


    while (fin >> letter >> number) {
        if (letter == 'i') {
            skip.insert(number);
        }
        else if (letter == 'd') {
            skip.deleteNode(number);
        }
    }
    fin.close();
}