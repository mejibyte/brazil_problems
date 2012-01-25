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

const int MAXN = 100005;

vector< int > G[MAXN];
vector< int > R[MAXN];
int win[MAXN]; // Optimal strategy, just to find out who wins
int dist[MAXN]; // Distance with the strange strategy in the problem statement
int cnt[MAXN];

bool inline isWinning(int u) {
    assert(win[u] != -1);
    return (win[u] & 1);
}

int main(){
    #ifndef LOCAL
    freopen("labyrinth.in", "r", stdin);
    freopen("labyrinth.out", "w", stdout);
    #endif
    
    int n, m; scanf("%d %d", &n, &m);
    for (int e = 0; e < m; ++e) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        G[u].push_back(v);
        R[v].push_back(u);
        cnt[u]++;
    }
    
    // Standard algorithm
    queue< int > q;
    for (int i = 0; i < n; ++i) {
        win[i] = -1;
        if (cnt[i] == 0) {
            win[i] = 0;
            q.push( i );
        }
    }
    
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        //printf("popped %d\n", u + 1);
        assert( win[u] != -1 );
        for (int k = 0; k < R[u].size(); ++k) {
            int v = R[u][k];
            if (!isWinning(u) || --cnt[v] == 0) {
                if (win[v] == -1) {
                    win[v] = win[u] + 1;
                    q.push( v );
                }
            }
        }
    }
    // At this point, it's a draw from node u if win[u] == -1, it's a win if win[u] % 2 == 1 and it's a loss otherwise.

    assert(q.size() == 0);
    for (int i = 0; i < n; ++i) {
        dist[i] = -1;
        cnt[i] = 0;
        for (int k = 0; k < G[i].size(); ++k) {
            int v = G[i][k];
            cnt[i] += win[v] != -1 and !isWinning(v); // outgoing edges that point to losing nodes
        }
        
        if (G[i].size() == 0) {
            dist[i] = 0;
            q.push( i );
        }
    }

    while (q.size() > 0) {
        int u = q.front(); q.pop();
        // printf("popped %d\n", u + 1);
        if (win[u] == -1) continue;
        assert( dist[u] != -1 );
        if (dist[u] & 1) { // Normal BFS - From a losing position, the player will just suicide to this winning position.
            for (int k = 0; k < R[u].size(); ++k) {
                int v = R[u][k];
                if (win[v] != -1 and isWinning(v)) continue; // From a winning position v, you will never move to another winning position u.
                                                             // That would be giving away the game to your opponent.
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push( v );
                }
            }
        } else { // Counter BFS - Only go to winning positions for which we already saw all outgoing edges (in the
                 // non-reversed graph G) to non-winning positions
            for (int k = 0; k < R[u].size(); ++k) {
                int v = R[u][k];
                assert( win[v] == -1 or isWinning(v) ); // every possible position that comes into a losing position u is winning.
                if (--cnt[v] == 0) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push( v );
                    }
                }
            }
        }
    }
       
    for (int i = 0; i < n; ++i) {
        if (win[i] == -1) {
            puts("DRAW");
            continue;
        } 
        
        int len = dist[i];
        if (isWinning(i)) {
            len != -1 ? printf("WIN %d\n", len) : printf("WIN INF\n");
        } else { assert(!isWinning(i));
            len != -1 ? printf("LOSE %d\n", len) : printf("LOSE INF\n");
        }
    }

    return 0;
}