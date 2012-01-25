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
    Node(int k) : payload(k), y(rand()), size(1), l(null), r(null), sum(0) { }
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

int leftCount(Node * t) {
    assert(t);
    return t->l ? t->l->size : 0;
}

// moves elements at positions [0..x] to l, and those at positions [x+1, n-1] to r.
void split(Node* t, int x, Node* &l, Node* &r) {
    if (t == null) l = r = null; else {
        // apply lazy propagation here to t, if needed
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
        // apply lazy propagation here to l, if needed
        l->r = merge(l->r, r);
        return relax(l);
    } else {
        // apply lazy propagation here to r, if needed
        r->l = merge(l, r->l);
        return relax(r);
    }
}

// Free this tree's memory
void erase(Node * t) {
    if (t == null) return;
    erase(t->l); erase(t->r);
    delete t;
}

void print(Node *p) {
    if (p == null) return;
    print(p->l);
    printf("payload = %d, y = %d, size = %d\n", p->payload, p->y, p->size);
    print(p->r);
}

void traverse(Node * p) {
    if (p == null) return;
    traverse(p->l);
    printf("%d ", p->payload);
    traverse(p->r);
}

void split(Node * tree, int l, int r, Node * &a, Node * &b, Node * &c) {
    split(tree, l - 1, a, b);
    split(b, r - l, b, c);
}

int round(int a, int b) {
    if (a >= 0) return a / b;
    else return a / b - 1;
}

int main(){
    #ifndef LOCAL
    freopen("swapper.in", "r", stdin);
    freopen("swapper.out", "w", stdout);
    #endif
    int N, M;
    int run = 0;
    while (scanf("%d %d", &N, &M) == 2) {
        if (N == 0 and M == 0) break;
        if (run > 0) puts("");
        printf("Swapper %d:\n", ++run);
        
        Node * even = null;
        Node * odd = null;
        for (int i = 0; i < N; ++i) {
            int x; scanf("%d", &x);
            if (i & 1) {
                odd = merge(odd, new Node(x));
            } else {
                even = merge(even, new Node(x));
            }
        }
        if (N & 1) odd = merge(odd, new Node(0));
        
        assert(even->size == odd->size and even->size == (N + 1) / 2);
        
        for (int i = 0; i < M; ++i) {
            int type, l, r;
            scanf("%d %d %d", &type, &l, &r);
            l--, r--;

            // printf("Before query %s [%d, %d]:\n", type == 1 ? "swap" : "sum", l, r);
            // puts("even:"); traverse(even); puts("");
            // puts("odd:"); traverse(odd); puts("");
            
            Node * a, * b, * c;
            Node * d, * e, * f;
            split(even, (l + 1) / 2, r / 2, a, b, c);
            split(odd, l / 2, round(r - 1, 2), d, e, f);
            
            // printf("splitting query %s [%d, %d]:\n", type == 1 ? "swap" : "sum", l, r);
            // printf("splitting even in [%d %d] and odd in [%d %d]\n", (l + 1) / 2, r / 2, l / 2, (r - 1) / 2);
            // printf("a:"); traverse(a); puts("");
            // printf("b:"); traverse(b); puts("");
            // printf("c:"); traverse(c); puts("");
            // printf("d:"); traverse(d); puts("");
            // printf("e:"); traverse(e); puts("");
            // printf("f:"); traverse(f); puts("");
            
            if (type == 1) { // swap
                even = merge(a, merge(e, c));
                odd  = merge(d, merge(b, f));
            } else if (type == 2) { // sum
                long long ans = (b ? b->sum : 0) + (e ? e->sum : 0);
                cout << ans << '\n';
                even = merge(a, merge(b, c));
                odd = merge(d, merge(e, f));
            } else assert(false);
            
            // puts("===================");
            
        }
        erase(odd);
        erase(even);
    }
    return 0;
}