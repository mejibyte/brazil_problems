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
    freopen("golf.in", "r", stdin);
    freopen("golf.out", "w", stdout);
    #endif
    
    int ans = 0;
    for (int i = 0; i < 18; ++i) {
        int k; cin >> k;
        string s; getline(cin, s);
        s = s.substr(1);
        if (s == "triple bogey") ans += k + 3;
        else if (s == "double bogey") ans += k + 2;
        else if (s == "bogey") ans += k + 1;
        else if (s == "par") ans += k;
        else if (s == "birdie") ans += k - 1;
        else if (s == "eagle") ans += k - 2;
        else if (s == "albatross") ans += k - 3;
        else if (s == "hole in one") ans += 1;
        else assert(false);
    }
    printf("%d\n", ans);
    return 0;
}