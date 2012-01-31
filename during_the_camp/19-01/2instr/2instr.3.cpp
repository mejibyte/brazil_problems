// Accepted

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
int dist[MAXN];
vector< pair<int, int > > R[MAXN];

int swap(int u) {
    return (u >> 8) | ((u & 0xFF) << 8);
}

int load(int u) {
    return memory[u] | (memory[(u + 1) & 0xFFFF] << 8);
}

int main(){
    #ifndef LOCAL
    freopen("2instr.in", "r", stdin);
    freopen("2instr.out", "w", stdout);
    #endif
    int start, end;
    scanf("%X %X", &start, &end);
    for (int i = 0; i < MAXN; ++i) {
        scanf("%X", &memory[i]);
    }
    
    // Build reverse graph
    for (int u = 0; u < MAXN; ++u) {
        R[swap(u)].push_back(make_pair(2, u));
        R[load(u)].push_back(make_pair(1, u));
        
        dist[u] = (1 << 30);
    }
    
    // Run Dijkstra's
    set< pair<int, int> > q;
    dist[end] = 0;
    q.insert( make_pair(0, end) );
    while (q.size() > 0) {
        int u = q.begin()->second, w = q.begin()->first;
        q.erase(q.begin());
        if (w > dist[u]) continue;
        foreach(e, R[u]) {
            if (w + e->first < dist[e->second]) {
                dist[e->second] = w + e->first;
                q.insert( make_pair(dist[e->second], e->second) );
            }
        }
    }

    if (dist[start] == (1 << 30)) {
        puts("IMPOSSIBLE");
    } else {
        vector< int > ans;
        // Reconstruct the lexicographically smallest path
        for (int u = start; u != end; ) {
            // Since this edge is lexicographically smaller than the other, take it
            // as long as you are still on the shortest path.
            if (dist[swap(u)] == dist[u] - 2) {
                ans.push_back(0x0F);
                ans.push_back(0xCC);
                u = swap(u);
            } else {
                ans.push_back(0x5C);
                u = load(u);
            }
        }
        
        // Print the answer
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