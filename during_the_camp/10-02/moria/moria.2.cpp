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

int N, E;
const int MAXN = 205;


vector< int > g[MAXN];

int prev[MAXN];
int cap[MAXN][MAXN];
int residual[MAXN][MAXN];
int fordFulkerson(int n, int s, int t){
  memcpy(residual, cap, sizeof cap);

  int ans = 0;
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      vector<int> &out = g[u];
      for (int k = 0, m = out.size(); k<m; ++k){
        int v = out[k];
        if (v != s && prev[v] == -1 && residual[u][v] > 0)
          prev[v] = u, q.push(v);
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

typedef int node;
typedef char color;
const color WHITE = 0, GRAY = 1, BLACK = 2;
map<node, color> colors;
map<node, int> d, low;

set<node> cameras; //contendrá los puntos de articulación
int timeCount;

// Uso: Para cada nodo u:
// colors[u] = WHITE, g[u] = Aristas salientes de u.
// Funciona para grafos no dirigidos.

void dfs(node v, bool isRoot = true){
  colors[v] = GRAY;
  d[v] = low[v] = ++timeCount;
  const vector<node> &neighbors = g[v];
  int count = 0;
  for (int i=0; i<neighbors.size(); ++i){
    if (colors[neighbors[i]] == WHITE){
      //(v, neighbors[i]) is a tree edge
      dfs(neighbors[i], false);
      if (!isRoot && low[neighbors[i]] >= d[v]){
        //current node is an articulation point
        cameras.insert(v);
      }
      low[v] = min(low[v], low[neighbors[i]]);
      ++count;
    }else{ // (v, neighbors[i]) is a back edge
      low[v] = min(low[v], d[neighbors[i]]);
    }
  }
  if (isRoot && count > 1){
    //Is root and has two neighbors in the DFS-tree
    cameras.insert(v);
  }
  colors[v] = BLACK;
}




int main(){
    int run = 1;
    int N, E;
    bool first = true;
    while (cin >> N >> E) {
        assert(N > 0); assert(E > 0);
        if (!first) puts("");
        first = false;
        
        for (int i = 0; i < N; ++i) {
            g[i].clear();
        }
        memset(cap, 0, sizeof cap);
        
        for (int i = 0; i < E; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            u--, v--;
            cap[u][v] += c;
            cap[v][u] += c;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int root; cin >> root; root--;
        
        for (int i = 0; i < N; ++i) {
            colors[i] = WHITE;
            d[i] = -1;
        }
        timeCount = 0;
        cameras.clear();
        
        for (int i = 0; i < N; ++i) {
            if (d[i] == -1) {
                dfs(i);
            }
        }
        
        cameras.erase(root);
        if (cameras.size() == 0) {
            for (int i = 0; i < N; ++i) if (i != root) cameras.insert(i);
        }
        
        printf("Case %d\n", run++);
        printf("\n");
        printf("Points: %d\n", cameras.size());
        
        vector< int > flows;
        foreach(c, cameras) {
            int f = fordFulkerson(N, root, *c);
            flows.push_back( f );
        }
        sort(flows.begin(), flows.end(), greater<int>());
        for (int i = 0; i < flows.size(); ++i) {
            printf("%d\n", flows[i]);
        }
    
        
        
    }
    return 0;
}
