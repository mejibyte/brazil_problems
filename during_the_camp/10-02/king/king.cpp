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

const int MAXN = 1005 * 2;

int N;
vector< int > g[MAXN];

inline int no(int u) {
    return (u < N ? u + N : u - N);
}

void addOr(int u, int v) {
    g[no(u)].push_back(v);
    g[no(v)].push_back(u);
}

/* Complexity: O(E + V)
 Tarjan's algorithm for finding strongly connected
components.

 *d[i] = Discovery time of node i. (Initialize to -1)
 *low[i] = Lowest discovery time reachable from node
 i. (Doesn't need to be initialized)
 *scc[i] = Strongly connected component of node i. (Doesn't
 need to be initialized)
 *s = Stack used by the algorithm (Initialize to an empty
 stack)
 *stacked[i] = True if i was pushed into s. (Initialize to
 false)
 *ticks = Clock used for discovery times (Initialize to 0)
 *current_scc = ID of the current_scc being discovered
 (Initialize to 0)
*/
int d[MAXN], low[MAXN], scc[MAXN];
bool stacked[MAXN];
stack<int> s;
int ticks, current_scc;
void tarjan(int u){
  d[u] = low[u] = ticks++;
  s.push(u);
  stacked[u] = true;
  const vector<int> &out = g[u];
  for (int k=0, m=out.size(); k<m; ++k){
    const int &v = out[k];
    if (d[v] == -1){
      tarjan(v);
      if (low[v] < low[u]) low[u] = low[v];
    }else if (stacked[v]){
      if (low[v] < low[u]) low[u] = low[v];
    }
  }
  if (d[u] == low[u]){
    int v;
    do{
      v = s.top();
      s.pop();
      stacked[v] = false;
      scc[v] = current_scc;
    }while (u != v);
    current_scc++;
  }
}


int main(){
    ios::sync_with_stdio(false);
    
    while (cin >> N) {
        if (N == 0) break;
        
        for (int i = 0; i < 2*N; ++i) {
            g[i].clear();
            d[i] = -1;
        }
        ticks = 0;
        current_scc = 0;
        while (s.size() > 0) s.pop();
        
        For(k, 0, N) {
            char type; int u, v;
            cin >> type >> u;
            if (type == 'U') u = no(u);
            
            cin >> type >> v;
            if (type == 'U') v = no(v);
            addOr(u, v);
        }
        
        For(i, 0, 2*N) if (d[i] == -1) tarjan(i);
        
        bool ok = true;
        For(i, 0, N) {
            if (scc[i] == scc[no(i)]) { ok = false; break; }
        }
       cout << (ok ? "Y" : "N") << endl;
    }
    return 0;
}
