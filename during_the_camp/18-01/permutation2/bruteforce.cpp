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
#include <bitset>

const int MAXN = 100005;
const int L = 400;
int a[MAXN];
char str[8];

int main(){
    #define problem_name "permutation2"
    #ifndef LOCAL
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    while (q--) {
        int x, y;
        scanf("%s %d %d", str, &x, &y);
        if (str[0] == 'G') {
            int ans = 0;
            int k, l; scanf("%d %d", &k, &l);
            x--, y--;
            for (int i = x; i <= y; ++i) {
                ans += (k <= a[i] and a[i] <= l);
            }
            printf("%d\n", ans);
        } else {
            x--;
            a[x] = y;
        }
    }
    
    return 0;
}