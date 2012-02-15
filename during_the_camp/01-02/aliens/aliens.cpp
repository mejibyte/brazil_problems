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

const int MAXN = 40015;

char text[MAXN];
long long key[MAXN];
int N, sa[MAXN], rank[MAXN], *lcp=(int*)key;
struct Cmp { bool operator()(int i, int j) const { return key[i] < key[j]; } };

void build() {
    for (int i = 0; i < N; ++i) { sa[i] = i; key[i] = text[i]; }
    sort(sa, sa+N, Cmp());
    for (int k = 1; ; k *= 2) {
        for (int i = 0; i < N; ++i){
            rank[sa[i]] = i > 0 && key[sa[i-1]]==key[sa[i]] ? rank[sa[i-1]] : i;
        }
        if (k >= N) break;
        for (int i = 0; i < N; ++i){ 
            key[i] = rank[i] * (N + 1LL) + (i + k < N ? rank[i+k]+1 : 0);
        }
        sort(sa, sa+N, Cmp());
    }
    for (int i = 0, k = 0; i < N; ++i) {
        if (k > 0) k--;
        if (rank[i] == N-1){ lcp[N-1] = -1; k = 0; continue; }
        int j = sa[rank[i]+1];
        while (text[i+k] == text[j+k]) k++;
        lcp[rank[i]] = k;
    }
}

bool can(int p, int m) {
    m--;
    //ver si hay un subarreglo de longitud m con elementos >= p
    for (int i = 0; i < N; ) {
        if (lcp[i] < p) {
            i++;
            continue;
        }
        
        int j = i;
        while (j < N and lcp[j] >= p) j++;
        int len = j - i;
        if (len >= m) return true;
        i = j;
    }
    return false;
}

int find(int p, int m) {
    m--;
    //ver si hay un subarreglo de longitud m con elementos >= p
    int ans = -1;
    for (int i = 0; i < N; ) {
        if (lcp[i] < p) {
            i++;
            continue;
        }
        int j = i;
        while (j < N and lcp[j] >= p) j++;
        int len = j - i;
        if (len >= m) {
            for (int k = i; k <= j; ++k) {
                ans = max(ans, sa[k]);
            }
        }
        i = j;
    }
    return ans;    
}

int main(){
    int m;
    while (scanf("%d ", &m) == 1) {
        if (m == 0) break;
        scanf("%s ", text);
        N = strlen(text);   
        text[N] = '\0';     
        if (m == 1) {
            printf("%d 0\n", N);
            continue;
        }
        build();      
        //for (int i = 0; i < N; ++i) D( sa[i] ); puts("**");
        //for (int i = 0; i < N; ++i) D( string(text).substr(sa[i]) );
        //for (int i = 0; i < N; ++i) D( lcp[i] ); puts("**");
                
        if (!can(1, m)){
            puts("none");
            continue;
        }  
        
        int low = 1, high = N;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (can(mid, m)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        assert(can(low, m));
        printf("%d ", low);
        printf("%d", find(low, m));
        puts("");
    }
    
    return 0;
}
