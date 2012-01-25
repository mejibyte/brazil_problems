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

bool prime[33000001];
bool prime2[33000001];
int main(){
	freopen("countpr.in", "r", stdin);
	freopen("countpr.out", "w", stdout);  
	ll a, b; cin >> a >> b;
	clr(prime, true);
	clr(prime2, true);
	if(a == 1) prime[0] = false;

	for(ll i = 2; i <= 33000000; i++) if(prime2[i]){
		if(i * i <= b)
		for(ll j = i * i; j <= 33000000;  j += i)
			prime2[j] = false;
		ll fst =  i * ((a + i - 1)/ i);
	        if(fst == i) fst += i;
		for(ll j = fst; j <= b; j += i)
			prime[j - a] = false;	
	}
	int res = 0;
	for(ll i = a; i <= b; i++) res += prime[i - a];
	cout << res << endl;
}



