using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "pawns"

bool losing(int k);

int mex(vector<int> &v) {
    sort(v.begin(), v.end());
    v.resize( unique(v.begin(), v.end()) - v.begin() );
    if (v.at(0) > 0) return 0;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if (i + 1 >= n or v[i] + 1 < v[i + 1]) {
            return v[i] + 1;
        }
    }
    assert(false);  
}

vector< int > w;

void precompute() {
    const int MAX = 2000;    
    vector< int > g(MAX);
    g[0] = 0;
    g[1] = g[2] = g[3] = 1;
    for (int k = 4; k < MAX; ++k) {
        vector<int> options;
        for (int take = 0; take <= k - 3; ++take) {
            options.push_back( g[take] ^ g[k - 3 - take] );
        }
        g[k] = mex(options);
    }

    for (int i = 0; i < MAX; ++i) {
        if (g[i] == 0) w.push_back( i );
    }
    
    int period[12] = {2, 6, 2, 2, 6, 2, 2, 6, 2, 8, 2, 8};
    
    for (int i = 0; i < 5; ++i) printf("%d, ", w[i]);
    
    for (int i = 5; i < w.size(); ++i) {
        int diff = w.at(i) - w.at(i - 1);
        printf("%d\n", w[i]);
        assert(diff == period[(i - 5) % 12]);
        assert( losing( w[i] ) );
    }
    
    puts("");
}

bool losing(int n) {
    assert(n > 30);
    int period[12] = {2, 6, 2, 2, 6, 2, 2, 6, 2, 8, 2, 8};
    int sum = 0; for (int i = 0; i < 12; ++i) sum += period[i];
    n -= 30;
    n %= sum;
    if (n == 0) return true;
    
    int partial = 0;
    for (int i = 0; i < 12; ++i) {
        partial += period[i];
        if (partial == n) return true;
    }
    
    return false;
}

int main(){
    #ifndef LOCAL    
    assert( freopen(INPUT_FILE ".in", "r", stdin) != NULL );
    assert( freopen(INPUT_FILE ".out", "w", stdout) != NULL );
    #endif
    
    //precompute();
    
    int n;
    while (cin >> n) {
        assert(n <= 1000000000);
        if (n <= 30) {
            if (n == 0 or n == 4 or n == 10 or n == 20 or n == 30) {
                puts("Black");
            } else {
                puts("White");
            }
        } else {
            //printf("n=%d->", n);
            puts(losing(n) ? "Black" : "White");
        }
        break;
    }
    
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
