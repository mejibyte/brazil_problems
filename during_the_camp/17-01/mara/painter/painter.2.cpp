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

#include <bitset>

const int MAXN = 500000;
const int MAXL = 2*MAXN*4;

enum { Pending, Black, White };

int C[MAXL]; // count of black segments
int L[MAXL]; // length of black segments
bitset<MAXL> P; // Starts with black or not
bitset<MAXL> Q; // Ends with black or not
int pending[MAXL]; // 0 if not pending, 1 if pending black, 2 if pending white

int maxNode = -1;

void propagate(int node, int l, int r) {
    maxNode = max(node, maxNode);
    if (pending[node]) {
        int color = pending[node];
        pending[node] = false;
        C[node] = (color == Black);
        L[node] = (color == Black) ? (r - l + 1) : 0;
        P[node] = Q[node] = (color == Black);
        if (l < r) { // push the flag to my sons
            pending[2*node] = pending[2*node + 1] = color;
        }
    }
}

void paint(int node, int l, int r,   int p, int q,  int color) {
    propagate(node, l, r);
    if (q < l) return;
    if (p > r) return;
    p = max(p, l);
    q = min(q, r);
    if (p == l and q == r) {
        pending[node] = color;
        propagate(node, l, r);
    } else {
        int m = (l + r) / 2;
        paint(2*node, l, m, p, q, color);
        paint(2*node + 1, m + 1, r, p, q, color);
        
        C[node] = C[2*node] + C[2*node + 1];
        if (Q[2*node] and P[2*node + 1]) C[node]--;
        L[node] = L[2*node] + L[2*node + 1];
        P[node] = P[2*node];
        Q[node] = Q[2*node + 1];
    }
}


int main(){
    #ifndef LOCAL
    #define problem_name "painter"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif

    int n; scanf("%d ", &n);
    
    for (int i = 0; i < n; ++i) {
      char c;
      int x, l;
      scanf(" %c %d %d ", &c, &x, &l);
      x += MAXN;
      if (l > 0) {
          paint(1, 0, 2*MAXN + 1, x, x + l - 1,  c == 'B' ? Black : White);
      }
      printf("%d %d\n", C[1], L[1]);
    }
    D(maxNode);
    return 0;
}


