// Wrong answer

// Andr&#233;s Mej&#237;a
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <bitset>
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

const int POSITIVE_INF = 127;
const int NEGATIVE_INF = -127;
vector< int > words[2];

char lower[1 << 26];
char upper[1 << 26];
int L;

int score(int remain) {
    int a[2] = {0, 0};
    for (int p = 0; p < 2; ++p) {
        for (int k = 0; k < words[p].size(); ++k) {
            int w = words[p][k];
            if ((w & remain) == w) {
                a[p]++;
            }
        }
    }
    return a[0] - a[1];
}

bool canFormWord(int remain) {
    for (int p = 0; p < 2; ++p) {
        for (int k = 0; k < words[p].size(); ++k) {
            int w = words[p][k];
            if ((w & remain) == w) {
                return true;
            }
        }
    }
    return false;
}

void update(int remain, int value, int alpha, int beta) {
    if(value <= alpha)           // a lowerbound value
        lower[remain] = value;
    else if (value >= beta)         // an upperbound value
        upper[remain] = value;
    else                           // a true minimax value
        lower[remain] = upper[remain] = value; 
}

int dfs(int depth, int remain, int alpha, int beta) {
    if (depth == L) {
        int value = score(remain);
        update(remain, value, alpha, beta);
        return value;
    }

    if (lower[remain] != NEGATIVE_INF or upper[remain] != POSITIVE_INF) {
       if (lower[remain] == upper[remain]) // stored value is exact
           return lower[remain];
       alpha = max(alpha, int(lower[remain]));
       beta = min(beta, int(upper[remain]));
       if (alpha >= beta) {
           assert( lower[remain] == NEGATIVE_INF or upper[remain] == POSITIVE_INF );
           return upper[remain] != POSITIVE_INF ? upper[remain] : lower[remain]; // if lowerbound surpasses upperbound
       }
    }
    
    int best = NEGATIVE_INF;
    for (int take = 0; take < 26; ++take) if (remain & (1 << take)) {
        int value = -dfs(depth + 1, remain - (1 << take), -beta, -alpha);
        best = max(best, value);
        alpha = max(alpha, best);
        if (best >= beta) break;
    }
    update(remain, best, alpha, beta);
    return best;
}

int main(){
    #ifndef LOCAL
    freopen("keyboard.in", "r", stdin);
    freopen("keyboard.out", "w", stdout);
    #endif
    
    memset(lower, NEGATIVE_INF, sizeof lower); // Something small
    memset(upper, POSITIVE_INF, sizeof upper); // Something big
    
    cin >> L;
    for (int p = 0; p < 2; ++p) {
        int x; cin >> x;
        for (int i = 0; i < x; ++i) {
            string w; cin >> w;
            int mask = 0;
            for (int i = 0; i < w.size(); ++i) mask |= ( 1 << (w[i] - 'a') );
            words[p].push_back( mask );
        }
    }
    
    int ans = dfs(0, (1 << 26) - 1, NEGATIVE_INF, POSITIVE_INF);
    printf("%d\n", ans);
    return 0;
}