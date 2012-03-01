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

vector< vector<int> > dp[16][16];

int main(){
    #ifndef LOCAL
    #define problem_name "combo2"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".ovt", "w", stdout) != NULL);
    #endif
    ios::sync_with_stdio(false);
    
    int n, k;
    cin >> n >> k;
    
    // c[i][j] = c[i - 1][j] + c[i - 1][j - 1]
    
    dp[0][0].push_back(vector<int>());
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            // 0 + dp[i - 1][j]
            // 1 + rev(dp[i - 1][j - 1])
            const vector< vector<int> > &up = dp[i - 1][j];
            for (int e = 0; e < up.size(); ++e) {
                vector<int> add = up[e];
                add.insert(add.begin(), 0);
                dp[i][j].push_back(add);
            }
            
            if (j - 1 >= 0) {
                const vector< vector<int> > &left = dp[i - 1][j - 1];
                for (int e = left.size() - 1; e >= 0; --e) {
                    vector<int> add = left[e];
                    add.insert(add.begin(), 1);
                    dp[i][j].push_back(add);
                }
            }
        }
    }
    
    foreach(p, dp[n][k]) {
        assert(p->size() == n);
        for (int i = n - 1; i >= 0; --i) {
            if (p->at(i) == 1) {
                cout << n - i << " ";
            }
        }
        cout << endl;
    }

    return 0;
}


