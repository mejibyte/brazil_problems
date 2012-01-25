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

const int MAXN = 1 << 20;
vector< int > g[MAXN];

struct state {
    int wr, wc, br, bc;
    bool turn;

    state(){}
    state(int r1, int c1, int r2, int c2, int t) : wr(r1), wc(c1), br(r2), bc(c2), turn(t) {}

    bool operator < (const state &s) const {
        if (turn != s.turn) return turn < s.turn;
        if (wr != s.wr) return wr < s.wr;
        if (wc != s.wc) return wc < s.wc;
        if (br != s.br) return br < s.br;
        return bc < s.bc;
    }

    bool final() const {
        return wr == br and wc == bc;
    }
};

int dr[] = { -1, +1, +0, +0 };
int dc[] = { +0, +0, -1, +1 };


vector< int > winning_positions;
int outgoing[MAXN];
int dist[MAXN];
int nextStateId;
int n;

bool inline outside(int r, int c) {
    return (r < 0 or r >= n or c < 0 or c >= n);
}

int getId(const state &s) {
    int w = s.wr * n + s.wc;
    int b = s.br * n + s.bc;
    int ans = (w << 10) + (b << 1) + (s.turn & 1);
    assert(ans < MAXN);
    return ans;
}

void inline enqueue(int curid, const state &next, int n, queue< state > &q) {
    if (outside(next.br, next.bc)) return;
    if (outside(next.wr, next.wc)) return;

    int nextid = getId(next);
    
    // there's an edge from curid to nextid
    outgoing[curid]++;
    g[nextid].push_back(curid); //reversed
    if (dist[nextid] == -1) {
        dist[nextid] = dist[curid] + 1;
        q.push( next );
    }
}

void buildGraph(const state &start, int n) {
    memset(dist, -1, sizeof dist);

    dist[ getId(start) ] = 0;

    queue< state > q;
    q.push( start );
    while (q.size() > 0) {
        const state cur = q.front(); q.pop();

        int curid = getId(cur);

        // printf("popped (wr = %d, wc = %d, br = %d, bc = %d, curid = %d, dist = %d, final = %d)\n", cur.wr, cur.wc, cur.br, cur.bc, curid, dist[curid], cur.final());

        // assert( !outside(cur.wr, cur.wc, n) );
        // assert( !outside(cur.br, cur.bc, n) );
        // assert( dist[ curid ] != -1 );

        if ( cur.final() ) {
            winning_positions.push_back( curid );
            continue;
        }
        
        if (cur.turn == 1) { // black, one or two cells
            for (int k = 0; k < 4; ++k) {
                state next = cur;
                next.turn = !next.turn;
                next.br += dr[k];
                next.bc += dc[k];
                enqueue(curid, next, n, q);
                next.br += dr[k];
                next.bc += dc[k];
                enqueue(curid, next, n, q);
            }
        } else {
            for (int k = 0; k < 4; ++k) {
                state next = cur;
                next.turn = !next.turn;
                next.wr += dr[k];
                next.wc += dc[k];
                enqueue(curid, next, n, q);
            }
        }
    }
}

void minimax(const state &start) {
    queue< int > q;
    memset(dist, -1, sizeof dist);
    for (int k = 0; k < winning_positions.size(); ++k) {
        q.push( winning_positions[k] );
        dist[winning_positions[k]] = 0;
    }
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        assert(dist[u] != -1);
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            if ( (dist[u] & 1) == 0 || --outgoing[v] == 0) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    int w = getId(start);
    if (dist[w] == -1) {
        puts("DRAW");
    } else {
        assert(dist[w] > 0);
        if (dist[w] & 1) {
            printf("WHITE %d\n", dist[w]);
        } else {
            printf("BLACK %d\n", dist[w]);
        }
    }
}

int main(){
    #ifndef LOCAL
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    #endif

    int r1, c1, r2, c2;
    scanf("%d %d %d %d %d", &n, &r1, &c1, &r2, &c2);
    r1--, c1--, r2--, c2--;
    assert(r1 != r2 or c1 != c2);
    state start = state(r1, c1, r2, c2, 0);
    buildGraph(start, n);
    minimax(start);
    return 0;
}