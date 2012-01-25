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
bool visited[MAXN];

void dfs(int u, vector< int > &path) {
    if (visited[u]) return;
    visited[u] = true;
    path.push_back( u );
    for (int k = 0; k < g[u].size(); ++k) {
        dfs(g[u][k], path);
    }
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
            visited[i] = false;
        }
    
        int gCount = 0, rCount = 0, tCount = 0;
        int startG = -1, startR = -1;

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
            }
        }       
        
        if (gCount > 2 or tCount > 2) {
            puts("IMPOSSIBLE");
            continue;
        }
        
        vector< int > path;
        if (gCount > 0) {
            assert(startG != -1);  
            dfs(startG, path);
        } else if (tCount == 0) { // just start on any R, and we should get a simple loop
            dfs(startR, path);
        } else { assert(rCount > 0); assert(startR != -1);
            dfs(startR, path);
        }
        if (path.size() != n) {
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
