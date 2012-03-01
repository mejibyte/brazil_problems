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
    double p = (r1 * r1 - r2 * r2 + dx * dx + dy * dy) / (2.0);
    double m = (-1.0 * dx / dy);
    double d = p / dy;
    
    double a = m * m + 1;
    double b = 2 * m * d;
    double c = d * d - r1 * r1;
    
    double det = b * b - 4 * a * c;
    if (cmp(det, 0) < 0) return ans; // no solutions
    if (cmp(det, 0) == 0) {
        double x = -b / (2 * a);
        double y = m * x + d;
        ans.push_back(make_pair(x + x1, y + y1));
    } else {
        double x, y;
        x = (-b + sqrt(det)) / (2 * a);
        y = m * x + d;
        ans.push_back(make_pair(x + x1, y + y1));
        x = (-b - sqrt(det)) / (2 * a);
        y = m * x + d;
        ans.push_back(make_pair(x + x1, y + y1));
    }
    return ans;
}

void solve() {
    int x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    if (x1 == x2 and y1 == y2) { // same center
        if (r1 == r2) puts("I can't count them - too many points :("); //coincident
        else puts("There are no points!!!"); // one inside the other
    } else {
        bool swapped = false;
        if (y1 == y2) swap(x1, y1), swap(x2, y2), swapped = true;
        
        vector< pair<double, double> > p = getPoints(x1, y1, r1, x2, y2, r2);
        if (p.size() == 0) puts("There are no points!!!");
        else {
            printf("There are only %d of them....\n", p.size());
            if (swapped) foreach(k, p) swap(k->first, k->second);
            sort(p.begin(), p.end());
            for (int i = 0; i < p.size(); ++i) {
                printf("%.6lf %.6lf\n", p[i].first, p[i].second);
            }
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