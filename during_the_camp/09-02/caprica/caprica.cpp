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

const int MAXN = 1005;

bool B[MAXN];
int dist[MAXN];
vector< pair<int, int> > g[MAXN];

int main(){
    ios::sync_with_stdio(false);
    int N, M, a, b;
    while (cin >> N >> M >> a >> b) {
        if (N == 0 and M == 0 and a == 0 and b == 0) break;
        
        for (int i = 0; i < N; ++i) {
            dist[i] = (1 << 29);
            B[i] = false;
            g[i].clear();
        }
        
        priority_queue< pair<int, int>, vector<pair<int, int> >, greater< pair<int, int> > > q;
        for (int i = 0; i < a; ++i) {
            int u; cin >> u;
            dist[u] = 0;
            q.push(make_pair(0, u));
        }
        for (int i = 0; i < b; ++i) {
            int u; cin >> u;
            B[u] = true;
        }
        for (int i = 0; i < M; ++i) {
            int u, v, w; cin >> u >> v >> w;
            g[u].push_back( make_pair(v, w) );
            g[v].push_back( make_pair(u, w) );
        }
        
        int ans = (1 << 30);
        
        while (q.size() > 0) {
            int u = q.top().second;
            int w = q.top().first;
            q.pop();
            if (B[u]) ans = min(ans, dist[u]);
            if (w > dist[u]) continue;
            foreach(out, g[u]) {
                int v = out->first, wExtra = out->second;
                if (w + wExtra < dist[v]) {
                    dist[v] = w + wExtra;
                    q.push( make_pair(dist[v], v) );
                }
            }
        }
        
        cout << ans << endl;
    }
    return 0;
}
