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
const int inf = 1000000005;

int tree[4 * MAXN + 5];

void put(int node, int l, int r, int where, int what) {
    assert(l <= r);
    if (where < l) return;
    if (where > r) return;
    if (l == r) {
        assert(where == l);
        tree[node] = what;
        return;
    }
    
    int m = (l + r) / 2;
    put(2*node, l, m, where, what);
    put(2*node+1, m + 1, r, where, what);
    
    tree[node] = max(tree[2*node], tree[2*node+1]);
}

int get(int node, int l, int r,   int p, int q) {
    if (q < l) return -inf;
    if (p > r) return -inf;
    p = max(p, l);
    q = min(q, r);
    if (l == p and r == q) {
        return tree[node];
    }
    int m = (l + r) / 2;
    int a = get(2*node, l, m, p, q);
    int b = get(2*node+1, m + 1, r, p, q);
    return max(a, b);
}

void solve() {
    int N;
    long long B;
    scanf("%d %lld", &N, &B);
    memset(tree, 0, sizeof tree);
    for (int i = 0; i < N; ++i) {
        int x; scanf("%d", &x);
        put(1, 0, N - 1, i, x);
    }
    
    int Q; scanf("%d ", &Q);
    for (int i = 0; i < Q; ++i) {
        char type; scanf(" %c ", &type);
        if (type == 'A') {
            int k; scanf("%d", &k);
            B += k;
        } else if (type == 'B') {
            int where, what; scanf("%d %d", &where, &what);
            put(1, 0, N - 1, where, what);
        } else if (type == 'C') {
            int from, to;
            scanf("%d %d", &from, &to);
            int need = get(1, 0, N - 1, from, to); 
            long long ans = abs(B - need);
            printf("%lld\n", ans);
        }
    }
}

int main(){
    int T; scanf("%d", &T);
    for (int run = 0; run < T; ++run) {
        printf("Testcase %d:\n", run);
        solve();
        puts("");
    }
    
    return 0;
}
