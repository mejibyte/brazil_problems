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

const int MAXN = 1100000;
const int MAXR = 1000005;

int first[MAXN];
int next[MAXN];
int divisors[MAXN];
vector<int> primes;

void sieve() {
    primes.push_back(-1);
    for (int i = 2; i < MAXN; ++i) {
        if (!first[i]) { // this is a prime!
            first[i] = primes.size();
            primes.push_back(i);
        }
        for (int j = 1; j <= first[i] and i * primes[j] < MAXN; ++j) {
            first[i * primes[j]] = j;
        }
    }
    first[1] = -1;
}

int countDivisors(int x) {
    if (x == 1) return 1;
    int ans = 1;
    while (x > 1) {
        int cnt = 0;
        while (x > 1 and first[x] == first[ x / primes[first[x]] ]) {
            cnt++;
            x /= primes[first[x]];
        }
        x /= primes[first[x]];
        ans *= cnt + 2;
    }
    return ans;
}

// assuming there's a prime at position i, where's the next prime that occurs?
int findNext(int i) {
    int x = 2 + i;
    i++;
    while (divisors[x] > 2) { // not prime
        x = divisors[x] + i;
        i++;
    }
    return i;
}

int main(){
    #ifndef LOCAL
    #define problem_name "primes"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    sieve();
    for (int i = 1; i < MAXN; ++i) {
        divisors[i] = countDivisors(i);
    }

    for (int i = 1; i < MAXR; ++i) {
        next[i] = findNext(i);
    }
    
    int l, r, run = 1;
    while (scanf("%d %d", &l, &r) == 2) {
        if (l == 0 and r == 0) break;
        int * dp = first; // just use memory of array 'first', because we don't need it anymore.
        int ans = 1;
        for (int at = r; at >= l; --at) {
            dp[at] = 1;
            if (next[at] <= r) dp[at] += dp[next[at]];
            ans = max(ans, dp[at]);
        }
        printf("Window %d: There can be up to %d primes.\n", run++, ans);
    }

    return 0;
}
