// Accepted

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


#define null NULL

struct Node {
    int y, size, payload;
    long long sum;
    Node *l, *r;
    bool pending_reversal;
    Node(int k) : payload(k), y(rand()), size(1), l(null), r(null), sum(0), pending_reversal(false) { }
};

Node* relax(Node* p) {
    if (p) {
        p->size = 1;
        p->sum = p->payload;
        if (p->l) {
            p->size += p->l->size;
            p->sum += p->l->sum;
        }
        if (p->r) {
            p->size += p->r->size;
            p->sum += p->r->sum;
        }
    }
    return p;
}

Node* propagate(Node * t) {
    assert(t);
    if (t->pending_reversal) {
        swap(t->l, t->r);
        t->pending_reversal = false;
        if (t->l) t->l->pending_reversal ^= 1;
        if (t->r) t->r->pending_reversal ^= 1;
        relax(t);
    }
    return t;
}


int leftCount(Node * t) {
    assert(t);
    return t->l ? t->l->size : 0;
}

// moves elements at positions [0..x] to l, and those at positions [x+1, n-1] to r.
void split(Node* t, int x, Node* &l, Node* &r) {
    if (t == null) l = r = null; else {
    // apply lazy propagation here to t
        propagate(t);
        if ( x < leftCount(t) ) {
            split(t->l, x, l, t->l);
            r = relax(t);
        } else {
            split(t->r, x - 1 - leftCount(t), t->r, r);
            l = relax(t);
        }
    }
}

Node* merge(Node* l, Node *r) {
    if (l == null) return relax(r);
    if (r == null) return relax(l);

    if (l->y > r->y) {
    // apply lazy propagation here to l
        propagate(l);
        l->r = merge(l->r, r);
        return relax(l);
    } else {
    // apply lazy propagation here to r
        propagate(r);
        r->l = merge(l, r->l);
        return relax(r);
    }
}

void print(Node *p) {
    if (p == null) return;
    propagate(p);
    print(p->l);
    printf("payload = %d, y = %d, size = %d\n", p->payload, p->y, p->size);
    print(p->r);
}

void traverse(Node * p) {
    if (p == null) return;
    propagate(p);
    traverse(p->l);
    printf("%d ", p->payload);
    traverse(p->r);
}

int main(){
    #ifndef LOCAL
    #define problem_name "reverse"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif

    int n, m;
    scanf("%d %d", &n, &m);

    int x; scanf("%d", &x);
    Node * root = new Node(x);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &x);
        root = merge(root, new Node(x));
    }

    for (int i = 0; i < m; ++i) {
        int type, l, r; scanf("%d %d %d", &type, &l, &r);
        l--, r--;
        Node * a, * b, * c;
        split(root, l - 1, a, b);
        split(b, r - l, b, c);
        if (type == 0) { // sum
            cout << b->sum << '\n';
        } else { // reverse
            assert( !b->pending_reversal );
            b->pending_reversal = true;
        }
        
        //puts("a:"); traverse(a); puts("");
        //puts("b:"); traverse(b); puts("");
        //puts("c:"); traverse(c); puts("");
        
        root = merge(a, merge(b, c));
        
        
        //printf("after query %s [%d, %d]:\n", type == 0 ? "sum" : "rev", l, r);
        //traverse(root); puts("");
    }
    return 0;
}


