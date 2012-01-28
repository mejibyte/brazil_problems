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

const int MAXN = 1000005;
vector< int > G[2][MAXN];
vector< int > R[2][MAXN];
int N[2], M[2];
int grundy[2][MAXN];
const int oo = (1 << 30);

// Fills the grundy array with the appropriate grundy number for each node
void calculate(vector< int > G[MAXN], vector< int > R[MAXN], int n, int grundy[MAXN]) {
    static int count[MAXN];
    static int dist[MAXN];
    
    for (int i = 0; i < n; ++i) {
        grundy[i] = -1;
    }
    
    for (int k = 0, changed = true; changed; ++k) {
        changed = false;

        queue< int > q;
        for (int i = 0; i < n; ++i) {
            dist[i] = -1;
            
            count[i] = 0;
            for (int e = 0; e < G[i].size(); ++e) {
                int v = G[i][e];
                count[i] += (grundy[v] == -1 or grundy[v] > k);  // infinity is the only value > k at this point
            }
            if (count[i] == 0 and grundy[i] == -1) {
                dist[i] = 0;
                q.push( i );
                // printf("on iteration k = %d, node i = %d has 0 count\n", k, i + 1);
            }
        }
        
        while (q.size() > 0) {
            int u = q.front(); q.pop();
            assert( dist[u] != -1 );
            for (int e = 0; e < R[u].size(); ++e) {
                int v = R[u][e];
                if (dist[v] != -1) continue;
                if (dist[u] % 2 == 0) { // normal BFS. 
                    //v can't have the same grundy number as u (which is K), because there's an edge from v to u in the original graph.
                    
                    if (grundy[v] != -1 and grundy[v] != oo) continue;                    
                    dist[v] = dist[u] + 1;
                    q.push( v );
                } else {
                    //v might have grundy number K, as long as we are sure that there are no edges to bigger grundy numbers.
                    
                    if (grundy[v] != -1) continue;   
                    if (--count[v] == 0) {
                        dist[v] = dist[u] + 1;
                        q.push( v );
                    }
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            if (dist[i] != -1 and dist[i] % 2 == 0) {
                assert( grundy[i] == -1 );
                grundy[i] = k;
                changed = true;
            }
        }
        
        // put infinity in nodes that don't have an edge pointing to k
        for (int i = 0; i < n; ++i) {
            if (grundy[i] != -1) continue;
            bool has = false;
            for (int e = 0; e < G[i].size() and !has; ++e) {
                int v = G[i][e];
                if (grundy[v] == k) has = true;
            }
            if (!has) grundy[i] = oo;
        }
    }    
    
//    printf("grundy numbers are:\n");
//    for (int i = 0; i < n; ++i) {
//        printf("grundy[%d] = %d\n", i + 1, grundy[i]);
//    }

}

// g - value of the other non-infinity game
// u - node with grundy[u] == oo
bool canWinWithInfinity(int g,   int u, vector< int > G[MAXN], int grundy[MAXN]) {
    for (int e = 0; e < G[u].size(); ++e) {
        int v = G[u][e];
        assert( grundy[v] != -1 );
        if (grundy[v] == oo) continue;
        if (grundy[v] ^ g == 0) return true;
    }
    return false;
}

vector< int > sumG[MAXN];
vector< int > sumR[MAXN];
int sumGrundy[MAXN];
int sumGSize;

void print(vector< int > G[MAXN], int n) {
    for (int i = 0; i < N[0]; ++i) {
        if (G[i].size() > 0) {
            printf("%d -> ", i + 1);
            foreach(v, G[i]) printf("%d ", *v + 1); puts("");
        }
    }
}

bool hasGrundy(int u, vector<int> G[MAXN], int grundy[MAXN], int which) {
    foreach(v, G[u]) if (grundy[*v] == which) return true;
    return false;
}

void printGraphs() {
    printf("g0 (%d nodes):\n", N[0]);
    print(G[0], N[0]);
    
    printf("g1 (%d nodes):\n", N[1]);
    print(G[1], N[1]);
    
    puts("sum graph:");
    print(sumG, sumGSize);
    exit(0);    
}

string nimSum(int u0, int u1) {
    int g0 = grundy[0][u0];
    int g1 = grundy[1][u1];
    if (g0 != oo and g1 != oo) return g0 ^ g1 == 0 ? "second" : "first";
    if (g0 == oo and g1 == oo) return "draw";
    if (g0 == oo) {
        D(u0);
        D(g1);
        return (hasGrundy(u0, G[0], grundy[0], g1) ? "first" : "draw");
    }
    assert(g1 == oo and g0 != oo);
    return (hasGrundy(u1, G[1], grundy[1], g0) ? "first" : "draw");    
}

string sumGraph(int su) {
    if (sumGrundy[su] != oo) return sumGrundy[su] != 0 ? "first" : "second";
    return hasGrundy(su, sumG, sumGrundy, 0) ? "first" : "draw";
}

bool checkEqual(int u0, int u1, int su) {
    string s = nimSum(u0, u1);
    string t = sumGraph(su);
    if (t != s) {
        printf("Sum gave %s, sum-graph gave %s\n", s.c_str(), t.c_str());
        printf("u0 = %d (g0 = %d), u1 = %d (g1 = %d)\n", u0 + 1, grundy[0][u0], u1 + 1, grundy[1][u1]);
        printGraphs();
        exit(0);
    }
    return true;
}

int main(){
    #ifndef LOCAL
    freopen("smith.in", "r", stdin);
    freopen("smith.out", "w", stdout);
    #endif
    
    srand(1234563);
    
    int single = 5;
    int pow = 100;
    int both = pow * pow; 
    sumGSize = both;   
    
    for (int k = 0; k < 10000; ++k) {
        
        for (int i = 0; i < both; ++i) {
            G[0][i].clear();
            G[1][i].clear();
            R[0][i].clear();
            R[1][i].clear();
            sumG[i].clear();
            sumR[i].clear();
        }
        printf(".");    
        // generate random graphs to check
        for (int g = 0; g < 2; ++g) {
            N[g] = rand() % single + 1;
            M[g] = rand() % 5 + 1;

            for (int k = 0; k < M[g]; ++k) {
                int u = rand() % N[g];
                int v = rand() % N[g];
                G[g][u].push_back( v );
                R[g][v].push_back( u );
            }
            
            calculate(G[g], R[g], N[g], grundy[g]);
        }
        
        // generate the sum graph    
        for (int u0 = 0; u0 < single; ++u0) {
            for (int u1 = 0; u1 < single; ++u1) {
                int cur = u0 * pow + u1;
                assert( cur < MAXN );
                
                for (int k = 0; k < G[0][u0].size(); ++k) {
                    int next = G[0][u0][k] * pow + u1;    
                    assert( next < MAXN );
                    sumG[cur].push_back( next );
                    sumR[next].push_back( cur );
                }
                
                for (int k = 0; k < G[1][u1].size(); ++k) {
                    int next = u0 * pow + G[1][u1][k];                
                    assert( next < MAXN );
                     
                    sumG[cur].push_back( next );
                    sumR[next].push_back( cur );
                }
            }
        }
        
        calculate(sumG, sumR, both, sumGrundy);
        for (int i = 0; i < N[0]; ++i) {
            for (int j = 0; j < N[1]; ++j) {
                checkEqual(i, j, i * pow + j);
            }
        }
        
    }
   
    return 0;
     
    // Answer queries
    int T; scanf("%d", &T);
    while (T--) {
        int u0, u1;
        scanf("%d %d", &u0, &u1);
        u0--, u1--;
        
        int g0 = grundy[0][u0], g1 = grundy[1][u1];
        assert(g0 != -1 and g1 != -1);
        
        if (g0 == oo and g1 == oo) {
            puts("draw");
            continue;
        }
        
        if (g0 != oo and g1 != oo) {
            puts(g0 ^ g1 == 0 ? "second" : "first");
            continue;
        }
        
        if (g0 == oo) { assert(g1 != oo);
            bool ans = canWinWithInfinity(g1, u0, G[0], grundy[0]);
            puts(ans ? "first" : "draw");
        } else { assert(g0 != oo and g1 == oo);
            bool ans = canWinWithInfinity(g0, u1, G[1], grundy[1]);
            puts(ans ? "first" : "draw");
        }
    }
    return 0;
}
