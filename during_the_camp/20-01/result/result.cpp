using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "result"

int mex(vector<int> &v) {
    sort(v.begin(), v.end());
    v.resize( unique(v.begin(), v.end()) - v.begin() );
    if (v.at(0) > 0) return 0;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if (i + 1 >= n or v[i] + 1 < v[i + 1]) {
            return v[i] + 1;
        }
    }
    assert(false);  
}

const int MAXN = 5005;
int grundy[MAXN];

vector< int > g[MAXN];

int find(int u) {
    if (g[u].size() == 0) return 0;
    if (grundy[u] != -1) return grundy[u];
    
    vector< int > options;
    for (int k = 0; k < g[u].size(); ++k) {
        options.push_back( find(g[u][k]) );
    }
    return grundy[u] = mex(options);
}

int main(){
    #ifndef LOCAL    
    assert( freopen(INPUT_FILE ".in", "r", stdin) != NULL );
    assert( freopen(INPUT_FILE ".out", "w", stdout) != NULL );
    #endif
  
    int n, e; scanf("%d %d", &n, &e);
    for (int i = 0; i < e; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--, y--;
        g[x].push_back( y );
    }
    
    for (int i = 0; i < n; ++i) {
        grundy[i] = -1;
    }
    
    for (int i = 0; i < n; ++i) {
        printf("%d\n", find(i));
    }
  
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
