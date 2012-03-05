#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<string>
#include<cstring>
#include<map>
#include<numeric>
#include<sstream>
#include<cmath>
using namespace std;
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define f(i,x,y) for(int i = x; i<y; i++ )
#define FOR(it,A) for(typeof A.begin() it = A.begin(); it!= A.end(); it++)
#define quad(x) (x) * (x)
#define mp make_pair
#define clr(x, y) memset(x, y, sizeof x)
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;
#define inf (1 << 30)
#define N 1001009
int dp[N];
int prime[N], divs[N];
int main(){
   #ifndef LOCAL
   #define problem_name "primes"
   assert( freopen(problem_name ".in", "r", stdin) != NULL);
   assert( freopen(problem_name ".out", "w", stdout) != NULL);
   #endif
   ios::sync_with_stdio(false);
   f(i, 2, N) prime[i] = i;
   for(int i = 2; i * i < N; i++) if(prime[i] == i)
      for(int j = i * i; j < N; j += i) prime[j] = i;

   divs[1] = 1;
   for(int i = 2; i < N; i++){
      int x = i, cnt = 0;
      while(x % prime[i] == 0) cnt++, x /= prime[i];
      divs[i] = divs[x] * (cnt + 1);
   }

   int l, r, caso = 1;
   while(cin >> l >> r && (l || r)){
      int best = 0;
      for(int i = r; i >= l; i--){
         dp[i] = 1;
         int x = 2;
         int n = i;
         while(n < r){
            x = n + divs[x];
            n++;
            if(divs[x] == 2){
               dp[i] += dp[n];
               break;
            }
         }
         best = max(best, dp[i]);
      }
      cout << "Window " << caso++ << ": There can be up to " << best << " primes." << endl;
   }
}
