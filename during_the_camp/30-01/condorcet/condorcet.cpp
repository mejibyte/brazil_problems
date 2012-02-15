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
int rank [505][2505];
int ballots, candidates;

void solve(){
    for (int u = 0; u < candidates; u++){
        bool is_condorcet = true;
        for (int v = 0; v < candidates; v++){
            if (u == v) continue;
            int s = 0; // En cuantas balotas u le gano a v
            for (int i = 0; i < ballots; i++){
                if (rank[i][u] < rank[i][v]) s++;    
            }
            if (s <= ballots - s) {
                is_condorcet = false;
                break;
            }
        }
        if (is_condorcet){
            printf("%d\n", u);
            return;   
        }    
    }
    printf("No Condorcet winner\n");  
}

int main(){
    int run = 0;
    while (scanf("%d %d", &ballots, &candidates) == 2){
        if(ballots == 0 and candidates == 0) break;
        run++;       
        for (int i = 0; i < ballots; i++){
            for (int j = 0; j < candidates; j++){
                int c; scanf("%d", &c);
                rank[i][c] = j;
            }               
        }
        printf("Case %d: ", run);
        solve();
    }
    
    return 0;
}
