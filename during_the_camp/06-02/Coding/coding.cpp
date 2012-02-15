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

int main(){
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 and m == 0) break;
        
        map<int, int> times;
        for (int i = 0; i < m; ++i) {
            int x; scanf("%d", &x);
            times[x]++;
        }
        
        vector< int > a;
        foreach(p, times) {
            a.push_back( p->second );
        }
        sort(a.begin(), a.end(), greater<int>());
        
        long long ans = 0;
        for (int i = 0; i < a.size(); ++i) {
            ans += 1LL * a[i] * (i + 1);
        }
        if (a.size() == (1 << n)) {
            ans -= a.back();            
        }
        printf("%lld\n", ans);
    }
    return 0;
}
