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

const int MAXN = 46;
int dp[MAXN][2];

int main(){
    #ifndef LOCAL
    #define problem_name "fib"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int n, k;
    cin >> n >> k;
    
    string ans(n, '*');
    
    dp[0][0] = dp[0][1] = 1;
    for (int len = 1; len < MAXN; ++len){
      for (int ones = 0; ones < 2; ++ones) {
	dp[len][ones] = dp[len - 1][true];
	if (ones){
	  dp[len][ones] += dp[len - 1][false];
	}
      }
    }
    
    for (int i = 0; i < n; ++i) {
      if (i - 1 >= 0 and ans[i - 1] == '1') {
	ans[i] = '0';
	continue;
      }
      
      // 1 or 0
      int remain = n - i - 1;
      
      // 0
      if (dp[remain][true] >= k) {
	ans[i] = '0';
      } else { // 1
	k -= dp[remain][true];
	ans[i] = '1';
      }
    }
    
    cout << ans << endl;
    return 0;
}


