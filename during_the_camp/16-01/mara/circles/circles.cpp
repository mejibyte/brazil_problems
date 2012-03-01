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


vector< pair<double, double> > getPoints(int x1, int y1, int r1, int x2, int y2, int r2) {
    vector< pair<double, double> > ans;
    int dx = x2 - x1;
    int dy = y2 - y1;
    assert(dy != 0);
    
    if (dx * dx + dy * dy > (r1 + r2) * (r1 + r2)) {
        return ans; // too far away
    }
    if (dx * dx + dy * dy == (r1 + r2) * (r1 + r2)) {
        double t = 1.0 * r1 / (r1 + r2);
        double x = x1 + t * (x2 - x1), y = t * (y2 - y1);
        ans.push_back(make_pair(x, y));
        return ans;
    }
    
    int dr = r2 * r2 - r1 * r1;
    int cc = dx * dx + dy * dy;
    double d = (dr - cc) / -2.0;
    double e = (1.0 * -dx / dy);
    double f = d / dy;

    double a = e * e + 1;
    double b = 2 * f * e;
    double c = f * f - r1 * r1;
    //printf("%d %d %d %d %d %d\n", x1, y1, r1, x2, y2, r2);
    //D(f*f - r2*r2);
    assert(cmp(a, 0) != 0);
    
    double det = b * b - 4 * a * c;
    if (cmp(det, 0) < 0) return ans;
    
    assert(cmp(det, 0) >= 0);
    if (cmp(det, 0) == 0) { // just one point
        double xx1 = -b / (2*a);
        double yy1 = e * xx1 + f;
        ans.push_back( make_pair(xx1 + x1, yy1 + y1) );
        return ans;
    }
    
    double xx1 = (-b - sqrt(det)) / (2*a);
    double yy1 = e * xx1 + f;
    
    double xx2 = (-b + sqrt(det)) / (2*a);
    double yy2 = e * xx2 + f;
    ans.push_back(make_pair(xx1 + x1, yy1 + y1));
    ans.push_back(make_pair(xx2 + x1, yy2 + y1));
    return ans;
}

void solve() {
    int x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    
    // same center
    if (x1 == x2 and y1 == y2) {
        //coincident
        if (r1 == r2) {
            puts("I can't count them - too many points :(");
            return;
        }
        // one inside the other
        puts("There are no points!!!");
        return;
    }
    
    bool swapped = false;
    if (y1 == y2) {
        swap(x1, y1), swap(x2, y2);
        swapped = true;
    }
    
    vector< pair<double, double> > p = getPoints(x1, y1, r1, x2, y2, r2);
    if (p.size() == 0) {
        puts("There are no points!!!");
    } else {
        printf("There are only %d of them....\n", p.size());
        if (swapped) for (int i = 0; i < p.size(); ++i) swap(p[i].first, p[i].second);
        sort(p.begin(), p.end());
        for (int i = 0; i < p.size(); ++i) {
            double x = p[i].first, y = p[i].second;
            printf("%.6lf %.6lf\n", x, y);
        }
    }
}

int main(){
    #ifndef LOCAL
    #define problem_name "circles"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int K; cin >> K;
    for (int i = 0; i < K; ++i){
        if (i > 0) puts("");
        solve();
    }
    return 0;
}