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

const int MAXN = 100005;

vector<int> bucket[MAXN];
int a[MAXN];

int count(int b, int p, int q) {
    const vector<int> &v = bucket[b];
    // count how many numbers are in [p, q] in the sorted vector v
    int ans = upper_bound(v.begin(), v.end(), q) - lower_bound(v.begin(), v.end(), p);
    return ans;
}

int main(){
    #ifndef LOCAL
    #define problem_name "permutation"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    
    int S = sqrt(n) + 1;
    //D(S);
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        bucket[i / S].push_back(a[i]);
    }
    for (int i = 0; i <= n / S; ++i) {
        sort(bucket[i].begin(), bucket[i].end());
    }
    
    while (m--) {
        int x, y, p, q;
        cin >> x >> y >> p >> q;
        x--, y--;
        
        int ans = 0;
        if (x / S == y / S) { // both endpoints are on the same bucket
            for (int i = x; i <= y; ++i) {
                ans += (p <= a[i] and a[i] <= q);
            }
        } else {        
            for (int b = x / S + 1; b <= y / S - 1; ++b) { // intermediate buckets
                ans += ::count(b, p, q);
            }
            for (int i = x; i < S * (x / S) + S and i < n; ++i) {
                ans += (p <= a[i] and a[i] <= q);
            }
            for (int i = y; i >= S * (y / S) and i > 0; --i) {
                ans += (p <= a[i] and a[i] <= q);
            }
        }
        cout << ans << endl;
    }
    return 0;
}


