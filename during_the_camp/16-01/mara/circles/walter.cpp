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
typedef pair<double, double> pii;
typedef long long ll;
typedef long double ld;
#define inf (1 << 28)
#define N 10001
#define l(x) (x * 2 + 1)
#define r(x) (x * 2 + 2)
double eps = 1e-7;
int cmp(double a, double b = 0){
	return a + eps < b ? -1 : a - eps > b ? 1 : 0;
}
 
vector<pii> solve(){
	vector<pii> res;
	int r1, r2, x1, y1, x2, y2;
	scanf("%d %d %d", &x1, &y1, &r1);
	scanf("%d %d %d", &x2, &y2, &r2);
	int dist2 = quad(x1 - x2) + quad(y1 - y2);
	if(r1 < r2) swap(r1, r2), swap(x1, x2), swap(y1, y2);
	bool uno = false;
	
	if(dist2 == 0){
		if(r1 == r2) printf("I can't count them - too many points :(\n");
				else printf("There are no points!!!\n");
		return res;
	}
	
	if(dist2 < quad(r1)){
		if(dist2 < quad(r1 - r2)){
			printf("There are no points!!!\n");
			return res;
		}else if(dist2 == quad(r1 - r2)) uno = true;
	}else if(dist2 > quad(r1)){
		if(dist2 == quad(r1 + r2)) uno = true;
		else if(quad(r1 + r2) < dist2){
			printf("There are no points!!!\n");
			return res;
		}
	}
	
	
	double d = quad(r1) - quad(r2) + dist2;
	d /= 2 * sqrt(dist2);
	double dx = x2 - x1;
	double dy = y2 - y1;
	double norm = hypot(dx, dy);
	dx /= norm; dy /= norm;
	double cx = dx * d + x1, cy = dy * d + y1;
	double per = sqrt(r1 * r1 - d * d);
	swap(dx, dy); dx = -dx;
	res.pb(mp(cx + dx * per, cy + dy * per));	
	if(!uno)
		res.pb(mp(cx - dx * per, cy - dy * per));	
	sort(res.begin(), res.end());
	return res;
}

int main(){
    #ifndef LOCAL
	freopen("circles.in", "r", stdin);
	freopen("circles.out", "w", stdout);
	#endif
	int k; cin >> k; bool first = true;
	while(k--){
		if(first) first = false;
		else printf("\n");
		vector<pii> res = solve();	
		if(!res.empty()){
			printf("There are only %d of them....\n", res.size());
			f(i, 0, res.size())
				printf("%.06f %.06f\n", res[i].fst, res[i].snd);
		}
	}
}


