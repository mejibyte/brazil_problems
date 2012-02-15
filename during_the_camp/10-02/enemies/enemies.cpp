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
#include <bitset>
////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 65;

short color[MAXN];
vector< int > g[MAXN];
int N;

bool colorize(int u, int c) {
    if (color[u] != -1) {
        return color[u] == c;
    }
    
    color[u] = c;
    foreach(out, g[u]) {
        if (!colorize(*out, c ^ 1)) return false;
    }
    return true;
}

bitset<MAXN> seen;
int matchL[MAXN], matchR[MAXN];

bool bpm( int u ) {
    foreach(out, g[u]) {
        int v = *out;
        if( seen[v] ) continue;
        seen[v] = true;

        if( matchR[v] < 0 || bpm( matchR[v] ) )
        {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}


void solve() {
    For(i, 0, N) {
        if (color[i] == -1) {
            if (!colorize(i, 0)) {
                puts("The meeting will be canceled");            
                return;
            }
        }
    }   
    
    // es bipartito
    For(i, 0, N) matchL[i] = matchR[i] = -1;
    int cnt = 0;
    for( int i = 0; i < N; i++ ) {
        assert(color[i] != -1);
        if (color[i] == 1) continue;
        seen.reset();
        if( bpm( i ) ) cnt++;
    }
    
    cout << cnt << endl;
    
}

int main(){
    int E;
    while (cin >> N >> E) {
        if (N == 0 and E == 0) break;
        For(i, 0, N) g[i].clear(), color[i] = -1;
        For(e, 0, E){
            int u, v; cin >> u >> v;
            if (u == v) continue;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        solve();
    }
    return 0;
}
