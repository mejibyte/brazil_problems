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

const int MAXN = 505;
const int oo = (1 << 30);

inline int in(int u) {
    return 2 * u;
}

inline int out(int u) {
    return 2 * u + 1;
}

vector< int > g[MAXN];
int cap[MAXN][MAXN];
int weight[MAXN][MAXN];
int residual[MAXN][MAXN];

void link(int u, int v, int c) {
    cap[u][v] = c;
    //g[u].push_back(v);
    //g[v].push_back(u);
}

int prev[MAXN];
int ford(int n, int s, int t, int maxDanger) {
    memcpy(residual, cap, sizeof cap);
    int ans = 0;
    while (true) {
        For(i, 0, n) prev[i] = -1;
        queue< int > q;
        q.push(s);
        while (q.size() and prev[t] == -1) {
            int u = q.front();
            q.pop();
            vector< int > &out = g[u];
            for (int v = 0; v < n; ++v) {
                assert( weight[u][v] == weight[v][u] );
                if ( weight[u][v] > maxDanger ) continue;
                if (v != s and prev[v] == -1 and residual[u][v] > 0) prev[v] = u, q.push(v);
            }
        }
        if (prev[t] == -1) break;
        int bottleneck = INT_MAX;
        for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
            bottleneck = min(bottleneck, residual[u][v]);
        }
        for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
            residual[u][v] -= bottleneck;
            residual[v][u] += bottleneck;
        }            
        ans += bottleneck;
    }
    return ans;
}

void setWeight(int u, int v, int danger) {
    weight[u][v] = weight[v][u] = danger;
}

int main(){
    int n;
    int run = 0;
    while (scanf("%d", &n) == 1){
        if (n == 0) break;
        
        n += 2; // source, sink, y las dos aldeas
        int last = n - 1;
        n *= 2;
        n += 2;
        
        int source = n - 2, sink = n - 1;
        
        
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            for (int j = 0; j < n; ++j) {
                cap[i][j] = 0;
                weight[i][j] = (1 << 30);
            }
        }
        
        run++;
        int t;
        scanf("%d", &t);
        For (i, 0, t){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            if (v < u) swap(u, v);
            assert(u < v);

            link( out(u), in(v), oo );
            setWeight( out(u), in(v), w );
        }
        int k;
        scanf("%d", &k);   
        
        
        for (int i = 1; i < last; ++i) {
            link(in(i), out(i), 1);
            setWeight(in(i), out(i), 0);
        }
        link(in(0), out(0), oo);
        setWeight(in(0), out(0), 0);
        link(in(last), out(last), oo);
        setWeight(in(last), out(last), 0);
        
        assert( out(last) == n - 3 );
        
        link(source, in(0), k);
        setWeight(source, in(0), 0);
        link(out(last), sink, k);
        setWeight(out(last), sink, 0);
        
//        D(n);
//        puts("Cap:");
//        for (int i = 0; i < n; ++i) {
//            printf("i = %3d | ", i);
//            for (int j = 0; j < n; ++j) {
//                if (cap[i][j] == oo) printf("  oo ");
//                else printf("%4d ", cap[i][j]);
//            }
//            puts("");
//        }

        
        printf("Case %d: ", run);   
        int f = ford(n, source, sink, 100000);
        if (f < k) {
            puts("no solution");
        } else {
            int low = 0, high = 100000;
            while (low < high) {
                int m = (low + high) / 2;
                if (ford(n, source, sink, m) >= k) { // solution
                    high = m;
                } else {
                    low = m + 1;
                }
            }
            printf("%d\n", low);            
        }
    }
    return 0;
}
