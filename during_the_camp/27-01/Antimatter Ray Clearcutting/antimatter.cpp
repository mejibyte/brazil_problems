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

struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
    point(){}
};

vector< point > p;

bool sameLine(const point &a, const point &b, const point &c) {
    int x1 = b.x - a.x;
    int y1 = b.y - a.y;
    int x2 = c.x - a.x;
    int y2 = c.y - a.y;
    return (x1 * y2 - x2 * y1) == 0;
}

int n;
int memo[1 << 16][17];

int minRays(int alive, int mustKill) {
    //printf("alive = %d, mustKill = %d\n", alive, mustKill);
    if (mustKill <= 0) return 0; // no extra work needed
    int count = __builtin_popcount(alive);
    if (count < mustKill) return (1 << 30); // even if I kill every alive tree it won't be enough
    if (count == 1) {
        assert(mustKill == 1);
        return 1; // just kill this sucker
    }
    if (memo[alive][mustKill] != -1) return memo[alive][mustKill];
    int ans = (1 << 30);
    for (int i = 0; i < n; ++i) if (alive & (1 << i)) {
        for (int j = i + 1; j < n; ++j) if (alive & (1 << j)) {
            int onLine = 2, killed = (1 << i) | (1 << j);
            for (int k = j + 1; k < n; ++k) if (alive & (1 << k)) {
                if (!sameLine(p[i], p[j], p[k])) continue;
                killed |= (1 << k);
                onLine++;
            }
            assert(onLine == __builtin_popcount( killed ));
            ans = min(ans, 1 + minRays(alive & ~killed, mustKill - onLine));
        }
    }
    return memo[alive][mustKill] = ans;   
}

int main(){
    int runs; scanf("%d", &runs);
    for (int run = 1; run <= runs; ++run){
        if (run > 1) puts("");
        int m;
        scanf("%d %d", &n, &m);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &p[i].x, &p[i].y);
        }
        memset(memo, -1, sizeof memo);
        printf("Case #%d:\n", run);
        printf("%d\n", minRays((1 << n) - 1, m));
    }
    
    return 0;
}
