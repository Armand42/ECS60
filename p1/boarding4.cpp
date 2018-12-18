#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

// Main issues:
// 1. Checking other passengers in the aisle // might be addressed already
// 2. Determining when the passengers should move a row ahead
// 3. When 2A moved forward, 3D didn't enter plane
// 4. 2A moving forward and storing luggage happened at the same time

using namespace std;

struct United {
    

}

class Row {
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



string nextRow(Row classrow, Queue<Row>queuerow, int currow){ // keeps taking people off top of queue, just make a passenger class in the row
	/*Row Q = classrow;
	queuerow.enqueue(classrow);			// since we dequeued in begining of for loop, must be enqueued back
	if(currow==3){
		while(Q.returnrow()!=1){	// changed to Q
			queuerow.enqueue(queuerow.dequeue());
			Q = queuerow.getFront();	// changed to Q
		}
	}
	else{
		while(Q.returnrow()!=currow+1){	// changed to classrow
			queuerow.enqueue(queuerow.dequeue());
			Q = queuerow.getFront();		// changed to classrow
		}
	}
	Row finalrow = queuerow.getFront();
	return finalrow.getstatus();*/
    Queue<Row> cat(48); //temporary queue    //48
    Row tempQ1;
    for (int i = 0; i < 48; i++)
    {
        Row tempQ2;
        tempQ1 = queuerow.dequeue();
        tempQ2.rowcondition(tempQ1.getstatus());
        cat.enqueue(tempQ2); 
        queuerow.enqueue(tempQ1);
    }
    
    for (int i = 0; i < 48; i++) 
    {
        tempQ1 = cat.dequeue();
        if (tempQ1.number == currow + 1)
        {
            return tempQ1.getstatus();
        }
    }
}

// create a function that moves people one row forward
// moves everyone at once when i=3
// assume T is struct 
template<typename T>
Queue<T> movepeople(Row classrow, Queue<Row>queuerow, Queue<T>aisle){
	cout<<"SUCCESS-0"<<endl;
	int X = aisle.getFront().assignedrow;
    char Y = aisle.getFront().assignedseat;
	int Z = aisle.getFront().currentpos;

	T person = aisle.dequeue();
	cout<<"SUCCESS-1"<<endl;
	if((nextRow(classrow, queuerow,Z)!= "STORING_LUGGAGE1")
        &&(nextRow(classrow,queuerow,Z)!= "STORING_LUGGAGE2")) {

		person.currentpos++;
		cout << person.assignedrow << person.assignedseat << " moved forward" << endl;
		aisle.enqueue(person);

		while((aisle.getFront().assignedrow!=X)&&(aisle.getFront().assignedseat!=Y)){

			if((nextRow(classrow, queuerow, aisle.getFront().currentpos)!="STORING_LUGGAGE1")&&(nextRow(classrow,queuerow,aisle.getFront().currentpos)!="STORING_LUGGAGE2")){
				person = aisle.dequeue();
				person.currentpos++;

				cout << person.assignedrow << person.assignedseat << " moved forward" << endl;
				aisle.enqueue(person);
			}
		}
	}
	return aisle;
}

void boarding(string filename){
	// structure for each passenger
	struct passenger{

		int assignedrow;   
		char assignedseat; 
		int currentpos;
	};

	Queue <passenger> planeAisle = Queue<passenger>(3);     // put the passenger in the row class, u dont want to use this, more checks will be needed
                                                            // take 2 people out of queue at once, take out row 47 with dequeue,
                                                            // ex: want to put 48A in row 47 to row 48
                                                            // change state of both row 47 and 48
                                                            // enqueue row 48
                                                            // dequeue row 46
                                                            // taking 2 guys out of queue at once
                                                            // we shouldnt enqueue until we move a passenger
                                                            // were looking at row 2 but we never enqueued them back in
                                                       // for big passenger list will have to clear it
	Queue <passenger> passengerlist = Queue<passenger>(18);

	// 48 or 3 different Row classes for each row
	Queue <Row> classrows = Queue<Row>(3);
	Row row_class;
	for (int i = 1; i <= 3; ++i){

		row_class.RowNum(4-i);
		row_class.rowcondition("");
		classrows.enqueue(row_class);

	}	// if dequeued -> goes from 3->1 top to bottom

	
	// filling the queue with passengers
	int rownum; char letters;
	ifstream txtfile;
	txtfile.open(filename);
	while(txtfile >> rownum >> letters) {

		passenger person;
		person.assignedrow = rownum;
		person.assignedseat= letters;
		person.currentpos = 1;
		passengerlist.enqueue(person);
	}
	
	// declaring variables for while loop
	Row currentrow;
	int time = 5;
	passenger frontpassenger;
	
	planeAisle.enqueue(passengerlist.dequeue());
	cout << endl;
	cout << "FIRST PASSENGER:" << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << endl;
	
	// iterator
	while((!passengerlist.isEmpty())||(!planeAisle.isEmpty())){
		for(int i=1; i<=3; i++){
			currentrow = classrows.dequeue();

			if((planeAisle.getFront().assignedrow)==(planeAisle.getFront().currentpos)){
				if(currentrow.returnrow()==planeAisle.getFront().assignedrow){		// just added - might be incorrect
				if(currentrow.getstatus()=="STORING_LUGGAGE2"){

					if((planeAisle.getFront().assignedseat=='A')||(planeAisle.getFront().assignedseat=='B')
                    ||(planeAisle.getFront().assignedseat=='C')){

						if(currentrow.ACseats.isEmpty()){
							currentrow.ACseats.push(planeAisle.getFront().assignedseat);
							cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " has seated" << endl;
							planeAisle.dequeue();

							if((currentrow.returnrow()==1)&&(!passengerlist.isEmpty())){
								planeAisle.enqueue(passengerlist.dequeue());

								cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " entered plane" << endl;
								//cout << "rowpos = " << currentrow.returnrow() << endl;
								currentrow.rowcondition("");
								//cout << "i = " << i << endl;
							}
							classrows.enqueue(currentrow);
						}
						else{
							if(int(currentrow.ACseats.top()) > int(planeAisle.getFront().assignedseat)){

								currentrow.ACaisle.push(currentrow.ACseats.topAndPop());

								if(int(currentrow.ACseats.top()) > int(planeAisle.getFront().assignedseat)){
									currentrow.rowcondition("AC_OUT");
									classrows.enqueue(currentrow);
								}
								else{
									currentrow.rowcondition("AC_EMPTY");
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
					else if((planeAisle.getFront().assignedseat =='D')||(planeAisle.getFront().assignedseat=='E')
                    ||(planeAisle.getFront().assignedseat=='F')){
						currentrow.rowcondition("DF_OUT");
					}
				}
				else if(currentrow.getstatus()=="STORING_LUGGAGE1"){
					currentrow.rowcondition("STORING_LUGGAGE2");
					cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " storing luggage 2" << endl;
					classrows.enqueue(currentrow);
					
				}
				else{
					currentrow.rowcondition("STORING_LUGGAGE1");	// 2A never went here
					cout << planeAisle.getFront().assignedrow << planeAisle.getFront().assignedseat << " storing luggage 1" << endl;
					classrows.enqueue(currentrow);
					cout << "i = " << i << endl;
				    }
				}
			}
			else{
				cout<<"i = "<<i<<endl;
				cout <<"E" << endl;
				if(i==3){

					cout<<"A" << endl;

					planeAisle = movepeople(currentrow,classrows,planeAisle);	// error

					planeAisle.enqueue(passengerlist.dequeue()); 
					// want person in the very front though
				}
				cout <<"F" << endl;
				classrows.enqueue(currentrow);
				cout <<"G" << endl;
			}
			cout<<"H"<<endl;
			planeAisle.enqueue(planeAisle.dequeue()); 		// to check other people in the aisle? // doesn't account if there are less than 3 in the aisle
			cout<<"I"<<endl;
			//classrows.enqueue(currentrow); // SOURCE OF ERROR
			cout <<"J"<< endl;
			//Row nexrow = classrows.getFront();
			//cout << "nextrowpos = " << nexrow.returnrow() << endl;
		}
		//classrows = shufflerow(classrows);
		time = time + 5;
		cout << "time elapsed = " << time << endl;
	}
}


int main(int argc, char* argv[]){
    cout << " FUCK THIS FUCKING UNITED AIRLINES BULLSHIT";
	string filename = argv[1];
	boarding(filename);
	return 0;
}