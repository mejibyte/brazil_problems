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

#include <iomanip>

int main(){
    #ifndef LOCAL
    #define problem_name "sqrooots"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
     
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    
    if (cmp(a, 0) == 0 and cmp(b, 0) == 0) {
        if (cmp(c, 0) == 0) {
            printf("-1\n");
        } else {
            printf("0\n");
        }
        return 0;
    }
    
    if (cmp(a, 0) == 0) {
        assert(cmp(b, 0) != 0);
        printf("1\n%.6lf\n", -c / b);
        return 0;
    }
    
        
    // (-b +- sqrt(b^2 - 4ac)) / 2a
    double det = b*b - 4*a*c;
    if (cmp(det, 0) < 0) {
        printf("0\n");
        return 0;
    }
    
    assert(det >= 0);
    double p = (-b - sqrt(det)) / 2 / a;
    double q = (-b + sqrt(det)) / 2 / a;
    
    if (cmp(p, q) != 0) {
        printf("2\n%.6lf\n%.6lf\n", min(p, q), max(p, q));
    } else {
        printf("1\n%.6lf\n", p);
    }
    return 0;
}

