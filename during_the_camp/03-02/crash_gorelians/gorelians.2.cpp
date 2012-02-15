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

const long double EPS = 1e-9;
int cmp(long double x, long double y = 0, long double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

struct Circle {
    long double x, y, r;
    Circle(){}
};

vector< Circle > cur;

bool canTalk(const Circle &a, const Circle &b) {
    long double dist = hypotl(a.x - b.x, a.y - b.y);
    if (cmp(a.r, dist) >= 0) return true;
    if (cmp(b.r, dist) >= 0) return true;
    return false;
}

bool compact() {
    for (int j = 0; j < cur.size(); ++j) {
        const Circle &next = cur[j];
        vector< int > merge;
        for (int i = 0; i < cur.size(); ++i) {
            if (canTalk(next, cur[i])) {
                merge.push_back( i );
            }
        }
        if (merge.size() == 1) continue;
        
        long double sx = 0, sy = 0, sa = 0;
        for (int i = 0; i < merge.size(); ++i) {
            int k = merge[i];
            sx += cur[k].x;
            sy += cur[k].y;
            sa += cur[k].r * cur[k].r;
        }
        
        long double sr = sqrtl(sa);
        sx /= (merge.size());
        sy /= (merge.size());
        
        vector< Circle > ncur;
        for (int i = 0; i < cur.size(); ++i) {         
            if (binary_search(merge.begin(), merge.end(), i)) continue;
            ncur.push_back( cur[i] );
        }

        Circle merged; merged.x = sx, merged.y = sy, merged.r = sr;
        ncur.push_back( merged );
        
        cur = ncur;
        return true;
    }
    return false;
}

int main(){
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        cur.clear();
        
        for (int i = 0; i < n; ++i) {
            int x, y, r;
            scanf("%d %d %d", &x, &y, &r);
            //printf("Landing (%d, %d, %d)\n", x, y, r);
            Circle next; next.x = x, next.y = y, next.r = r;
            cur.push_back( next );
            while (compact());
        }
        printf("%d\n", cur.size());
    }
    return 0;
}
