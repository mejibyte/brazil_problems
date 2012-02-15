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

vector< int > num;

long long memo[25][180][2];

long long f(int pos, int sum, bool smaller) {
    if (sum < 0) return false;
    if (pos == num.size()) {
        return sum == 0;
    }
    
    if (memo[pos][sum][smaller] != -1) return memo[pos][sum][smaller];
    long long ans = 0;
    
    int limit = smaller ? 9 : num[pos];
    for (int place = 0; place <= limit; ++place) {
        ans += f(pos + 1, sum - place, smaller || (place < num[pos]));
    }
    return memo[pos][sum][smaller] = ans;
}

long long count(long long x, int sum) {
    num.clear();
    while (x > 0) {
        num.push_back( x % 10 );
        x /= 10;
    }
    reverse(num.begin(), num.end());
    memset(memo, -1, sizeof memo);
    return f(0, sum, false);
    
}

long long Count(long long a, long long b, int sum) {
    long long ans = count(b, sum);
    if (a - 1 > 0) ans -= count(a - 1, sum);
    return ans;
}

int main(){
    int T; cin >> T;
    while (T--) {
        long long a, b, x;
        if (!(cin >> a >> b >> x)) break;
        
        long long ans = 0;
        for (int s = 1; ;++s) {
            if (ans >= (b - a + 1)) break; // los compre todos
            if (x < s) break;
            
            long long tickets = Count(a, b, s);
            long long buy = x / (long long)s;
            buy = min(buy, tickets);
            
            ans += buy;
            x -= buy * s;
        }
        cout << ans << endl;   
    }
    return 0;
}
