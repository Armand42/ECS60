// Author Sean Davis

#include "tripper.h"
#include "RoadRunner.h"
//#include "BinaryHeap.h"

//using namespace std;




Tripper::Tripper(Road *roads, int numRoads, int size)
{
  V = size * size;        // V is size * size
  graph = new int*[V]; // assign V rows to the adj list
  for(int i = 0; i < V; i++){
    graph[i] = new int[25]; // create an empty list and assign to that rows
    graph[i][0] = 0;        // assiging zero to the first value of the list
  }
  
  for(int i = 0; i < numRoads; i++) {
    int u = roads[i].city1;
    int v = roads[i].city2;
    int s = graph[u][0];
    graph[u][0] += 1;
    
    graph[u][3 * s + 1] = v;              // first element data
    graph[u][3 * s + 2] = roads[i].distance;  // second element data
    graph[u][3 * s + 3] = roads[i].num;       // third element data
  }
} // Tripper()



Tripper::~Tripper()
{
  for(int i = 0; i < V; i++){
     delete [] graph[i];
  }
  delete [] graph;
} // ~Tripper()


int Tripper::findPath(int city1, int city2, int path[], int *pathCount)
{
// city1 and city2 - dijkstras to find shortest path
// path[] stores the actual vertex numbers in the shortest path from city1 to city2
// pathcount - counts how many edges we end up using
  int start = city1;  
  int end = city2;
  int dist[V];     // initializing an array of distance to vertices
  int previous[V];     // initializing an array of previous vertices
  bool known[V];  // initializing an array of truth values for the table

int d, u, v, w, id, idx;

for (int i = 0; i < V; i++) {   // initializing all the values
  known[i] = false;
  dist[i] = INF;
  previous[i] = -1;
}

dist[start] = 0;
MinHeap heap(V);
heap.insert(Pair(0, start));

while (!heap.isEmpty()){
   Pair top = heap.findMin();
   heap.deleteMin();
   d = top.dist;
   u = top.city;
   //if (known[u]) continue;
   if (u == end) break;
   known[u] = true;
   for (int i = 0; i < graph[u][0]; i++){     //dijkstras
        v = graph[u][3*i+1];
        d = graph[u][3*i+2];
        if (!known[v] && d + dist[u] < dist[v]){
          dist[v] = d + dist[u];
          previous[v] = u;
          idx = heap.getIndex(v);
          if (idx != -1){
            heap.decreaseKey(idx, Pair(dist[v], v));
          }
          else{
              heap.insert(Pair(dist[v], v));
          }
        }
   }
}

int cur = end, length = 0;
int P[V];
while (cur != start){
  P[length++] = cur;
  cur = previous[cur];
}
P[length++] = start;
*pathCount = 0;
for (int i = length - 1; i > 0; i--){
  u = P[i];
  v = P[i-1];
  for (int j = 0; j < graph[u][0]; j++){
    w = graph[u][3*j+1];
    id = graph[u][3*j+3];
    if (w == v){
      path[*pathCount] = id;
      *pathCount += 1;
      break;
    }
  }
}

return dist[end]; // returns shortest distance from dijkstras 
  
   // to avoid warning for now
}  // findPath()
