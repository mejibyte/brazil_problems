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
#include <bitset>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 1000005;
int big[4 * MAXN + 5];
int sum[4 * MAXN + 5];
bitset< 4 * MAXN + 5 > pending;

int a[MAXN], C;



void initialize(int node,  int l, int r) {
    pending[node] = true;
}

void propagate(int node, int l, int r) {
    if (pending[node]) {
        pending[node] = false;
        sum[node] = (r - l + 1) * C;
        big[node] = C;
        if (l < r) {
            pending[2*node] = pending[2*node+1] = true;
        }
    }
}

void update(int node, int l, int r) {
    int m = (l + r) / 2;
    propagate(2*node, l, m);
    propagate(2*node+1, m+1, r);
    sum[node] = sum[2*node] + sum[2*node+1];
    big[node] = max(big[2*node], big[2*node+1]);
}

void insert(int node, int l, int r,   int v) {
    propagate(node, l, r);
    if (sum[node] < v) {
        printf("node = %d, l = %d, r = %d, v = %d, sum = %d\n", node, l, r, v, sum[node]);
    }
    assert( sum[node] >= v );
    if (l == r) {
        sum[node] -= v;
        big[node] = sum[node];
        return;
    }
    int m = (l + r) / 2;
    if (big[2*node] >= v) {
        insert(2*node, l, m, v);
    } else {
        insert(2*node+1, m+1, r, v);
    }
    update(node, l, r);
}

pair<int, int> query(int node, int l, int r) {
    propagate(node, l, r);
    if (sum[node] == (r - l + 1) * C) { // nothing wasted used in this segment
        return make_pair(0, 0);
    }
    if (l == r) {
        return make_pair(1, sum[node]);
    }
    int m = (l + r) / 2;
    pair<int, int> ans = query(2*node, l, m);
    pair<int, int> tmp = query(2*node+1, m+1, r);
    ans.first += tmp.first;
    ans.second += tmp.second;
    return ans;
}

int main(){
    bool first = true;
    while (scanf("%d", &C) == 1) {
        #ifdef LOCAL
            int timeBefore = clock();
        #endif
        if (first) {
            first = false;
        } else {
            puts("");
        }
        pending.reset();
        int n; scanf("%d ", &n);
        for (int i = 0; i < n; ) {
            static char line[1024];
            scanf("%s ", line);
            if (line[0] == 'b') {
                int times, v;
                scanf("%d %d", &times, &v);
                for (int k = 0; k < times; ++k) {
                    a[i++] = v;
                }
            } else {
                sscanf(line, "%d", &a[i]);
                i++;
            }
        }
        //for (int i = 0; i < n; ++i) printf("%d ", a[i]); puts("");
        for (int i = 0; i < n; ++i) assert( !pending[i] );
        initialize(1, 0, n);
        for (int i = 0; i < n; ++i) {
            assert( 0 < a[i] and a[i] <= C );
            insert(1, 0, n, a[i]);
        }
        pair<int, int> ans = query(1, 0, n);
        printf("%d %d\n", ans.first, ans.second);
        #ifdef LOCAL
            fprintf(stderr, "TIME: %lfs\n", (clock() - timeBefore) * 1.0 / CLOCKS_PER_SEC);
        #endif
    }
    return 0;
}
