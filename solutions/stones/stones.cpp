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

const int MAXN = 1005;

int memo[MAXN][MAXN];

bool canWin(int pile, int limit) {
    if (pile == 0) return false;
    limit = min(limit, pile);
    if (memo[pile][limit] != -1) return memo[pile][limit];
    bool ans = false;
    for (int take = 1; take <= limit and take <= pile; ++take) {
        if (!canWin(pile - take, 2 * take)) {
            ans = true;
            break;
        }
    }
    return memo[pile][limit] = ans;
}

int main(){
    memset(memo, -1, sizeof memo);
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        assert(2 <= n and n <= 1000);
        if (canWin(n, n - 1)) {
            puts("Alicia");
        } else {
            puts("Roberto");
        }
    }
    return 0;
}