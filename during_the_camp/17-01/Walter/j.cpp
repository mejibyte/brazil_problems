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
int bit[129][129][129];
int n;
int add(int x, int y, int z){
	ll res = 0;
	for(int xx = x; xx; xx -= xx & -xx)
	for(int yy = y; yy; yy -= yy & -yy)
	for(int zz = z; zz; zz -= zz & -zz)
		res += bit[xx][yy][zz];
	return res;
}
void update(int x, int y, int z, int k){
	for(int xx = x; xx <= n; xx += xx & -xx)	
	for(int yy = y; yy <= n; yy += yy & -yy)	
	for(int zz = z; zz <= n; zz += zz & -zz)	
		bit[xx][yy][zz] += k;
}

int main(){
	freopen("stars.in", "r", stdin);
	freopen("stars.out", "w", stdout);  
	clr(bit, 0);
	cin >> n;
	int m;
	while(scanf("%d", &m))
		if(m == 3) break;
		else if(m == 1){
			int x, y, z, k; 
			scanf("%d %d %d %d", &x, &y, &z, &k);
			x++; y++; z++;
			update(x, y, z, k);
		}else{
			int res = 0;
			int x, y, z, xx, yy, zz;
			scanf("%d %d %d", &x, &y, &z);
			scanf("%d %d %d", &xx, &yy, &zz);
			x++; y++; z++;
			xx++; yy++; zz++;
			res += add(xx, yy, zz);
			res -= add(x - 1, yy, zz);
			res -= add(xx, y - 1, zz);
			res -= add(xx, yy, z - 1);
			res += add(x - 1, y - 1, zz);
			res += add(x - 1, yy, z - 1);
			res += add(xx, y - 1, z - 1);
			res -= add(x - 1, y - 1, z - 1);
			printf("%d\n", res);
		}


}



