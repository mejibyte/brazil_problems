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

#define hasBit(mask, bit) ((mask) & (1LL << (bit)))
#define setBit(mask, bit) ((mask) | (1LL << (bit)))

long long need;

const int MAXS = 43;
int ops[MAXS][3], stackTop;
bool done;

#define pushStack(type, a, b) { \
    ops[stackTop][0] = type;    \
    ops[stackTop][1] = a;       \
    ops[stackTop][2] = b;       \
    stackTop++;                 \
}

#define popStack() { \
    stackTop--;      \
}


void search(int d, long long have) {
    int estimate = __builtin_popcountll( need & ~have );
    if (estimate == 0) {
        done = true;
        return;
    }
    if (estimate > d) return; // no solution

    for (int i = 1; i <= 42; ++i) {
        if (!hasBit(have, i)) continue;
        for (int k = i << 1, j = 1; k <= 42; ++j, k <<= 1) {
            long long next = setBit(have, k);
            if (next != have) {
                search(d - 1, next);
                if (done) {
                    pushStack(1, i, j);
                    return;
                }
            }
        }

        for (int j = 1; j < i; ++j) {
            if (!hasBit(have, j)) continue;
            // add i + j
            long long next = setBit(have, i + j);
            if (i + j <= 42 and next != have) {
                search(d - 1, next);
                if (done) {
                    pushStack(2, i, j);
                    return;
                }
            }
            // subtract
            next = setBit(have, i - j);
            if (i - j >= 1 and next != have) {
                search(d - 1, next);
                if (done) {
                    pushStack(3, i, j);
                    return;
                }
            }
        }
    }
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

    stackTop = 0;
    done = false;

    for (int d = 1; d <= 100; ++d) {
        search(d, 1LL << 1);
        if (done) {
            printf("%d\n", stackTop);
            for (int i = stackTop - 1; i >= 0; --i) {
                printf("%d%s%d\n", ops[i][1], ops[i][0] == 1 ? "<<" : ops[i][0] == 2 ? "+" : "-", ops[i][2]);
            }
            break;
        }
    }
    return 0;
}