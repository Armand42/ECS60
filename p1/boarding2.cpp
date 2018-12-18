//Important Questions:
//2. WHEN DO WE NEED "BREAK"?
//3. Passengers going in, and another passenger entering aisle, does it happen at the same time?
//4. What is condition after putting someone in seat?

#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

using namespace std;

class Row{
	public:
		void RowNum(int num){					// HAVEN'T BEEN USED
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

void boarding(string filename);
Queue<Row> shufflerow(Queue <Row> classrow);

Queue<Row> shufflerow(Queue <Row> classrow){
	Row toprow = classrow.getFront();
	while(toprow.returnrow()!=3){
		classrow.enqueue(classrow.dequeue());
		toprow = classrow.getFront();
	}
	return classrow;
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
		classrows.enqueue(row_class);
	}

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
	/* TESTING STRUCT ENTRIES
	while(!passengerlist.isEmpty()){
		passenger personoutput = passengerlist.dequeue();
		cout << personoutput.assignedrow << personoutput.assignedseat << personoutput.currentpos << endl;
	}*/

	// declaring variables for while loop
	Row currentrow;
	int time = 0;
	passenger personatfront;
	int breaker = 0;
	
	// iteration
	planeAisle.enqueue(passengerlist.dequeue());									// moving FIRST data from passengerlist to planeAisle
	cout << "FIRST PASSENGER:" << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << endl;
	cout << "begin" << endl;
	while(!(planeAisle.isEmpty())&&!(passengerlist.isEmpty())&&(breaker==0)){
		for(int i=1; i<=3; ++i){
			currentrow = classrows.dequeue();										// dequeue-ing per row class
			if(currentrow.getstatus()=="AC_IN"){
				cout << "J" << endl;
				currentrow.ACseats.push(currentrow.ACaisle.topAndPop());			// push passengers on aisle back to their seats
				if(currentrow.ACaisle.isEmpty()){
					currentrow.rowcondition("");									// changing row condition to nothing
					if(currentrow.returnrow()==1){									// if first row
						planeAisle.enqueue(passengerlist.dequeue());				// push people into aisle
					}
					classrows.enqueue(currentrow);									// queue-ing row back
				}
				else{
					currentrow.rowcondition("AC_IN");								// precaution
				}
			}
			else if(currentrow.getstatus()=="DF_IN"){
				cout << "I" << endl;
				currentrow.DFseats.push(currentrow.DFaisle.topAndPop());			// push passengers on aisle back to their seats
				if(currentrow.DFaisle.isEmpty()){
					currentrow.rowcondition("");									// changing row condition to nothing
					if(currentrow.returnrow()==1){									// if first row
						planeAisle.enqueue(passengerlist.dequeue());				// push people into aisle
					}
					classrows.enqueue(currentrow);									// queue-ing row back
				}
				else{
					currentrow.rowcondition("DF_IN");
				}
			}
			else if(currentrow.getstatus()=="AC_EMPTY"){
				cout << "H" << endl;
				currentrow.ACseats.push(planeAisle.getFront().assignedseat);		// push passenger into stack from aisle		// ERROR
				cout << "ERROR-1" << endl;
				planeAisle.dequeue();												// delete row entry, because it won't be needed anymore
				cout << "ERROR-2" << endl;
				if(!(currentrow.ACaisle.isEmpty())){
					currentrow.rowcondition("AC_IN");								// changing row state
					classrows.enqueue(currentrow);									// queue-ing row back
				}
				else{
					currentrow.rowcondition("");									// changing row condition to nothing
					cout << "PASS1?" << endl;
					if(currentrow.returnrow()==1){									// if first row
						cout << "PASS?" << endl;
						planeAisle.enqueue(passengerlist.dequeue());				// push people into aisle
						cout << "ERROR-3" << endl;
					}
					cout << "ERROR-4" << endl;
					classrows.enqueue(currentrow);									// queue-ing row back
					cout << "ERROR-5" << endl;
				}
			}
			else if(currentrow.getstatus()=="DF_EMPTY"){
				cout << "G" << endl;
				currentrow.DFseats.push(planeAisle.getFront().assignedseat);		// push passenger into stack from aisle
				planeAisle.dequeue();												// delete row entry, because it won't be needed anymore
				if(!(currentrow.DFaisle.isEmpty())){
					currentrow.rowcondition("DF_IN");								// changing row state
					classrows.enqueue(currentrow);									// queue-ing row back
				}
				else{
					currentrow.rowcondition("");									// changing row condition to nothing
					if(currentrow.returnrow()==1){									// if first row
						planeAisle.enqueue(passengerlist.dequeue());				// push people into aisle
					}
					classrows.enqueue(currentrow);									// queue-ing row back
				}
			}
			else if(currentrow.getstatus()=="AC_OUT"){
				cout << "F" << endl;
				if(currentrow.ACseats.isEmpty()){									// if nobody is sitting in ABC
					currentrow.rowcondition("AC_EMPTY");							// changing row state
					classrows.enqueue(currentrow);									// queue-ing row back
				}
				else{
					if(int(currentrow.ACseats.top())>int(planeAisle.getFront().assignedseat)){
						currentrow.ACaisle.push(currentrow.ACseats.topAndPop());	// pushing from seats to aisle
					}
					else{
						currentrow.rowcondition("AC_EMPTY");						// changing row state
						classrows.enqueue(currentrow);								// queue-ing row back
					}
				}
			}
			else if(currentrow.getstatus()=="DF_OUT"){
				cout << "E" << endl;
				if(currentrow.DFseats.isEmpty()){									// if nobody is sitting in DEF
					currentrow.rowcondition("DF_EMPTY");							// changing row state
					classrows.enqueue(currentrow);									// queue-ing row back
				}
				else{
					if(int(currentrow.DFseats.top())<int(planeAisle.getFront().assignedseat)){					
						currentrow.DFaisle.push(currentrow.DFseats.topAndPop());	// pushing from seats to aisle
					}
					else{	
						currentrow.rowcondition("DF_EMPTY");						// changing row state
						classrows.enqueue(currentrow);								// queue-ing row back
					}
				}
			}
			else if(currentrow.getstatus()=="STORING_LUGGAGE2"){
				cout << "D" << endl;
				passenger frontper = planeAisle.getFront();
				if((frontper.assignedseat=='A')||(frontper.assignedseat=='B')||(frontper.assignedseat=='C')){
					currentrow.rowcondition("AC_OUT");}								// changing row state
				else if((frontper.assignedseat=='D')||(frontper.assignedseat=='E')||(frontper.assignedseat=='F')){
					currentrow.rowcondition("DF_OUT");}								// changing row state
				classrows.enqueue(currentrow);										// queue-ing row back
			}
			else if(currentrow.getstatus()=="STORING_LUGGAGE1"){							
				cout << "C" << endl;
				currentrow.rowcondition("STORING_LUGGAGE2");						// changing row state
				classrows.enqueue(currentrow);										// queue-ing row back	
			}
			else if((planeAisle.getFront().assignedrow==planeAisle.getFront().currentpos)&&(planeAisle.getFront().assignedrow==currentrow.returnrow())){
				cout << "B" << endl;
				currentrow.rowcondition("STORING_LUGGAGE1");						// changing row state
				classrows.enqueue(currentrow);										// queue-ing row back
				//breaker = 1;
			}
			else{
				cout << "A" << endl;
				classrows.enqueue(currentrow);										// changing row class to be edited
				/*
				// deals with changing current position
				personatfront = planeAisle.dequeue();
				personatfront.currentpos++;
				int personatfront_row = personatfront.assignedrow;
				char personatfront_seat = personatfront.assignedseat;
				planeAisle.enqueue(personatfront);
				while((planeAisle.getFront().assignedrow!=personatfront_row)&&(planeAisle.getFront().assignedseat!=personatfront_seat)){
					planeAisle.enqueue(planeAisle.dequeue());
				}
				*/
				cout << "TEST SHIT 1" << endl;
				if(!passengerlist.isEmpty()&&!planeAisle.isFull()&&(i==3)){			// i==3 added
					planeAisle.enqueue(passengerlist.dequeue());					// adding next passenger into the aisle
				}
				cout << "TEST SHIT 2" << endl;
				cout << "TEST SHIT" << endl;
			}
		}
		shufflerow(classrows);
		time = time + 5;
		cout << time << endl;
	}
	
}

int main(int argc, char* argv[]){
	string filename = argv[1];
	boarding(filename);
	return 0;
}