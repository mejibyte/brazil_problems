// This will time out, but it's used to verify the answers.
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

void solve(int n) {
    long long best = (1LL << 60);
    if (n > 5000 or a[n - 1] > 5000) {
        puts("Too big for me. Skipping.");
        return;
    }
    
    int small = a[0];
    int big = a[n - 1];
    for (int start = small; start <= big; ++start) {
        long long option = 0;
        for (int i = 0; i < n; ++i) {
            option += abs(a[i] - start - i);
        }
        best = min(best, option);
    }
    printf("%lld\n", best);
}

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
        solve(n);
    }
    return 0;
}