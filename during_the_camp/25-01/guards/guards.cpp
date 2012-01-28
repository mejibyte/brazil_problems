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

int main(){
    int n1, n2, n3;
    while (scanf("%d %d %d", &n1, &n2, &n3) == 3) {
        int best = (1 << 30), a, b, c, d;
        a = b = c = d = -1;
        for (int x1 = 0; x1 <= 3000; x1 += 3) {
            for (int x3 = 0; x3 <= 4000; x3 += 4) {
                if (x1 / 3 + x3 / 2 < n2) continue;
                int x4 = (5 * (max(0, n3 - x1 / 3 - x3 / 4)) + 1) / 2;
                x4 += (5 - x4 % 5) % 5;
                assert(x4 % 5 == 0);
                int x2 = max(0, n1 - x1 / 3 - x3 / 2 - 3 * x4 / 5);

                assert(x1 >= 0 and x2 >= 0 and x3 >= 0 and x4 >= 0);
                assert(x1 / 3 + x2 + x3 / 2 + 3 * x4 / 5 >= n1);
                assert(x1 / 3 + x3 / 2 >= n2);
                assert(x1 / 3 + x3 / 4 + 2 * x4 / 5 >= n3);
                
                if (x1 + x2 + x3 + x4 < best) {
                    best = x1 + x2 + x3 + x4;
                    a = x1, b = x2, c = x3, d = x4;
                }
            }
        }
        printf("%d %d %d %d\n", a, b, c, d);
    }
    return 0;
}