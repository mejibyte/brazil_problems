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

map<string, vector< string > > g[256];

inline bool endsWith(const string &s, const string &t) {
    if (s.size() < t.size()) return false;
    for (int k = 0; k < t.size(); ++k) {
        if ( s[s.size() - 1 - k] != t[t.size() - 1 - k] ) {
            return false;
        }
    }
    return true;
}

int main(){
    int R;
    static char buf1[256], buf2[256];
    int run = 1;
    while(scanf(" %s %s %d ", &buf1, &buf2, &R) == 3) { 
        string S(buf1), T(buf2);    
               
        printf("Case %d: ", run++);
        if (S.size() != T.size()){
            puts("No solution");
            continue;
        }
    
        For(k, 0, 256) g[k].clear();
        For(i, 0, R) {
            string from, to; cin >> from >> to;
            g[from[from.size() - 1]][from].push_back( to );
        }
        map< string, int > been;
        queue< string > q;
        been[S] = 1;
        q.push( S );
        while (q.size() > 0) {
            const string u = q.front(); q.pop();
            if (u == T) break;
            char last = u[u.size() - 1];
            foreach(out, g[last]) {
                //D(u); D(out->first);
                if (!endsWith(u, out->first)) continue;
                foreach(next, out->second) {
                    string v = u.substr(0, u.size() - next->size());
                    v += *next;
                    if (been.count(v) > 0) continue;
                    been[v] = been[u] + 1;
                    q.push( v );
                }
            }
        }
        if (been[T] > 0) {
            printf("%d\n", been[T] - 1);
        } else {
            puts("No solution");
        }
    }
    return 0;
}
