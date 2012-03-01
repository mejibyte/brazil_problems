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

const int MAXN = 100005;

int tree[MAXN];
int a[MAXN];

void add(int at) {
    for (at++; at < MAXN; at += at & -at) {
        tree[at]++;
    }
}

int sum(int at) {
    int ans = 0;
    for (at++; at > 0; at -= at & -at) {
        ans += tree[at];
    }
    return ans;
}

int sum(int from, int to) {
    return sum(to) - sum(from - 1);
}

struct Event {
    int at, low, high, sign, index;
    bool operator < (const Event &e) const {
        return at < e.at;
    }
};

Event E[2*MAXN];

int main(){
    #ifndef LOCAL
    #define problem_name "permutation"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif

    ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    for (int i = 0; i < m; ++i) {
        Event e;
        int x, y;
        cin >> x >> y >> e.low >> e.high;
        e.index = i;
        
        e.at = x - 1;
        e.sign = -1;
        E[2*i]= e;
        
        e.at = y;
        e.sign = +1;
        E[2*i+1] = e;
    }
    sort(E, E + 2*m);
    
    static int ans[MAXN] = {0};
    
    for (int i = 0, nextEvent = 0; i <= n; ++i) {
        add(a[i]);
        while (nextEvent < 2*m and E[nextEvent].at == i) {
            const Event &e = E[nextEvent];
            ans[e.index] += e.sign * sum(e.low, e.high);
            nextEvent++;
        }
    }
    
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}


