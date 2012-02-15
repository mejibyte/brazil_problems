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

pair <double, double> line_intersection(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3){
    double t0 = (y3 - y2) * (x0 - x2) - (x3 - x2) * (y0 - y2);
    double t1 = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
    double det = (y1 - y0) * (x3 - x2) - (y3 - y2) * (x1 - x0);
    assert(cmp(det, 0) != 0); // Not parallel
    t0 /= det;
    t1 /= det;
    double x = x0 + t0 * (x1 - x0);
    double y = y0 + t0 * (y1 - y0);
    return (make_pair(x, y));
    
}

double dist (double x0, double y0, double x1, double y1){
    double d = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
    return sqrt(d);    
}

double find_side(double r1, double r2, double r3){
    double ax = r1; double ay = r1;
    double bx = r1 + 2 * sqrt(r1 * r2); double by = r2;
    double cx = bx + 2 * sqrt(r2 * r3); double cy = r3;
    pair<double, double> p = line_intersection (ax, ay, bx, by, 0, 0, 1, 0);
    pair<double, double> q = line_intersection (bx, by, cx, cy, 0, 0, 1, 0);
    
   return dist(p.first, p.second, q.first, q.second); 
    
}

int main(){
    int run = 1;
    double r, r1, r2, r3;
    while (scanf("%lf %lf %lf %lf", &r, &r1, &r2, &r3) == 4){
        if (r1 == -1 and r2 == -1 and r3 == -1 and r == -1) break;
        
        double a = find_side(r2, r, r3);
        double b = find_side(r3, r, r1);
        double c = find_side(r1, r, r2);
        
        double ans = r * (a + b + c) / 2.0;
        
        printf("Case %d: %.2lf\n", run++, ans);
    }
    return 0;
}
