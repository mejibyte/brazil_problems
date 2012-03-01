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
    int y, payload, size;
    int rightZero; // the rightmost zero in this subtree
    
    Node * l, * r;
    Node(int p) {
        y = rand();
        payload = p;
        l = r = null;
        size = 1;
        rightZero = payload == 0 ? 0 : -1;
    }
};

int leftCount(Node * p) {
    assert(p);
    if (p->l) return p->l->size;
    return 0;
}

Node * refresh(Node *u) {
    if (u) {
        u->size = 1;
        u->rightZero = -1;
        if (u->l) {
            u->size += u->l->size;
            if (u->l->rightZero != -1) u->rightZero = max(u->rightZero, u->l->rightZero);
        }
        if (u->r) {
            u->size += u->r->size;
            if (u->r->rightZero != -1) u->rightZero = max(u->rightZero, u->r->rightZero + leftCount(u) + 1);
        }
        if (u->payload == 0) u->rightZero = max(u->rightZero, leftCount(u));
    }
    return u;
}

void split(Node *t, int x, Node *&l, Node *&r) {
    if (t == null) l = r = null;
    else if (x < leftCount(t))
        split(t->l, x, l, t->l), r = refresh(t);
    else
        split(t->r, x - 1 - leftCount(t), t->r, r), l = refresh(t);
}

Node * merge(Node *l, Node *r) {
    if (l == null) return refresh(r);
    if (r == null) return refresh(l);
    if (l->y > r->y)
        return l->r = merge(l->r, r), refresh(l);
    else
        return r->l = merge(l, r->l), refresh(r);
}

Node * eraseZero(Node *t, int at) {
    // D(at);
    // D(t->size);
    assert(t); 
    //printf("eraseZero(%d, at = %d). RightZero = %d\n", t, at, t->rightZero);
    assert(at <= t->rightZero);
    assert(at < t->size);
    if (t->l and at <= t->l->rightZero) {
        //puts("  going left");
        t->l = eraseZero(t->l, at);
        return refresh(t);
    } else if (leftCount(t) >= at and t->payload == 0) {
        //printf("  it's here because at = %d and leftCount = %d\n", at, leftCount(t));
        Node * q = merge(t->l, t->r);
        delete t;
        return refresh(q);
    } else {
        //puts("  going right");
        t->r = eraseZero(t->r, max(at - leftCount(t) - 1, 0));
        return refresh(t);
    }
}


void print(Node * t) {
    if (t == null) return;
    print(t->l);
    printf("%d ", t->payload);
    print(t->r);
}


void debug(Node * t, int depth = 0, int delta = 0) {
    if (!t) return;
    for (int i = 0; i < depth; ++i) printf("  ");
    printf("[%d] = %d, size = %d, rightZero = %d\n", leftCount(t) + delta, t->payload, t->size, t->rightZero);
    debug(t->l, depth + 1, delta);    
    debug(t->r, depth + 1, delta + 1 + leftCount(t));
}

const int MAXN = 131072;
int ans[2 * MAXN];
int W;

void traverse(Node * u) {
    if (u == null) return;
    traverse(u->l);
    ans[W++] = u->payload;
    traverse(u->r);
}

int main(){
    #ifndef LOCAL
    #define problem_name "key"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    

    int n, m;
    scanf("%d %d", &n, &m);
    Node * root = null;
    for (int i = 0; i < n + m; ++i) {
        root = merge(root, new Node(0));
    }
    for (int i = 1; i <= n; ++i) {
        int at; scanf("%d", &at);
        at--;
        
        // puts("Before erasing zero: "); debug(root); puts("");
        // D(root->rightZero);
        
        // erase first zero at "at" or to the right of "at"
        root = eraseZero(root, at);
        
        // puts("After erasing zero: "); debug(root); puts("");
        // D(root->rightZero);
        
        // insert this element at "at"
        Node * left, * right;
        split(root, at - 1, left, right);

        //printf("After splitting:\n"); printf("left = "); print(left); printf("\nright = "); print(right); puts("");
        
        
        root = merge(left, merge(new Node(i), right));
        
        //printf("After inserting i = %d at position %d: ", i, at); print(root); puts("\n");
    }
    
    W = 0;
    traverse(root);
    while (W >= 1 and ans[W - 1] == 0) W--;
    printf("%d\n", W);
    for (int i = 0; i < W; ++i){
        printf("%d ", ans[i]);
    }
    puts("");
    
    return 0;
}


