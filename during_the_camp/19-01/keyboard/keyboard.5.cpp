// Wrong answer

// Andrés Mejía
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

const int oo = 127;
vector< int > words[2];

char Alpha[1 << 26];
char Beta[1 << 26];
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

int dfs(int depth, int remain, int alpha, int beta) {
    if (depth == L) return score(remain);
    if (!canFormWord(remain)) return 0;
    
    alpha = max(alpha, int(Alpha[remain]));
    beta = min(beta, int(Beta[remain]));
    if (alpha < beta) {
        for (int take = 0; take < 26; ++take) if (remain & (1 << take)) {
            if ((depth & 1) == 0)
                alpha = max(alpha, dfs(depth + 1, remain - (1 << take), alpha, beta));
            else
                beta = min(beta, dfs(depth + 1, remain - (1 << take), alpha, beta));
            if (alpha >= beta) break;
        }
    }
    if ((depth & 1) == 0) {
        if (Alpha[remain] <= alpha and alpha <= Beta[remain]) {
            Alpha[remain] = Beta[remain] = alpha;
        } else if (alpha >= Alpha[remain]) {
            Beta[remain] = min(Beta[remain], char(alpha));
        }
        return alpha;
    } else {
        if (Alpha[remain] <= beta and beta <= Beta[remain]) {
            Alpha[remain] = Beta[remain] = beta;
        } else if (beta <= Beta[remain]) {
            Alpha[remain] = max(Alpha[remain], char(beta));
        }
        return beta;
    }
}

int main(){
    #ifndef LOCAL
    freopen("keyboard.in", "r", stdin);
    freopen("keyboard.out", "w", stdout);
    #endif
    
    memset(Alpha, 0x80, sizeof Alpha); // Something small
    memset(Beta, 0x7F, sizeof Beta); // Something big
    
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
    
    int ans = dfs(0, (1 << 26) - 1, -oo, +oo);
    printf("%d\n", ans);
    return 0;
}