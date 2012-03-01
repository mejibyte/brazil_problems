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

const int MAXN = 50005;
int X[MAXN], Y[MAXN];

int main(){
    #ifndef LOCAL
    #define problem_name "area"
    assert( freopen(problem_name ".ln", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d %d", X + i, Y + i);
    
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ans += X[i] * Y[j] - X[j] * Y[i];
    }
    assert(ans >= 0);
    cout << ans / 2;
    printf(".%d", (int)(ans % 2) * 5);
    for (int i = 0; i < 599; ++i) printf("0");
    printf("\n");
    
    return 0;
}