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

bool isSqr(long long x) {
    long long r = (int)(sqrt(x) + EPS);
    for (int d = -2; d <= +2; ++d) {
        if ((r + d) * (r + d) == x) return true;
    }
    return false;
}

void bruteforce(int n) {
    long long ans = -1, which = -1;
    for (int mask = 1; mask < (1 << n); ++mask) {
        long long p = 1;
        for (int k = 0; k < n; ++k) {
            if (mask & (1 << k)) p *= (long long)(k + 1);
        }
        if (isSqr(p)) ans = p, which = mask;
    }
    long long r = sqrt(ans);
    printf("With n = %d:   %I64d = %I64d x %I64d = ", n, ans, r, r);
    for (int k = 0; k < n; ++k) {
            if (which & (1 << k)) printf("%d*", k + 1);
    }
    puts("1\n");
}

int main(){
    for (int i = 1; i <= 23; ++i) {
        bruteforce(i);
    }
    return 0;
}
