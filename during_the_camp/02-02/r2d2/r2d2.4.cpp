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
        int n; scanf("%d ", &n);
        initialize(1, 0, n);
        for (int i = 0; i < n; ) {
            static char line[1024];
            scanf("%s ", line);
            if (line[0] == 'b') {
                int times, v;
                scanf("%d %d", &times, &v);
                for (int k = 0; k < times; ++k) {
                    a[i] = v;
                    i++;
                }
            } else {
                int v; sscanf(line, "%d", &v);
                a[i] = v;
                i++;
            }
        }
        
        
        #ifdef LOCAL
            fprintf(stderr, "TIME: %lfs\n", (clock() - timeBefore) * 1.0 / CLOCKS_PER_SEC);
        #endif
    }
    return 0;
}
