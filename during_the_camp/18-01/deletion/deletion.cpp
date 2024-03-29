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

const int oo = (1 << 30);
const int MAXN = 5000005;

int P[MAXN];
int T[MAXN];
int C[MAXN]; // Count of eliminated in each round

int main(){
    #ifndef LOCAL
        freopen("deletion.in", "r", stdin);
        freopen("deletion.out", "w", stdout);
    #endif
    
    int n, k, l;
    scanf("%d %d %d", &n, &k, &l);
    
    for (int x = 0; x <= n; ++x) {
        if (x < k) {
            P[x] = T[x] = oo;
        } else {
            P[x] = x % k == 0 ? 1 : P[x - x / k] + 1;
            T[x] = x % k == 0 ? x / k : T[x - x / k];
        }
        
        if (P[x] < oo) C[P[x]]++;
    }
    for (int x = n, i = 1; x >= k; i++) {
        assert( C[i] == x / k );
        x = x - x / k;
    }
    
    for (int i = 1; i <= n; ++i) {
       C[i] += C[i - 1];
    }
    
    for (int q = 0; q < l; ++q) {
        int x; scanf("%d", &x);
        if (x < k) printf("0\n");
        else printf("%d\n", T[x] + C[P[x] - 1]);
    }
    
    return 0;
}
