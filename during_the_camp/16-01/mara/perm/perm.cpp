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
#include <deque>
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

typedef deque<int> List;

vector< List > permute(List &v) {
  if (v.size() == 1) {
    return vector< List >(1, v);
  }
  
  vector< List > ans;
  
  int n = v.size();
  for (int k = 0; k < n; ++k) {
    List remain = v;
    remain.pop_front();
    
    vector< List > add = permute(remain);
    
    for (int i = 0; i < add.size(); ++i) {
      
      List &next = add[i];
      next.push_front( v.front() );
      
      ans.push_back( next );
    }
    
    v = ans.back();
    swap(v[0], v[1]);
  }
  return ans;
  
}

int main(){
    #ifndef LOCAL
    #define problem_name "perm"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    
    int N;
    cin >> N;
    List v(N);
    for (int i = 1; i <= N; ++i) v[i - 1] = i;
    
    vector< List > ans = permute(v);
    for (int k = 0; k < ans.size(); ++k) {
      for (int i = 0; i < N; ++i) {
	if (i > 0) printf(" ");
	printf("%d", ans[k][i]);
      }
      puts("");
    }
    
    return 0;
}

