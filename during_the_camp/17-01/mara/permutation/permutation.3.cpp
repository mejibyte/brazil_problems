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
    int low, high, sign, index;
};

vector<Event> E[MAXN];

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

        e.sign = -1;
        E[x - 1].push_back(e);
        
        e.sign = +1;
        E[y].push_back(e);
    }
    
    static int ans[MAXN] = {0};
    
    for (int i = 0; i <= n; ++i) {
        add(a[i]);
        foreach(e, E[i]) {
            ans[e->index] += e->sign * sum(e->low, e->high);
        }
    }
    
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}


