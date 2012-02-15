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

#define hasBit(mask, bit) (!!( (mask) & (1 << (bit)) ))
#define setBit(mask, bit) ( (mask) | (1 << (bit)) )

int moveX [15];
int moveY [15];
int d [20][20][1 << 15];
int board [20][20];
int Y, X, K, T;

struct state{
    int x, y, mask;
    state(int x, int y, int mask) : x(x), y(y), mask(mask) {}
};

bool inside(int x, int y){
    if ( x >= 0 and x < X and y >= 0 and y < Y) return true;
    return false;    
}


int bfs(int mask0){
    queue <state> q;
    q.push(state(0, 0, mask0));
    d[0][0][mask0] = 0;
    while (q.size() > 0){
        state curr = q.front(); q.pop();
        //printf("Popped x = %d, y = %d, mask = %d\n", curr.x, curr.y, curr.mask );
        if ((curr.x == X - 1) and (curr.y == Y - 1)){ //Finished
            assert(d[curr.x][curr.y][curr.mask] != -1);
            return d[curr.x][curr.y][curr.mask];
        }
        for (int i = 1; i <= K; i++){
            if (hasBit (curr.mask, i)){ // Make move
                int next_x = curr.x + moveX[i];
                int next_y = curr.y + moveY[i];
                if (inside(next_x, next_y) and (d[next_x][next_y][curr.mask] == -1)){
                    q.push(state(next_x, next_y, curr.mask));
                    d[next_x][next_y][curr.mask] = 1 + d[curr.x][curr.y][curr.mask];   
                } 
            }    
        }
        if (board[curr.x][curr.y] != 0){ // learn move
            int mask = setBit(curr.mask, board[curr.x][curr.y]);
            if (d[curr.x][curr.y][mask] == -1){
                q.push(state(curr.x, curr.y, mask));
                d[curr.x][curr.y][mask] = 1 + d[curr.x][curr.y][curr.mask]; 
            }
        }                 
    }
    return -1;
}

int main(){
    int run = 1;
    while (scanf("%d %d %d %d", &Y, &X, &K, &T) == 4){
        if (Y == 0 and X == 0 and K == 0 and T == 0) break;
        
        for (int i = 0; i < X; i++){
            for (int j = 0; j < Y; j++){
                for (int k = 0; k <= (1 << (K + 1)); k++){
                    d[i][j][k] = -1;
                }
            }        
        }
        
        for (int i = 1; i <= K; i++){
            scanf("%d %d", &moveX[i], &moveY[i]);  
        }
        int mask = 0;
        for (int i = 0; i < T; i++){
            int k; scanf("%d", &k);
            mask = setBit(mask, k);
        }
        
        for (int y = Y - 1; y >= 0; y--){
            for (int x = 0; x < X; x++){
                scanf("%d", &board[x][y]);    
            }    
        }
        
        /*for (int y = Y - 1 ; y >= 0; y--){
            for (int x = 0; x < X; x++){
                printf("%d ", board[x][y]);    
            }
            puts("");
        }*/
        
        printf("Case #%d: %d\n", run++, bfs(mask));
    }
    return 0;
}
