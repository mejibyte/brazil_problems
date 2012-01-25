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

const int LIMIT = 31622779;

int sieve[LIMIT + 1];
int primes[LIMIT + 1];
bool marked[LIMIT + 1];

int main(){
    #ifndef LOCAL
    #define problem_name "countpr"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif

    int pc = 1;
    for (int i = 2; i <= LIMIT; ++i) {
        if (!sieve[i]) {
            primes[pc] = i;
            sieve[i] = pc;
            pc++;
        }
        
        for (int j = 1; j <= sieve[i] and i * primes[j] <= LIMIT; j++) {
            sieve[ i * primes[j] ] = j;
        }
    }

    long long a, b;
    cin >> a >> b;


    for (int i = 1; i < pc and primes[i] <= b; ++i) {
        long long p = primes[i];
        if (p * p > b) break;

        long long start = max(a / p, p);
        for (long long k = start; p * k <= b; ++k) {
            if (k < 2) continue;
            long long multiple = p * k;
            if (a <= multiple and multiple <= b) {
                marked[ multiple - a ] = true;
            }
        }
    }

    int ans = 0;
    for (long long i = max(a, 2LL); i <= b; ++i) {
        ans += !marked[i - a];
    }

    printf("%d\n", ans);

    return 0;
}


