#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define dbg(x) cerr << #x << " == " << x << endl
#define _ << " " <<

template<class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }

typedef long long ll;

int a[30], b[30] , n, m, l;

char dfs1(int,char,char,char);
char dfs2(int,char,char,char);

char f[1<<26], h[1<<26];

char dfs1(int mask, char alpha, char beta, char level) {

	if(!level) {
		if(h[mask])
			return h[mask]-40;
		char func = 0;
		for(int i = 0; i < n; ++i) func += (a[i]&mask)==a[i];
		for(int i = 0; i < m; ++i) func -= (b[i]&mask)==b[i];
		return h[mask]=func+40,func;
	}
	
	char& res = f[mask];
	
	if(beta <= res)
		return res;
	
	if(alpha < res)
		alpha = res;
	
	int vx[26], cx=0, _mask, i;
	for(_mask = mask;_mask;) {
		vx[cx] = _mask&-_mask;
		_mask ^= vx[cx++];
	}
	
	for(i = 0; i < cx; ++i) {
		char nalpha = dfs2(mask^vx[i],alpha,beta,level-1);
		if(nalpha > alpha) res = alpha = nalpha;
		if(alpha >= beta) break;
	}
	
	return alpha;
}

char dfs2(int mask, char alpha, char beta, char level) {

	if(!level) {
		if(h[mask])
			return h[mask]-40;
		char func = 0;
		for(int i = 0; i < n; ++i) func += (a[i]&mask)==a[i];
		for(int i = 0; i < m; ++i) func -= (b[i]&mask)==b[i];
		return h[mask]=func+40,func;
	}

	char& res = f[mask];
	
	if(alpha >= res)
		return res;
	
	if(beta > res)
		beta = res;

	int vx[26], cx=0, _mask, i;
	for(_mask = mask;_mask;) {
		vx[cx] = _mask&-_mask;
		_mask ^= vx[cx++];
	}
	
	for(i = 0; i < cx; ++i) {
		char nbeta = dfs1(mask^vx[i],alpha,beta,level-1);
		if(nbeta < beta) res = beta = nbeta;
		if(alpha >= beta) break;
	}
	
	return beta;
}

int main() {

	#ifndef LOCAL
		freopen("keyboard.in","r",stdin);
		freopen("keyboard.out","w",stdout);
	#endif
	
	srand(777);	
	map<char,int> fc;
	string alphabet;
	for(char c = 'a'; c <= 'z'; c++)
		alphabet.push_back(c);
	random_shuffle(alphabet.begin(),alphabet.end());
	for(int i = 0; i < 26; i++)
		fc[alphabet[i]]=i;
	
	cin >> l;
	
	char str[40];
	
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> str;
		for(int j = 0; str[j]; ++j)
			a[i] |= 1 << fc[str[j]];
	}
	
	cin >> m;
	for(int i = 0; i < m; ++i) {
		cin >> str;
		for(int j = 0; str[j]; ++j)
			b[i] |= 1 << fc[str[j]];
	}
	
	for(int i = 0; i < 1<<26; ++i)
		if(__builtin_popcount(i)&1)
			f[i]=+n;
		else
			f[i]=-m;
	
	cout << (int)dfs1((1<<26)-1,-m,+n,l) << endl;
	
	return 0;
}
