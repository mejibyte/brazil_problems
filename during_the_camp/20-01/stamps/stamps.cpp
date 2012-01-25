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

const int MAXN = 32;
int price[MAXN];
int have[MAXN];
int value[MAXN];

void generate(int i, int j, vector< pair<int, int> > &ans) {
  int n = j - i + 1;
  ans.push_back( make_pair(0, 0) );
  if (n <= 0) return;
  for (int s = 1; s < (1 << n); ++s) {
    int v = 0, p = 0;
    for (int k = 0; k < n; ++k) {
      if (s & (1 << k)) {
        v += value[k + i];
        p += price[k + i];
      }
    }
    ans.push_back( make_pair(v, p) );
  }
  sort(ans.begin(), ans.end());
}

int main(){
    #ifndef LOCAL
    freopen("stamps.in", "r", stdin);
    freopen("stamps.out", "w", stdout);
    #endif
    
    int N, K;
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i) scanf("%d", price + i);
    for (int i = 0; i < N; ++i) scanf("%d", have + i);
    int sum = 0;
    for (int i = 0; i < N; ++i) {
      scanf("%d", value + i);
      sum += value[i];
    }
    
    if (sum < K) {
      puts("-1");
      return 0;
    }
    
    vector< pair<int, int> > A, B;
    generate(0, N / 2 - 1, A);
    generate(N / 2, N - 1, B);
    
    for (int i = A.size() - 2; i >= 0; --i) {
      A[i].second = min(A[i].second, A[i + 1].second);
    }
    for (int i = B.size() - 2; i >= 0; --i) {
      B[i].second = min(B[i].second, B[i + 1].second);
    }
    
    int ans = (1 << 30);
    for (int a = 0, b = B.size() - 1; a < A.size() and b >= 0; ) {
      if (A[a].first + B[b].first >= K) {
        ans = min(A[a].second + B[b].second, ans);
        b--;
      } else {
        a++;
      }
    }
    
    sum = 0;
    for (int i = 0; i < N; ++i) sum += have[i] * price[i];
    ans = max(0, ans - sum);
    printf("%d\n", ans);
    return 0;
}