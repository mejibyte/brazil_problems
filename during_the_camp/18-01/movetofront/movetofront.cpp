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
  Node *l, *r;
  Node(int k) : payload(k), y(rand()), size(1), l(null), r(null) { }
};

Node* relax(Node* p) {
  if (p) {
    p->size = 1;
    if (p->l) {
      p->size += p->l->size;
    }
    if (p->r) {
      p->size += p->r->size;
    }
  }
  return p;
}

int leftCount(Node * t) {
  assert(t);
  return t->l ? t->l->size : 0;
}

void split(Node* t, int x, Node* &l, Node* &r) {
  if (t == null) l = r = null; else {
    // apply lazy propagation here to t
    
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
    l->r = merge(l->r, r);
    return relax(l);
  } else {
    // apply lazy propagation here to r
    r->l = merge(l, r->l);
    return relax(r);
  }
}

Node* insert(Node* t, Node* m, int x) {
  if (t == null || m->y > t->y) {
    split(t, x, m->l, m->r);
    return relax(m);
  }
  // apply lazy propagation here t
  if (x < leftCount(t)) t->l = insert(t->l, m, x);
  else t->r = insert(t->r, m, x - 1 - leftCount(t));
  return relax(t);
}

Node* erase(Node* t, int x) {
  if (t == null) return null;
  if (leftCount(t) == x) {
    Node *q = merge(t->l, t->r);
    delete t;
    return relax(q);
  } else {
    if (x < leftCount(t)) t->l = erase(t->l, x);
    else t->r = erase(t->r, x - 1 - leftCount(t));
    return relax(t);
  }
}

Node* find(Node* cur, int x) {
  while (cur != null and leftCount(cur) != x) {
    if (x < leftCount(cur)) cur = cur->l;
    else {
      x = x - 1 - leftCount(cur);
      cur = cur->r;
    }
  }
  return cur;
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

int main(){
    #ifndef LOCAL
    #define problem_name "movetofront"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
        
    int n, m;
    scanf("%d %d", &n, &m);
    
    Node * root = new Node(1);
    for (int i = 2; i <= n; ++i){
      root = merge(root, new Node(i));
    }
    
    for (int i = 0; i < m; ++i) {
      int l, r; scanf("%d %d", &l, &r);
      l--, r--;
      
      // find all elements at position <= r
      Node * a, * b, * c;
      split(root, r, b, c);
      
      // find all elements at position >= l
      split(b, l - 1, a, b);
    
//       printf("Separate l = %d and r = %d\n", l, r);
//       puts("a:");
//       print(a);
//       puts("b:");
//       print(b);
//       puts("c:");
//       print(c);
//       
      
      root = merge(b, a);
      root = merge(root, c);
      
//       puts("After merging:");
//       print(root);
//       puts("");
    }
    traverse(root);
    puts("");
    
    return 0;
}


