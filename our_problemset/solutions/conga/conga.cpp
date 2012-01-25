// Solution to problem Conga Line
//
// Problem setter: Ana Echavarría
// Intended solution: Greedy algorithm
// Complexity: O(n) per test case
//

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

#define D(x) cout << #x " is " << (x) << endl

const int MAXN = 1000005;

int a[MAXN];

int main(){
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        assert(1 <= n and n <= 1000000);
        for (int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            assert(1 <= a[i] and a[i] <= 1000000000);
        }
        
        // assert the array is sorted
        for (int i = 0; i + 1 < n; ++i) {
            assert(a[i] < a[i + 1]);
        }
        
        // now find the answer
        long long ans = 0;
        for (int i = 1; i < n; ++i) {
            ans += 1LL * min(i, n - i) * (0LL + a[i] - a[i - 1] - 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}