// Andrés Mejía
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
    #ifndef LOCAL
    freopen("username.in", "r", stdin);
    freopen("username.out", "w", stdout);
    #endif
    
    int n; cin >> n;
    set<string> taken;
    for (int i = 0; i < n; ++i){
        string s; cin >> s;
        taken.insert( s );
    }
    
    string want;
    cin >> want;
    
    if (taken.count(want)) {
        for (int i = 1; ; ++i){
            stringstream t; t << want << i;
            string suggestion = t.str();
            if (!taken.count(suggestion)) {
                cout << suggestion << endl;
                break;
            }
        }
        
    } else {
        cout << want << endl;
    }
    return 0;
}