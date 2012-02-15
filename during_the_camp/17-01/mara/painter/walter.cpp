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

vector<int> falta(1 << 21, -1);
vector<int> cle(1 << 21, 0);
vector<int> cri(1 << 21, 0);
vector<int> cnt(1 << 21, 0);
vector<int> seg(1 << 21, 0);
int n = 1000002;
vector<int> res[1000002];

inline void refresh(int u, int a, int b){
	int c = falta.at(u);
	if(a != b) falta[u * 2 + 1] = falta[u * 2 + 2] = falta.at(u);
	falta.at(u) = -1;
	cle.at(u) = cri.at(u) = c;
	seg.at(u) = c == 1 ? 1 : 0;
	cnt.at(u) = c == 1 ? (b - a + 1) : 0;
}

void paint(int c, int le, int ri, int u, int a, int b){
	if(falta.at(u) != -1)
		refresh(u, a, b); 
	if(le > ri) return;
	if(le == a && b == ri){
		falta.at(u) = c;
		refresh(u, a, b);
	}else{
		int mid = (a + b) >> 1;
		int x = u * 2 + 1, y = u * 2 + 2;
		paint(c, le, min(ri, mid), x, a, mid);
		paint(c, max(le, mid + 1), ri, y, mid + 1, b);
		cnt.at(u) = cnt[x] + cnt[y];
		seg.at(u) = seg[x] + seg[y];
		if(cri[x] == cle[y] && cri[x] == 1) seg.at(u)--;
		cri.at(u) = cri[y];
		cle.at(u) = cle[x];
	}
}

int main(){
	freopen("painter.in", "r", stdin);
	freopen("painter.out", "w", stdout);  
	int m; scanf("%d", &m);
	while(m--){
		int x, l; char c;
		scanf(" %c %d %d", &c, &x, &l);
		x += 500000;
		if(c == 'W') paint(0, x, x + l - 1, 0, 0, n);
		else paint(1, x, x + l - 1, 0, 0, n);	
		printf("%d %d\n", seg[0], cnt[0]);
	}
}



