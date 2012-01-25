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

bool compatible(const string &s, const string &t) {
  int n = s.size();
  for (int i = 0; i < n; ++i) {
    if (s[i] == t[i]) return false;
  }
  return true;
}

vector< string > f(int n) {
  if (n == 1){
     vector< string > ans(3);
     ans[0] = "0";
     ans[1] = "1";
     ans[2] = "2";
     return ans;
  }
  
  vector< string > p = f(n - 1);
  
  assert(p.size() % 3 == 0);
  
  vector< string > ans;
  
    
  for (int i = 0; i < p.size(); ++i){
    string next = "";
    next += char('0' + i % 3);
    next += p[i];
    ans.push_back( next );
  }
  
  //puts("Placed first pack of 3");
  //D(p[0]);
  
  for (int i = 1; i < p.size(); ++i) {
    if (compatible(p.back(), p[i])) {
      rotate(p.begin(), p.begin() + i, p.end());
      break;
    }
  }
  
  //D(p[0]);
  
  for (int i = 0; i < p.size(); ++i){
    string next = "";
    next += char('0' + i % 3);
    next += p[i];
    ans.push_back( next );
  }
  
  for (int i = 1; i < p.size(); ++i) {
    if (compatible(p.back(), p[i])) {
      rotate(p.begin(), p.begin() + i, p.end());
      break;
    }
  }

  for (int i = 0; i < p.size(); ++i){
    string next = "";
    next += char('0' + i % 3);
    next += p[i];
    ans.push_back( next );
  }
  return ans;
}

int main(){
    #ifndef LOCAL
    #define problem_name "antigray"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    int n; cin >> n; 	
    
    vector< string > ans = f(n);
    for (int i = 0; i < ans.size(); ++i) {
      puts(ans[i].c_str());
    }
    
    return 0;
}


