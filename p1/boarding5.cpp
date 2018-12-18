#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

// 4.41AM - works until second 70 => because haven't dealt fully with AC_OUT/DF_OUT - AC_EMPTY/DF_EMPTY - AC_IN/DF_IN

using namespace std;

class Passenger{
	public:
		int assignedrow;
		char assignedseat;
};

class Row{
	public:
		void RowNum(int num){					
			number = num;
		}

		void rowcondition(string row_state){
			cond = row_state;
		}
		
		void insertppl(Passenger a){
			person = a;
		}

		int getrow(){
			return number;
		}
		
		string getstatus(){
			return cond;
		}
		
		Passenger getpassenger(){
			return person;
		}
		
		// previously seated passengers
		StackAr <char> ACseats = StackAr<char>(3);
		StackAr <char> DFseats = StackAr<char>(3);
		// passengers in aisle -> for moving passengers into aisle when someone wants to get inside 
		StackAr <char> aisle = StackAr<char>(2);
		
	private:
		string cond;
		int number;
		Passenger person;
};

template<typename T>
void printpassengers(Queue<T> passqueue){
	while(!passqueue.isEmpty()){
		T peeps = passqueue.dequeue();
		cout << peeps.assignedrow << peeps.assignedseat << endl;
	}
}

void emptystack(StackAr<char> stack){
	if(stack.isEmpty()){
		cout << "STACK IS EMPTY" << endl;
	}
	else{
		cout << "STACK IS NOT EMPTY" << endl;
	}
}

void rowloss(Queue<Row> queuerow){
	int i = 0;
	while(!queuerow.isEmpty()){
		queuerow.dequeue();
		i++;
	}
	if(i==3){
		cout << "All rows accounted for" << endl;
	}
	else{
		cout<<"Rows missing"<<endl;
	}
}

Queue<Row> shufflerow(Queue <Row> classrow){
	Row toprow = classrow.getFront();
	while(toprow.getrow()!=3){
		classrow.enqueue(classrow.dequeue());
		toprow = classrow.getFront();
	}
	//cout << "toprow by shufflerow = " << toprow.getrow() << endl;
	return classrow;
}

void printrows(Queue<Row> someq){
	someq = shufflerow(someq);
	for(int i=0;i<=2;i++){
		Row somerow = someq.dequeue();
		cout << "Row " << somerow.getrow() << " has condition: " << somerow.getstatus() << endl;
	}
}

// works
Queue<Row> movepassengers(Queue <Row> rq){
	//cout << "A" << endl; rowloss(rq);
	rq = shufflerow(rq);
	Row row_a = rq.dequeue();
	Row row_b = rq.dequeue();
	for(int i = 0 ; i <= 1; i++){
		if((row_a.getstatus()=="EMPTY")&&(row_b.getstatus()=="WAITING")){
			row_a.insertppl(row_b.getpassenger());
			cout << row_a.getpassenger().assignedrow << row_a.getpassenger().assignedseat << " moved forward" << endl;

			row_a.rowcondition("WAITING");
			row_b.rowcondition("EMPTY");
			
			//cout << "Row " << row_a.getrow() << " status: " << row_a.getstatus() << " and Row " << row_b.getrow() << " status: " << row_b.getstatus() << endl;
		}
		//cout << "row_a is row# " << row_a.getrow() << "and gets enqueued back" << endl;
		//cout << "row_b is row# " << row_b.getrow() << "and will turn into row_a" << endl;
		rq.enqueue(row_a);
		row_a = row_b;
		row_b = rq.getFront();
	}
	rq.dequeue();
	rq.enqueue(row_a); // previously row_b
	printrows(rq);
	rq = shufflerow(rq);
	return rq;
}

// returns queue with 1st row in top
// works
Queue<Row> getfirstrow(Queue<Row>rq){
	Row toprow = rq.getFront();
	//cout << "Row " << toprow.getrow() << " status is: " << toprow.getstatus() << endl;
	while(toprow.getrow()!=1){
		
		rq.enqueue(rq.dequeue());
		toprow = rq.getFront();
		//cout << "Row " << toprow.getrow() << " status is: " << toprow.getstatus() << endl;
	}
	//cout << "firstrowstatus in getfirstrow = " << toprow.getstatus() << endl;
	return rq;
}

