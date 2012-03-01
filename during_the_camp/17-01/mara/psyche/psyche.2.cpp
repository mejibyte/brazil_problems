// Andrés Mejía

// Accepted

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

long long joseph(long long n, int k) {
    assert(n >= 1);
    if (n == 1) return 0LL;
    if (k == 1) return n - 1;
    if (n < k) return (joseph(n - 1, k) + k) % n;
    long long w = joseph(n - n / k, k) - n % k;
    if (w < 0) return w + n;
    return w + w / (k - 1);
}

int main(){
    #ifndef LOCAL
    #define problem_name "psyche"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    long long n;
    int p;
    cin >> n >> p;
    cout << joseph(n, p) + 1 << endl;
    return 0;
}


