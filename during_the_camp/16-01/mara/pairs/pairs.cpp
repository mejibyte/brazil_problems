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

const int MAXN = 255;

bool g[MAXN][MAXN], seen[MAXN];
int L, R, matchL[MAXN], matchR[MAXN];

bool assign(int i) {
    for (int j = 0; j < R; ++j) {
        if (g[i][j] and !seen[j]) {
            seen[j] = true;
            if (matchR[j] < 0 or assign(matchR[j])) {
                matchL[i] = j;
                matchR[j] = i;
                return true;
            }
        }
    }
    return false;
}

int maxBipartiteMatching() {
    for (int i = 0; i < L; ++i) matchL[i] = -1;
    for (int j = 0; j < R; ++j) matchR[j] = -1;
    int ans = 0;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < R; ++j) seen[j] = false;
        if (assign(i)) ans++;
    }
    return ans;
}

int main(){
    #ifndef LOCAL
    #define problem_name "pairs"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    scanf("%d %d", &L, &R);
    for (int i = 0; i < L; ++i) {
        int j; while(scanf("%d", &j) == 1 and j > 0) {
            g[i][j - 1] = true;
        }
    }
    int ans = maxBipartiteMatching();
    printf("%d\n", ans);
    for (int i = 0; i < L; ++i) {
        if (matchL[i] != -1) {
            assert(i == matchR[matchL[i]]);
            printf("%d %d\n", i + 1, matchL[i] + 1);
        }
    }
    
    return 0;
}