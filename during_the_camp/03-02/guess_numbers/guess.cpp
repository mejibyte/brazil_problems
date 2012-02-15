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


map< char, int > values;
int assign[10];
vector< char > letters;
int n;

string input;
int pos;

long long expr();

long long factor() {
    if (isalpha(input[pos])){
        pos++;
        return values[input[pos-1]];
    } else {
        assert(input[pos] == '(');
        pos++;
        long long ans = expr();
        assert(input[pos] == ')');
        pos++;
        return ans;
    }
}

long long term(){
    long long ans = factor();
    while (input[pos] == '*') {
        pos++;
        ans *= factor();
    }
    return ans;
}

long long expr() {
    long long ans = term();
    while (input[pos] == '+' or input[pos] == '-') {
        char op = input[pos++];
        long long next = term();
        if (op == '+') ans += next;
        else ans -= next;
    }
    return ans;
}

bool solve(int result) {
    assert(letters.size() == n);
    sort(assign, assign + n);
    do {
        for (int i = 0; i < n; ++i) {
            values[letters[i]] = assign[i];
        }
        pos = 0;
        if (expr() == result) {
            return true;
        }
    } while (next_permutation(assign, assign + n));
    return false;
}

int main(){
    while (scanf("%d ", &n) == 1) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) scanf("%d " , &assign[i]);
        int result; scanf("%d ", &result);
        getline(cin, input);
        input += "$";
        
        letters.clear();
        for  (int i = 0; i < input.size(); ++i) if (isalpha(input[i])) letters.push_back(input[i]);
        sort(letters.begin(), letters.end());
        letters.resize( unique(letters.begin(), letters.end()) - letters.begin() );
        
        if (solve(result)) puts("YES");
        else puts("NO");
       
    }
    return 0;
}
