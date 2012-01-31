// Andr&#233;s Mej&#237;a
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

vector< int > words[2];

char best_alpha[1 << 26];
char best_beta[1 << 26];

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

char dfs1(int depth, int remain, char alpha, char beta);

char dfs0(int depth, int remain, char alpha, char beta) {
    if (depth == L) return score(remain);
    if (!canFormWord(remain)) return 0;
    if (beta <= best_alpha[remain]) return best_alpha[remain];
    if (best_alpha[remain] > alpha) alpha = best_alpha[remain];
    
    for (int take = 0; take < 26; ++take) if (remain & (1 << take)) {
        int t = dfs1(depth + 1, remain - (1 << take), alpha, beta);
        if (t > best_alpha[remain]) best_alpha[remain] = t;
        if (t > alpha) alpha = t;
        if (alpha >= beta) break;
    }
    return alpha;
}

char dfs1(int depth, int remain, char alpha, char beta) {
    if (depth == L) return score(remain);
    if (!canFormWord(remain)) return 0;
    if (alpha >= best_beta[remain]) return best_beta[remain];
    if (best_beta[remain] < beta) beta = best_beta[remain];
    
    for (int take = 0; take < 26; ++take) if (remain & (1 << take)) {
        int t = dfs0(depth + 1, remain - (1 << take), alpha, beta);
        if (t < best_beta[remain]) best_beta[remain] = t;
        if (t < beta) beta = t;
        if (alpha >= beta) break;
    }
    return beta;
}

int main(){
    #ifndef LOCAL
    freopen("keyboard.in", "r", stdin);
    freopen("keyboard.out", "w", stdout);
    #endif
    
    memset(best_alpha, 0x80, sizeof best_alpha); // something small
    memset(best_beta, 0x7F, sizeof best_beta); // something big
        
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
    
    int ans = dfs0(0, (1 << 26) - 1, 0x80, 0x7F);
    printf("%d\n", ans);
    return 0;
}