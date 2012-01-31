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

const int MAXN = 65536;
int memory[MAXN];
int from[MAXN];
int instr[MAXN];

int main(){
    #ifndef LOCAL
    freopen("2instr.in", "r", stdin);
    freopen("2instr.out", "w", stdout);
    #endif
    int start, end;
    scanf("%X %X", &start, &end);
    for (int i = 0; i < MAXN; ++i) {
        scanf("%X", &memory[i]);
        from[i] = instr[i] = -1;
    }
    

    queue< int > q;
    from[ start ] = -2;
    q.push( start );
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        
        //printf("popped %.4X\n", u);
        // swap
        int v = (u >> 8) + ((u & 0xFF) << 8);
        //printf("  Swapping: %.4X\n", v);
        if (from[v] == -1) {
            from[v] = u;
            instr[v] = 2;
            q.push( v );
        }
        
        // load
        v = memory[u] + (memory[(u + 1) % MAXN] << 8);
        //printf("  Memory: %.4X\n", v);
        if (from[v] == -1) {
            from[v] = u;
            instr[v] = 1;
            q.push( v );
        }
    }
    if (from[end] == -1) {
        puts("IMPOSSIBLE");
    } else {
        vector< int > ans;
        for (int u = end; u != start; u = from[u]) {
            // printf("reached %.4X from %.4X using instruction %d\n", u, from[u], instr[u]);
            if (instr[u] == 2) {
                ans.push_back( 0xCC );
                ans.push_back( 0x0F );
            } else {
                ans.push_back( 0x5C );
            }
        }
        reverse(ans.begin(), ans.end());
        printf("%d\n", ans.size());
        for (int i = 0; i < ans.size(); ++i){
            printf("%.2X", ans[i]);
            if (i % 16 == 15) {
                printf("\n");
            } else if (i % 8 == 7) {
                printf("  ");
            } else {
                printf(" ");
            }
        }
        if (ans.size() % 16 != 0) printf("\n");
    }
    
    return 0;
}