// Andrés Mejía

// Accepted!

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

const int MAXS = 36*36*36*2;

int king_dr[8] = { -1, -1, -1, +1, +1, +1, +0, +0 };
int king_dc[8] = { -1, +0, +1, -1, +0, +1, -1, +1 };

int rook_dr[4] = { -1, +1, +0, +0 };
int rook_dc[4] = { +0, +0, -1, +1 };

enum { White, Black };

bool attacked[6][6];

#define inside(i, j) (0 <= (i) and (i) < 6 and 0 <= (j) and (j) < 6)

vector< int > R[MAXS]; // reversed graph

struct State {
    char p[6]; // white king, white rook, black king
    bool turn; // 0 - white, 1 - black
    bool operator == (const State &other) const {
        for (int i = 0; i < 6; ++i) if (p[i] != other.p[i]) return false;
        return turn == other.turn;
    }
    
    bool adjacentKings() const {
        int dr = abs(p[0] - p[4]);
        int dc = abs(p[1] - p[5]);
        return (dr <= 1 and dc <= 1);
    }
    
    bool occupied(int r, int c) const {
        assert(inside(r, c));
        for (int i = 0; i < 6; i += 2) {
            if (p[i] == r and p[i + 1] == c) return true;
        }
        return false;
    }
    
    void attackedCellsByWhite(bool attack[6][6]) const {
        memset(attack, false, 6 * 6);
        for (int k = 0; k < 8; ++k) {
            int ni = p[0] + king_dr[k];
            int nj = p[1] + king_dc[k];
            if (inside(ni, nj)) {
                attack[ni][nj] = true;
            }
        }
        for (int k = 0; k < 4; ++k) {
            for (int d = 1; d <= 6; ++d) {
                int ni = p[2] + d * rook_dr[k];
                int nj = p[3] + d * rook_dc[k];
                if (!inside(ni, nj)) break;
                attack[ni][nj] = true;
                if (occupied(ni, nj)) break;
            }
        }
    }
    
    bool blackIsOnCheck() const {
        attackedCellsByWhite(attacked);
        return attacked[ p[4] ][ p[5] ];
    }
    
    bool blackIsOnMate() const {
        return (turn == Black and blackIsOnCheck() and availableMovesForBlackKing() == 0);
    }
    
    int availableMovesForBlackKing() const {
        assert(turn == Black);
        attackedCellsByWhite(attacked);
        int cnt = 0; // count available moves for black king
        for (int k = 0; k < 8; ++k) {
            int ni = p[4] + king_dr[k];
            int nj = p[5] + king_dc[k];
            if (inside(ni, nj)) {
                State next = *this;
                next.p[4] = ni;
                next.p[5] = nj;
                next.turn = White;
                if (next.valid() and !next.blackIsOnCheck()) cnt++;
            }
        }
        return cnt;
    }
    
    bool isDraw() const {
        assert(valid());
        if (p[2] == p[4] and p[3] == p[5]) { // black king captured white rook, leaving just two kings wich is an immediate draw.
            assert(!blackIsOnCheck());
            return true;
        }
        if (blackIsOnCheck()) return false;
        return (turn == Black and availableMovesForBlackKing() == 0); // Not on check, but black can't move, so it's a draw.
    }
    
    bool valid() const {
        #define reason(x...) //puts(x)
        if (this->adjacentKings()) {
            reason("Adjacent kings");
            return false;
        }
        // check if black king and white rook are on the same cell. If they are, it must be white's turn.
        if (p[2] == p[4] and p[3] == p[5] and turn != White) {
            reason("Black king and white rook are on the same cell but it's not white's turn");
            return false;
        }
        if (p[0] == p[2] and p[1] == p[3]) {
            reason("Both white pieces are on the same cell");
            return false; // both white pieces are on the same spot  
        } 
        if (blackIsOnCheck() and turn != Black) {
            reason("Black is on check but it's white's turn");
            return false;
        }
        for (int i = 0; i < 6; i += 2) {
            if (!inside(p[i], p[i + 1])) {
                reason("One piece is outside");
                return false;
            }
        }
        return true;
        #undef reason
    }
    
    void print() const {
        char b[6][6];
        memset(b, '.', sizeof b);
        b[ p[0] ][ p[1] ] = 'W'; // White King
        b[ p[2] ][ p[3] ] = 'R'; // White Rook
        b[ p[4] ][ p[5] ] = 'b'; // Black King
        printf("%s's turn:\n", turn == White ? "White" : "Black");
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                printf("%c", b[i][j]);
            }
            puts("");
        }
    }
};

int pack(const State &s) {
    int ans = 0;
    for (int i = 0; i < 6; ++i) {
        ans = ans * 6 + s.p[i];
    }
    ans = (ans << 1) + s.turn;
    assert(ans < MAXS);
    return ans;
}

