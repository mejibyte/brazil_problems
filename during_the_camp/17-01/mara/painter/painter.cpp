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

const int MAXN = 500000;

struct Node {
  int C;
  int L;
  bool endsBlack;
  bool startsBlack;
  
  void set(int c, int l, bool starts, bool ends) {
    C = c;
    L = l;
    endsBlack = ends;
    startsBlack = starts;
  }
  
  bool full(int l, int r){
    return L == l - r + 1;
  }
  
  bool makeFull(int l, int r, bool black) {
    if (black) {
      L = l - r + 1;
      C = 1;
      endsBlack = startsBlack = true;
    } else {
      L = 0;
      C = 0;
      endsBlack = startsBlack = false;
    }
  }
};

Node tree[500005 * 2 * 4 + 10];

int split(int l, int r) {
  if (l + 1 == r) return l;
  return (l + r) / 2;
}

void paint(int node, int l, int r,    int p, int q, bool black) {
  //printf("node = %d, l = %d, r = %d, p = %d, q = %d, black = %d\n", node, l, r, p, q, black);
  
  if (l > r) return;
  
  if (p > r) return;
  if (q < l) return;
  
  assert(l <= p and p <= r or l <= q and q <= r);
  
  p = max(p, l);
  q = min(q, r);
  
  Node &s = tree[node];
  
  
  int a = 2 * node;
  int b = 2 * node + 1;
  int m = split(l, r);
  
  if (l == r) { // hoja
    if (black){
      s.set(1, 1, true, true);
    } else {
      s.set(0, 0, false, false);
    }
    return;
  }
  
  assert(l < r);
  
  
  if (s.full(l, r)) {
    tree[a].makeFull(l, m, s.startsBlack);
    tree[b].makeFull(m + 1, r, s.startsBlack);
  }
  
  if (l == p and q == r) { // full segment
    if (black){
      s.makeFull(l, r, true);
    } else {
      s.makeFull(l, r, false);
    }
    tree[a].makeFull(l, m, black);
    tree[b].makeFull(m + 1, r, black);    
    return;
  }
  
   
  paint(a, l, m,            p, q, black);
  paint(b, m + 1, r,    p, q, black);
  
  s.C = tree[a].C + tree[b].C;
  if (tree[a].endsBlack and tree[b].startsBlack) {
    s.C--;
  }
  s.L = tree[a].L + tree[b].L;
  
  s.startsBlack = tree[a].startsBlack;
  s.endsBlack = tree[b].endsBlack;
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
      if (l > 0) {
	paint(1, -MAXN, MAXN,   x, x + l - 1,  c == 'B');
      }
      printf("%d %d\n", tree[1].C, tree[1].L);
    }
    
    return 0;
}


