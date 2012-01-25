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

vector<string> codes[12];
string s[3] = {"0", "1", "2"};
void recurse(int step){
	if(step == 1){
		codes[1].pb("0");
		codes[1].pb("1");
		codes[1].pb("2");
	}else{
		recurse(step - 1);
		f(itt, 0, 3){
			int it = itt;
			f(i, 0, codes[step - 1].size()){
				codes[step].pb(s[it] + codes[step - 1][i]);
				it++;
				if(it == 3) it = 0;
			}
		}
	}
}

int main(){
	freopen("antigray.in", "r", stdin);
	freopen("antigray.out", "w", stdout);  
	int n; cin >> n;
	recurse(n);
	f(i, 0, codes[n].size())
		printf("%s\n", codes[n][i].c_str());
}



