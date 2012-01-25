// Accepted
// Iterative algorithm to find Grundy numbers (right now only works in acyclic graphs)

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

#define INPUT_FILE "result"

const int MAXN = 5005;

// Fills the grundy array with the appropriate grundy number for each node
void calculate(vector< int > G[MAXN], vector< int > R[MAXN], int n, int grundy[MAXN]) {
    static int count[MAXN];
    static int dist[MAXN];
    
    for (int i = 0; i < n; ++i) {
        count[i] = G[i].size();
        grundy[i] = -1;
    }
    
    for (int k = 0, changed = true; changed; ++k) {
        changed = false;

        queue< int > q;
        for (int i = 0; i < n; ++i) {
            dist[i] = -1;
            
            count[i] = 0;
            for (int e = 0; e < G[i].size(); ++e) {
                int v = G[i][e];
                count[i] += (grundy[v] == -1 or grundy[v] > k);
            }
            if (count[i] == 0 and grundy[i] == -1) {
                dist[i] = 0;
                q.push( i );
                // printf("on iteration k = %d, node i = %d has 0 count\n", k, i + 1);
            }
        }
        
        while (q.size() > 0) {
            int u = q.front(); q.pop();
            assert( dist[u] != -1 );
            for (int e = 0; e < R[u].size(); ++e) {
                int v = R[u][e];
                if (dist[v] != -1) continue;
                if (grundy[v] != -1) continue;
                if (dist[u] % 2 == 0) { // normal BFS. 
                    //v can't have the same grundy number as u (which is K), because there's an edge from v to u in the original graph.
                    dist[v] = dist[u] + 1;
                    q.push( v );
                } else {
                    //v might have grundy number K, as long as we are sure that there are no edges to bigger grundy numbers.
                    if (--count[v] == 0) {
                        dist[v] = dist[u] + 1;
                        q.push( v );
                    }
                }
            }
        }
        
        
        for (int i = 0; i < n; ++i) {
            if (dist[i] % 2 == 0) {
                assert( grundy[i] == -1 );
                grundy[i] = k;
                changed = true;
            }
            // printf("grundy[%d] = %d\n", i + 1, grundy[i]);
        }
    }
}

vector< int > g[MAXN];
vector< int > r[MAXN];

int main(){
    #ifndef LOCAL    
    assert( freopen(INPUT_FILE ".in", "r", stdin) != NULL );
    assert( freopen(INPUT_FILE ".out", "w", stdout) != NULL );
    #endif
  
    int n, e; scanf("%d %d", &n, &e);
    for (int i = 0; i < e; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--, y--;
        g[x].push_back( y );
        r[y].push_back( x );
    }
    
    static int grundy[MAXN];
    calculate(g, r, n, grundy);
    
    for (int i = 0; i < n; ++i) {
        printf("%d\n", grundy[i]);
    }
  
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
