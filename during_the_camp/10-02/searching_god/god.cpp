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

string msg, rule;

int main(){
    ios::sync_with_stdio(false);
    int L;
    while (cin >> L) {
        cin >> msg;
        cin >> rule;

        set< string > seen;
        int rounds; cin >> rounds;
        for (int r = 0; r < rounds; ++r) {
            string m;
            for (int i = 0; i < L; ++i) {
                int a = msg[(i + L - 1) % L] - '0';
                int b = msg[i] - '0';
                int c = msg[(i + 1) % L] - '0';
                
                int index = (a << 2) + (b << 1) + c;
                m += rule[index];
            }
            msg = m;
            if (seen.count(msg)) {
                printf("Period after %d steps\n", r);
                break;
            }
            seen.insert(msg);
        }
        //cout << msg << endl;
    }
    return 0;
}
