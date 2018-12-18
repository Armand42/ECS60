#include <iostream>
#include "vector.h"
#include "BinaryHeap.h"

using namespace std;
void insert(int e, int r, vector< vector<int> > &a){
    int s = a[r].size();
    a[r].resize(s + 1);
    a[r][s] = e;
}
int main(){
    vector< vector<int> > a;
    a.resize(5);
    for(int i = 0; i < a.size(); i++){
        vector<int> b;
        a[i] = b;
    }
    //insert to a[2]
    insert(2, 1, a);
    insert(3, 2, a);
    insert(4, 1, a);
    insert(5, 4, a);

    for(int i = 0; i < a.size(); i++){
        if (a[i].size() > 0) {
            cout << "Row " << i << ": ";
            for (int j = 0; j < a[i].size(); j++){
                cout << a[i][j] << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}