void boarding(string filename){
	Queue <Passenger> passengerlist = Queue<Passenger>(18);
	Queue <Row> rowqueue = Queue<Row>(3);
	
	// filling the queue with passengers
	int rownum; char letters;
	ifstream txtfile;
	txtfile.open(filename);
	while(txtfile >> rownum >> letters){
		Passenger person;
		person.assignedrow = rownum;
		person.assignedseat= letters;
		passengerlist.enqueue(person);
	}
	
	for(int i=0; i<=2; i++){
		Row a;
		a.RowNum(3-i);
		a.rowcondition("EMPTY");
		if(i==2){
			a.insertppl(passengerlist.dequeue());
			cout << "First Passenger: " << a.getpassenger().assignedrow << a.getpassenger().assignedseat << " at Row: " << a.getrow() << endl;
		}
		rowqueue.enqueue(a);
	}
	int time = 5;
	Row currentrow;
	while(!passengerlist.isEmpty()){
		for(int x = 0; x<=2; x++){
			currentrow = rowqueue.dequeue();
			//cout << "analyzed row = " << currentrow.getrow() << endl;
			if(currentrow.getrow() == currentrow.getpassenger().assignedrow){
				// recently added
				if(currentrow.getstatus()=="AC_EMPTY"){
					currentrow.ACseats.push(currentrow.getpassenger().assignedseat);
					cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
					Passenger emptypassenger;
					emptypassenger.assignedrow = 0;
					emptypassenger.assignedseat = 'A';
					currentrow.insertppl(emptypassenger);
					if(!currentrow.aisle.isEmpty()){
						currentrow.rowcondition("AC_IN");
					}
					else{
						currentrow.rowcondition("EMPTY");
					}
				}


				else if(currentrow.getstatus()=="DF_EMPTY"){
					currentrow.DFseats.push(currentrow.getpassenger().assignedseat);
					cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
					Passenger emptypassenger;
					emptypassenger.assignedrow = 0;
					emptypassenger.assignedseat = 'A';
					currentrow.insertppl(emptypassenger);
					if(!currentrow.aisle.isEmpty()){
						currentrow.rowcondition("DF_IN");
					}
					else{
						currentrow.rowcondition("EMPTY");
					}
				}


				else if(currentrow.getstatus() == "AC_OUT"){
					cout << "A" << endl;
					currentrow.aisle.push(currentrow.ACseats.topAndPop());
					cout << currentrow.getrow() << currentrow.aisle.top() << " now waiting in aisle" << endl;
					currentrow.rowcondition("AC_EMPTY");
				}

 
				else if(currentrow.getstatus() == "DF_OUT"){
					currentrow.aisle.push(currentrow.DFseats.topAndPop());
					cout << currentrow.getrow() << currentrow.aisle.top() << " now waiting in aisle" << endl;
					currentrow.rowcondition("DF_EMPTY");
				}


				else if(currentrow.getstatus() == "STORING_LUGGAGE2"){
					if((currentrow.getpassenger().assignedseat=='A')||(currentrow.getpassenger().assignedseat=='B')||(currentrow.getpassenger().assignedseat=='C')){
						if(currentrow.ACseats.isEmpty()){
							currentrow.ACseats.push(currentrow.getpassenger().assignedseat);
							cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
							// want to delete passenger entry, overwrite with 0 seat?
							Passenger emptypassenger;
							emptypassenger.assignedrow = 0;
							emptypassenger.assignedseat = 'A';
							currentrow.insertppl(emptypassenger);
							// cout << "UPDATED PASSENGER = " << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << endl;
							currentrow.rowcondition("EMPTY");
							if(currentrow.getrow() == 1){
								currentrow.insertppl(passengerlist.dequeue());
								cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
								currentrow.rowcondition("WAITING");
							}
						}
						else{
							// missing state where: 1A wants to enter and 1C has to get out, but row 1 ACseats already empty because popped twice
							//cout << "C" << endl;
							if(int(currentrow.ACseats.top())>int(currentrow.getpassenger().assignedseat)){
								//cout << "D" << endl;
								//emptystack(currentrow.ACseats);
								currentrow.aisle.push(currentrow.ACseats.topAndPop());
								if(!currentrow.ACseats.isEmpty()){
									if(int(currentrow.ACseats.top())>int(currentrow.getpassenger().assignedseat)){
										currentrow.rowcondition("AC_OUT");
									}
								}
								else{
									currentrow.rowcondition("AC_EMPTY");
									//cout <<"EMPTY = AC" << endl;
								}
							}
							else{
								currentrow.ACseats.push(currentrow.getpassenger().assignedseat);
								cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
								/*
								Passenger emptypassenger;
								emptypassenger.assignedrow = 0;
								emptypassenger.assignedseat= 'Z';
								currentrow.insertppl(emptypassenger);
								*/
								currentrow.rowcondition("EMPTY");
								if(currentrow.getrow()==1){
									currentrow.insertppl(passengerlist.dequeue());
									cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
									currentrow.rowcondition("WAITING");
								}
							}
						}
					}

					else if((currentrow.getpassenger().assignedseat=='D')||(currentrow.getpassenger().assignedseat=='E')||(currentrow.getpassenger().assignedseat=='F')){
						if(currentrow.DFseats.isEmpty()){
							currentrow.DFseats.push(currentrow.getpassenger().assignedseat);
							cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
							// want to delete passenger entry, overwrite with 0 seat?
							Passenger emptypassenger;
							emptypassenger.assignedrow = 0;
							emptypassenger.assignedseat= 'A';
							currentrow.insertppl(emptypassenger);
							// cout << "UPDATED PASSENGER = " << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << endl;
							currentrow.rowcondition("EMPTY");
							if(currentrow.getrow()==1){
								currentrow.insertppl(passengerlist.dequeue());
								cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
								currentrow.rowcondition("WAITING");
							}
						}

						else{
							if(int(currentrow.DFseats.top())<int(currentrow.getpassenger().assignedseat)){
								currentrow.aisle.push(currentrow.DFseats.topAndPop());
								if(!currentrow.aisle.isEmpty()){
									if(int(currentrow.DFseats.top())<int(currentrow.getpassenger().assignedseat)){
										currentrow.rowcondition("DF_OUT");
									}
								}
								else{
									currentrow.rowcondition("DF_EMPTY");
								}
							}
							else{
								currentrow.DFseats.push(currentrow.getpassenger().assignedseat);
								cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
								/*
								Passenger emptypassenger;
								emptypassenger.assignedrow = 0;
								emptypassenger.assignedseat= 'Z';
								currentrow.insertppl(emptypassenger);
								*/
								currentrow.rowcondition("EMPTY");
								if(currentrow.getrow()==1){
									currentrow.insertppl(passengerlist.dequeue());
									cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
									currentrow.rowcondition("WAITING");
								}
							}
						}
					}
				}
				else if(currentrow.getstatus()=="STORING_LUGGAGE1"){
					currentrow.rowcondition("STORING_LUGGAGE2");
					cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " storing luggage (2)" << endl;
				}
				else{
					currentrow.rowcondition("STORING_LUGGAGE1");
					cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " storing luggage (1)" << endl;
				}
				// enqueue row back
				//cout << "B" << endl;
				rowqueue.enqueue(currentrow);
			}
			else{

				if(x==2){
					rowqueue.enqueue(currentrow);
					rowqueue = movepassengers(rowqueue);
					Row checkfirstrow = getfirstrow(rowqueue).getFront();
					//cout << "firstrowstatus in else = " << checkfirstrow.getstatus() << endl;
					
                    if(checkfirstrow.getstatus()== "EMPTY"){
						rowqueue = getfirstrow(rowqueue);
						Row firstrow = rowqueue.dequeue();
						cout << passengerlist.getFront().assignedrow << passengerlist.getFront().assignedseat << " entered plane" << endl;
						firstrow.insertppl(passengerlist.dequeue());
						firstrow.rowcondition("WAITING");
						rowqueue.enqueue(firstrow);
						rowqueue = shufflerow(rowqueue);
					}
					break;
				}
				// enqueue row back
				rowqueue.enqueue(currentrow);
			}
		}
		//rowloss(rowqueue);
		time = time + 5;
		cout << "time frame = " << time << endl;
	}
}

int main(int argc, char* argv[]){
	string filename = argv[1];
	boarding(filename);
	return 0;
}
