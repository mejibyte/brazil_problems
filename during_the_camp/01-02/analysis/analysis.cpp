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

string decode(const string &coded, const string &uncoded){
    
}

string decode(const string &coded, const string &uncoded){
    
}



int main(){
    
    
    int k;
    string c1, c2, text;
    while (cin >> k){
        if (k == 0) break;
        cin >> c1 >> c2 >> text;
        
        if (c2.size() > c1.size()) swap(c1, c2);
        
        for (int i = 0; i <= text.size() - c1.size(); i++){
            //Where to put word
            string key = decode(text.substr(i, c1.size()), c1);
            //Does key have less letters than c1?
            string newText = code(text, key);
            if (newText.substr(0, i).find(c2) != string::npos or newText.substr(i + c1.size()).find(c2) != string::npos ){
                //This is a solution    
            }
        }
        
    }
    return 0;
}
