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
    freopen("equal.in", "r", stdin);
    freopen("equal.out", "w", stdout);
    #endif

    string s; cin >> s;
    for (int l = s.size(); l >= 0; --l) {
        string x = s.substr(0, l);
        string y = s.substr(l);
        int a = 0, b = 0;
        for (int i = 0; i < x.size(); ++i) a += x[i] == 'a';
        for (int i = 0; i < y.size(); ++i) b += y[i] == 'b';
        if (a == b) {
            cout << x << endl;
            cout << y << endl;
            break;
        }
    }
    
    return 0;
}