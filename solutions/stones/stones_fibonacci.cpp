// 
// Refer to Part 1, Chapter 1, exercise 7b from http://www.math.ucla.edu/~tom/Game_Theory/comb.pdf
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

int main(){
    vector<int> f;
    f.push_back(1);
    f.push_back(2);
    while (f.back() < 1000) {
        f.push_back( f[f.size() - 1] + f[f.size() - 2] );
    }
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        if (binary_search(f.begin(), f.end(), n)) {
            puts("Roberto");
        } else {
            puts("Alicia");
        }
    }
    return 0;
}
