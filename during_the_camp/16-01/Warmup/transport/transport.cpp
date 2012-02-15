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

const int MAXN = 55;
int pos[MAXN];
int speed[MAXN];
bool seen[MAXN];

int main(){
 #ifndef LOCAL
    freopen("transport.in", "r", stdin);
    freopen("transport.out", "w", stdout);
    #endif    
    int S, K, N;
    cin >> S >> K >> N;
    for (int i = 0; i < N; ++i) {
        cin >> pos[i];
        if (pos[i] == 0) seen[i] = true;
    }
    for (int i = 0; i < N; ++i) cin >> speed[i];
    
    int me = 0;
    for (int t = 0; t < K; ++t) {
        for (int i = 0; i < N; ++i) {
            if (me + S >= pos[i] + speed[i]) {
                seen[i] = true;
            }
            pos[i] += speed[i];
        }
        me += S;
    }
    
    int ans = 0;
    for (int i = 0; i < N; ++i) ans += seen[i];
    cout << ans << endl;
    
    return 0;
}