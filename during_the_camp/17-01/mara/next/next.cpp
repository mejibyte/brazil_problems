// Andrés Mejía

// This will certainly time out, but it should give correct answers on the
// first few cases.

// Gave Wrong Answer on test 11. What's wrong? Maybe an overflow somewhere?

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

int N, M, a[MAXN];


bool f(int s, int k) {
    if (s == 0) return true;
    if (s < 0) return false;
    int limit = min(s, k);
    
    static map< pair<int, int>, bool > memo;
    
    pair<int, int> key = make_pair(s, limit);
    if (memo.count(key) > 0) return memo[key];

    for (int take = limit; take >= M; --take) {
        if (f(s - take, take)) return memo[key] = true;
    }
    return memo[key] = false;
}

vector< int > first(int s, int k) {
    vector< int > ans;
    int limit = min(s, k);
    assert(f(s, k));
    while (s > 0) {
        for (int take = M; take <= limit; ++take) {
            if (f(s - take, take)) {
                s -= take;
                limit = take;
                ans.push_back(take);
                break;
            }
        }
    }
    return ans;
}

vector< int > solve() {
    int sum = 0; // might overflow, be careful
    for (int i = 0; i < N; ++i) sum += a[i];

    //For(i, 0, N) printf("%d ", a[i]); puts(""); D(sum);
    
    int need = a[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        // try to increase a[i]
        if (f(need - 1, a[i] + 1)) { // found a solution
            vector< int > ans;
            for (int j = 0; j < i; ++j) ans.push_back(a[j]);
            ans.push_back(a[i] + 1);
            // generate first partition of need - 1
            vector< int > tmp = first(need - 1, a[i] + 1);
            for (int k = 0; k < tmp.size(); ++k) ans.push_back(tmp[k]);
            return ans;
        }
        need += a[i];
    }
    
    // no solution found, first try to create next partition for sum
    for (int take = a[0] + 1; take <= sum; ++take) {
        if (f(sum - take, take)) {
            vector< int > ans;
            ans.push_back(take);
            vector< int > tmp = first(sum - take, take);
            for (int k = 0; k < tmp.size(); ++k) ans.push_back(tmp[k]);
            return ans;
        }
    }
    
    // no solution found, return first partition of sum + 1
    return first(sum + 1, sum + 1);
}

int main(){
    #ifndef LOCAL
    #define problem_name "next"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; ++i) scanf("%d", &a[i]);
    vector< int > ans = solve();

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i) printf("%d ", ans[i]);
    puts("");

    return 0;
}