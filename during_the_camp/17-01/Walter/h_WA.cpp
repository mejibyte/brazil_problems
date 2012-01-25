#include<iostream>
#include<stack>
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
#define FORV(it,A) for(vector<int>::iterator it = A.begin(); it!= A.end(); it++)
#define FORS(it,A) for(set<int>::iterator it = A.begin(); it!= A.end(); it++)
#define quad(x) (x) * (x)
#define mp make_pair
#define clr(x, y) memset(x, y, sizeof x)
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;
#define inf (1 << 30)
#define N 1000003
#define M 6
int road[M][N];
int factor[N];
int cnt[N];
int sum[M][N + 1];

int main(){
	freopen("primes.in", "r", stdin);
	freopen("primes.out", "w", stdout);  
	f(i, 1, N) factor[i] = i;
	for(int i = 2; i * i < N; i++) if(factor[i] == i)
		for(int j = i * i; j < N; j += i)
			factor[j] = i;

	cnt[1] = 1;
	f(i, 2, N){
		int x = i;
		int pot = 0;
		while(x % factor[i] == 0) x /= factor[i], pot++;
		cnt[i] = (pot + 1) * cnt[x];
	}
	int begs[] = {2, 3, 6, 48, 64, 1 << 29};
	f(it, 0, M){
		road[it][0] = it == 1;
		int x = begs[it];
		f(i, 1, N){
			road[it][i] = (x > N ? __builtin_ctz(x) + 1 : cnt[x]) == 2;
			x = (x > N ? __builtin_ctz(x) + 1 : cnt[x]) + i + 1;
		}
		sum[it][0] = 0;
		f(i, 0, N) sum[it][i + 1] = sum[it][i] + road[it][i];
	}
	int l, r;
	int caso = 1;
	while(cin >> l >> r && (l || r)){
		int best = 0;
	       f(it, 0, M) best = max(best, sum[it][r] - sum[it][l - 1]);
       		cout << "Window " << caso++ << ": There can be up to " << best << " primes." << endl;	       
	}

			
/*	
	set<int> last;
	set<vector<int> > aux;
	for(int beg = 1; beg < N; beg++){
		int x = beg;
		vector<int> bb;
		f(i, 2, 30){
			bb.pb(cnt[x] == 2);
			x = cnt[x] + i;
		}
		if(!aux.count(bb)) cout << beg << endl;
		aux.insert(bb);
		//cout << endl;
	}
	cout << aux.size() << endl;
	*/

}



