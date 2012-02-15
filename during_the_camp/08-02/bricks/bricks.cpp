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

int size[1005][5];
int gcd[5];

int main(){
    int n;
    while (cin >> n){
        if (n == 0) break;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 3; j++){
                cin >> size[i][j];    
            }    
        }
        for (int i = 0; i < 3; i++){
            gcd[i] = size[0][i];
            for (int j = 1; j < n; j++){
                 gcd[i] = __gcd(gcd[i], size[j][i]);   
            }    
        }
        int lado = __gcd(gcd[0], __gcd(gcd[1], gcd[2]));
        
        long long ans = 0;
        for (int i = 0; i < n; i++){
            long long prod = 1;
            for (int j = 0; j < 3; j++){
                assert(size[i][j] % lado == 0);
                prod *= size[i][j] / lado;   
            }
            ans += prod;  
        }
        
        cout << ans << endl;
            
    }

    return 0;
}
