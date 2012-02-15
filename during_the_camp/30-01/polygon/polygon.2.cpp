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

const double EPS = 1e-5;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const double pi = 2.0 * acos(0);

struct point{
    double x, y;
    point (double x, double y) : x(x), y(y){}  
    point (){}  
};

point center (const point &p, const point &q, const point &r){
    double ax = q.x - p.x;
    double ay = q.y - p.y;
    double bx = r.x - p.x;
    double by = r.y - p.y;
    double d = ax * by - bx * ay;    
        
    double cx = (q.x + p.x) / 2.0;
    double cy = (q.y + p.y) / 2.0;
    double dx = (r.x + p.x) / 2.0;
    double dy = (r.y + p.y) / 2.0;
    
    double t1 = bx * dx + by * dy;
    double t2 = ax * cx + ay * cy;
    
    double x = (by * t2 - ay * t1) / d;
    double y = (ax * t1 - bx * t2) / d;
    
    return point(x, y);
    
}

point operator - (const point &p, const point &q){
    point ans (p.x - q.x, p.y - q.y);
    return ans;
}

bool operator == (const point &p, const point &q){
   return (cmp (p.x, q.x) == 0 and cmp(p.y, q.y) == 0);
}

void print(point p) {
    cout << p.x << " " << p.y << endl;
}

int main(){
    ios::sync_with_stdio(false);
    double x1, y1, x2, y2, x3, y3;
    while (scanf("%lf %lf %lf %lf %lf %lf", &x1,&y1,&x2,&y2,&x3,&y3) == 6) {
        point p(x1, y1); point q(x2, y2); point r(x3, y3);
        point c = center(p, q, r);
        p = p - c;
        q = q - c;
        r = r - c;
        
        double radius = sqrt(p.x * p.x + p.y * p.y);
        double theta = atan2(p.y, p.x);
        
        bool found = false;
        for (int v = 3; v <= 1000; v++){
            bool sp, sq, sr;
            sp = sq = sr = false;
            double alpha = theta;
            double delta = 2 * pi / v;
            
            
            for (int k = 0; k < v; k++){
                double x = radius * cos(alpha);
                double y = radius * sin(alpha);
                point t (x , y );
                /*if (v == 20){
                    printf("t = "); print(t);
                    printf("p = "); print(p);
                    printf("q = "); print(q);
                    printf("r = "); print(r);
                    puts("");
                }*/
                if (p == t) sp = true;
                if (q == t) sq = true;
                if (r == t) sr = true;
                if (sp and sq and sr) break;
                
                alpha += delta;
            }
            
            //if(v==20){D(sp); D(sq); D(sr);}
            if (sp and sq and sr){ found = true; cout << v << endl; break;}
        }
        
        assert(found);
        /*printf("Point: (%lf,%lf)\n", p.x, p.y);
        printf("Point: (%lf,%lf)\n", q.x, q.y);
        printf("Point: (%lf,%lf)\n", r.x, r.y);*/
        
    }
    return 0;
}
