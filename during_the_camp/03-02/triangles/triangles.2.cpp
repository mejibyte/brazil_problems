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

int n;
int X[1005], Y[1005];
long long dists[1005];

inline long long d (int i, int j){
    int x1 = X[i], y1 = Y[i];
    int x2 = X[j], y2 = Y[j];
    
    long long dist = 1LL * (x1 - x2) * (x1 - x2) + 1LL * (y1 - y2) * (y1 - y2);
    
    return dist;  
}

long long solve(){
    long long ans = 0;
    for (int a = 0; a < n; a++){ 
        int cnt = 0;
        for (int b = 0; b < n; b++){
            if (a == b) continue;
            long long dist = d(a, b);
            //printf("Distancia entre (%d, %d) y (%d, %d)es ", p[a].first, p[a].second, p[b].first, p[b].second);
            //cout << dist << endl;
            dists[cnt++] = dist;
        }
        sort(dists, dists + cnt); 
        for (int i = 0; i < cnt; ) {
            int j = i;
            while (j < cnt and dists[j] == dists[i]) j++;
            int l = j - i;
            if (l >= 2){
                ans +=  1LL * l * (l - 1) / 2;            
            }
            i = j;
        }
               
    }
 //   for (int i = 0; i < n; i++){
//        map <long long, int> :: iterator it;
//        for (it = m[i].begin(); it != m[i].end(); it++){
//            int l = it->second;
//            if (l >= 2){
//                ans +=  1LL * l * (l - 1) / 2;
//                //printf("Para el punto (%d, %d) hay dos distancias = ", p[a].first, p[a].second);
//                //cout << l << endl << endl;   
//            }                
//        } 
//    }   
    return ans;  
}

int main(){
    while (scanf("%d", &n) == 1){
        if (n == 0) break;
        for (int i = 0; i < n; i++){
            scanf("%d %d", &X[i], &Y[i]);
        }
        long long ans = solve();
        cout << ans << endl;
    }
    return 0;
}
