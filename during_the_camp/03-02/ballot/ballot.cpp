using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////
int pop [500005];
int n, b;

bool can(int l){
    //If it can be done assigning l peopel per box
    int cnt = 0;
    for (int i = 0; i < n; i++){        
        cnt  += (pop[i] + (l - 1)) / l;
        if (cnt > b) return false;   
    }   
    return true;
}


int main(){
    while (scanf("%d %d", &n, &b) == 2) {
        if (n == -1 and b == -1) break;
        int hi = 0;
        for (int i = 0; i < n; i++){
             scanf("%d", &pop[i]);
             hi = max(hi, pop[i]);    
        }
        int lo = 1;
        while (hi > lo){
            int m = ( hi + lo ) / 2;
            if (can(m)){
                hi = m;   
            }else{
                lo = m + 1;
            }
        }
        cout << lo << endl;
            
    }
    return 0;
}
