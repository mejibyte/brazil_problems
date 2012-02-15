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

bool valid(long long a, long long b, long long c) {
    if (c > b) return false;
    if (a <= c and c <= b) return true;
    for (long long x = 0, p = 1; x <= 10; ++x) {
        long long y1 = a - c * p;
        long long y2 = b - c * p;
        assert(y1 <= y2);
        
        y1 = max(y1, 0LL);
        y2 = min(y2, p - 1LL);
        if (y1 <= y2) return true;
        
        p *= 10;
    }
    return false;
}

int main(){
    #ifndef LOCAL
    freopen("inputbox.in", "r", stdin);
    freopen("inputbox.out", "w", stdout);
    #endif    
    
    int a, b, n; cin >> a >> b >> n;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (!valid(a, b, x)) printf("IN");
        puts("VALID");
    }
    return 0;
}