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

struct Poly {
    vector< int > c;
    
    void normalize() {
        while (c.size() > 0 and c.back() == 0) c.pop_back();
    }
    
    bool isRoot(int x) {
        //printf(" trying root = %d\n", x);
        int right = 0;
        for (int i = 0; i < c.size(); ++i) {
            right -= c[i];
            if (right % x != 0) return false;
            right /= x;
            //printf("   After c[%d] = %d right is %d\n", i, c[i], right);
        }
        if (right != 0) return false;
        return true;
    }
};

Poly operator + (const Poly &a, const Poly &b) {
    Poly ans;
    ans.c.assign(max(a.c.size(), b.c.size()), 0);
    for (int i = 0; i < a.c.size(); ++i) ans.c[i] += a.c[i];
    for (int i = 0; i < b.c.size(); ++i) ans.c[i] += b.c[i];
    ans.normalize();
    return ans;
}

Poly operator - (const Poly &a, const Poly &b) {
    Poly ans;
    ans.c.assign(max(a.c.size(), b.c.size()), 0);
    for (int i = 0; i < a.c.size(); ++i) ans.c[i] += a.c[i];
    for (int i = 0; i < b.c.size(); ++i) ans.c[i] -= b.c[i];
    ans.normalize();
    return ans;
}

Poly operator * (const Poly &a, const Poly &b) {
    Poly ans;
    ans.c.assign(a.c.size() + b.c.size(), 0);  
    for (int i = 0; i < a.c.size(); ++i) {
        for (int j = 0; j < b.c.size(); ++j) {
            ans.c.at(i + j) += a.c[i] * b.c[j];
        }
    }
    ans.normalize();
    return ans;
}


void print(Poly p) {
    for (int i = 0; i < p.c.size(); ++i){
        if (i > 0) printf(" + ");
        printf("%dx^%d", p.c[i], i);
    }
    puts("");
}

string s; int pos;

Poly number() {
    assert(isdigit( s[pos] ));
    Poly ans;
    for (; isdigit(s[pos]); pos++) {
        int num = s[pos] - '0';
        ans.c.push_back(num);
    }
    reverse(ans.c.begin(), ans.c.end());
    assert( ans.c.size() == 1 or ans.c.back() != 0 );
    return ans;
}

Poly factor() {
    Poly ans = number();
    //printf("first factor: "); print(ans);
    assert(s[pos] == '*' or s[pos] == '$' or s[pos] == '=' or s[pos] == '+');
    while (s[pos] == '*') {
        pos++;
        Poly t = number();
        //printf("next factor: "); print(t);
        ans = ans * t;
        //printf("product: "); print(ans);
    }
    return ans;
}

Poly expression() {
    Poly ans = factor();
    assert(s[pos] == '+' or s[pos] == '$' or s[pos] == '=');
    while (s[pos] == '+') {
        pos++;
        Poly t = factor();
        ans = ans + t;
    }
    return ans;
}




int main(){
    while (getline(cin, s)) {
        if (s == "=") break;
        s += "$";
        
        int minBase = 2;
        for (int i = 0; i < s.size(); ++i) {
            if (isdigit(s[i])) minBase = max(minBase, s[i] - '0' + 1);
        }
                
        // parse
        pos = 0;
        Poly left = expression();
        assert( s[pos] == '=' );
        pos++; // eat =
        Poly right = expression();
        assert( pos == s.size() - 1 );
        Poly p = left - right;
        
        if (p.c.size() == 0){
            printf("%d+\n", minBase);
            continue;
        }
        
        //printf("left: "); print(left);
        
        while (p.c.size() > 0 and p.c[0] == 0) {
            p.c.erase( p.c.begin() );
        }

        set< int > ans;
        int independent = abs( p.c[0] );
        for (int i = 1; 1LL * i * i <= independent; ++i) {
            if (independent % i != 0) continue;
            if (i >= minBase and p.isRoot(i)) ans.insert( i );
            int j = independent / i;
            if (j >= minBase and p.isRoot(j)) ans.insert( j );
        }
       
        if (ans.size() == 0) {
            printf("*\n");
            continue;
        } else {
            printf("%d", *ans.begin());
            for(set<int>::iterator i = ++ans.begin(); i != ans.end(); ++i) {
                printf(" %d", *i);
            }
            puts("");
        }
    }
    return 0;
}
