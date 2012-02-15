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
    freopen("medici.in", "r", stdin);
    freopen("medici.out", "w", stdout);
    #endif
    
    int n; cin >> n;
    int scores[n][3];
    for (int p = 0; p < 3; ++p) {
        for (int i = 0; i < n; ++i) {
            cin >> scores[i][p];
        }
    }
    vector< int > winners;
    int bestScore = -1;
    for (int i = 0; i < n; ++i) {
        int s = *min_element(scores[i], scores[i] + 3);
        if (s > bestScore) {
            winners.clear();
            winners.push_back(i);
            bestScore = s;
        } else if (s == bestScore) {
            winners.push_back(i);
        }
    }
    if (winners.size() != 1) puts("-1");
    else printf("%d\n", winners[0]);
    return 0;
}