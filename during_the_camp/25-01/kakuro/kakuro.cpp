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

bool white [10][10];
int clue [10][10][2];

int run[10][10][2];
int need[100];
int size[100];
int used[100];
int placed[10][10];

#define hasBit(mask, bit) ((mask) & (1 << (bit)))
#define setBit(mask, bit) ((mask) | (1 << (bit)))
#define unsetBit(mask, bit) ((mask) & ~(1 << (bit)))

int memo[50][1 << 10][10];


bool canFinish(int sum, int used, int size) {
    if (sum >= 50) return false;
    if (sum < 0) return false;
    bool found = false;
    if (sum == 0 and size == 0) return true;
    if (sum <= 0 or size < 0) return false;
    if (size == 0 and sum != 0) return false;
    if (memo[sum][used][size] != -1) return memo[sum][used][size];
    
    for (int i = 1; i <= 9; ++i) {
        if (!(hasBit(used, i)) ) {
            if (canFinish(sum - i, setBit(used, i), size - 1)) return memo[sum][used][size] = true;
        }
    }
    return memo[sum][used][size] = false;
}

int rows, cols;

bool search(int i, int j) {
    if (i == rows - 1 and j == cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (j > 0) printf(" ");
                if (white[i][j])
                    printf("%d", placed[i][j]);
                else
                    printf("_");    
            }
            printf("\n");
        }
        return true;
    }
    
    if (j == cols) return search(i + 1, 0);
    if (!white[i][j]) return search(i, j + 1);
    for (int k = 1; k <= 9; ++k) {
        int r0 = run[i][j][0];
        int r1 = run[i][j][1];
        assert( size[r0] > 0 );
        assert( size[r1] > 0 );
        if (hasBit( used[r0], k )) continue;
        if (hasBit( used[r1], k )) continue;
        if (!canFinish(need[r0] - k, setBit(used[r0], k), size[r0] - 1)) continue;
        if (!canFinish(need[r1] - k, setBit(used[r1], k), size[r1] - 1)) continue;
        
        placed[i][j] = k;
        used[r0] = setBit (used[r0], k );
        used[r1] = setBit (used[r1], k );
        need[r0] -= k;
        need[r1] -= k;
        size[r0]--;
        size[r1]--;
        if (search(i, j + 1) ) {
            return true;
        }
        used[r0] = unsetBit (used[r0], k );
        used[r1] = unsetBit (used[r1], k );
        need[r0] += k;
        need[r1] += k;
        size[r0]++;
        size[r1]++;            
    }
    return false;
}
   

int main(){
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 2; k++)
                clue[i][j][k] = -1;
    
     scanf("%d %d ", &rows, &cols);
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            char cell [10]; scanf("%s ", &cell);
            if (cell[0] == '.'){
                white[i][j] = true;
            }else if (cell[2] == '\\'){
                // Vertical clue
                if (cell[0] != 'X' and cell[1] != 'X'){
                    int value = (cell[0] - '0') * 10 + (cell[1] - '0');
                    clue[i][j][0] = value;
                }
                
                // Horizontal clue
                if (cell[3] != 'X' and cell[4] != 'X'){
                    int value = (cell[3] - '0') * 10 + (cell[4] - '0');
                    clue[i][j][1] = value;
                }           
            }else{
                white[i][j] = false;    
            }
        }    
    }

 //   for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            printf("%d ", white[i][j]);
//        }
//        puts("");
//    }
//    
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            printf("%2d|%2d ", clue[i][j][0], clue[i][j][1]);
//        }
//        puts("");
//    }
//  

    int nextRun = 0; 
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) { 
            if (!white[i][j]) continue;
            // izquierda
            if (white[i][j-1]) {
                int r = run[i][j-1][0];
                run[i][j][0] = r;
                size[r]++;
            } else {
                run[i][j][0] = nextRun;
                need[nextRun] = clue[i][j-1][1];
                size[nextRun] = 1;
                nextRun++;
            }
            // arriba
            if (white[i-1][j]) {
                int r = run[i-1][j][1];
                run[i][j][1] = r;
                size[r]++;
            } else {
                run[i][j][1] = nextRun;
                need[nextRun] = clue[i-1][j][0];
                size[nextRun] = 1;
                nextRun++;
            }            
        }
    }

    search(0, 0);
    return 0;
}
