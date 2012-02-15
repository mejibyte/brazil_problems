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

const int MAXN = 1000005;
int a[MAXN];
int next[MAXN];

int main(){
    int m, q;
    while (scanf("%d %d", &m, &q) == 2) {
        if (m == 0 and q == 0) break;
        map<int, int> pos;
        for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
        for (int i = m - 1; i >= 0; --i) {
            int x = a[i];
            next[i] = pos.count(x) ? pos[x] : (1 << 30);
            pos[x] = i;
        }
        //For(i, 0, m) printf("%d ", a[i]); puts("");
        //For(i, 0, m) printf("%d ", next[i]); puts("");
        for (int i = m - 2; i >= 0; --i) {
            if (next[i + 1] < next[i]) {
                next[i] = next[i + 1];
            }
        }
        //For(i, 0, m) printf("%d ", next[i]); puts("");
        
        for (int i = 0; i < q; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            if (next[u] > v) {
                printf("OK\n");
            } else {
                printf("%d\n", a[next[u]]);
            }
        }
        printf("\n");
    }
    return 0;
}
