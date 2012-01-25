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

const int MAXN = 105;

bool been[MAXN][MAXN];

typedef pair<int, int> Pair;
pair<int, int> from[MAXN][MAXN];

int dx[4] = { -1, -1, +1, +1 };
int dy[4] = { -1, +1, -1, +1 };

int M, N;

bool inside(int x, int y){
  return 1 <= x and x <= M and 1 <= y and y <= N;
}

int main(){
    #ifndef LOCAL
    #define problem_name "horse"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int p, q, x1, y1, x2, y2;
    cin >> M >> N >> p >> q >> x1 >> y1 >> x2 >> y2;
    
    queue< pair<int, int> > Q;
    Q.push( make_pair(x1, y1) );
    been[x1][y1] = true;
    from[x1][y1] = make_pair(-1, -1);
    
    while (Q.size() > 0) {
      int x = Q.front().first;
      int y = Q.front().second;
      Q.pop();
      
      for (int k = 0; k < 8; ++k) {
	int nx, ny;
	if (k < 4){
	  nx = x + dx[k] * p;
	  ny = y + dy[k] * q;
	} else {
	  nx = x + dx[k - 4] * q;
	  ny = y + dy[k - 4] * p;	  
	}
	
	if (!inside(nx, ny)) continue;
	if (been[nx][ny]) continue;
	
	been[nx][ny] = true;
	from[nx][ny] = make_pair(x, y);
	Q.push( make_pair(nx, ny) );
      }
    }
    
    if (!been[x2][y2]) {
      puts("-1");
      return 0;
    }
    
    vector< Pair > ans;
  
    while (x2 != x1 or y2 != y1) {
      ans.push_back( make_pair(x2, y2) );
      
      Pair next = from[x2][y2];
      x2 = next.first, y2 = next.second;
    }
    ans.push_back( make_pair(x1, y1) );
    
    printf("%d\n", ans.size() - 1);
    for (int k = ans.size() - 1; k >= 0; --k) {
      printf("%d %d\n", ans[k].first, ans[k].second);
    }
    
    return 0;
}


