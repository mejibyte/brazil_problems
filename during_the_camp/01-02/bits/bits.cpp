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

long long choose[70][70];
int need[70];
long long memo[25][70][2];

// contar cuantos numeros hay <= a digits que tengan exactamente k bits en 1
long long f( const vector< int > &digits, int i, int k, bool smaller ) {
    if (i == digits.size()){
        return (k == 0);
    }
    
    if (memo[i][k][smaller] != -1) return memo[i][k][smaller];
    
    long long &ans = memo[i][k][smaller];
    ans = 0;
    // place 0
    ans += f(digits, i + 1, k, smaller || (digits[i] == 1));
    // place 1
    if (smaller or digits[i] == 1) ans += f(digits, i + 1, k - 1, smaller);
    return ans;
}


long long count(long long limit, int target) {
    if (limit <= 64) {
        long long ans = 0;
        for (int i = 1; i <= limit; ++i) {
            if (need[i] == target) ans++;
        }
        return ans;
    }
    assert( limit > 64 );
    if (target == 0 ) {
        return 1; // only 1
    }
    assert( target - 1 >= 0 );
    
    
    vector< int > digits;
    while (limit > 0) {
        digits.push_back( limit & 1 );
        limit >>= 1;
    }
    reverse(digits.begin(), digits.end() );
    //for (int i = 0; i < digits.size(); ++i) printf("%d", digits[i]); puts("");
    
    memset(memo, -1, sizeof memo);
    long long ans = 0;
    for (int i = 1; i <= 64; ++i) {
        if (need[i] == target - 1) {
            //printf("si tiene i=%d unos cumple\n", i);
            long long extra = f( digits, 0, i, false );
            if (target == 1) extra--;
            assert( extra >= 0 );
            ans += extra;
        }
    }
    return ans;
}


void check(int lo, int hi, int x) {
    long long ans = count(hi, x) - count(lo - 1, x);
    
    int slow = 0;
    for (int i = lo; i <= hi; ++i) {
        int need = 0;
        for (int p = i; p > 1; p = __builtin_popcount(p)){
            need++;
        }
        if (need == x) slow++;
    }
    
    if (ans != slow) {
        printf("Lo = %d, hi = %d, x = %d. Fast = %I64d, slow = %d\n", lo, hi, x, ans, slow);
    }
    
}


int main(){
    choose[0][0] = 1LL;
    for (int i = 0; i <= 64; ++i) {
        for (int j = 0; j <= 64; ++j) {
            if (i == 0 and j == 0) continue;
            if (i > 0) choose[i][j] += choose[i-1][j];
            if (i > 0 and j > 0) choose[i][j] += choose[i-1][j-1];
            assert(choose[i][j] >= 0LL );
        }
    }
    
    
    for (int i = 1; i <= 64; ++i) {
        need[i] = 0;
        for (int p = i; p > 1; p = __builtin_popcount(p)){
            need[i]++;
        }
    }
    //For(i, 1, 65) printf("i=%d, need = %d\n", i, need[i]);
    
//    For(i, 0, 100000){
//        int lo = rand() % 1000 + 1;
//        int hi = rand() % 1000 + 1;
//        if (hi < lo) swap(lo, hi);
//        int x = rand() % 11;
//        check(lo, hi, x);
//        printf(".");
//    }
//    

    long long lo, hi;
    int x;
    while (cin >> lo >> hi >> x){
        if (lo == 0 and hi == 0 and x == 0) break;
        //D( count(hi, x) );
        //D( count(lo - 1, x) );
        long long ans = count(hi, x) - count(lo - 1, x);
        cout << ans << endl;
    }
    return 0;
}
