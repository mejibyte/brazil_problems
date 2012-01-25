// Wrong Answer on test 9
// Andrés Mejía
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

const int MAXN = 10005;
vector< int > G[2][MAXN];
vector< int > R[2][MAXN];
int N[2], M[2];
int grundy[2][MAXN];
const int oo = (1 << 30);

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
                if (dist[u] % 2 == 0) { // normal BFS. 
                    //v can't have the same grundy number as u (which is K), because there's an edge from v to u in the original graph.
                    
                    // for even positions, ignore marked and infinities
                    if (grundy[v] != -1) continue;
                    dist[v] = dist[u] + 1;
                    q.push( v );
                } else {
                    //v might have grundy number K, as long as we are sure that there are no edges to bigger grundy numbers.
                    
                    // for odd positions, ignored marked with anything else than infinity
                    if (grundy[v] != -1 and grundy[v] != oo) continue;
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
        }
        
        // put infinity in nodes that don't have an edge pointing to k
        for (int i = 0; i < n; ++i) {
            if (grundy[i] != -1) continue;
            bool has = false;
            for (int e = 0; e < G[i].size() and !has; ++e) {
                int v = G[i][e];
                if (grundy[v] == k) has = true;
            }
            if (!has) grundy[i] = oo;
        }
    }
    // printf("grundy numbers are:\n");
    // for (int i = 0; i < n; ++i) {
    //     printf("grundy[%d] = %d\n", i + 1, grundy[i]);
    // }
}

int sumInfinity(int g,   int u, vector< int > G[MAXN], int grundy[MAXN]) {
    vector< int > options; // options from infinity
    for (int e = 0; e < G[u].size(); ++e) {
        int v = G[u][e];
        assert( grundy[v] != -1 );
        if (grundy[v] == oo) continue;
        options.push_back( grundy[v] );
    }
    if (options.size() == 0) return g;
    for (int k = 0; k < options.size(); ++k) {
        if (g ^ options[k] == 0) return 1; // win
    }
    return 0;
}

int main(){
    #ifndef LOCAL
    freopen("smith.in", "r", stdin);
    freopen("smith.out", "w", stdout);
    #endif
    
    for (int g = 0; g < 2; ++g) {
        scanf("%d %d", &N[g], &M[g]);
        for (int i = 0; i < M[g]; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            G[g][u].push_back( v );
            R[g][v].push_back( u );
        }
    }
    
    // Precompute
    calculate(G[0], R[0], N[0], grundy[0]);
    calculate(G[1], R[1], N[1], grundy[1]);
    
    // Answer queries
    int T; scanf("%d", &T);
    while (T--) {
        int u0, u1;
        scanf("%d %d", &u0, &u1);
        u0--, u1--;
        
        int g0 = grundy[0][u0], g1 = grundy[1][u1];
        
        if (g0 == oo and g1 == oo) {
            puts("draw");
            continue;
        }
        
        if (g0 != oo and g1 != oo) {
            puts(g0 ^ g1 == 0 ? "second" : "first");
            continue;
        }
        
        if (g0 == oo) { assert(g1 != oo);
            int ans = sumInfinity(g1, u0, G[0], grundy[0]);
            puts(ans == 0 ? "second" : "first");
        } else { assert(g0 != oo and g1 == oo);
            int ans = sumInfinity(g0, u1, G[1], grundy[0]);
            puts(ans == 0 ? "second" : "first");
        }
    }
    return 0;
}