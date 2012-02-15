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

const int MAXN = 1005;

int cnt [MAXN];
vector <int> g [MAXN];
bool faul [MAXN];
map <int, string> m;
int n, k;

void refresh (){
    m.clear();
    for (int i = 0; i < n; i++){
        faul[i] = false;
        cnt[i] = 0;
        g[i].clear();    
    }   
}


int main(){
    while (scanf("%d %d", &k, &n) == 2){
        if (n == 0 and k == 0) break;
        refresh();
        for (int i = 0; i < n; i++){
            cin >> m[i];
            for (int j = 0; j < k; j++){
                int paper; cin >> paper;
                paper--;
                cnt[paper]++;
                g[i].push_back(paper);    
            }    
            sort(g[i].begin(), g[i].end());
            //See if i reviewed the same paper twice
            int prev = -1;
            for (int j = 0; j < k; j++){
                if (g[i][j] == prev) faul[prev] = true;
                prev = g[i][j];    
            }
                  
        }
        //See if a paper was reviewed more or less 
        for (int i = 0; i < n; i++){
            if (cnt[i] != k) faul[i] = true;    
        }
        //See if i reviewed a paper from my faculty
        for (int i = 0; i < n; i++){
            for (int j = 0; j < k; j++){
                int paper = g[i][j];
                if (m[i] == m[paper]) faul[paper] = true;
            }    
        }
        // Count total number of problems
        int ans = 0;
        for (int i = 0; i < n; i++){
            if (faul[i]) ans++;    
        }
        assert(ans <= n);
        if (ans == 0) printf("NO PROBLEMS FOUND\n");    
        if (ans == 1) printf("1 PROBLEM FOUND\n");
        if (ans >= 2) printf("%d PROBLEMS FOUND\n", ans);
        
        
    }
    
    return 0;
}
