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

#define bitSet(mask, bit) (!!((mask) & (1 << (bit))))

double dist(int x1, int y1, int x2, int y2) {
    long long dx = x2 - x1;
    long long dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

struct Tree {
    int x, y, v, l, index;
    bool operator < (const Tree &t) const {
        return x < t.x or x == t.x and y < t.y;
    }
} T[15];

int n;

int sumValues(int cut) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!bitSet(cut, i)) continue;
        //printf("i = %d is present, value is %d\n", i, T[i].v);
        ans += T[i].v;
    }
    return ans;
}

int sumLength(int cut) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!bitSet(cut, i)) continue;
        ans += T[i].l;
    }
    return ans;
}

int cross(const Tree &o, const Tree &a, const Tree &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double perimeter(int standing) {
    vector< Tree > points;
    for (int i = 0; i < n; ++i) if (bitSet(standing, i)) points.push_back( T[i] );
    
    if (points.size() == 0) return 0.0;
    if (points.size() == 1) return 0.0;
    if (points.size() == 2) return 2 * dist(points[0].x, points[0].y, points[1].x, points[1].y);
    
    int n = points.size(), k = 0;
    vector< Tree > H(2 * n);
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k-2], H[k-1], points[i]) <= 0) k--;
        H[k++] = points[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(H[k-2], H[k-1], points[i]) <= 0) k--;
        H[k++] = points[i];
    }
    assert( k > 1 );
    H.resize(k - 1);
    
    double ans = 0.0;
    for (int i = 0; i < H.size(); ++i) {
        int j =  (i + 1) % H.size();
        ans += dist(H[i].x, H[i].y, H[j].x, H[j].y);
    }
    return ans;
}

int main(){
    int run = 0;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        if (run > 0) puts("");
        printf("Forest %d\n", ++run);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d %d", &T[i].x, &T[i].y, &T[i].v, &T[i].l);
            T[i].index = i;
        }
        sort(T, T + n);
        
        int minValue = (1 << 30), which = -1, minCount = -1;
        double excess = -1;
        
        for (int cut = 0; cut < (1 << n); ++cut) {
            int cost = sumValues( cut );
            int availableWood = sumLength( cut );
            double requiredWood = perimeter( ~cut & ((1 << n) - 1) );
            
            if (cmp(requiredWood, 1.0 * availableWood) > 0) continue; // not enough
            
            int count = __builtin_popcount( cut );
            if (cost < minValue or cost == minValue and count < minCount) {
                minValue = cost;
                which = cut;
                minCount = count;
                excess = 1.0 * availableWood - requiredWood;
            }
        }
        assert( which != -1 );

        printf("Cut these trees:");
        
        vector< int > ans;
        for (int k = 0; k < n; ++k) if (bitSet(which, k)) ans.push_back( T[k].index );
        sort(ans.begin(), ans.end());
        for (int k = 0; k < ans.size(); ++k) printf(" %d", ans[k] + 1);
        puts("");
        printf("Extra wood: %.2lf\n", excess);
        
//        D( sumValues( 26 ) );
//        D( sumLength( 26 ) );
//        D( perimeter( 37 ) );
    }
    return 0;
}
