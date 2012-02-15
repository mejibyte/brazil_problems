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

const int MAXN = 200005;

long long X[MAXN], Y[MAXN], Z[MAXN];

int main(){
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        if (n == 0) break;
        
        for (int i = 0; i < n; ++i) cin >> X[i] >> Y[i] >> Z[i];
        
        long long ans = -1;
        for (int mask = 0; mask < 8; ++mask) {
            long long left = -(1LL << 60), right = -(1LL << 60);
            
            for (int i = 0; i < n; ++i) {
                long long a = 0, b = 0;
                long long sign;
                
                sign = (mask & 1) ? +1 : -1;
                a += sign * X[i];
                b += -sign * X[i];
                
                sign = (mask & 2) ? +1 : -1;
                a += sign * Y[i];
                b += -sign * Y[i];
                
                sign = (mask & 4) ? +1 : -1;
                a += sign * Z[i];
                b += -sign * Z[i];
                
                left = max(left, a);
                right = max(right, b);
            }
            
            ans = max(ans, left + right);
        }
        assert(ans >= 0);
        cout << ans << endl;
    }
    return 0;
}
