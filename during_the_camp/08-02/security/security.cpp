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

const int MAXN = 100005;
int n, t, q;
int id[MAXN];
int sor[MAXN];
set <int> teams;

void build_team(int a, int b){
    if (a == 0){
        teams.insert(sor[b]);
    }else{
        assert( a >= 1 );
        teams.insert(sor[a - 1] ^ sor[b]); //Xor from a to b
    }   
}

int main(){
    while (scanf("%d %d %d", &n, &t, &q) == 3){
        if (n == 0 and t == 0 and q == 0) break;
        assert( n > 0 and t > 0 and q > 0 );
        for (int i = 0; i < n; i++) scanf("%d", &id[i]);
        
        sor[0] = id[0];
        for (int i = 1; i < n; i++) {
            sor[i] = id[i] ^ sor[i - 1];
        }
        
        teams.clear();
        for (int i = 0; i < t; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            build_team(a, b);
        }
        assert(teams.size() <= t);
        
        for (int i = 0; i < n; ++i) teams.insert(id[i]);
        
        for (int i = 0; i < q; i++){
            int new_id; 
            scanf("%d", &new_id);
            if (teams.count(new_id) == 0){
                puts("Y");    
            }else{
                puts("N");    
            }              
        }
        puts("-");
    } 
    return 0;
}
