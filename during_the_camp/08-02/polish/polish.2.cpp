using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////
const int MAXN = 1e5 + 5;
const int mod = 1e9 + 7;

int a[MAXN];
long long tree[MAXN];

void add(int at, long long what) {
    for (at++; at < MAXN; at += at & -at) {
        tree[at] += what;
        if (tree[at] >= mod) tree[at] -= mod;
    }
}

long long sum(int at) {
    long long ans = 0;
    for (at++; at > 0; at -= at & -at) {
        ans += tree[at];
        if (ans >= mod) ans -= mod;
    }
    return ans;
}

char text[MAXN]; long long key[MAXN];
int N, sa[MAXN], rank[MAXN], *lcp = (int*) key;

struct Cmp { bool operator () (int i, int j) const {return key[i] < key[j];} };

void build(){
    for (int i = 0; i < N; i++){ sa[i] = i; key[i] = text[i]; }
    sort (sa, sa + N, Cmp());
    for (int k = 1; ; k *= 2){
        for (int i = 0; i < N; i++)
            rank[sa[i]] = i > 0 and key[sa[i-1]] == key[sa[i]] ? rank[sa[i-1]] : i;
        if (k >= N) break;
        for (int i = 0; i < N; i++)
            key[i] = rank[i] * (N + 1LL) + (i + k < N ? rank[i+k] + 1 : 0);
        sort (sa, sa + N, Cmp());    
    }        
}
int main(){
    while (scanf("%s", text) == 1){
        memset(tree, 0, sizeof tree);
        N = strlen(text);       
        build();
        for (int i = 0; i < N; ++i) a[i] = N - sa[i];
        // for (int i = 0; i < N; ++i) printf("%d ", a[i]); puts("");
        
        
        for (int i = N - 1; i >= 0; --i) {
            int x = a[i];
            assert(1 <= x and x <= N);
            
            assert(sum(x) - sum(x-1) == 0);
            long long s = sum(N) - sum(x);
            s++;
            s = (s % mod + mod) % mod;
            printf(" at %d will add %lld\n", x, s);
            add(x, s);    
        }
        
        D(sum(N));
        int ans = sum(N) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
