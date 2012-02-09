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
#include <bitset>
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

int wordCount[2];
int words[2][15];

char best[1 << 26];
//char score_memo[1 << 26];
//char form_memo[1 << 26];


int L;

inline char score(int remain) {
    //if (score_memo[remain] != 0) return score_memo[remain] - 40;
    char a[2] = {0, 0};
    for (int p = 0; p < 2; ++p) {
        for (int k = 0, m = wordCount[p]; k < m; ++k) {
            int w = words[p][k];
            a[p] += ((w & remain) == w);
        }
    }
    char ans = a[0] - a[1];
    //score_memo[remain] = ans + 40;
    return ans;
}

inline bool canFormWord(int remain) {
    //if (form_memo[remain] != 0) return form_memo[remain] - 1;
    for (int p = 0; p < 2; ++p) {
        for (int k = 0; k < wordCount[p]; ++k) {
            int w = words[p][k];
            if ((w & remain) == w) {
                //form_memo[remain] = 2;
                return true;
            }
        }
    }
    //form_memo[remain] = 1;
    return false;
}

char dfs1(char depth, int remain, char alpha, char beta);

char dfs0(char depth, int remain, char alpha, char beta) {
    if (depth == L) return score(remain);
    //if (L > 18 and !canFormWord(remain)) return 0;
    //if (!canFormWord(remain)) return 0;
    if (best[remain] == -128) {
        best[remain] = -127;
    }
    if (beta <= best[remain]) return best[remain];
    if (best[remain] > alpha) alpha = best[remain];
    if (alpha >= beta) return alpha;
    for (int take = remain; take; take = take & (take - 1)) {
        char t = dfs1(depth + 1, remain - (1 << __builtin_ctz(take)), alpha, beta);
        if (t > best[remain]) best[remain] = t;
        if (t > alpha) alpha = t;
        if (alpha >= beta) break;
    }
    return alpha;
}

char dfs1(char depth, int remain, char alpha, char beta) {
    if (depth == L) return score(remain);
    //if (L > 18 and !canFormWord(remain)) return 0;
    //if (!canFormWord(remain)) return 0;
    if (best[remain] == -128) {
        best[remain] = +127;
    }
    if (alpha >= best[remain]) return best[remain];
    if (best[remain] < beta) beta = best[remain];
    if (alpha >= beta) return beta;
    for (int take = remain; take; take = take & (take - 1)) {
        char t = dfs0(depth + 1, remain - (1 << __builtin_ctz(take)), alpha, beta);
        if (t < best[remain]) best[remain] = t;
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
    
    memset(best, 0x80, sizeof best);

    static int permutation[26];
    // for (int i = 0; i < 26; ++i) {
    //     permutation[i] = i;
    // }
    // srand(113581321); // TL29
    // srand(1734507); // TL19
    // srand(410653677); // TL29
    // srand(8464); // TL20
    // srand(3524); // TL20
    // srand(541705002); // TL20
    // random_shuffle(permutation, permutation + 26);
    
    static char text[2][15][32];
    
    scanf("%d", &L);
    for (int p = 0; p < 2; ++p) {
        scanf("%d ", wordCount + p);
        for (int i = 0; i < wordCount[p]; ++i) {
            scanf("%s ", text[p][i]);
        }
    }

    pair<int, int> score[26];
    for (int i = 0; i < 26; ++i) {
        score[i].first = 0;
        score[i].second = i;
    }

    for (int p = 0; p < 2; ++p) {
        for (int i = 0; i < wordCount[p]; ++i) {
            int mask = 0;
            for (int j = 0; text[p][i][j]; ++j) {
                int pos = (text[p][i][j] - 'a');
                if (mask & (1 << pos) ) continue;
                score[pos].first++;
                mask |= ( 1 << pos );
            }
        }
    }
    sort(score, score + 26);
    for (int i = 0; i < 26; ++i) {
        permutation[i] = score[i].second;
    }
    
    for (int p = 0; p < 2; ++p) {
        for (int i = 0; i < wordCount[p]; ++i) {
            int mask = 0;
            for (int j = 0; text[p][i][j]; ++j) mask |= ( 1 << permutation[(text[p][i][j] - 'a')] );
            words[p][i] = mask;
        }
    }

    
    int ans = dfs0(0, (1 << 26) - 1, 0x80, 0x7F);
    printf("%d\n", ans);
    return 0;
}