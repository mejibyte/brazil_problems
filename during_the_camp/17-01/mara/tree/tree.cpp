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

const int MAXN = 50005;
pair<int, int> keys[MAXN];

int L[MAXN], R[MAXN], P[MAXN];
int sorted[MAXN];

bool compare(int i, int j) {
    return keys[i] < keys[j];
}

int main(){
    #ifndef LOCAL
    #define problem_name "tree"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    ios::sync_with_stdio(false);
    int n; cin >> n;
    assert(n > 0);
    for (int i = 0; i < n; ++i) {
        cin >> keys[i].first >> keys[i].second;
        sorted[i] = i;
        L[i] = R[i] = P[i] = -1;
    }

    sort(sorted, sorted + n, compare);
    
    vector<int> seen;
    seen.push_back(sorted[0]);
    
    for (int i = 1; i < n; ++i) {
        int next = sorted[i];
        
        int k = seen.size() - 1;
        while (k >= 0 and keys[next].second < keys[seen[k]].second) {
            k--;
        }
        
        if (k >= 0) {
            R[seen[k]] = next;
            P[next] = seen[k];
        }
        
        if (k + 1 < seen.size()) {
            L[next] = seen[k + 1];
            P[seen[k + 1]] = next;
        }

        seen.resize(k + 1);
        seen.push_back(next);
    }
    
    puts("YES");
    for (int i = 0; i < n; ++i) {
        printf("%d %d %d\n", P[i] + 1, L[i] + 1, R[i] + 1);
    }

    return 0;
}


