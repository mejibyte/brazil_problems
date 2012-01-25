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

const int MAXN = 105;
vector <pair <int, int> > g [MAXN];

const int oo = (1 << 30);

bool used[MAXN][MAXN];

int from[MAXN];
int dist[MAXN];

void dijkstra(int s, int f, int n) {
    for (int i = 0; i < n; ++i) {
        dist[i] = oo;
    }
    dist[s] = 0;
    priority_queue< pair<int, int>, vector<pair<int, int> >, greater< pair<int, int> > > q;
    q.push(make_pair(0, s));
    while (q.size() ) {
        pair< int, int > cur = q.top(); q.pop();
        int u = cur.second, w = cur.first;
        //printf("popped (u=%d, w=%d)\n", u, w);
        if (u == f) {
            break;
        }
        if (w > dist[u]) continue;
        
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k].second;
            if (used[u][v]) continue;
            int w_extra = g[u][k].first;
            if (w + w_extra >= dist[v]) continue;
            dist[v] = w + w_extra;
            from[v] = u;
            q.push( make_pair(dist[v], v) );
        }
    }
}

int main(){
    int nodes;
    while (scanf("%d ", &nodes) == 1){
        if (nodes == 0) break;
        
        for (int i = 0; i < nodes; ++i) {
            g[i].clear();
            for (int j = 0; j < nodes; ++j) {
                used[i][j] = false;
            }
        }
        
        int edges;
        scanf("%d ", &edges);
        for (int i = 0; i < edges; i++){
            int u, v, w;
            scanf("%d %d %d ", &u, &v, &w);
            u--, v--;
            g[u].push_back(make_pair(w, v));
            g[v].push_back(make_pair(w, u));    
        }
       
        dijkstra(0, nodes - 1, nodes);
        if (dist[nodes - 1] == oo) {
            puts("Back to jail");
            continue;
        }
        long long ans = dist[nodes - 1];
        
        for (int u = nodes - 1; u != 0; u = from[u]) {
            used[from[u]][u] = true;
            for (int k = 0; k < g[u].size(); ++k) {
                int v = g[u][k].second;
                if (v != from[u]) continue;
                
                g[u][k].first *= -1;
            }
        }
        dijkstra(0, nodes - 1, nodes);
        
        if (dist[nodes - 1] == oo) {
            puts("Back to jail");
            continue;            
        }

        ans += dist[nodes - 1];
        cout << ans << endl;
            
    }
    return 0;
}
