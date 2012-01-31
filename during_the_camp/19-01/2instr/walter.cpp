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
#define N 100001
int vals[70000];
int sw[70000];
int dist[70000];
vector<int> E[70000], W[70000];
int sz;
inline int sig(int x){
	if(x % 2 == 1)
		return (vals[x / 2] & 0xFF) + 
		       ((vals[(x / 2 + 1) % (sz / 2)] >> 8) << 8);  
	else return sw[x / 2];
}
int va = 0;
void print(int x){
	if(va == 16){
		printf("\n");
		va = 0;
	}
	else if(va == 8) printf("  ");
	else if(va) printf(" ");
	printf("%02X", x);
	va++;
}
int main(){
    #ifndef LOCAL
	    freopen("2instr.in", "r", stdin);
	    freopen("2instr.out", "w", stdout);  
	#endif
	int beg, end;
	scanf("%x %x", &beg, &end);
	sz = 65536;
	f(i, 0, sz){
		int a, b; scanf("%x %x", &a, &b);
		vals[i] = (a << 8) + b;
		sw[i] = (b << 8) + a;
	}
	
	f(x, 0, sz){
		int nx = x & (0xFF);
		nx = (nx << 8) | (x >> 8);
		E[nx].pb(x); W[nx].pb(2);
		nx = sig(x);
		E[nx].pb(x); W[nx].pb(1);
	}

	set<pii> q;
	f(i, 0, sz) dist[i] = inf;
	q.insert(mp(0, end)); dist[end] = 0;

	while(!q.empty()){
		int x = q.begin()->snd, d = q.begin()->fst;
		q.erase(q.begin());
		if(d > dist[x]) continue;
		f(i, 0, E[x].size()){
			int u = E[x][i];
			if(dist[u] > dist[x] + W[x][i])
				dist[u] = dist[x] + W[x][i],
				q.insert(mp(dist[u], u));
		}
	}
	if(dist[beg] == inf)
		cout << "IMPOSSIBLE" << endl;
	else{
		cout << dist[beg] << endl;
		int x = beg;
		bool first = true;
		while(dist[x]){
			int nx = x & (0xFF);
			nx = (nx << 8) | (x >> 8);
			if(dist[nx] == dist[x] - 2){
				print(0x0F);
				print(0xCC);
				x = nx;
				continue;
			}
			x = sig(x);
			print(0x5C);
		}
		cout << endl;
	}
}


