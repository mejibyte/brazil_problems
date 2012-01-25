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

struct Pyramid {
    int cubes;
    int base;
    bool high;
    
    bool operator < (const Pyramid &t) const {
        if (cubes != t.cubes) return cubes > t.cubes;
        return high > t.high; 
    }
};

const int oo = (1 << 30);
const int MAXS = 1000001;

int moves[MAXS + 1];
vector <int> sol;
vector< Pyramid > p;

bool dfs (int len, int s, int from){
    if (s < 0) return false;
    if ( moves[s] == oo ) return false;    
    if ( len == 0) {
        if (s != 0) return false;
        //print solution
        int total = 0;
        for (int i = 0; i < sol.size(); i++){
            if (i > 0) printf(" ");
            printf("%d%c", p[sol[i]].base, p[sol[i]].high ? 'H' : 'L' );
            total += p[sol[i]].cubes;
        }
        puts("");
        assert( sol.size() == moves[ total ] );
        return true;
    }
    if ( len * p[from].cubes < s ){
        return false;
    }
    for (int i = from; i < p.size(); i++){
        sol.push_back(i);
        bool son = dfs( len - 1, s - p[i].cubes, i + 1); 
        sol.pop_back();
        if (son) return true;   
    }    
    return false;
} 


void solve(int n) {
    if (moves[n] == oo) {puts("impossible"); return;}
    dfs (moves[n], n, 0);
}

int main(){
    for (int i = 2, s = 1; s <= 1000000; ++i) {
        s += i * i;
        if (s > MAXS) continue;
        Pyramid n;
        
        n.cubes = s;
        n.base = i;
        n.high = true;
        p.push_back( n );
    }
    
    for (int i = 3, s = 1; s <= 1000000; i += 2) {
        s += i * i;
        if (s > MAXS) continue;        
        Pyramid n;
        n.cubes = s;
        n.base = i;
        n.high = false;
        p.push_back( n );
    }
    
    for (int i = 4, s = 4; s <= 1000000; i += 2) {
        s += i * i;
        if (s > MAXS) continue;        
        Pyramid n;
        n.cubes = s;
        n.base = i;
        n.high = false;
        p.push_back( n );
    }
    
    sort(p.begin(), p.end());
    
    for (int i = 0; i < p.size() - 1; ++i) {
        assert(p[i].cubes != p[i+1].cubes);
    }
    
    for (int i = 0; i < MAXS; ++i) {
        moves[i] = oo;
    }
    moves[0] = 0;
    for (int i = 0; i < p.size(); i++){
        int v = p[i].cubes;
        for (int s = MAXS - 1; s >= v; s--){
            if (moves[s] > 1 + moves[s - v]) moves[s] = 1 + moves[s - v];
        }    
    }
    
    
    int run = 1, n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        printf("Case %d: ", run++);
        solve(n);
    }

    return 0;
}
