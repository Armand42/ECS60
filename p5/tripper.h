// Author Sean Davis
#ifndef _TRIPPER_H
#define	_TRIPPER_H

#include "RoadRunner.h"
#define INF 1000000000

struct Pair {
    int dist;
    int city;
    Pair () {}
    Pair(int d, int c) : dist(d), city(c) {}
    bool operator<(const Pair &p) const { return dist < p.dist;}
};

class Underflow { };
class Overflow  { };

class MinHeap {
public:
	explicit MinHeap( int size = 100 ) : currentSize(0), capacity(size) 
	{ 
		array = new Pair[size+1]; 
		hash = new int[size+1];
		for (int i = 0; i < size+1; i++) hash[i] = -1;
	}
	~MinHeap() { delete [] array; delete [] hash;}
	bool isEmpty( ) const { return currentSize == 0; }
	const Pair findMin() const { if (isEmpty()) throw Underflow(); return array[1];}
	void insert(const Pair &x){
		if (currentSize == capacity-1) throw Overflow();
		int idx = ++currentSize;
		for(; idx > 1 && x < array[idx/2]; idx /= 2){
			array[idx] = array[idx/2];
			hash[array[idx/2].city] = idx;
		}
		array[idx] = x;
		hash[x.city] = idx;
	}
	void deleteMin() {
		if (isEmpty()) throw Underflow();
		hash[array[1].city] = -1;
		hash[array[currentSize].city] = 1;
		array[1] = array[currentSize--];
		shiftDown(1);
	}
	void decreaseKey(int idx, const Pair &x){
		for(; idx > 1 && x < array[idx/2]; idx /= 2){
			array[idx] = array[idx/2];
			hash[array[idx/2].city] = idx;
		}
		array[idx] = x;
		hash[x.city] = idx;
	}
	int getIndex(int city) { return hash[city];}
private:
	int currentSize, capacity;
	Pair *array;
	int *hash;
	void shiftDown(int idx) {
		int child;
		Pair tmp = array[idx];
		for(; idx * 2 <= currentSize; idx = child){
			child = idx * 2;
			if (child != currentSize && array[child+1] < array[child])
				child++;
			if (array[child] < tmp) {
				array[idx] = array[child];
				hash[array[child].city] = idx;
			}
			else
				break;
		}
		array[idx] = tmp;
		hash[tmp.city] = idx;
	}
};
class Tripper {
  int **graph;  // unknown size for a 2D graph
  int V; // number of cities
public:
  Tripper(Road *roads, int numRoads, int size);
  int findPath(int city1, int city2, int path[], int *pathCount);
  ~Tripper();
private:

}; // class Tripper

#endif	/* _TRIPPER_H */

