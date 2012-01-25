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

const int MAXN = 20 * 20 * 20 * 20 + 10;
vector< int > g[MAXN];

struct state {
    int wr, wc, br, bc;
    state(){}
    state(int r1, int c1, int r2, int c2) : wr(r1), wc(c1), br(r2), bc(c2) {}

    bool operator < (const state &s) const {
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

bool inline outside(int r, int c, int n) {
    return (r < 0 or r >= n or c < 0 or c >= n);
}

vector< int > winning_positions;
int outgoing[MAXN];

map< state, int > id;

void buildGraph(const state &start, int n) {
    int nextStateId = 1;
    id[start] = nextStateId++;
    vector< int > dist(MAXN, -1);

    dist.at( id[start] ) = 0;

    queue< state > q;
    q.push( start );
    while (q.size() > 0) {
        const state cur = q.front(); q.pop();

        int curid = id[cur];

        // printf("popped (wr = %d, wc = %d, br = %d, bc = %d, curid = %d, dist = %d, final = %d)\n", cur.wr, cur.wc, cur.br, cur.bc, curid, dist[curid], cur.final());

        assert( !outside(cur.wr, cur.wc, n) );
        assert( !outside(cur.br, cur.bc, n) );
        assert( dist.at( curid ) != -1 );

        if ( cur.final() ) {
            winning_positions.push_back( curid );
            continue;
        }

        for (int k = 0; k < 4; ++k) {
            state next = cur;
            // black's turn
            if ( dist.at(curid) & 1 ) { 
                next.br += dr[k];
                next.bc += dc[k];
            } else { // white's turn
                next.wr += dr[k];
                next.wc += dc[k];
            }

            // printf("going to (wr = %d, wc = %d, br = %d, bc = %d, final = %d)\n", next.wr, next.wc, next.br, next.bc, next.final());

            if (outside(next.br, next.bc, n)) continue;
            if (outside(next.wr, next.wc, n)) continue;


            int nextid = id[next];
            if (nextid == 0) {
                nextid = nextStateId;
                id[next] = nextStateId++;
            }

            // there's an edge from curid to nextid
            outgoing[curid]++;
            g[nextid].push_back(curid); //reversed
            if (dist.at(nextid) == -1) {
                dist.at(nextid) = dist.at(curid) + 1;
                q.push( next );
            }

        }
    }
}

void minimax(const state &start) {
    queue< int > q;
    vector< int > dist(id.size() + 1, -1);
    for (int k = 0; k < winning_positions.size(); ++k) {
        q.push( winning_positions[k] );
        dist.at(winning_positions[k]) = 0;
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

    int w = id[start];
    if (dist[w] == -1) {
        puts("DRAW");
    } else if (dist[w] & 1) {
        assert((start.wr + start.wc + start.br + start.bc) % 2 == 1);
        printf("WHITE %d\n", dist[w]);
    } else {
        assert((start.wr + start.wc + start.br + start.bc) % 2 == 0);
        printf("BLACK %d\n", dist[w]);
    }
}

int main(){
    #ifndef LOCAL
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    #endif

    int n, r1, c1, r2, c2;
    scanf("%d %d %d %d %d", &n, &r1, &c1, &r2, &c2);
    r1--, c1--, r2--, c2--;
    assert(r1 != r2 or c1 != c2);
    state start = state(r1, c1, r2, c2);
    buildGraph(start, n);
    minimax(start);
    return 0;
}