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
vector< int > v;

bool works(int k) {
    int n = v.size();
    for (int start = 0; start < k; ++start) {
        if (start + k > n) continue; // not enough space for a full measure
        int full = 0;
        int loud = 0;
        for (int startMeasure = start; startMeasure + k <= n; startMeasure += k) {
            full++;
            
            bool loudEnough = true;
            for (int i = startMeasure + 1; i < startMeasure + k; ++i) {
                if (v[i] > v[startMeasure]) loudEnough = false;
            }
            if (loudEnough) loud++;
        }
        assert(full > 0);
        if (100 * loud >= 80 * full) return true;
    }
    return false;
}

int main(){
    #ifndef LOCAL
    freopen("measures.in", "r", stdin);
    freopen("measures.out", "w", stdout);
    #endif

    for (int x; cin >> x; v.push_back(x));
    
    int ans = -1;
    for (int k = 2; k <= 10; ++k) {
        if (works(k)) {
            ans = k;
            break;
        }
    }
    cout << ans << endl;
   return 0;
}