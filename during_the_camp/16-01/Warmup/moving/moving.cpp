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

int main(){
    #ifndef LOCAL
    freopen("moving.in", "r", stdin);
    freopen("moving.out", "w", stdout);
    #endif
    
    
    vector< int > v;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int h, m, s; scanf("%d:%d:%d ", &h, &m, &s);
        v.push_back(h * 60 * 60 + m * 60 + s);
    }
    int t;
    scanf("%d", &t);
    for (int i = 0; i + t <= n; ++i) {
        int s = 0;
        for (int j = i; j < i + t; ++j) s += v[j];
        printf("%d\n", s / t);
    }
    return 0;
}