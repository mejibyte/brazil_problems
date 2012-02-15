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
    freopen("chivalry.in", "r", stdin);
    freopen("chivalry.out", "w", stdout);
    #endif

    string a, b; cin >> a >> b;
    int i = 0, j = 0;
    while (i < a.size() and j < b.size()) {
        if (a[i] == b[j]) cout << a[i++];
        else if (a[i] == 'W' and b[j] == 'M') cout << a[i++];
        else cout << b[j++];
    }
    while (i < a.size()) cout << a[i++];
    while (j < b.size()) cout << b[j++];
    cout << endl;
    return 0;
}