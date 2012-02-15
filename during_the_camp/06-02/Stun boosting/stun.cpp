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

const int STUN = 300;
const int KILL = 1800;
const int GAME_TIME = 4 * 60;
const int STUN_TIME = 7;
int score[10];
int times[1005][10];
int R, X;

int has_won(){
    for (int i = 0; i < 6; i++){
        if (score[i] >= X) return i + 1;        
    }
    return -1;      
}

bool play_round (int round){
    round--;
    //Gather everyone
    int minA = 0;
    int minB = 0;
    vector <int> playersA, playersB;
    for (int i = 0; i < 6; i+= 2){
        int first = i; int second = i + 1;
        if (times[round][first] > times[round][second]) swap(first, second);
        playersA.push_back(first);
        minA = max (minA, times[round][first]);
        playersB.push_back(second);
        minB = max (minB, times[round][second]);
    }
    // PlayersA => Players on first group, minA => time first group starts to stun
    // PlayersB => Players on second group, minB => time second group starts to stun
    
    //See how many stuns each group made
    int roundA = (max(0, GAME_TIME - minA)) / STUN_TIME;
    int roundB = (max(0, GAME_TIME - minB)) / STUN_TIME;
    
    assert(minA <= minB);
    
    //Update scores
    int prev_scores[6];
    for (int i = 0; i < 6; i++){
        prev_scores[i] = score[i];
    }
    
    vector< pair<int, int> > winners;
    for (int i = 0; i < 3; i++){
        score[playersA[i]] += roundA * STUN;
        score[playersB[i]] += roundB * STUN;
        
        if (score[playersA[i]] >= X) {
            int wonAt = minA + (X - prev_scores[playersA[i]] + STUN - 1) / STUN * STUN_TIME;
            winners.push_back( make_pair(wonAt, playersA[i]) );
        }    

        if (score[playersB[i]] >= X) {
            int wonAt = minB + (X - prev_scores[playersB[i]] + STUN - 1) / STUN * STUN_TIME;
            winners.push_back( make_pair(wonAt, playersB[i]) );
        }            
    }
    sort(winners.begin(), winners.end());
    if (winners.size() > 0) {
        printf("%d %d\n", winners[0].second + 1, round + 1);
        return true;
    }

    //See if you can kill
    int spareA = (max(0, GAME_TIME - minA)) % STUN_TIME;
    if (spareA >= 2){
        for (int i = 0; i < 3; i++){
            score[playersA[i]] += KILL;    
        }    
    }
    
    int spareB = (max(0, GAME_TIME - minB)) % STUN_TIME;
    if (spareB >= 2){
        for (int i = 0; i < 3; i++){
            score[playersB[i]] += KILL;    
        }    
    }
    
    return false;
}

void game() {
    int winner = has_won();       
    if (winner != -1){
        printf("%d 0\n", winner);
        return;
    }
    
    int round = 1;
    for (; round <= R; round++){
        if (play_round(round)) return;
        winner = has_won();
        if (winner != -1) {
            printf("%d %d\n", winner, round);                
            return;
        }
    }
    printf("-1");
    for (int i = 0; i < 6; i++) printf(" %d", score[i]);
    printf("\n");
}


int main(){
    while (scanf("%d %d", &X, &R) == 2){
        if (R == 0 and X == 0) break;
        for (int i = 0; i < 6; i++) scanf("%d", &score[i]);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < 6; j++) 
                scanf("%d", &times[i][j]);
          
        /*for (int i = 0; i < R; i++){
            for (int j = 0; j < 6; j++){
                printf("%d ", times[i][j]);
            }
            puts("");
        }*/
          
             
        // printf("score inicial:\n"); for (int i = 0; i < 6; ++i) printf("%d ", score[i]); puts("");
             
        game();
    }
    return 0;
}
