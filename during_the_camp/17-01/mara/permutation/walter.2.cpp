#include <iomanip>
#include <ctime>
#include <numeric>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <climits>
#include <cmath>
#include <cctype>
#include <sstream>
#include <map>
#include <set>
#include <cstdio>
#include <queue>
#define f(i,x,y) for(int i=x;i<y;i++)
#define fd(i,y,x) for(int i=y;i>=x;i--)
#define FOR(it,A) for( typeof A.begin() it = A.begin(); it!=A.end(); it++)
#define impr(A) for( typeof A.begin() chen = A.begin(); chen !=A.end(); chen++ ) cout<<*chen<<" "; cout<<endl
#define ll long long
#define vint vector<int>
#define clr(A,x) memset(A,x,sizeof(A))
#define CLR(v) f(i,0,n) v[i].clear()
#define oo (1<<30)
#define ones(x) __builtin_popcount(x)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define pb push_back
#define eps (1e-9)
#define cua(x) (x)*(x)
using namespace std;

int a[100005], n,m;
int s[100005];
inline void add (int x){
    for(; x<=n; x+= x&(-x)) s[x]++;
}
inline int get (int x){
    int res = 0;
    for(; x; x-= x&(-x)) res += s[x];
    return res;
}
inline int get (int a, int b){ return get(b) - get(a-1); }

struct nodo{
    int x,y,ind, le;
    nodo (int a, int b, int c, int d): x(a), y(b), ind(c), le(d){}
    nodo(){}
};

vector<nodo> v[100005];
int ri[100005], le[100005];

int main()
{
    freopen ("permutation.in", "r", stdin);
    freopen ("permutation.out", "w", stdout);
    cin >> n >> m;
    f(i,0,n) scanf ("%d", a+i);
    f(i,0,m){
        int le, ri, x,y;
        scanf ("%d%d%d%d", &le, &ri, &x, &y);
        v[ri].pb (nodo (x, y, i, 0));
        v[le-1].pb (nodo (x, y, i, 1));
    }
    f(j,0,v[0].size()) le[v[0][j].ind] = 0;

    f(i,0,n){
        add (a[i]);
        f(j,0,v[i+1].size()){
            nodo A = v[i+1][j];
            int cuantos = get (A.x, A.y);
            if (A.le) le[A.ind] = cuantos;
            else ri[A.ind] = cuantos;
        }
    }
    f(i,0,m) printf ("%d\n", ri[i] - le[i]);
}