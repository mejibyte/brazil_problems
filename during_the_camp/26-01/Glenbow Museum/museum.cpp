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

const int MAXN = 1005;
long long dp[MAXN][MAXN][2];

int main(){
    dp[1][1][false] = 1;
    for (int len = 1; len + 1 < MAXN; ++len) {
        for (int r = 0; r < MAXN; ++r) {
            for (int p = 0; p < 2; ++p) {
                
                if (r + 1 < MAXN) {
                    dp[len + 1][r + 1][false] += dp[len][r][p];
                }
                
                if (p == 0) { // last letter was R, so we can put an O too
                    dp[len + 1][r][true] += dp[len][r][p];
                }
            }
        }
    }    
    for (int run = 1; ; ++run) {
        int len; scanf("%d", &len);
        if (len == 0) break;
        long long ans = 0;
        for (int r = 0; r <= len; ++r){
            int o = len - r;
            if (r - o == 4) {
            //printf("r = %d, o = %d -> added %d\n", r, o, int(dp[len][r][false] + dp[len][r][true]));
                ans += dp[len][r][false] + 2 * dp[len][r][true];
            }
        }
        printf("Case %d: ", run);
        cout << ans << endl;
    }
    
    return 0;
}
