// Solution to problem Stones
//
// Problem setter: Andrés Mejía-Posada <andr@esmejia.com>
// Intended solution: Dynamic Programming
// Complexity: O(n^2) per test case

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

#define D(x) cout << #x " is " << (x) << endl

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