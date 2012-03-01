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

string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
int numberOfDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
string days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

bool isLeap(int y) {
    return y % 4 == 0 and y % 100 != 0 or y % 400 == 0;
}

int main(){
    #ifndef LOCAL
    #define problem_name "dayofw"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif

    int day; string month, s;
    while (cin >> day >> month >> s) {
        int year = 0;
        for (int i = 0; i < s.size(); ++i) year = (year * 10 + s[i] - '0') % 2800;
        
        int ans = 0;
        for (int y = 0; y < year; ++y) ans += 365 + isLeap(y);
        for (int i = 0; i < 12; ++i) {
            if (months[i] == month) break;
            ans += numberOfDays[i];
            if (i == 1 and isLeap(year)) ans++; // 29th of February
        }
        ans += day;
        cout << days[(ans + 4) % 7] << endl;
    }
    return 0;
}