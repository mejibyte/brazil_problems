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
#include <bitset>

const int MAXN = 100005;
int L, R;
int matchL[MAXN], matchR[MAXN];
bitset<MAXN> seenL, seenR;
vector<int> g[MAXN];

void dfs(int u) { // u is on L
    if (u == -1 or seenL[u]) return;
    seenL[u] = true;
    foreach(out, g[u]) {
        int v = *out;
        if (!seenR[v]) {
            seenR[v] = true;
            dfs(matchR[v]);
        }
    }
}

int main(){
    #define problem_name "intel"
    #ifndef LOCAL
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    ios::sync_with_stdio(false);
    int e;
    cin >> L >> R >> e;
    memset(matchL, -1, sizeof matchL);
    memset(matchR, -1, sizeof matchR);
    
    for (int k = 0; k < e; ++k) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }
    for (int i = 0; i < L; ++i) {
        int girlfriend; cin >> girlfriend;
        if (girlfriend != -1) matchL[i] = girlfriend, matchR[girlfriend] = i;
    }
    
    int size = 0;
    for (int i = 0; i < L; ++i) {
        if (matchL[i] == -1) dfs(i);
        else size++;
    }
    
    cout << size << endl;

    size = 0;
    for (int i = 0; i < L; ++i) if (!seenL[i]) size++;
    cout << size;
    for (int i = 0; i < L; ++i) if (!seenL[i]) cout << " " << i;
    cout << endl;

    size = 0;
    for (int i = 0; i < R; ++i) if (seenR[i]) size++;
    cout << size;
    for (int i = 0; i < R; ++i) if (seenR[i]) cout << " " << i;
    cout << endl;
    
    return 0;
}