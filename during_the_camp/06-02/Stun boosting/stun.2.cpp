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

const long long STUN = 300;
const long long KILL = 1800;
const long long GAME_TIME = 4 * 60;
const long long STUN_TIME = 7;
long long score[10];
long long times[1005][10];
int X, R;


// retorna true si alguien ganó
bool round(int r) {
    for (int i = 0; i < 6; ++i) assert(score[i] < X);
    long long minA = -1, minB = -1;
    vector< int > teamA, teamB;
    for (int i = 0; i < 6; i += 2) {
        int a = i, b = i + 1;
        if (times[r][a] > times[r][b]) swap(a, b);
        assert(times[r][a] <= times[r][b]);
        if (times[r][a] == times[r][b]) assert(a < b);
        
        teamA.push_back(a);
        teamB.push_back(b);
        minA = max(minA, times[r][a]);
        minB = max(minB, times[r][b]);
    }
    assert(minA >= 1); assert(minB >= 1);
    assert(minA < GAME_TIME); assert(minB < GAME_TIME);
    
    //D(minA); D(minB);
    
    vector< pair<long long, int> > winners;
    
    for (int i = 0; i < 3; ++i) {
        int who = teamA[i];
        long long extra = ((GAME_TIME - minA) / STUN_TIME) * STUN;
        if (score[who] + extra >= X) { // this player will win
            long long wonAt = (X - score[who] + STUN - 1) / STUN * STUN_TIME;
            wonAt += minA;
            winners.push_back( make_pair(wonAt, who) );
        }
        score[who] += extra;
    }
    
    for (int i = 0; i < 3; ++i) {
        int who = teamB[i];
        long long extra = ((GAME_TIME - minB) / STUN_TIME) * STUN;
        if (score[who] + extra >= X) { // this player will win
            long long wonAt = (X - score[who] + STUN - 1) / STUN * STUN_TIME;
            wonAt += minB;
            winners.push_back( make_pair(wonAt, who) );
        }
        score[who] += extra;
    }
    
    sort(winners.begin(), winners.end());
    if (winners.size() > 0) {
        printf("%d %d\n", winners[0].second + 1, r + 1);
        return true;
    }
    
    int spareA = (GAME_TIME - minA) % STUN_TIME;
    if (spareA >= 2) {
        for (int i = 0; i < 3; ++i) {
            score[teamA[i]] += KILL;
        }
    }
    
    int spareB = (GAME_TIME - minB) % STUN_TIME;
    if (spareB >= 2) {
        for (int i = 0; i < 3; ++i) {
            score[teamB[i]] += KILL;
        }
    }    
    
    for (int i = 0; i < 6; ++i) {
        if (score[i] >= X) {
            printf("%d %d\n", i + 1, r + 1);
            return true;
        }
    }
    
    return false;
}

void game() {
    for (int i = 0; i < 6; ++i) {
        if (score[i] >= X) {
            printf("%d 0\n", i + 1);
            return;
        }
    }
    
    for (int r = 0; r < R; ++r) {
        if (round(r)) return;
    }
    
    printf("-1");
    for (int i = 0; i < 6; ++i) printf(" %lld", score[i]);
    puts("");
}


int main(){
    while (scanf("%d %d", &X, &R) == 2) {
        if (X == 0 and R == 0) break;
        for (int i = 0; i < 6; ++i) scanf("%lld", &score[i]);
        for (int r = 0; r < R; ++r) for (int i = 0; i < 6; ++i) scanf("%lld", &times[r][i]);
        game();
    }
    return 0;
}
