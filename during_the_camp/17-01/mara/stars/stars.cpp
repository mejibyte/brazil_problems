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

const int MAXN = 130;

long long cube[MAXN][MAXN][MAXN];

void add(int X, int Y, int Z, long long howmuch) {
  for (int x = X + 1; x < MAXN; x += x & -x) {
    for (int y = Y + 1; y < MAXN; y += y & -y) {
      cube[x][y][Z] += howmuch;
      //printf("increased (x=%d, y=%d, z=%d)\n", x, y, Z);
    }
  }
}

long long square(int X, int Y, int Z){
  long long ans = 0;
  for (int x = X + 1; x > 0; x -= x & -x) {
    for (int y = Y + 1; y > 0; y -= y & -y) {
      ans += cube[x][y][Z];
      //printf("added (x=%d, y=%d, z=%d) = %lld\n", x, y, Z, cube[x][y][Z]);      
    }
  }
  return ans;
}

long long sum(int x1, int x2, int y1, int y2, int Z) {
  long long ans = square(x2, y2, Z);
  if (y1 > 0) ans -= square(x2, y1 - 1, Z);
  if (x1 > 0) ans -= square(x1 - 1, y2, Z);
  if (x1 > 0 and y1 > 0) ans += square(x1 - 1, y1 - 1, Z);
  return ans;
}

long long box(int x1, int x2, int y1, int y2, int z1, int z2) {
  long long ans = 0;
  for (int z = z1; z <= z2; ++z) {
    ans += sum(x1, x2, y1, y2, z);
  }
  return ans;
}

int main(){
    #ifndef LOCAL
    #define problem_name "stars"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int n;
    scanf("%d", &n);
    
    int e;
    while (scanf("%d", &e) == 1) {
      if (e == 1) {
	int x, y, z, k;
	scanf("%d %d %d %d", &x, &y, &z, &k);
	add(x, y, z, k);	
      } else if (e == 2) {
	int x1, y1, z1, x2, y2, z2;
	scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
	long long ans = box(x1, x2, y1, y2, z1, z2);
	cout << ans << "\n";
      } else {
	break;
      }
    }
    
    return 0;
}


