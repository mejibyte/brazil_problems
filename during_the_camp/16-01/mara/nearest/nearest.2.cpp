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
const int INF = 1 << 30;
const int MAXN = 10005;
int a[MAXN], dp[MAXN];

int main(){
    #ifndef LOCAL
    assert( freopen("nearest.in", "r", stdin) != NULL );
    assert( freopen("nearest.out", "w", stdout) != NULL );
    #endif
    
    int n, A, sum = 0;
    cin >> n >> A;
    for (int i = 0; i < n; ++i) cin >> a[i], sum += abs(a[i]);
    sum -= abs(a[0]);
    
    reverse(a + 1, a + n);

    // dp[i][p] = True if can place signs in front of the numbers in
    // the range [1..i] such that the sum of the numbers that have a
    // plus sign is p.
    
    // The range is [1..i] instead of [0..i] because in this problem
    // we can't change the sign of the first number.
    
    // dp[i][p] = dp[i - 1][p] || dp[i - 1][p - abs(a[i])].
    // This is just a knapsack problem, and we can solve it using linear
    // memory instead of the full table. The trick is to store in
    // dp[p] the first value of i for which dp[i][p] is true. From that
    // point on, every dp[i + something][p] will be true as well, so
    // we only need the first row where there's a true value in column p.
    for (int p = 1; p <= sum; p++) dp[p] = INF;
    dp[0] = 0;
    
    for (int i = 1; i < n; i++){
        int value = abs(a[i]);
        for (int p = sum; p >= value; --p){
            if (dp[p - value] < INF){
                dp[p] = min(dp[p], i);
            }
        }
    }

    int best_diff = INF, best_p = -1;
    for (int p = 0; p <= sum; p++){
        if (dp[p] < INF){
            int s = 2 * p - sum + a[0];
            if (abs(A - s) < best_diff){
                best_p = p;
                best_diff = abs(A - s);
            }
        }
    }
    assert(best_diff < INF);
    cout << 2 * best_p - sum + a[0] << endl;

    int curr_p = best_p;
    assert(dp[curr_p] < INF);
    
    cout << a[0];
    for (int i = n - 1; i > 0; i--){
        int sign;
        if (dp[curr_p] <= i - 1){
            sign = -1;
        }else{
            sign = +1;
            curr_p -= abs(a[i]);
        }
        if (a[i] * sign < 0) cout << "-";
        else cout << "+";
        cout << a[i];
    }
    cout << endl;
    return 0;
}