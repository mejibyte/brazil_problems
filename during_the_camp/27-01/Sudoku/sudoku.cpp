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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define hasBit(mask, bit)   (((mask) >> (bit)) & 1)
#define setBit(mask, bit)   ((mask) | (1 << (bit)))
#define unsetBit(mask, bit) ((mask) & ~(1 << (bit)))

short board[9][9];

int fila[9];
int columna[9];
int cuadro[3][3];

bool resuelto;

void imprimirMascara(int mask) {
    for (int i = 0; i <= 32; ++i) {
        if (hasBit(mask, i)) printf("%d ", i);
    }
    puts("");
}

inline void poner(int i, int j, int num) {
    assert( board[i][j] == 0 or board[i][j] == num );
    board[i][j] = num;
    fila[i] = unsetBit(fila[i], num);
    columna[j] = unsetBit(columna[j], num);
    cuadro[i / 3][j / 3] = unsetBit(cuadro[i / 3][j / 3], num);
}

inline void quitar(int i, int j) {
    assert( board[i][j] != 0 );
    int num = board[i][j];
    board[i][j] = 0;
    fila[i] = setBit(fila[i], num);
    columna[j] = setBit(columna[j], num);
    cuadro[i / 3][j / 3] = setBit(cuadro[i / 3][j / 3], num);    
}

inline void imprimir() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d", board[i][j]);
        }
        puts("");
    }
}

inline bool puedoPoner(int i, int j, int k) {
    if (!hasBit(fila[i], k)) return false;
    if (!hasBit(columna[j], k)) return false;
    if (!hasBit(cuadro[i/3][j/3], k)) return false;
    return true;
}

void buscar(int i, int j) {
    //printf("i = %d, j = %d\n", i, j);
    
    if (i == 8 and j == 9) {
        imprimir();
        resuelto = true;
        return;
    }
    
    if (j == 9) {
        buscar(i + 1, 0);
        return;
    }
    
    if (board[i][j] != 0) {
        buscar(i, j + 1);
        return;
    }
    
    for (int k = 1; k <= 9; ++k) {
        if (puedoPoner(i, j, k)) {
            poner(i, j, k);
            //printf(" en (%d, %d) puse %d\n", i, j, k);
            buscar(i, j + 1);
            if (resuelto) return;
            quitar(i, j);
        }
    }
}

int main(){
    int runs; scanf("%d ", &runs);
    while (runs--) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char c; scanf("%c ", &c);
                board[i][j] = (c - '0');
            }
        }
        
        //For(i, 0, 9) { For(j, 0, 9) printf("%d ", (int)board[i][j]); puts(""); }
        for (int i = 0; i < 9; ++i) {
            fila[i] = columna[i] = cuadro[i/3][i%3] = 0;
            for (int num = 1; num <= 9; ++num) {
                fila[i] = setBit(fila[i], num);
                columna[i] = setBit(columna[i], num);
                cuadro[i / 3][i % 3] = setBit(cuadro[i / 3][i % 3], num);
            }
        }
        for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) poner(i, j, board[i][j]);
        resuelto = false;
        //D( puedoPoner(0, 1, 4 ) );
        
        //imprimirMascara( cuadro[0][0] );
        buscar(0, 0);
    }
    return 0;
}
