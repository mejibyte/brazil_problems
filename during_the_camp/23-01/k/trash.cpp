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
//typedef long long CoordType;

struct Point{
    double x, y;
    Point (double x, double y) : x(x), y(y) {}
    Point () {}
    bool operator <(const Point &p) const{
        return x < p.x || (x == p.x && y < p.y);
    }
    
    double length() const {
        return sqrt(x * x + y * y);
    }
    
    double lengthSqr() const {
        return x * x + y * y;
    }
};

double cross (const Point &O, const Point &A, const Point &B){
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);   
}

vector <Point> convexHull(vector<Point> P){
    int n = P.size(), k = 0;
    vector <Point> H(2*n);
    sort (P.begin(), P.end());
    
    for (int i = 0; i < n; i++){
        while (k >= 2 && cmp(cross(H[k-2], H[k-1], P[i]), 0) <= 0) k--;
        H[k++] = P[i];    
    }
    
    for (int i = n - 2, t = k + 1; i >= 0; i--){
        while (k >= t && cmp(cross(H[k-2], H[k-1], P[i]), 0) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k);    
    return H;    
}

double dot(const Point &a, const Point &b) {
    double ans = a.x * b.x + a.y * b.y;
    return ans;
}

Point project(const Point &v, const Point &u) { // retorna v proyectado sobre u
    double k = dot(u, v) / u.lengthSqr();
    Point ans = u;
    ans.x *= k;
    ans.y *= k;
    return ans;
    
}

Point sub(const Point &a, const Point &b) {
    Point ans = a;
    ans.x -= b.x;
    ans.y -= b.y;
    return ans;
}

double d(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double distsqr(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return (dx * dx + dy * dy);
}

double dPointLine(Point a, Point b, Point pnt) {
    double u = ((pnt.x - a.x) * (b.x - a.x) + (pnt.y - a.y) *(b.y - a.y)) / distsqr(a, b);
    Point i;
    i.x = a.x + u * (b.x - a.x);
    i.y = a.y + u * (b.y - a.y);
    return d(pnt, i);
    
}


double parallel( const vector< Point > &p) {
    double ans = 1e100;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;        
        Point u = sub(p[next], p[i]);
   
        double farthest = -1;
        for (int j = 0; j < n; ++j) {
            farthest = max(farthest, dPointLine(p[i], p[next], p[j]));
        }
        //printf(" edge from (%.0lf, %.0lf) to (%.0lf, %.0lf): farthest is %lf\n", p[i].x, p[i].y, p[next].x, p[next].y, farthest);
        ans = min(ans, farthest);
    }
    return ans;
}

void solve( const vector< Point > &p) {
    int n = p.size();
    //for (int i = 0; i < n; ++i) printf("(%.1lf, %.1lf)-", p[i].x, p[i].y); puts("");
    double ans = 1e100;
//    for (int i = 0; i < n; ++i) {
//        int next = (i + 1) % n;
//        
//        Point u = p[next];
//        u.x -= p[i].x;
//        u.y -= p[i].y;
//        
//        Point pl = project( sub(p[ (i - 1 + n) % n ], p[i]), u);
//        Point pr = project( sub(p[ (i + 2) % n ], p[next]), u);
//        
//        double option =       d(pl, p[next]);
//        option = max( option, d(pl, pr) );
//        option = max( option, d(p[i], p[next]) );
//        option = max( option, d(p[i], pr) );
//        
//       // printf(" edge from (%.0lf, %.0lf) to (%.0lf, %.0lf): option is %lf\n", p[i].x, p[i].y, p[next].x, p[next].y, option);
////        printf(" pl = (%lf, %lf), pr = (%lf, %lf)\n" , pl.x, pl.y, pr.x, pr.y);
////        
//      //  D( d(pl, p[next]) );
////        D( d(pl, pr) );
////        D( d(p[i], p[next]) );
////        D( d(p[i], pr) );
//        
//        ans = min(ans, option);
//    }
    ans = min(ans, parallel(p));
    ans = ceil(ans * 100) / 100;
    printf("%.2lf\n", ans);
}

int main(){
    
    int n; int run = 0;
    while (scanf("%d ", &n) == 1 ){
        if (n == 0) break;
        run++;
        vector <Point> P;
        for (int i = 0; i < n; i++){
            int x, y;
            scanf("%d %d ", &x, &y);
            Point p(x, y);
            P.push_back(p);
        }    
        vector< Point > hull = convexHull(P);
        hull.pop_back(); // remove repeated element
        printf("Case %d: ", run); solve( hull );
    }
    return 0;
}
