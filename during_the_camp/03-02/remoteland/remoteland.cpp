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
#include <bitset>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////
const int MAXN = 10000005;
const int MAXP = 665000;
const int mod = 1000000007;
int n;
int sieve [MAXN];
int primes [MAXP];
int ans[MAXN];
bitset<MAXP> avail;

void build() {
    //List of primes and prime factorization
    int pc = 1;
    for (int i = 2; i < MAXN; i++){
        if (sieve[i] == 0){ // Is prime
            primes[pc] = i;
            sieve[i] = pc;
            pc++;
        }        
        for (int j = 1; j <= sieve[i] and i * primes[j] < MAXN; j++){
            sieve[i * primes[j]] = j;
        }  
    }
    /*for (int i = 1; i <= 100; i++){
        printf("primes[%d] = %d\n", i, primes[i]);    
    }*/
    
    //Build answer
    ans[1] = 1;
    for (int x = 2; x < MAXN; x++){
        ans[x] = ans[x - 1];
        int k = x;
        while (k > 1){
            int p = sieve[k];
            k /= primes[p];
            if (avail[p]){
                long long pp = primes[p] % mod;
                pp = (pp * pp) % mod;
                ans[x] = (ans[x] * pp) % mod;
            }   
            avail[p] = avail[p] ^ 1;
        }
    }
    
}


int main(){
    build();
    while (scanf("%d", &n) == 1){
        if (n == 0) break;
        cout << ans[n] << endl;  
    }
    return 0;
}
