#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

using namespace std;

class Row{
	public:
		void RowNum(int num){					
			number = num;
		}

		void rowcondition(string row_state){
			cond = row_state;
		}
		
		int returnrow(){
			return number;
		}
		
		string getstatus(){
			return cond;
		}
		
		// previously seated passengers
		StackAr <char> ACseats = StackAr<char>(3);
		StackAr <char> DFseats = StackAr<char>(3);
		// passengers in aisle -> for moving passengers into aisle when someone wants to get inside 
		StackAr <char> ACaisle = StackAr<char>(2);
		StackAr <char> DFaisle = StackAr<char>(2);
		
	private:
		string cond;
		int number;	
};

Queue<Row> shufflerow(Queue <Row> classrow){
	Row toprow = classrow.getFront();
	while(toprow.returnrow()!=3){
		classrow.enqueue(classrow.dequeue());
		toprow = classrow.getFront();
	}
	return classrow;
}

string nextRow(Row classrow, Queue <Row> queuerow){
	Row toprow = queuerow.getFront();
	int z = classrow.returnrow();
	while(toprow.returnrow()!=z+1){
		queuerow.enqueue(queuerow.dequeue());
		toprow = queuerow.getFront();
	}
	return toprow.getstatus();
}

void boarding(string filename){
	// structure for each passenger
	struct passenger{
		int assignedrow;
		char assignedseat;
		int currentpos;
	};

	Queue <passenger> planeAisle = Queue<passenger>(3);
	Queue <passenger> passengerlist = Queue<passenger>(18);

	// 48 or 3 different Row classes for each row
	Queue <Row> classrows = Queue<Row>(3);
	Row row_class;
	for(int i=1;i<=3;++i){
		row_class.RowNum(4-i);
		row_class.rowcondition("");
		classrows.enqueue(row_class);
	}	// if dequeued -> goes from 3->1 top to bottom

	
	// filling the queue with passengers
	int rownum; char letters;
	ifstream txtfile;
	txtfile.open(filename);
	while(txtfile >> rownum >> letters){
		passenger person;
		person.assignedrow = rownum;
		person.assignedseat= letters;
		person.currentpos = 1;
		passengerlist.enqueue(person);
	}
	
	// declaring variables for while loop
	Row currentrow; // CLASS OBJECT
	int time = 5;
	passenger frontpassenger;
	int breaker = 0;
	int permitpass = 1;
	
	planeAisle.enqueue(passengerlist.dequeue());
	cout << endl;
	cout << "FIRST PASSENGER:" << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << endl;
	
	// iterator for checking each element in the stacks
	while((!passengerlist.isEmpty())||(!planeAisle.isEmpty())){
		for(int i=1; i<=3; i++){
			currentrow = classrows.dequeue();
			cout << "assigned row = " << planeAisle.getFront().assignedrow << endl;
			cout << "current row pos = " << currentrow.returnrow() << endl;
			cout << "passenger pos = " << planeAisle.getFront().currentpos << endl;
			if((planeAisle.getFront().assignedrow)==(currentrow.returnrow())){
				if((planeAisle.getFront().currentpos)==(currentrow.returnrow())){
					cout << "DID IT PASS?" << endl;
					if(currentrow.getstatus()=="STORING_LUGGAGE2"){
						if((planeAisle.getFront().assignedseat=='A')||(planeAisle.getFront().assignedseat=='B')||(planeAisle.getFront().assignedseat=='C')){
							if(currentrow.ACseats.isEmpty()){
								currentrow.ACseats.push(planeAisle.getFront().assignedseat);        // after checking to see if were finally in row A-C, and if its empty then we push assigned seat
								cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " has seated" << endl;
								planeAisle.dequeue();   // dequeing for the the next stack in the big queue
								if((currentrow.returnrow()==1)&&(!passengerlist.isEmpty())){
									planeAisle.enqueue(passengerlist.dequeue()); // not entirely sure what this does
									cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " entered plane" << endl;
									//cout << "i = " << i << endl;
								}
								classrows.enqueue(currentrow);  // reinsertin a row class back into the big queue
							}
							else{
								if(int(currentrow.ACseats.top())>int(planeAisle.getFront().assignedseat)){  // checking the state of the next row?
									currentrow.ACaisle.push(currentrow.ACseats.topAndPop());
									if(int(currentrow.ACseats.top())>int(planeAisle.getFront().assignedseat)){
										currentrow.rowcondition("AC_OUT");
										classrows.enqueue(currentrow);
									}
									else{
										currentrow.rowcondition("AC_EMPTY");    // if AC_Empty, then we enqueue the class
										classrows.enqueue(currentrow);
									}
								}
								else{
									currentrow.ACseats.push(planeAisle.getFront().assignedseat);
									planeAisle.dequeue();	
									classrows.enqueue(currentrow);
								}
							}
						}
						else if((planeAisle.getFront().assignedseat=='D')||(planeAisle.getFront().assignedseat=='E')||(planeAisle.getFront().assignedseat=='F')){   // after checking to see if were finally in row A-C,
							currentrow.rowcondition("DF_OUT");  // shouldn't we check to see if it is empty?
						}
					}
					else if(currentrow.getstatus()=="STORING_LUGGAGE1"){    //checking row condition
						currentrow.rowcondition("STORING_LUGGAGE2");
						cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " storing luggage 2" << endl;
						classrows.enqueue(currentrow);
					}
					else{
						currentrow.rowcondition("STORING_LUGGAGE1");	// 2A never went here
						cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " storing luggage 1" << endl;
						classrows.enqueue(currentrow);
					}
				}
			}
			else{
				if(i==3){
					cout << "A" << endl;
					if(nextRow(currentrow,classrows)!=""){      // are you trying to see if the next row is empty?
						cout << "B" << endl;
						break;
					}
					else if(!passengerlist.isEmpty()){
						cout << "C" << endl;
						cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " moving forward" << endl;
						frontpassenger = planeAisle.dequeue();
						frontpassenger.currentpos++;
						int x = frontpassenger.assignedrow;
						char y = frontpassenger.assignedseat;
						planeAisle.enqueue(frontpassenger);
						// cout << "current position = " << frontpassenger.currentpos << endl;
						while((planeAisle.getFront().assignedrow!=x)&&(planeAisle.getFront().assignedseat!=y)){
							passenger nextperson = planeAisle.dequeue();
							nextperson.currentpos++;
							planeAisle.enqueue(nextperson);
						}
						planeAisle.enqueue(passengerlist.dequeue());
					}
					cout << "D" << endl;
				}
				cout << "E" << endl;
				classrows.enqueue(currentrow);
				// planeAisle.enqueue(planeAisle.dequeue());
			}
		}
		shufflerow(classrows);
		//planeAisle.enqueue(planeAisle.dequeue());
		time = time + 5;
		cout << "time elapsed = " << time << endl;
	}
}


int main(int argc, char* argv[]){
	string filename = argv[1];
	boarding(filename);
	return 0;
}