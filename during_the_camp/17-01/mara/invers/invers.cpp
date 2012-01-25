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

int tree[1 << 20 + 5];

void clear(int len){
  for (int k = len - 1; k >= 1; --k){ 
    tree[k] = tree[2*k] + tree[2*k+1];
  }
}

int count(int node, int left, int right,    int after) {
  if (after >= right) return 0;
  // after < right

  if (left > after) {
    return tree[node];
  }
  // left <= after
  
  if (left == right) {
    return tree[node];
  }

  int middle = (left + right) / 2;
  
  int ans = count(2 * node, left, middle,  after) + count(2 * node + 1, middle + 1, right, after);
  return ans;
}

int main(){
    #ifndef LOCAL
    #define problem_name "invers"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    
    vector< int > inversion_table;
    for (int x; scanf("%d", &x) == 1; ){
      inversion_table.push_back(x);
    }
    int n = inversion_table.size();
    if (n == 1) {
      assert( inversion_table[0] == 0 );
      puts("0");
      return 0;
    }
    
    int len = 1;
    while (len < n) len <<= 1;

    // init tree
    for (int k = 0; k < n; ++k) {
      tree[len + k] = 1;
    }
    clear(len);
    
    vector< int > permutation(n, -1);
    
    for (int i = 0; i < n; ++i) {
      int bigger = inversion_table[ i ];
    
      // find the bigger-th available spot
      
      int node = 1; // root
      assert( tree[node] > bigger );
      
      while (node < len) { // while non-root
	node <<= 1;
	if (tree[node] <= bigger) {
	  bigger -= tree[node];
	  node++;
	  assert( tree[node] > bigger );
	}
      }
      
      int spot = node - len;
      assert( permutation.at(spot) == -1 );
      
      permutation[ spot ] = i;
      
      tree[node] = 0;
      node >>= 1;
      while (node >= 1) {
	tree[node] = tree[2*node] + tree[2*node+1];
	node >>= 1;
      }
    }
    
//     puts("original permutation:\n");
//     for (int i = 0; i < n; ++i) {
//       printf("%d ", permutation[i]);
//     }
//     puts("");

    
    vector< int > inverse_permutation(n);
    for (int i = 0; i < n; ++i) {
      inverse_permutation[ permutation[i] ] = i;
    }
    
//     puts("Inverse permutation:\n");
//     for (int i = 0; i < n; ++i){
//       printf("%d ", inverse_permutation[i]);
//     }
//     puts("");

    for (int k = 0; k < n; ++k) {
      assert(tree[k] == 0);
    }
    
    vector< int > ans(n);
    for (int i = 0; i < n; ++i) {
      int next = inverse_permutation[i];
      
      // count elements inserted in positions after next
      int cnt = count(1, 0, len - 1, next);
      
      
      ans[ next ] = cnt;      
    
      // insert 1 into next
      int node = len + next;
      tree[node] = 1;
      node >>= 1;
      while (node >= 1) {
	tree[node] = tree[2*node] + tree[2*node+1];
	node >>= 1;
      }      
    }
    
    for (int i = 0; i < n; ++i) {
      if (i > 0) printf(" ");
      printf("%d", ans[i]);
    }
    puts("");
    
    return 0;
}


