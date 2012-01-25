// Accepted

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

#define INPUT_FILE "gg"

const int MAXN = 100005;
vector< int > g[MAXN];

enum { White, Gray, Black };
int status[MAXN];
int memo[MAXN][2];

bool cycle(int u) {
    if (status[u] == Black) return false;
    if (status[u] == Gray) return true;
    status[u] = Gray;
    for (int k = 0; k < g[u].size(); ++k) {
        if (cycle(g[u][k])) return true;
    }
    status[u] = Black;
    return false;
}

bool findPath(int u, int parity) {
    if (g[u].size() == 0) return parity == 0;
    if (memo[u][parity] != -1) return memo[u][parity];
    for (int k = 0; k < g[u].size(); ++k) {
        if (findPath(g[u][k], !parity)) {
            return memo[u][parity] = true;
        }
    }
    return memo[u][parity] = false;
}

int main(){
    #ifndef LOCAL    
    assert( freopen(INPUT_FILE ".in", "r", stdin) != NULL );
    assert( freopen(INPUT_FILE ".out", "w", stdout) != NULL );
    #endif
    
    
    int V, E, start, run = 1;
    while (scanf("%d %d %d", &V, &E, &start) == 3) {
        if (V == 0 and E == 0 and start == 0) break;
        
        start--;
        
        for (int i = 0; i < V; ++i) {
            g[i].clear();
            status[i] = White;
            memo[i][0] = memo[i][1] = -1;
        }
        
        for (int i = 0; i < E; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            g[u].push_back(v);
        }
        
        if (cycle(start) || findPath(start, 0)) {
            printf("Players can avoid first player winning in game %d.\n", run);;
        } else {
            printf("First player always wins in game %d.\n", run);
        }
        run++;
    }
    
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
