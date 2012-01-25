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

int mark[215][215];
bool pic[215][215];

int h, w;

// llena toda la seccion de (i, j) con la marka marker, siempre y cuando sea de color "color"
void flood(int i, int j, int marker, int color) {
    if (i < 0 or i >= h) return;
    if (j < 0 or j >= w) return;
    if (pic[i][j] != color) return;
    if (mark[i][j] == marker) return;  
    //D(i); D(j); D(mark[i][j]); D(marker);
    assert( mark[i][j] == 0 );
    mark[i][j] = marker;
    flood(i - 1, j, marker, color);
    flood(i + 1, j, marker, color);
    flood(i, j - 1, marker, color);
    flood(i, j + 1, marker, color);
    
}

int main(){
    int run = 1;
    while (scanf("%d %d ", &h, &w) == 2){
        if (h == 0 and w == 0) break;
        w *= 4;
        
        for (int i = 0; i <= h + 5; ++i) {
            for (int j = 0; j <= w + 5; ++j) {
                pic[i][j] = 0;
            }
        }
        
        for (int i = 1; i <= h; ++i) {
            string s; getline(cin, s);            
            for (int j = 1; j <= w; j += 4) {
                string hex = "";
                hex += s[(j - 1) / 4];
                int value; sscanf(hex.c_str(), "%x", &value);
                for (int k = 0; k < 4; ++k) {
                    pic[i][j + 3 - k] = (value >> k) & 1;
                }
            }
        }
        h++, w++; // 0 arriba e izquierda
        h++, w++; // 0 abajo y derecha
        // filas desde [0, h-1]
        // columnas desde [0, w-1]
        for (int i = 0; i <= h; ++i)
            for (int j = 0; j <= w; ++j) 
                mark[i][j] = 0;
                
                
        //For(i, 0, h) {For(j, 0, w) printf("%d", pic[i][j]); puts(""); } puts("");
        flood(0, 0, -1, 0);
        //For(i, 0, h) {For(j, 0, w) printf("%2d ", mark[i][j]); puts(""); } puts("");
        
        int nextFigure = 1;
        for (int i = 0; i < h; ++i) {
            for (int j = 0;  j < w; ++j) {
                if (pic[i][j] == 1 and !mark[i][j]) { // unmarked black
                    flood(i, j, nextFigure, 1);
                    nextFigure++; 
                }
            }
        }
        //For(i, 0, h) {For(j, 0, w) printf("%2d ", mark[i][j]); puts(""); } puts("");        
        map< int, int > holes;
        for (int i = 0; i < h; ++i) {
            for (int j = 0;  j < w; ++j) {
                if (pic[i][j] == 0 and !mark[i][j]) { // hueco blanco
                    for (int ii = i; ii >= 0; --ii) {
                        if (pic[ii][j] == 1) {
                            holes[ mark[ii][j] ]++;
                            break;
                        }
                    }
                    flood(i, j, -1, 0);
                }
            }
        }

        //For(i, 0, h) {For(j, 0, w) printf("%2d ", mark[i][j]); puts(""); } puts("");          
        string s = "";
        for (int i = 1; i < nextFigure; ++i) {
            if (holes[i] == 0) s += "W";
            else if (holes[i] == 1) s += "A";
            else if (holes[i] == 2) s += "K";
            else if (holes[i] == 3) s += "J";
            else if (holes[i] == 4) s += "S";
            else if (holes[i] == 5) s += "D";
            else assert(false);
        }
        sort(s.begin(), s.end());
        printf("Case %d: %s\n", run++, s.c_str());
    }
    
    return 0;
}
