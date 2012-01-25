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
#define N 263000
int n;
int inv[N];
int seg[N];

void make(int u = 0, int le = 0, int ri = n - 1){
	if(le == ri) seg[u] = 1;
	else{
		int mid = (le + ri) / 2;
		make(u * 2 + 1, le, mid);
		make(u * 2 + 2, mid + 1, ri);
		seg[u] = ri - le + 1;
	}
}
int get(int k, int u = 0, int le = 0, int ri = n - 1){
	if(le == ri) return le;
	int mid = (le + ri) / 2;
	if(seg[u * 2 + 1] >= k) return get(k, u * 2 + 1, le, mid);
	else return get(k - seg[u * 2 + 1], u * 2 + 2, mid + 1, ri);
}
void update(int val, int pos, int u = 0, int le = 0, int ri = n - 1){
	if(le == ri) seg[u] += val;
	else{
		int mid = (le + ri) / 2;
		if(pos <= mid) update(val, pos, u * 2 + 1, le, mid);
		else update(val, pos, u * 2 + 2, mid + 1, ri);
		seg[u] = seg[u * 2 + 1] + seg[u * 2 + 2];
	}
}

int bit[N];
int getb(int u){
	int res = 0;
	while(u){
		res += bit[u];
		u -= u & -u;
	}
	return res;
}
void updateb(int u){
	while(u <= n){
		bit[u]++;
		u += u & -u;
	}
}
pii P[N]; 
int ret[N];
int main(){
	freopen("invers.in", "r", stdin);
	freopen("invers.out", "w", stdout);  
	n = 0;
	int x; 
	while(scanf("%d", &x) == 1) inv[n++] = x;
	make();
	f(i, 0, n){
		int p = get(inv[i] + 1);
		update(-1, p);
		P[i] = mp(p, i);
	}	
	clr(bit, 0);
	sort(P, P + n);
	reverse(P, P + n);
	f(i, 0, n){
		ret[P[i].fst] = getb(P[i].snd);
		updateb(P[i].snd + 1);
	}
	f(i, 0, n){
		if(i) printf(" ");
		printf("%d", ret[i]);
	}
	printf("\n");

}



