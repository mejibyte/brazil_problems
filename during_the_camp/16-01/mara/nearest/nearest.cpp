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
int a[MAXN], b[MAXN];
int dp[MAXN];
int sign[MAXN];

int main(){
    //ios::sync_with_stdio(false);
    
    #ifndef LOCAL
    assert( freopen("nearest.in", "r", stdin) != NULL );
    assert( freopen("nearest.out", "w", stdout) != NULL );
    #endif
    
    int n, A;
    cin >> n >> A;
    for (int i = 0; i < n; ++i){
        string s;
        cin >> s;
        
        assert(s != "-0");
        assert(s[0] != '+');
        
        stringstream(s) >> a[i];
        b[i] = abs(a[i]);
    }
    
    A -= a[0];
    int sum = 0;
    for (int i = 1; i < n; i++) sum += b[i];
    
    for (int p = 1; p <= sum; p++) dp[p] = INF;
    dp[0] = 0;
    
    //puts("b: "); For(i, 0, n) printf("%d ", b[i]); puts("");
    for (int i = 1; i < n; i++){
        for (int p = sum; p >= b[i]; --p){
            if (dp[p - b[i]] < INF){
                dp[p] = min(dp[p], i);
            }
        }
    }
    
    //For(i, 0, n) printf("%d ", dp[i]); puts("");
    
    int best_diff = INF;
    int best_p = -1;
    for (int p = 0; p <= sum; p++){
        if (dp[p] < INF){
            int s = 2 * p - sum;
            if (abs(A - s) < best_diff){
                best_p = p;
                best_diff = abs(A - s);
            }
        }
    }
    
    assert(best_diff < INF);
    printf("%d\n", 2 * best_p - sum + a[0]);
    
    int curr_p = best_p;
    assert(dp[curr_p] < INF);
    for (int i = n - 1; i > 0; i--){
        if (dp[curr_p] <= i - 1){
            sign[i] = -1;
        }else{
            sign[i] = +1;
            curr_p -= b[i];
        }
    }
    
    printf("%d", a[0]);
    for (int i = 1; i < n; i++){
        //printf("sign[i = %d] = %d\n", i, sign[i]);
        char op;
        if (a[i] < 0){
            op = sign[i] == +1 ? '-' : '+';
        }else{
            op = sign[i] == +1 ? '+' : '-';
        }
        printf("%c%d", op, a[i]);
    }
    puts("");
    
    return 0;
}