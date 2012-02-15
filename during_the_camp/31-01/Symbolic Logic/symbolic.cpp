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

map< char, bool > value;
string s; int pos;

bool validVar(char c) {
    return ('a' <= c and c <= 'z');
}

bool validOp(char c) {
    const string v = "CNKADEJ";
    return v.find(c) != -1;
}

bool operation(char c, bool a, bool b) {
    if (c == 'C') return (not a) or b;
    if (c == 'K') return a and b;
    if (c == 'A') return a or b;
    if (c == 'D') return not (a and b);
    if (c == 'E') return a == b;
    if (c == 'J') return a ^ b;
    assert( false );
}

bool expr() {
    if (!validVar(s[pos]) and !validOp(s[pos])) {
        throw string("invalid character");
    }
    
    if (validVar(s[pos])) {
        return value[s[pos++]];
    } else { assert(validOp(s[pos]));
        char op = s[pos++];
        if (op == 'N') {
            if (s[pos] == '$') throw string("insufficient operands");
            return !expr();
        } else {
            if (s[pos] == '$') throw string("insufficient operands");
            bool a = expr();
            if (s[pos] == '$') throw string("insufficient operands");
            bool b = expr();
            return operation(op, a, b);
        }
    
    }   
}

void categorize() {
    int n = value.size();
    assert(n <= 10);
    bool tautology = true;
    bool contradiction = true;
    for (int mask = 0; mask < (1 << n); ++mask) {
        
        int k = 0;
        for (map<char, bool>::iterator i = value.begin(); i != value.end(); ++i) {
            i->second = ((mask >> k) & 1);
            k++;
        }
        assert( k == n );
        
//        printf("Assignment %X:\n", mask);
//        for (map<char, bool>::iterator i = value.begin(); i != value.end(); ++i) {
//           printf("%c -> %d\n", i->first, i->second);
//        }
        
        pos = 0;
        bool t = expr();
        tautology &= t;
        contradiction &= !t;
    }
    printf("valid: ");
    if (tautology) {
        assert(!contradiction);
        printf("tautology");
    } else if (contradiction) {
        assert(!tautology);
        printf("contradiction");
    } else {
        printf("contingent");
    }
    puts("");
}

int main(){
    while (getline(cin, s)) {
        if (s == "") break;
        assert(s.find("$") == -1);
        printf("%s is ", s.c_str());
        s += "$";
        pos = 0;
        value.clear();
        try {
            expr();
            if (pos != s.size() - 1) {
                throw string("extraneous text");
            }
            categorize();
        } catch(string reason) {
            printf("invalid: %s\n", reason.c_str());
        }
    }
    return 0;
}
