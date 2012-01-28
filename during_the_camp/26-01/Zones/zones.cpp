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


int main(){
    int n, allow;
    int run = 1;
    while (scanf("%d %d", &n, &allow) == 2) {
        if (n == 0 and allow == 0) break;
        vector< int > score(n);
        for (int i = 0; i < n; ++i) scanf("%d", &score.at(i));
        int m; scanf("%d", &m);
        vector< pair<int, long long> > common(m); // first = mask, second = value
        for (int i = 0; i < m; ++i) {
            int size; scanf("%d", &size);
            int mask = 0;
            for (int i = 0; i < size; ++i) {
                int k; scanf("%d", &k);
                k--;
                mask |= (1 << k);
            }
            foreach(p, common) assert( mask != p->first );
            long long int v; cin >> v;
            common.push_back( make_pair(mask, v) );
        }
        
        assert(allow <= n);
        
        long long ans = -1;
        int which = -1;
        for (int subset = 0; subset < (1 << n); ++subset) {
            if (__builtin_popcount(subset) != allow) continue;
            long long option = 0;
            for (int i = 0; i < n; ++i) {
                if (subset & (1 << i)) option += score[i];
            }
            foreach(p, common) {
                
                if ((subset & p->first) == p->first ) {
                    int count = __builtin_popcount(p->first & subset);
                    if (count > 1) {
                        option += ((count % 2) ? 1 : -1) * (count - 1) * (p->second);
                    }
                }
            }
            if (option > ans) {
                ans = option;
                which = subset;
            }
        }
        assert(ans != -1);
        assert(which != -1);
        
        printf("Case Number %d\n", run++);
        printf("Number of Customers: %d\n", ans);
        printf("Locations recommended:");
        for (int k = 0; k < n; ++k) {
            if (which & (1 << k)) printf(" %d", k + 1);
        }
        puts("");
        puts("");
    }
    return 0;
}
