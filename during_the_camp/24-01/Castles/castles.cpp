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

int A[MAXN], B[MAXN];
vector< int > g[MAXN];

bool comp(pair<int, int> a, pair<int, int> b){
  if ( 1LL * a.second * b.first != 1LL * a.first * b.second)
       return 1LL * a.second * b.first > 1LL * a.first * b.second;
  return a.second > b.second;
}

pair< int, int > dfs(int u, int parent = -1) {
    vector< pair<int, int> > sons(1, make_pair(B[u], A[u]));
    for (int k = 0; k < g[u].size(); ++k) {
        int v = g[u][k];
        if (v == parent) continue;
        sons.push_back( dfs(v, u) );
    }
    sort( sons.begin() + 1, sons.end(), comp );
    
    //printf(" On node %d: Sons are: ", u );
//    foreach(p, sons) {
//        printf("(%d, %d) ", p->first, p->second);
//    }
//    puts("");
    
    long long int need = 0, alive = 0;
    for (int k = 0; k < sons.size(); ++k) {
        int b = sons[k].first, a = sons[k].second;
        if (alive < a) {
            need += a - alive;
            alive = a;
        }
        //D(alive); D(a); D(b);
        alive -= b;
        assert( alive >= 0 );
    }
    return make_pair(need - alive, need);
}

void solve(int n) {
    for (int i = 0; i < n; ++i) {
        g[i].clear();
        A[i] = B[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        int a, m, g; scanf("%d %d %d", &a, &m, &g);
        int b = m + g;
        a = max(a, b);
        A[i] = a;
        B[i] = b;
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int best = (1 << 30);
    for (int i = 0; i < n; ++i) {
        pair<int, int> t = dfs(i);
        // printf(" with root in i = %d need %d\n", i, t.second);
        best = min(best, t.second);
    }
    printf("%d\n", best);
}

int main(){
    for (int run = 1, n; scanf("%d", &n) == 1 and n > 0; run++) {
        printf("Case %d: ", run);
        solve(n);
    }
    return 0;
}
