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

#include <bitset>

const int MAXN = 505;
vector< int > g[MAXN];
int color[MAXN];
vector< pair<int, int> > edges;

int K;

int other(int u, int e) {
    int v = edges[e].first;
    if (v == u) v = edges[e].second;
    return v;
}

bool colorize(int u, int c) {
    if (color[u] != -1) return c == color[u];
    
    color[u] = c;
    foreach(e, g[u]) {
        int v = other(u, *e);
        bool change = (*e < K);
        if (!colorize(v, c ^ change)) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        
        int N, E;
        if (!(cin >> N >> E >> K)) break;
        assert(N >= 2);
        assert(E >= 1);
        //assert(K >= 1);
        for (int i = 0; i < N; ++i) {
            g[i].clear();
            color[i] = -1;
        }
      
        edges.clear();
        for (int i = 0; i < E; ++i) {
            int u, v; cin >> u >> v;
            u--, v--;
            edges.push_back(make_pair(u, v));
            g[u].push_back(i);
            g[v].push_back(i);
        }
        
        int ans = true;
        for (int i = 0; i < N; ++i) { 
            if (color[i] == -1) {
                if (!colorize(i, 0)){ ans = false; break; }
            }
        }
        cout << (ans ? "YES" : "NO") << endl;
    }
    return 0;
}
