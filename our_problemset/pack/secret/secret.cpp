// Solution to problem Secret Word
//
// Problem setter: Andrés Mejía-Posada <andr@esmejia.com>
// Intended solution: Run KMP on str + "$" + reverse(str)
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

int border[2 * MAXN]; // KMP array

void solve(string &s) {
    int n = s.size();
    s = s + "$" + s;
    int m = 2 * n + 1; // size of the new string
    assert(s.size() == m);
    
    reverse(s.begin() + n + 1, s.begin() + m);
    // at this point we have s + $ + reverse(s) in the string

    // Compute standard KMP array
    border[0] = 0;
    for (int i = 1; i < m; ++i) {
        border[i] = border[i - 1];
        while (border[i] > 0 and s[border[i]] != s[i]) {
            border[i] = border[border[i] - 1];
        }
        if (s[border[i]] == s[i]) {
            border[i]++;
        }
    }
    
    // Search for the best match after the separator character ('$')
    int best = 0, at = -1;
    for (int i = n + 1; i < m; ++i) {
        if (border[i] > best) {
            best = border[i];
            at = i;
        }
    }

    assert(best >= 1);
    assert(at != -1);
    // Print the actual word
    for (int k = 0; k < best; ++k) {
        assert(at - k >= 0);
        printf("%c", s[at - k]);
    }
    printf("\n");
}

int main(){
    int T; cin >> T;
    assert(T <= 150);
    string s; getline(cin, s); // dummy end of line after T
    while (T--) {
        getline(cin, s);
        assert(s.size() >= 1 and s.size() <= 1000000);
        solve(s);
    }
    return 0;
}