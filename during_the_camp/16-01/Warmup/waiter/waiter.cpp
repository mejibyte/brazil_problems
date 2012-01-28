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
    string problemName = "waiter";  
    #ifndef LOCAL
        freopen((problemName + ".in").c_str(), "r", stdin);
        freopen((problemName + ".out").c_str(), "w", stdout);
    #endif
    
    int total, percent, money;
    scanf("%d %d %d", &total, &percent, &money);
    for (int tip = money; tip >= 0; --tip) {
        int v = total + (total * percent) / 100 + (total * tip) / 100;
        if (v <= money) {
            printf("%d\n", tip);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
