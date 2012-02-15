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
int board[MAXN][MAXN];
long long dp[MAXN][MAXN];

int main(){
    int n;
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; i++){
            for (int j = 0; j <= i; j++){
                 cin >> board[i][j];
            }
            for (int j = i + 1; j < n; j++){
                board[i][j] = 0;
            }
        } 
        
        /*for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                printf("%2d ", board[i][j]);    
            }
            puts("");
        }*/
        long long best = - (1LL << 60) ;
        for (int i = 0; i < n; i++){
            for (int j = 0; j <= i; j++){
                dp[i][j] = board[i][j];
                if (i - 1 >= 0){
                    dp[i][j] += dp[i - 1][j];
                    if (j - 1 >= 0) 
                        dp[i][j] += dp[i - 1][j - 1];
                }
                if (i - 2 >= 0 and j - 1 >= 0){
                    dp[i][j] -= dp[i - 2][j - 1];
                }
                best = max(best, dp[i][j]);
            }    
        }
        cout << best << endl;
        
    }
    return 0;
}
