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

vector <pair <int, int> > rhs;

int my_pow (int k){
    int ans = 1;
    for (int i = 1; i <= k; i++) ans *= 10;
    return ans;    
}

int bigmod(long long b, long long p, long long m){ // b ^ p mod m
    long long mask = 1;
    long long pow2 = b % m;
    long long r = 1;
    while (mask){
        if (p & mask) r = (r * pow2) % m;
        pow2 = (pow2 * pow2) % m; 
        mask <<= 1;
    }
    return r;
}

bool Cmp(const pair <int, int> &a, const pair <int, int> &b){
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;    
}

void compute_rhs (const int &n, const int &b, const int &a, const int &m){
    rhs.clear();
    for (int z = 0; z < n; z++){
        long long pow2 = bigmod(1LL * a, 1LL * z, 1LL * m); 
        pow2 *= 1LL * b;
        pow2 = pow2 % m;
        rhs.push_back(make_pair(pow2, z));  
    }
    sort(rhs.begin(), rhs.end());
    //for (int i = 0; i < n; i++) printf("(%d, %d)\n", rhs[i].first, rhs[i].second);
}



int main(){
    string s;
    while (cin >> s){
        int k = s.size();
        int b = 0;
        for (int i = 0; i < k; i++){
            b *= 10;
            b += int(s[i] - '0');
        }
        if (b == 1){ puts("1"); continue;}
        
        int a = 7;
        int m = my_pow(k);
        int n = (int) ceil(sqrt(m));

        compute_rhs(n, b, a, m);
        
        int y;
        int z = -1;
        for (y = 1; y < n ; y++){
            int lhs = bigmod (a, 1LL * n * y, m);
            vector <pair <int, int> > :: iterator it;
            it = upper_bound( rhs.begin(), rhs.end(), make_pair(lhs, 1 << 30));
            it--;
            if (it != rhs.end() and it->first == lhs){
                // found
                z = (*it).second;
                break;    
            }                
        }
        if (z == -1){
            puts("-1");    
        }else{
            //D(z);
            //D(y);
            printf("%d\n", n * y  - z + 1);
        }
    }
    return 0;
}
