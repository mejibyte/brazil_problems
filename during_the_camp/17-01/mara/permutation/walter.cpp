#include <iostream>
#include <stack>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <map>
#include <numeric>
#include <sstream>
#include <cmath>
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
#define N 1000001
int bit[N];
int n;
void add(int x){
    while(x <= n){
        bit[x]++;
        x += x & -x;
    }
}
int sum(int x){
    int res = 0;
    while(x){
        res += bit[x];
        x -= x & -x;
    }
    return res;
}
int pos[N];
struct event{
    int le, ri, target, val, i;
    event(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0){
        le = a, ri = b, target = c, val = d, i = e;	
    }
    bool operator <(const event& B) const{
        return target < B.target;
    }
};
event E[2 * N];
int res[N];
int main(){
    #ifndef LOCAL
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);  
    #endif
    int m;
    scanf("%d %d", &n, &m);
    f(i, 0, n){
        int u;
        scanf("%d", &u);
        pos[u] = i + 1;
    }
    clr(bit, 0);
    int sz = 0;
    int x, y, k, l;
    f(i, 0, m){
        scanf("%d %d %d %d", &x, &y, &k, &l);
        E[sz++] = event(x, y, l, 1, i);
        if(k != 1)
            E[sz++] = event(x, y, k - 1, -1, i);
        res[i] = 0;	
    }
    sort(E, E + sz);
    int it = 0;
    f(i, 1, n + 1){
        add(pos[i]);
        while(it < sz && E[it].target == i){
            //cout << i << " " < E[it].
            res[E[it].i] += E[it].val * (sum(E[it].ri) - sum(E[it].le - 1));
            it++;
        }
    }
    f(i, 0, m)
        printf("%d\n", res[i]);
}


