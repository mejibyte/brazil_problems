// This solution times out, but it's used to verify the answers are correct.
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

void solve(const string &s) {
    int best = 0, at = -1;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            string possible = s.substr(i, j - i + 1);
            reverse(possible.begin(), possible.end());
            if (possible.size() < best) continue;
            if (s.find(possible) != 0) continue;
            if (possible.size() > best) {
                best = possible.size();
                at = i;
            }
        }
    }
    cout << s.substr(at, best) << endl;
}

int main(){
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        if (s.length() > 5000) {
            puts("Too big. Skipping.");
        } else {
            solve(s);
        }
    }
    return 0;
}