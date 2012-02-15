using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
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
const int MAXN = 100000 + 5;
const int mod = 1000000000 + 7;

char text[MAXN]; //input
int rank[MAXN], sa[MAXN]; //output
int cnt[MAXN], next[MAXN]; //internal
bool bh[MAXN], b2h[MAXN];
 
// Compares two suffixes according to their first characters
bool smaller_first_char(int a, int b){
  return text[a] < text[b];
}
 
void suffixSort(int n){
  //sort suffixes according to their first characters
  for (int i=0; i<n; ++i){
    sa[i] = i;
  }
  sort(sa, sa + n, smaller_first_char);
  //{sa contains the list of suffixes sorted by their first
  //character}
 
  for (int i=0; i<n; ++i){
    bh[i] = i == 0 || text[sa[i]] != text[sa[i-1]];
    b2h[i] = false;
  }
 
  for (int h = 1; h < n; h <<= 1){
    //{bh[i] == false if the first h characters of sa[i-1] ==
    // the first h characters of sa[i]}
    int buckets = 0;
    for (int i=0, j; i < n; i = j){
      j = i + 1;
      while (j < n && !bh[j]) j++;
      next[i] = j;
      buckets++;
    }
    if (buckets == n) break; // We are done! Lucky bastards!
    //{suffixes are separted in buckets containing textings
    // starting with the same h characters}
 
    for (int i = 0; i < n; i = next[i]){
      cnt[i] = 0;
      for (int j = i; j < next[i]; ++j){
        rank[sa[j]] = i;
      }
    }
 
    cnt[rank[n - h]]++;
    b2h[rank[n - h]] = true;
    for (int i = 0; i < n; i = next[i]){
      for (int j = i; j < next[i]; ++j){
        int s = sa[j] - h;
        if (s >= 0){
          int head = rank[s];
          rank[s] = head + cnt[head]++;
          b2h[rank[s]] = true;
        }
      }
      for (int j = i; j < next[i]; ++j){
        int s = sa[j] - h;
        if (s >= 0 && b2h[rank[s]]){
          for (int k = rank[s]+1; !bh[k] && b2h[k]; k++){
              b2h[k] = false;
          }
        }
      }
    }
    for (int i=0; i<n; ++i){
      sa[rank[i]] = i;
      bh[i] |= b2h[i];
    }
  }
  for (int i=0; i<n; ++i){
    rank[sa[i]] = i;
  }
}

int tree[MAXN];

void add(int at, int what) {
    for (at++; at > 0; at -= at & -at) {
        tree[at] += what;
        if (tree[at] >= mod) tree[at] %= mod;
    }
}

int sum(int at) {
    int ans = 0;
    for (at++; at < MAXN; at += at & -at) {
        ans += tree[at];
        if (ans >= mod) ans %= mod;
    }
    return ans % mod;
}

int main(){
    string s;
    while (getline(cin, s)) {
        memset(tree, 0, sizeof tree);
        int N = s.size();
        for (int i = 0; i < N; ++i) text[i] = s[i];
        text[N] = 0;
        assert( N >= 0 );     
        suffixSort(N);
        // for (int i = 0; i < N; ++i) printf("%d ", a[i]); puts("");
        
        for (int i = N - 1; i >= 0; --i) {
            int x = N - sa[i];
            //assert(1 <= x and x <= N);
            
            int s = sum(x);
            s++;
            assert(s >= 0);
            if (s >= mod) s %= mod;
            // printf(" at %d will add %lld\n", x, s);
            add(x, s);    
        }
        int ans = (sum(0) % mod + mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
