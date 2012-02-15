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

const int MAXN = 10005;

char A[MAXN], B[MAXN];
char rule[15];

int main(){
    int L;
    while (scanf("%d ", &L) == 1) {
        gets(A);
        gets(rule);
        for (int i = 0; i < L; ++i) A[i] -= '0';
        for (int i = 0; i < 8; ++i) rule[i] -= '0';

        int rounds; scanf("%d ", &rounds);
        
        char * cur = A, * next = B;
        
        for (int r = 0; r < rounds; ++r) {
            for (int i = 0; i < L; ++i) {
                int k = i == 0 ? L - 1 : i - 1;
                int a = cur[k];
                int b = cur[i];
                k = (i == L - 1) ? 0 : i + 1;
                int c = cur[k];
                
                int index = (a << 2) + (b << 1) + c;
                next[i] = rule[index];
            }
            swap(cur, next);
        }
        for (int i = 0; i < L; ++i) cur[i] += '0';
        puts(cur);
    }
    return 0;
}
