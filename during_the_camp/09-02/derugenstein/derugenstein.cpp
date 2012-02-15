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

const int INF = 1 << 29;
int g [105][105];
int n;

int dx [4] = { 0, 0, -1, +1};
int dy [4] = { +1, -1, 0, 0};

int id (int x, int y){
    return (x * n + y);    
}

void add_edge(int x0, int y0, int x1, int y1){
    if (x1 < 0 or x1 >= n or y1 < 0 or y1 >= n) return;
    int p = id(x0, y0);
    int q = id(x1, y1);
    g[p][q] = 1;
}

void floyd (){
    for (int k = 0; k < n * n; k++){
        for (int i = 0; i < n * n; i++){
            for (int j = 0; j < n * n; j++){
                g[i][j] = min (g[i][j], g[i][k] + g[k][j]);
            }    
        }    
    }    
}


int main(){
    while (cin >> n){
        if (n == 0) break;
        
        for (int i = 0; i < n * n; i++){
            for (int j = 0; j < n * n; j++){
                if (i == j) g[i][j] = 0;
                else g[i][j] = INF;
            }
        }
        
        for (int y = n - 1; y >= 0; y--){
            for (int x = 0; x < n; x++){
                for (int k = 0; k < 4; k++){
                    int a; cin >> a;
                    if (a == 1){
                        add_edge(x, y, x + dx[k], y + dy[k]);
                    }    
                }
            }    
        }
        
        floyd();
        int q; cin >> q;
        for (int i = 0; i < q; i++){
            int x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            if (g[id(x0, y0)][id(x1, y1)] >= INF){
                puts("Impossible");    
            }else{
                printf("%d\n", g[id(x0, y0)][id(x1, y1)]); 
            }
        }
         
    }
    return 0;
}
