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

pii seg[200000];
int n;

pii get(int a, int b, int u = 0, int le = 0, int ri = n - 1){
	if(a > b) return mp(inf, 0);
	if(a == le && b == ri) return seg[u];
        int mid = (le + ri) / 2;
	return min(get(a, min(b, mid), u * 2 + 1, le, mid),
		   get(max(a, mid + 1), b, u  * 2 + 2, mid + 1, ri));	
}

struct node{
	int k, a, i;
	node(int aa = 0, int bb = 0, int cc = 0){
		k = aa; a = bb; i = cc;
	}
	bool operator <(const node& B) const{
		return k < B.k;
	}
};
node p[N];
void make(int u = 0, int le = 0, int ri = n - 1){
	if(le == ri) seg[u] = mp(p[le].a, le); 
	else{
		int mid = (le + ri) / 2;
		make(u * 2 + 1, le, mid);
		make(u * 2 + 2, mid + 1, ri);
		seg[u] = min(seg[u * 2 + 1], seg[u * 2 + 2]);
	}
}
int pai[N], L[N], R[N];

int solve(int le, int ri, int up = -1){
	if(le > ri) return -1;
	int mid = get(le, ri).snd;
	int it = p[mid].i;
	pai[it] = up;
	L[it] = solve(le, mid - 1, it);
	R[it] = solve(mid + 1, ri, it);
	return it;
}

int main(){
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);  
	cin >> n;
	clr(pai, -1);
	clr(L, -1);
	clr(R, -1);
	f(i, 0, n){
		int k, a; scanf("%d %d", &k, &a);
		p[i] = node(k, a, i);
	}
	sort(p, p + n);
	make();
	solve(0, n - 1);
	printf("YES\n");
        f(i, 0, n)
	 printf("%d %d %d\n", pai[i] + 1, L[i] + 1, R[i] + 1);	
}