void unpack(int mask, State &s) {
    s.turn = (mask & 1);
    mask >>= 1;
    for (int i = 5; i >= 0; --i) {
        s.p[i] = (mask % 6);
        mask /= 6;
    }
    assert(mask == 0);
}

int out[MAXS];
int dist[MAXS];
int prev[MAXS];
queue< int > q;

void generate() {
    State cur;
    for (int turn = 0; turn < 2; ++turn) {
        for (int a = 0; a < 6; ++a) for (int b = 0; b < 6; ++b) {
            for (int c = 0; c < 6; ++c) for (int d = 0; d < 6; ++d) {
                for (int e = 0; e < 6; ++e) for (int f = 0; f < 6; ++f) {
                    cur.p[0] = a;
                    cur.p[1] = b;
                    cur.p[2] = c;
                    cur.p[3] = d;
                    cur.p[4] = e;
                    cur.p[5] = f;
                    cur.turn = turn;
                
                    if (!cur.valid()) continue;
                    if (cur.isDraw()) continue; // You can't continue the game when it's a draw
                    
                    int id = pack(cur);
                    if (cur.blackIsOnMate()) { // Terminal winning position
                        q.push(id);
                        dist[id] = 0;
                        continue;
                    }

                    if (turn == White) {
                        // move king
                        for (int k = 0; k < 8; ++k) {
                            int ni = cur.p[0] + king_dr[k];
                            int nj = cur.p[1] + king_dc[k];
                            if (inside(ni, nj)) {
                                State next = cur;
                                next.p[0] = ni;
                                next.p[1] = nj;
                                next.turn = Black;
                                if (next.valid()) {
                                    // Add edge
                                    R[pack(next)].push_back(id);
                                    out[id]++;
                                }
                            }
                        }
                        // move rook
                        for (int k = 0; k < 4; ++k) {
                            for (int d = 1; d <= 6; ++d) {
                                int ni = cur.p[2] + d * rook_dr[k];
                                int nj = cur.p[3] + d * rook_dc[k];
                                if (!inside(ni, nj)) break;
                                
                                State next = cur;
                                next.p[2] = ni;
                                next.p[3] = nj;
                                next.turn = Black;
                                if (next.valid()) {
                                    // Add edge
                                    R[pack(next)].push_back(id);
                                    out[id]++;
                                }
                                
                                if (cur.occupied(ni, nj)) break;
                            }
                        }
                    } else {
                        // move king
                        for (int k = 0; k < 8; ++k) {
                            int ni = cur.p[4] + king_dr[k];
                            int nj = cur.p[5] + king_dc[k];
                            if (inside(ni, nj)) {
                                State next = cur;
                                next.p[4] = ni;
                                next.p[5] = nj;
                                next.turn = White;
                                if (next.valid()) {
                                    // Add edge
                                    R[pack(next)].push_back(id);
                                    out[id]++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void minimax() {
    while (q.size() > 0) {
        int u = q.front(); q.pop();

        if (dist[u] & 1) { // odd, unusual BFS
            for (int k = 0; k < R[u].size(); ++k) {
                int v = R[u][k];
                if (--out[v] == 0) {                    
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        prev[v] = u;
                        q.push(v);
                    }
                }
            }
        } else { // even, normal BFS
            for (int k = 0; k < R[u].size(); ++k) {
                int v = R[u][k];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    prev[v] = u;
                    q.push(v);
                }
            }
        }
    }
}

int main(){
    #ifndef LOCAL
    #define problem_name "kingrook"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif

    State initial;
    for (int i = 0; i < 6; i += 2){
        string s; cin >> s;
        initial.p[i] = s[0] - 'a';
        initial.p[i + 1] = s[1] - '1';
        assert(0 <= initial.p[i] and initial.p[i] < 6);
        assert(0 <= initial.p[i + 1] and initial.p[i + 1] < 6);
    }
    char turn; cin >> turn;
    initial.turn = (turn == 'B' ? Black : White);
    
    // Check if there are two pieces on the same cell
    for (int i = 0; i < 6; i += 2) {
        for (int j = i + 2; j < 6; j += 2) {
            if (initial.p[i] == initial.p[j] and initial.p[i + 1] == initial.p[j + 1]) { // Two pieces on the same cell
                puts("-1");
                return 0;
                puts("Two pieces on the same cell");
                assert(false);
                return 0;
            }
        }
    }

    if (!initial.valid()) {
        puts("-1");
        return 0;
    }

    for (int i = 0; i < MAXS; ++i) dist[i] = -1, out[i] = 0;
    generate(); // generate graph
    minimax();
    
    int u = pack(initial);
    if (dist[u] == -1) {
        puts("-2");
    } else {
        printf("%d\n", dist[u]);
    }
    

    // To reconstruct the game, uncomment this.
    
    // while (u > 0) {
    //     State s; unpack(u, s); s.print();
    //     u = prev[u];
    // }
    
    return 0;
}

