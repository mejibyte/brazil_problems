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
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 and m == 0) break;
        
        map<int, int> times;
        for (int i = 0; i < m; ++i) {
            int x; scanf("%d", &x);
            times[x]++;
        }
        
        priority_queue< int, vector< int >, greater< int > > q;
        foreach(p, times) {
            q.push( p->second );
        }
        while (q.size() < (1 << n)) q.push(0);
        
        long long ans = 0;
        while (q.size() > 1) {
            int a = q.top(); q.pop();
            int b = q.top(); q.pop();
            
            ans += (a + b);
            q.push(a + b);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
