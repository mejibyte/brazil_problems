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

bool isSqr(long long x) {
    long long s = (int)sqrt(x);
    for (int d = -2; d <= +2; ++d) {
        if ((s + d) * (s + d) == x) return true;
    }
    return false;
}

long long root(long long x) {
    long long s = (int)sqrt(x);
    for (int d = -2; d <= +2; ++d) {
        if ((s + d) * (s + d) == x) return (s + d);
    }
    assert( false );
}

int main(){
    vector< int > good;
    for (long long p = 1; 1LL * p * p <= 1000000000; ++p) {
        long long x = p * p - 1;
        assert( x >= 0 );
        
        if (isSqr(1 + 8 * x)) {
            long long k = root(1 + 8 * x);
            k--;
            if (k >= 0 and k % 2 == 0) {
                good.push_back( x );
            }
        }
    }
    //foreach(p, good) printf("%d ", *p); puts("");
    
    int run = 1;
    int a, b;
    while (scanf("%d %d", &a, &b) == 2) {
        if (a == 0 and b == 0) break;
        int ans = 0;
        foreach(p, good) {
            int x = *p;
            if (a < x + 1 and x + 1 < b) ans++;
        }
        printf("Case %d: %d\n", run++, ans);
    }
    return 0;
}
