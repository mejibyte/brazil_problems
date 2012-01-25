using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "result"

enum { Up, Right, Down, Left };

int dx[] = { -1, +0, +1, +0 };
int dy[] = { +0, +1, +0, -1 };

bool wall[2][55][4];

const int MAXS = 20005;
vector< int > g[MAXS];
int cnt[MAXS];

bool wallThrough(int x1, int y1,   int x2, int y2) {
    assert(x1 == x2 or y1 == y2);
    if (x1 == x2) {
        for (int y = min(y1, y2); y != max(y1, y2); ++y) {
            if (wall[x1][y][Right]) return true;
        }
        return false;
    }
    
    if (y1 == y2) {
        for (int x = min(x1, x2); x != max(x1, x2); ++x) {
            if (wall[x][y1][Down]) return true;
        }
    }
    return false;
}

struct State {
    int kx, ky, qx, qy;
    bool operator < (const State &s) const {
        if (kx != s.kx) return kx < s.kx;
        if (ky != s.ky) return ky < s.ky;
        if (qx != s.qx) return qx < s.qx;
        if (qy != s.qy) return qy < s.qy;
    }
    
    // check if one piece attacks the other
};

void buildGraph() {
    
}


int main(){
    #ifndef LOCAL    
    assert( freopen(INPUT_FILE ".in", "r", stdin) != NULL );
    assert( freopen(INPUT_FILE ".out", "w", stdout) != NULL );
    #endif
  
    int n, w; scanf("%d %d", &n, &w);
    for (int i = 0; i < w; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x1 == x2) { // vertical wall
            if (y2 < y1) swap(y2, y1); assert(y1 + 1 == y2);
            int x = x1;
            wall[x][y1][Right] = true;
            wall[x][y2][Left] = true;
        } else { assert(y1 == y2);
            if (x2 < x1) swap(x2, x1); assert(x1 + 1 == x2);
            int y = y1;
            wall[x1][y][Down] = true;
            wall[x2][y][Up] = true;
        }           
    }
    buildGraph();
    
    
    #ifdef LOCAL
    //system("pause");
    #endif
    
    return 0;
}
