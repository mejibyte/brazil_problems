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

vector< int > g[MAXN];

int grundy[MAXN];


int getGrundy(int u) {
    if (g[u].size() == 0) return 0;
    
    if (grundy[u] != -1) return grundy[u];
    
    vector< int > out;
    foreach(v, g[u]) {
        out.push_back( getGrundy(*v) );
    }
    
    sort(out.begin(), out.end());
    out.resize( unique(out.begin(), out.end()) - out.begin() );
    
    assert(out.size() > 0);
    int ans = -1;
    if (out[0] > 0) ans = 0;
    else {
        for (int i = 0; i < out.size(); ++i) {
            if (out[i] + 1 < out[i+1]) {
                ans = out[i] + 1;
                break;
            }
        }
    }
    if (ans == -1) ans = out.size();
    return grundy[u] = ans;
}


int main(){
    ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            grundy[i] = -1;
        }
        
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            if (u == v) continue;
            if (v > u) swap(u, v); assert(u > v);
            g[u].push_back(v);
        }
        
        
        //for (int i = 0; i < n; ++i) { printf("grundy[i=%d] = %d\n", i, getGrundy(i)); }
        
        int K; cin >> K;
        int sum = 0;
        for (int i = 0; i < K; ++i) {
            int x; cin >> x;
            //D(x);
            //D(getGrundy(x));
            sum = sum ^ getGrundy(x);
        }
        if (sum == 0) puts("I lose");
        else puts("I win");
        
    }
    return 0;
}
