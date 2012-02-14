// Andrés Mejía

// This will certainly time out, but it should give correct answers on the
// first few cases.

// Time limit on case 62.

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

// Returns true if you can write s as a sum of integers all >= M and all <= k.
bool f(long long s, int k) {
    if (s == 0) return true;
    assert(s > 0);
    long long biggest = s / M;
    long long smallest = (s + k - 1) / k;
    assert(biggest >= 0 and smallest >= 0);
    return (smallest <= biggest);
}

vector< int > first(long long s, int k) {
    vector< int > ans;
    int limit = min(s, (long long)k);
    while (s > 0) {
        for (int take = M; take <= limit; ++take) {
            if (f(s - take, take)) {
                s -= take;
                limit = take;
                ans.push_back(take);
                assert(ans.size() <= 50000);
                break;
            }
        }
    }
    return ans;
}

vector< int > solve() {
    long long sum = 0;
    for (int i = 0; i < N; ++i) sum += a[i];

    long long need = a[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        for (int incr = 1; incr <= need; ++incr) {
            if (i - 1 >= 0 and a[i - 1] < a[i] + incr) break;
            // try to increase a[i]
            if (f(need - incr, a[i] + incr)) { // found a solution
                vector< int > ans;
                for (int j = 0; j < i; ++j) ans.push_back(a[j]);
                ans.push_back(a[i] + incr);
                vector< int > tmp = first(need - incr, a[i] + incr); // generate first partition of what remains
                for (int k = 0; k < tmp.size(); ++k) ans.push_back(tmp[k]);
                return ans;
            }
        }
        need += a[i];
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
    for (int i = 0; i + 1 < ans.size(); ++i) assert(ans[i] >= ans[i + 1]);
    for (int i = 0; i < ans.size(); ++i) printf("%d ", ans[i]);
    puts("");

    return 0;
}