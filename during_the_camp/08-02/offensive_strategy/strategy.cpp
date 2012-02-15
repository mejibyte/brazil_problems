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

const int MAXN = 110;
vector< pair<int, int> > g[MAXN][MAXN];

vector<pair< int, int > > pos;

bool visited[MAXN][MAXN];

int W, H, M;

void dfs(int i, int j) {
    if (visited[i][j]) return;
    visited[i][j] = true;
    foreach(out, g[i][j]) dfs(out->first, out->second);
}

int main(){
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &W, &H, &M);
        pos.clear();
        for (int i = 0; i <= W; ++i) for (int j = 0; j <= H; ++j) g[i][j].clear(), visited[i][j] = false;
        
        bool valid = true;
        for(int i = 0; i < M; ++i) {
            int x0, y0, x1, y1; scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
            if (x1 < x0) valid = false;
            if (valid) {
               pos.push_back( make_pair(x0, y0) );
               pos.push_back( make_pair(x1, y1) );               
               g[x1][y1].push_back(make_pair(x0, y0));
            }
        }
        
        if (valid) {
            dfs(W, H / 2);
            foreach(p, pos) if (!visited[p->first][p->second]) valid = false;
        }
    
        if (!valid) {
            puts("No");
        } else {
            puts("Yes");
        }        
    }
    return 0;
}
