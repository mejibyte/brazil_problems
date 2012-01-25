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
  int x, y, size;
  long long sum;
  Node *l, *r;
  Node(int k) : x(k), y(rand()), size(1), l(null), r(null), sum(0) { }
};

Node* relax(Node* p) {
  if (p) {
    p->size = 1;
    p->sum = p->x;
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

void split(Node* t, int x, Node* &l, Node* &r) {
  if (t == null) l = r = null; else {
    if (x < t->x) {
	split(t->l, x, l, t->l);
	r = relax(t);
    } else {
	split(t->r, x, t->r, r);
	l = relax(t);
    }
  }
}

Node* merge(Node* l, Node *r) {
  if (l == null) return relax(r);
  if (r == null) return relax(l);
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    return relax(l);
  } else {
    r->l = merge(l, r->l);
    return relax(r);
  }
}

Node* insert(Node* t, Node* m) {
  if (t == null || m->y > t->y) {
    split(t, m->x, m->l, m->r);
    return relax(m);
  }
  if (m->x < t->x) t->l = insert(t->l, m);
  else t->r = insert(t->r, m);
  return relax(t);
}

Node* erase(Node* t, int x) {
  if (t == null) return null;
  if (t->x == x) {
    Node *q = merge(t->l, t->r);
    delete t;
    return relax(q);
  } else {
    if (x < t->x) t->l = erase(t->l, x);
    else t->r = erase(t->r, x);
    return relax(t);
  }
}

Node* find(Node* cur, int x) {
  while (cur != null and cur->x != x) {
    if (x < cur->x) cur = cur->l;
    else cur = cur->r;
  }
  return cur;
}

void print(Node *p) {
  if (p == null) return;
  print(p->l);
  printf("x = %d, y = %d, size = %d\n", p->x, p->y, p->size);
  print(p->r);
}

long long sum(Node* p, int x) { // find the sum of elements <= x
  if (p == null) return 0LL;
  if (p->x > x) return sum(p->l, x);
  long long ans = (p->l ? p->l->sum : 0) + p->x + sum(p->r, x);
  assert(ans >= 0);
  return ans;
}

void add(Node* &root, int w) {
  assert(w >= 0);
  if (find(root, w)) return; // already there
  root = insert(root, new Node(w));
}

long long sum(Node *p, int x, int y) {
  long long big = sum(p, y);
  long long small = sum(p, x - 1);
  assert(small <= big);
  return big - small;
}

int main(){
    #ifndef LOCAL
    #define problem_name "sum"
    assert( freopen(problem_name ".in", "r", stdin) != NULL);
    assert( freopen(problem_name ".out", "w", stdout) != NULL);
    #endif
    
    Node * root = new Node(0);
    
//     add(root, 3);
//     add(root, 3);
//     add(root, 3);
//     add(root, 3);
//     add(root, 8);
//     add(root, 20);
//     add(root, 20);
//     
//     D(sum(root, 10));
//     D(sum(root, 3));
//     D(sum(root, 2));
//     D(sum(root, -1));
//     D(sum(root, 0));
//     D(sum(root, -2));
//     D(sum(root, 20));
//     D(sum(root, 19));
    
    int n; scanf("%d", &n);
    
    long long prev = -1;
    for (int i = 0; i < n; ++i){
	char type; scanf(" %c ", &type);
	if (type == '?') {
	    int l, r;
	    scanf("%d %d", &l, &r);
	    
	    prev = sum(root, l, r);
	    cout << prev << "\n";
	    
	} else {
	  int i; scanf("%d", &i);
	  assert(i >= 0);
	  
	  if (prev == -1){
	    add(root, i);
	  } else {
	    int mod = 1000000000;

	    int next = (prev % mod + i % mod) % mod; 
	    assert(next >= 0);
	    add(root, next);
	  }
	  prev = -1;
	}
    }
    
    
    return 0;
}


