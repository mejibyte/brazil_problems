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

string board [1005];
int rows, cols, mod;
int di[] = {-1, +0, +1, +0};
int dj[] = {+0, +1, +0, -1};
int dist[1005][1005][4];

int ways[1005][1005][4];

void add(int &a, int b) {
    a += b;
    a %= mod;
}

struct state{
    int i, j, dir;
    state(int i, int j, int dir) : i(i), j(j), dir(dir){}
    state(){}    
};

bool inside(int i, int j){
    return (i >= 0 and i < rows and j >= 0 and j < cols);
}

bool valid(int i, int j){
    assert(inside(i, j));
    return (board[i][j] == '.');    
}


void bfs(int r, int c, int dir){
    state start(r, c, dir);
    queue <state> q;
    dist[r][c][dir] = 0;
    ways[r][c][dir] = 1;
    q.push(start);
    while(q.size() > 0 ){
        state curr = q.front(); q.pop();
        // printf("popped i = %d, j = %d, dir = %d\n", curr.i, curr.j, curr.dir);
        //Move forward
        int next_dir = curr.dir;
        int next_i = curr.i + di[next_dir];
        int next_j = curr.j + dj[next_dir];
        if (inside(next_i, next_j) and valid(next_i, next_j)){
            if (dist[next_i][next_j][next_dir] == -1){
                dist[next_i][next_j][next_dir] = 1 + dist[curr.i][curr.j][curr.dir];
                ways[next_i][next_j][next_dir] = ways[curr.i][curr.j][curr.dir];
                q.push(state(next_i, next_j, next_dir));
            } else if (dist[next_i][next_j][next_dir] == dist[curr.i][curr.j][curr.dir] + 1) {
                add(ways[next_i][next_j][next_dir], ways[curr.i][curr.j][curr.dir]);
            }
        }
        //Move clockwise
        next_dir = (curr.dir + 1) % 4;
        next_i = curr.i;
        next_j = curr.j;
        if (dist[next_i][next_j][next_dir] == -1){
            dist[next_i][next_j][next_dir] = 1 + dist[curr.i][curr.j][curr.dir];
            ways[next_i][next_j][next_dir] = ways[curr.i][curr.j][curr.dir];            
            q.push(state(next_i, next_j, next_dir));
        }  else if (dist[next_i][next_j][next_dir] == dist[curr.i][curr.j][curr.dir] + 1) {
            add(ways[next_i][next_j][next_dir], ways[curr.i][curr.j][curr.dir]);
        }
        
         //Move counter-clockwise
        next_dir = (curr.dir + 3) % 4;
        next_i = curr.i;
        next_j = curr.j;
        if (dist[next_i][next_j][next_dir] == -1){
            dist[next_i][next_j][next_dir] = 1 + dist[curr.i][curr.j][curr.dir];
            ways[next_i][next_j][next_dir] = ways[curr.i][curr.j][curr.dir];            
            q.push(state(next_i, next_j, next_dir));
        } else if (dist[next_i][next_j][next_dir] == dist[curr.i][curr.j][curr.dir] + 1) {
            add(ways[next_i][next_j][next_dir], ways[curr.i][curr.j][curr.dir]);
        }
        
    }
}

int main(){
    int run = 1;
    while (scanf("%d %d %d", &rows, &cols, &mod) == 3){
        if (mod == 0) break;
        for (int i = 0; i < rows; i++){
            cin >> board[i];   
        }
        int r1, c1, r2, c2;
        char dir;
        scanf("%d %d %d %d %c", &r1, &c1, &r2, &c2, &dir);
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                for (int k = 0; k < 4; k++) {
                    dist[i][j][k] = -1;
                    ways[i][j][k] = 0;
                }
          
        if (dir == 'N') bfs(r1, c1, 0);
        if (dir == 'E') bfs(r1, c1, 1);
        if (dir == 'S') bfs(r1, c1, 2);
        if (dir == 'W') bfs(r1, c1, 3);
        
        printf("Case %d: %d ", run++, mod );
        // D(dist[r2][c2][0]); D(dist[r2][c2][1]); D(dist[r2][c2][2]); D(dist[r2][c2][3]);
        if (dist[r2][c2][0] == -1) {
            puts("-1");
            continue;
        }

        int minDist = (1 << 30);
        For(k, 0, 4) minDist = min(minDist, dist[r2][c2][k]);
        
        int ans = 0;
        For(k, 0, 4) if (dist[r2][c2][k] == minDist) add(ans, ways[r2][c2][k]);

        //D(ways[r2][c2][0]); D(ways[r2][c2][1]); D(ways[r2][c2][2]); D(ways[r2][c2][3]);
        printf("%d\n", ans);
    }
    return 0;
}
