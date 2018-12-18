// Author Sean Davis

#include "tripper.h"
#include "RoadRunner.h"
#include <iostream>
#include <cstdio>

using namespace std;

Tripper::Tripper(Road *roads, int numRoads, int size)
{
  V = size * size;        // V is size * size
  graph = new int*[V];    // creating a new row of V elements
  roadID = new int*[V];
  for(int i = 0; i < V; i++) {  // how many columns
    graph[i] = new int[V];    // allocated space for a 2D graph
    roadID[i] = new int[V];
  }
  for (int i = 0; i < V; i++) {   // initializing all values in the 2D graph to be zero
    for (int j = 0; j < V; j++) {
      graph[i][j] = 0;  //distance
      roadID[i][j] = -1;  // ID
    }
  }
  for(int i = 0; i < numRoads; i++) {
    graph[roads[i].city1][roads[i].city2] = roads[i].distance;    // stores roads with data in it into our graph
    roadID[roads[i].city1][roads[i].city2] = roads[i].num;      //stores ID
  }
  //for(int i = 0; i < V; i++){
    //for(int j = 0; j < V; j++)
      //printf("%3d", graph[i][j]);
    //cout << endl;
  //}

  //for(int i = 0; i < numRoads; i++)
    //cout << "ID " << roads[i].num << " from " << roads[i].city1 << " to " << roads[i].city2 << endl;
} // Tripper()



Tripper::~Tripper()
{
  delete [] graph;
} // ~Tripper()


int Tripper::findPath(int city1, int city2, int path[], int *pathCount)
{
// city1 and city2 - dijkstras to find shortest path
// path[] stores the actual vertex numbers in the shortest path from city1 to city2
// pathcount - counts how many edges we end up using
  int start = city1;  
  int end = city2;
  int d[V];     // initializing an array of distance to vertices
  int p[V];     // initializing an array of previous vertices
  bool known[V];  // initializing an array of truth values for the table

for (int i = 0; i < V; i++) {   // initializing all the values
  known[i] = false;
  d[i] = INF;
  p[i] = -1;
}

d[start] = 0;
for (int count = 1; count < V; count++) {   // finding the min and assigning truth in table
   int min = INF, u;
   for(int i = 0; i < V; i++){
     if (!known[i] && d[i] <= min){
       min = d[i];
       u = i;
     }
   }
   known[u] = true;
   for (int w = 0; w < V; w++){   // checking for vertices
     if (graph[u][w] != 0 && !known[w] && d[u] + graph[u][w] < d[w]){
       d[w] = d[u] + graph[u][w];
       p[w] = u;
     }
   }
}

int cur = end, length = 0;
int P[V];
while (cur != start){
  P[length++] = cur;
  cur = p[cur];
}
P[length++] = start;
*pathCount = 0;
for (int i = length - 1; i > 0; i--){
  path[*pathCount] = roadID[P[i]][P[i-1]];
  *pathCount += 1;
}

//cout << city1 << "  " << city2 << ":  \n";
//for (int i = 0; i < V; i++)
  // printf("%2d %3d %4d %3d\n", i, known[i], d[i], p[i]);
//cout << "Path: ";
//for(int i = 0; i < *pathCount; i++)
  //cout << path[i] << ' ';
//cout << endl;

return d[end]; // returns shortest distance from dijkstras 
  
  
   // to avoid warning for now
}  // findPath()
