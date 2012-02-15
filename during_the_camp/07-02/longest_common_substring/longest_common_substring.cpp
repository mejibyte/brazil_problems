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

int N;
const int MAXN = 10005 * 10;

char text[MAXN];
long long key[MAXN]; int sa[MAXN], rank[MAXN], *lcp=(int*)key;
struct Cmp { bool operator()(int i, int j) const { return key[i] < key[j]; } };

void build(int n) {
    for (int i = 0; i < n; ++i) { sa[i] = i; key[i] = text[i]; }
    sort(sa, sa + n, Cmp());
    for (int k = 1; ; k *= 2) {
        for (int i = 0; i < n; ++i)
            rank[sa[i]] = i > 0 and key[sa[i-1]]==key[sa[i]] ? rank[sa[i-1]] : i;
        if (k >= n) break;
        for (int i = 0; i < n; ++i)
            key[i] = rank[i] * (n + 1LL) + (i+k < n ? rank[i+k]+1 : 0);
        sort(sa, sa+n, Cmp());
    }
    for (int i = 0, k = 0; i < n; ++i) {
        if (k > 0) k--;
        if (rank[i] == n-1) { lcp[n-1] = -1; k = 0; continue; }
        int j = sa[rank[i]+1];
        while (text[i+k] == text[j+k]) k++;
        lcp[rank[i]] = k;
    }
}

int id[MAXN];

bool can(int len, int n) {
    for (int i = 0; i < n - 1; ) {
        if (lcp[i] < len) {
            i++;
            continue;
        }
        
        int seen = (1 << id[i]) | (1 << id[i + 1]);
        int j = i;
        while (lcp[j] >= len) {
            seen |= (1 << id[j + 1]);
            j++;
        }
        if (seen == (1 << N) - 1) return true;        
        i = j;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        if (!(cin >> N)) break;
        int at = 0;
        int len = 0;
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            for (int k = 0; k < s.size(); ++k) {
                text[at++] = s[k];
            }
            text[at++] = i + 1;
        }
        if (N == 1) {
            cout << at - 1 << endl;
            continue;
        }
        build(at);
        for (int k = at, last; k >= 0; --k) {
            if (text[k] < 'a') last = text[k];
            id[rank[k]] = last - 1;
        }
//        for (int i = 0; i < at; ++i) {
//            for (int k = sa[i]; k < at; ++k) printf("%c", text[k]);
//            printf(" (belongs to %d)\n", id[i]);
//        }

        //for (int i = 0; i < at; ++i) {
//            printf("lcp[%d] = %d\n", i, lcp[i]);
//        }
    
        int low = 0, high = at;
        while (low < high) {
            int m = (low + high + 1) / 2;
            if (can(m, at)) {
                low = m;
            } else {
                high = m - 1;
            }
        }        
        printf("%d\n", low);
    }
    return 0;
}
