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

vector< vector<int> > memo[31][31];

bool been[31][31];

vector< vector<int> > f(int n, int least) {
  if (n == 0) {
    return vector<vector<int> >(1);
  }  
  least = min(least, n);
  
  if (been[n][least]) return memo[n][least];
  
  vector< vector<int> > ans;
  for (int take = least; take >= 1; --take){
    
    vector< vector<int> > sub = f(n - take, take);
    for (int k = 0; k < sub.size(); ++k) {
      ans.push_back(sub[k]);
      ans.back().push_back(take);
    }
  }
  
  been[n][least] = true;
  memo[n][least] = ans;
  return ans;
}

int main(){
    #ifndef LOCAL
    #define problem_name "part"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int n; cin >> n;
  
    vector< vector<int> > ans = f(n, n);
    for (int i = 0; i < ans.size(); ++i) {
      assert(ans[i].size() > 0);
      printf("%d", ans[i].back());
      for (int k = ans[i].size() - 2; k >= 0; --k){
	printf("+%d", ans[i][k]);
      }
      puts("");
    }
    
    return 0;
}


