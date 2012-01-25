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
ll mod = 1000000000;
struct node{
	node *L, *R;
	int y, x, rev, cnt, k;
	ll sum; 
	node(int value, int key){
		L = R = NULL;
		sum = k = value;
      x = key;
		y = rand();
		rev = 0; cnt = 1;
	}
};

void refresh(node* T){
	if(!T) return;
	if(T->rev){
		if(T->L) T->L->rev ^= 1;
		if(T->R) T->R->rev ^= 1;
      swap(T->L, T->R);
		T->rev = 0;
	}
}
void update(node *T){
	if(!T) return;
	T->sum = T->k; T->cnt = 1;
	if(T->L) T->sum += T->L->sum,
		 T->cnt += T->L->cnt;
	if(T->R) T->sum += T->R->sum,
		 T->cnt += T->R->cnt;
}

void split(node *T, int x, node* &L, node* &R){
	if(!T) L = R = NULL;
	else if(T->x > x){
		split(T->L, x, L, T->L);
		R = T;
	}else{
		split(T->R, x, T->R, R);
		L = T;
	}
	update(R); update(L);
}

void split2(node *T, int cnt, node* &L, node* &R){
   refresh(T);
	if(!T) L = R = NULL;
	else if(cnt <= (T->L ? T->L->cnt : 0)){
		split2(T->L, cnt, L, T->L);
		R = T;
	}else{
		split2(T->R, cnt - (T->L ? T->L->cnt : 0) - 1, T->R, R);
		L = T;
	}
	update(R); update(L);
}

node* merge(node*L, node*R){
   if(!L) return R;
   if(!R) return L;
   refresh(L); refresh(R);
   node *T;
   if(L->y > R->y)
      L->R = merge(L->R, R), T = L;
   else
      R->L = merge(L, R->L), T = R;
   update(T);
   return T;
}

node* add(node *T, node *N){
	if(!T || T->y < N->y){
		node* R; split(T, N->x, N->L, N->R);
		T = N;
	}else if(N->x < T->x)
		T->L = add(T->L, N);
	else
		T->R = add(T->R, N);
	update(T);
   return T;
}

int main(){
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);  
	ios::sync_with_stdio(false);
	int n, m;
   node *root = NULL;
   cin >> n >> m;
   f(i, 0, n){
      int x; cin >> x;
      root = add(root, new node(x, i));
   }
   while(m--){
      int q, l, r; cin >> q >> l >> r;
      node *A, *B, *C, *D;
      split2(root, r, A, B);
      split2(A, l - 1, C, D);
      if(q == 0)
         cout << D->sum << endl;
      else{
         D->rev ^= 1;
         refresh(D);
      }
      root = merge(merge(C, D), B);
   }
}


