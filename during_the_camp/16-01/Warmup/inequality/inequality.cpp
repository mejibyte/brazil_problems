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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    #ifndef LOCAL
    freopen("inequality.in", "r", stdin);
    freopen("inequality.out", "w", stdout);
    #endif
    
    int n; while (cin >> n) {
        int s = 0;
        for (int i = 1; i < n; ++i) s += i * i * i;
        
        int a = 8*s + 4*n*n*n - 2*n*n*n*n;
        int b = 8;
        int d = gcd(a, b);
        a /= d;
        b /= d;
        printf("%d\n%d\n", a, b);
    }
    
    return 0;
}