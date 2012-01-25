using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 100005;
vector< int > g[MAXN];
vector< bool > visited;

bool solve(int u, int remain, vector< int > &path) {
    if (path.size() > 0) {
        if (find(g[u].begin(), g[u].end(), path.back() ) == g[u].end() ){ // not connected to the last one in path
            return false;
        }
    }
    
    path.push_back( u );
    if (remain == 1) return true;
    visited[u] = true;
    for (int k = 0; k < g[u].size(); ++k) {
        int v = g[u][k];
        if (visited[v]) continue;

        if (solve(v, remain - 1, path)) {
            return true;
        }
    }
    visited[u] = false;
    path.pop_back();
    return false;
}

bool findFromT(const vector< int > &tees, int n, vector< int > &path) {
    for (int k = 0; k < tees.size(); ++k) {
        int t = tees[k];
        for (int kk = 0; kk < g[t].size(); ++kk){ 
            int r = g[t][kk];
            assert( g[r].size() == 2 );
            path.clear();
            if (solve(r, n, path)) return true;
        }
    }
    path.clear();
    return false;
}

int main(){
    #define INPUT_FILE "linear"
    #ifndef LOCAL    
    assert( freopen(INPUT_FILE ".in", "r", stdin) != NULL );
    assert( freopen(INPUT_FILE ".out", "w", stdout) != NULL );
    #endif
  
    int n; 
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        visited.assign(n, false);
    
        int gCount = 0, rCount = 0, tCount = 0;
        int startG = -1, startR = -1;
        vector< int > startT;

        for (int i = 0; i < n; ++i) {
            char type; scanf(" %c ", &type);
            if (type == 'G') {
                int x; scanf("%d", &x);
                g[i].push_back(x - 1);
                gCount++;
                startG = i;
            } else if (type == 'R') {
                int x, y; scanf("%d %d", &x, &y);
                g[i].push_back(x - 1);
                g[i].push_back(y - 1);
                rCount++;
                startR = i;
            } else { assert(type == 'T');
                int x, y, z; scanf("%d %d %d", &x, &y, &z);
                g[i].push_back(x - 1);
                g[i].push_back(y - 1);
                g[i].push_back(z - 1);
                tCount++;
                startT.push_back( i );
            }
        }       

        bool impossible = gCount > 2 or tCount > 2;        

        vector< int > path;
        
        if (!impossible) {
            if (gCount > 0) {
                impossible = !solve(startG, n, path);
            } else if (tCount == 0) {
                impossible = !solve(startR, n, path);
            } else {
                impossible = !findFromT(startT, n, path);
            }
        }
        
        if (!impossible) assert(path.size() == n);

        if (impossible) {
            puts("IMPOSSIBLE");
            continue;
        }
        for (int k = 0; k < n; ++k){ 
            if (k > 0) printf(" ");
            printf("%d", path[k] + 1);
        }
        puts("");
    }
  
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
