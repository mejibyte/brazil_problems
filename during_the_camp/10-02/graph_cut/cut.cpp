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

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = true;
    foreach(out, g[u]) dfs(*out);
}

int main(){
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        
        int N, E, K;
        if (!(cin >> N >> E >> K)) break;
        assert(N >= 2);
        assert(E >= 1);
        //assert(K >= 1);
        for (int i = 0; i < N; ++i) {
            g[i].clear();
        }
        visited.reset();
        
        for (int i = 0; i < E; ++i) {
            int u, v; cin >> u >> v;
            u--, v--;
            if (i < K) continue;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        int cnt = 0;
        For(i, 0, N) {
            if (!visited[i]) {
                dfs(i);
                cnt++;
            }
        }
        assert(cnt > 0);
        puts(cnt > 1 ? "YES" : "NO");
    }
    return 0;
}
