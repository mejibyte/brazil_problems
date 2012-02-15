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

struct Circle {
    double x, y, r;
    Circle(){}
};

vector< Circle > cur;

bool canTalk(const Circle &a, const Circle &b) {
    double dist = hypot(a.x - b.x, a.y - b.y);
    if (cmp(a.r, dist) >= 0) return true;
    if (cmp(b.r, dist) >= 0) return true;
    return false;
}

bool compact() {
    vector< int > merge;
    for (int j = 0; j < cur.size(); ++j) {
        const Circle &next = cur[j];
        for (int i = j + 1; i < cur.size(); ++i) {
            if (canTalk(next, cur[i])) {
                merge.push_back( i );
            }
        }
        if (merge.size() == 0) continue;
        
        merge.push_back( 1 << 30 );
        
        vector< Circle > ncur;
        for (int i = 0, j = 0; i < cur.size(); ++i) {
            while (merge[j] < i) j++;
            if (merge[j] == i) continue;
            ncur.push_back( cur[i] );
        }
        
        double sx = 0, sy = 0, sa = 0;
        for (int i = 0; i + 1 < merge.size(); ++i) {
            int k = merge[i];
            sx += cur[k].x;
            sy += cur[k].y;
            sa += cur[k].r * cur[k].r;
        }
        sx += next.x;
        sy += next.y;
        sa += next.r * next.r;
        
        double sr = sqrt(sa);
        sx /= merge.size();
        sy /= merge.size();
        
        Circle merged; merged.x = sx, merged.y = sy, merged.r = sr;
        ncur.push_back( merged );
        
        cur = ncur;
        return true;
    }
    return false;
}

void land(int x, int y, int r) {
    vector< int > merge;
    Circle next; next.x = x, next.y = y, next.r = r;
    
    for (int i = 0; i < cur.size(); ++i) {
        if (canTalk(next, cur[i])) {
            merge.push_back( i );
            printf("new guy can merge with (%.1lf, %.1lf, %.1lf)\n", cur[i].x, cur[i].y, cur[i].r);
        }
    }
    merge.push_back( 1 << 30 );
    
    vector< Circle > ncur;
    for (int i = 0, j = 0; i < cur.size(); ++i) {
        while (merge[j] < i) j++;
        if (merge[j] == i) continue;
        ncur.push_back( cur[i] );
    }
    
    double sx = 0, sy = 0, sa = 0;
    for (int i = 0; i + 1 < merge.size(); ++i) {
        int k = merge[i];
        sx += cur[k].x;
        sy += cur[k].y;
        sa += cur[k].r * cur[k].r;
    }
    sx += next.x;
    sy += next.y;
    sa += next.r * next.r;
    
    double sr = sqrt(sa);
    sx /= merge.size();
    sy /= merge.size();
    
    Circle merged; merged.x = sx, merged.y = sy, merged.r = sr;
    ncur.push_back( merged );
    
    cur = ncur;
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
