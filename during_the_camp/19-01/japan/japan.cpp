// Time Limit Exceeded
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

#define hasBit(mask, bit) (((mask) >> (bit)) & 1LL)
#define setBit(mask, bit) ((mask) | (1LL << (bit)))

long long need;

const int MAXS = 43;
int ops[MAXS][3], stackTop;

bool search(int d, long long have) {
    int estimate = __builtin_popcountll( need & ~have );
    if (estimate > d) return false; // no solution
    if (d == 0) {
        if ((need & have) == need) {
            printf("%d\n", stackTop);
            for (int i = 0; i < stackTop; ++i) {
                printf("%d%s%d\n", ops[i][1], ops[i][0] == 1 ? "<<" : ops[i][0] == 2 ? "+" : "-", ops[i][2]);
            }
            return true;
        }
        return false;
    }
    
    for (int p = 0; p < 2; ++p) {
        // when p == 0, only insert target numbers
        // when p == 1, only insert not target numbers
        for (int i = 1; i <= 42; ++i) {
            if (!hasBit(have, i)) continue;
            for (int j = 1; j <= 42; ++j) {
                // shift i << k
                if ((i << j) <= 42 and (p == 0 and hasBit(need, i << j) || p == 1 and !hasBit(need, i << j) ) ) {
                    ops[stackTop][0] = 1;
                    ops[stackTop][1] = i;
                    ops[stackTop][2] = j;
                    stackTop++;
                    if (search(d - 1, setBit(have, i << j))) return true;
                    stackTop--;
                }
            
                if (!hasBit(have, j)) continue;
                // add i + j
                if (i + j <= 42 and (p == 0 and hasBit(need, i + j) or p == 1 and !hasBit(need, i + j ) ) ) {
                    ops[stackTop][0] = 2;
                    ops[stackTop][1] = i;
                    ops[stackTop][2] = j;
                    stackTop++;
                    if (search(d - 1, setBit(have, i + j))) return true;
                    stackTop--;
                }
            
                if (i - j >= 1 and (p == 0 and hasBit(need, i - j) or p == 1 and !hasBit(need, i - j ) ) ) {
                    ops[stackTop][0] = 3;
                    ops[stackTop][1] = i;
                    ops[stackTop][2] = j;
                    stackTop++;                
                    if (search(d - 1, setBit(have, i - j))) return true;
                    stackTop--;
                }
            }
        }
    }
    return false;
}


int main(){
    #ifndef LOCAL
    freopen("japan.in", "r", stdin);
    freopen("japan.out", "w", stdout);
    #endif

    int n; scanf("%d", &n);
    need = 0;
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        need |= (1LL << x);
    }
        
    for (int d = 1; d <= 42; ++d) {
        stackTop = 0;
        if (search(d, setBit(0LL, 1))) {
            break;
        }
    }
    return 0;
}