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
int cunt[MAXN];
int dist[MAXN];

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
            cunt[i] = 0;
            dist[i] = -1;
        }
        
        for (int i = 0; i < E; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            g[v].push_back( u );
            cunt[u]++;
        }
        
        queue< int > q;
        for (int i = 0; i < V; ++i) {
            if (cunt[i] == 0) {
                dist[i] = 0;
                q.push(i);
            }
        }
        while (q.size() > 0) {
            int u = q.front();
            q.pop();
            
            //printf("popped %d with distance %d\n", u + 1, dist[u]);
            
            for (int k = 0; k < g[u].size(); ++k) {
                int v = g[u][k];
                if (dist[u] & 1) {
                    if (--cunt[v] == 0) {
                        if (dist[v] == -1) {
                            dist[v] = dist[u] + 1;
                            q.push( v );
                        }
                    }
                } else { // normal BFS
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push( v );
                    }
                }
            }
        }
        
        if (dist[start] == -1) {
            printf("Players can avoid first player winning in game %d.\n", run);
        } else if (dist[start] & 1) {
            printf("First player always wins in game %d.\n", run);
        } else {
            //printf("Second player always wins in game %d.\n", run);
            //printf("Players can avoid both players winning in game %d.\n", run);            
            printf("Second player sometimes wins in game %d.\n", run);
        }
        run++;
    }
    
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
