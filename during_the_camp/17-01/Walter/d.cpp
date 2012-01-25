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
#define inf (1 << 30)
#define N 100001
int n, m, l, f, q;
int E[100][2];
bool reg[100];

ll G[100][100];
ll g(int u, int falta){
	if(falta == 0) return reg[u];
	ll &res = G[u][falta];
	if(res >= 0) return res;
	res = 0;
	f(i, 0, 2) if(E[u][i] != -1)
		res += g(E[u][i], falta - 1);
	return res;
}

void make(ll k, int u = 0, int falta = l){
	if(falta == 0) cout << endl;
	else
	f(i, 0, 2) if(E[u][i] != -1){
		ll va = g(E[u][i], falta - 1);
		if(va >= k){
			cout << char('0' + i);
			make(k, E[u][i], falta - 1);
			break;
		}else k -= va;
	}
}
char s[100];
ll cuenta(){
	int u = 0; ll k = 1;
	f(j, 0, l)
		f(i, 0, 2) if(E[u][i] != -1)
			if(s[j] == i){
			       	u = E[u][i];
				break;
			}else k += g(E[u][i], l - j - 1);
	return k;
}

int main(){
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);  
	ios::sync_with_stdio(false);
	cin >> n >> m >> f >> l >> q;
	clr(E, -1);
	while(m--){
		int a, b, c; cin >> a >> b >> c;
		E[a - 1][c] = b - 1;
	}
	clr(reg, 0);
	while(f--){
		int u; cin >> u;
		reg[u - 1] = true;
	}
	clr(G, -1);
	while(q--){
		char c;
		cin >> c;
		if(c == '?'){
			ll k; cin >> k;
			make(k);
		}else{
			cin >> s;
			f(i, 0, l) s[i] -= '0';
			ll k = cuenta();
			if(c == '>') k++;
			else if(c == '<') k--;
			else{
				cout << k << endl;
				continue;
			}
			make(k);
		}

	}
}



