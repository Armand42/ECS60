// Author Sean Davis
#ifndef _TRIPPER_H
#define	_TRIPPER_H

#include "RoadRunner.h"

#define INF 1000000000

class Tripper {
  int **graph;  // unknown size for a 2D graph
  int **roadID;
  int V; // number of cities
public:
  Tripper(Road *roads, int numRoads, int size);
  int findPath(int city1, int city2, int path[], int *pathCount);
  ~Tripper();
private:

}; // class Tripper

#endif	/* _TRIPPER_H */

