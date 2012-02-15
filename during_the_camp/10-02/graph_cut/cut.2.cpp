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
bitset<MAXN> visited;
vector< pair<int, int> > edges;

int K;

void dfs(int u, bool ignore) {
    if (visited[u]) return;
    visited[u] = true;
    foreach(out, g[u]) {
        if (ignore and *out < K) continue;
        int v = edges[*out].first;
        if (v == u) v = edges[*out].second;
        dfs(v, ignore);
    }
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
        }
        visited.reset();
        
        edges.clear();
        for (int i = 0; i < E; ++i) {
            int u, v; cin >> u >> v;
            u--, v--;
            edges.push_back(make_pair(u, v));
            g[u].push_back(i);
            g[v].push_back(i);
        }
        
        //puts("primera vez: ");
        int cnt1 = 0;
        For(i, 0, N) {
            if (!visited[i]) {
                //printf(" i = %d\n", i);                
                dfs(i, false);
                cnt1++;
            }
        }
        
        //puts("segunda vez: ");
        visited.reset();
        int cnt2 = 0;
        For(i, 0, N) {
            if (!visited[i]) {
                //printf(" i = %d\n", i);
                dfs(i, true);
                cnt2++;
            }
        }
        assert(cnt1 <= cnt2);
        
        //D(cnt1);
        //D(cnt2);
        puts(cnt2 > cnt1 ? "YES" : "NO");
    }
    return 0;
}
