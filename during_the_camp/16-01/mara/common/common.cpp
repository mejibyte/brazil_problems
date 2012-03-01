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

int gcd(int a, int b) {
    return a == 0 ? b : gcd(b % a, a);
}

int square(int x) {
    return x * x;
}

bool isPerfectSquare(int x) {
    int root = int(sqrt(x) + EPS);
    return root * root == x;
}

int main(){
    #ifndef LOCAL
    #define problem_name "common"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int x11, y11, x12, y12, x21, y21, x22, y22;
    cin >> x11 >> y11 >> x12 >> y12;
    cin >> x21 >> y21 >> x22 >> y22;
    int L1 = square(x12 - x11) + square(y12 - y11);
    int L2 = square(x22 - x21) + square(y22 - y21);
    int M = gcd(L1, L2);
    if (isPerfectSquare(L1 / M) and isPerfectSquare(L2 / M)) {
        puts("YES");
        printf("%.6lf\n", sqrt(M));
    } else {
        puts("NO");
    }
    
    return 0;
}