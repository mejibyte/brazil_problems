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
    const int MAX = 5000;    
    vector< int > g(MAX);
    g[0] = 0;
    g[1] = g[2] = 1;
    g[3] = 2;
    for (int k = 4; k < MAX; ++k) {
        vector<int> options;
        // take only 2 from one extreme
        options.push_back( g[0] ^ g[k - 2] );
        
        // now always take 3
        for (int left = 0; left <= k - 3; ++left){
            options.push_back( g[left] ^ g[k - left - 3] );
            if (left > k - left - 3) break;            
        }
        g[k] = mex(options);
        //printf("g[%d] = %d\n", k, g[k]);
    }

    for (int i = 0; i < MAX; ++i) {
        if (g[i] == 0) {
            w.push_back( i );
            // printf("lose in i = %d\n", i);
        }
    }
    

    int period[5] = {4, 4, 10, 4, 12};
    
    printf("%d\n", w[0]);
    for (int i = 11; i < w.size(); ++i) {
        int diff = w.at(i) - w.at(i - 1);
        printf("%d, ", w[i]);
        // printf("%d (diff with previous = %d)\n", w[i], diff);
        assert(diff == period[(i - 11) % 5]);
        assert( losing( w[i] ) );
    }
    
    puts("");

}

bool losing(int n) {
    int small[11] = { 0, 4, 8, 14, 20, 24, 28, 34, 38, 42, 54 };
    if (n <= 54) return binary_search(small, small + 11, n);
    
    assert(n > 54);
    int period[5] = {4, 4, 10, 4, 12};
    int sum = 0; for (int i = 0; i < 5; ++i) sum += period[i];
    n -= 54;
    n %= sum;
    if (n == 0) return true;
    
    int partial = 0;
    for (int i = 0; i < 5; ++i) {
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
        bool black = losing(n);
        puts(black ? "Black" : "White");
        break;
    }
    
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
