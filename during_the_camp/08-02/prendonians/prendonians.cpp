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

void myAssert(bool f){
    while(!f);
}

int N;

const int MAXN = 3015;

struct Person {
    int gender; // 0 - male, 1 - female, -1 unknown
    int parents[2]; // -1 for unknown
    int mate; // -1 for unset, index for set
    vector< int > sons;
};

enum { Male, Female };
enum { White, Gray, Black };

Person people[MAXN];
bool visited[MAXN];
int color[MAXN];

map<string, int> id;
int nextId;

inline int getId(const string &s) {
    if (id.count(s) == 0) return id[s] = nextId++;
    return id[s];
}

bool areSiblings(int a, int b) {
    //myAssert(a != -1 and b != -1);
    for (int p = 0; p < 2; ++p) {
        
        int x = people[a].parents[p];
        if (x == -1) continue;
        
        for (int q = 0; q < 2; ++q) {
            int y = people[b].parents[q];
           if (y == -1) continue;
            
            if (x == y) return true;
        }
    }
    return false;
}

void dfs(int u){ 
    if (u == -1) return;
    if (visited[u]) return;
    visited[u] = true;
    dfs(people[u].parents[0]);
    dfs(people[u].parents[1]);
    foreach(s, people[u].sons) dfs(*s);
}

bool findCycle(int u) {
    //myAssert(u != -1);
    if (color[u] == Gray) return true;
    if (color[u] == Black) return false;
    
    color[u] = Gray;
    foreach(s, people[u].sons){ 
        if (findCycle(*s)) return true;
    }
    color[u] = Black;
    return false;
}

bool validLastName(const string &s) {
    if (s.size() <= 2) return false;
    // 3 o mas
    if (s.substr(s.size() - 2, 2) == "jk") return true;
    if (s.size() <= 3) return false;
    if (s.substr(s.size() - 3, 3) == "gvw") return true;
    return false;
}

bool sameSuffix(const string &s, const string &t) {
    if (s.substr(s.size() - 2, 2) == "jk"){
        return (t.substr(t.size() - 2, 2) == "jk");
    }
    
    if (s.substr(s.size() - 3, 3) == "gvw"){
        return (t.substr(t.size() - 3, 3) == "gvw");
    }
    return false;
}

void solve() {
    nextId = 0;
    id.clear();
    
    if (!(cin >> N)) return;
    //myAssert(N <= 1000);
    for (int i = 0; i <= 3 * N; ++i) {
        people[i].gender = -1;
        people[i].parents[0] = people[i].parents[1] = -1;
        people[i].mate = -1;
        people[i].sons.clear();
        visited[i] = false;
        color[i] = White;
    }
    
    bool monogamic = true;
    bool valid = true;
    
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        int name = getId(s);
        //myAssert(name >= 0 and name < MAXN);
        string m, p; cin >> m >> p;
        //myAssert(m[m.size() -1] == p[p.size() - 1]);
        //myAssert(m.size() >= 2 and p.size() >= 2);
        if (!validLastName(m) or !validLastName(p)) {
            valid = false;
            continue;
        }
        
        if (!sameSuffix(m, p)){
            valid = false;
            continue;
        }
        
        if (m[m.size() - 1] == 'k') { // male
            m.resize(m.size() - 2);
            p.resize(p.size() - 2);
            
            people[name].gender = Male;
        } else { // female
            m.resize(m.size() - 3);
            p.resize(p.size() - 3);
            
            people[name].gender = Female;
        }
        
        int mm = getId(m);
        int pp = getId(p);
        
        if (mm == pp) valid = false; // hijo de una persona con ella misma
        if (name == mm or name == pp) valid = false; // soy hijo de mi mismo
        
        if (people[mm].mate != -1 and people[mm].mate != pp) monogamic = false;
        if (people[pp].mate != -1 and people[pp].mate != mm) monogamic = false;
        
        people[mm].mate = pp;
        people[pp].mate = mm;
        
        if (people[name].parents[0] != -1 and people[name].parents[0] != min(mm, pp)) valid = false; // soy hijo de dos parejas
        if (people[name].parents[1] != -1 and people[name].parents[1] != max(mm, pp)) valid = false; // soy hijo de dos parejas
        
        people[name].parents[0] = min(mm, pp);
        people[name].parents[1] = max(mm, pp);
        people[mm].sons.push_back(name);
        people[pp].sons.push_back(name);
    }
    
    if (!monogamic or !valid) {
        puts("NO");
        return;
    }
    
    //myAssert(nextId <= 3 * N);
    N = nextId;
    myAssert(N < MAXN);
    
    // check homosexual males
    for (int i = 0; i < N; ++i) {
        if (people[i].gender != Male) continue; // mujer puede estar casada con lo que quiera
        int mate = people[i].mate;
        if (mate != -1 and people[mate].gender == Male) { // homosexual males
            puts("NO");
            return; 
        }
    }
    
    // check married siblings
    for (int i = 0; i < N; ++i) {
        if  (people[i].mate == -1) continue;
        if (areSiblings(i, people[i].mate)){ 
            puts("NO");
            return;
        }
    }
    
    // check loops
    int roots = 0;
    for (int i = 0; i < N; ++i) {
        if (people[i].parents[0] == -1) {
            //myAssert(people[i].parents[1] == -1);
            roots++;
            if (findCycle(i)){
                puts("NO");
                return;
            }
        }
    }
    
    if (roots == 0) { // no hubo donde empezar
        puts("NO");
        return;
    }
    
    // check all are related
    dfs(0);
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            puts("NO");
            return;
        }
    }
    puts("YES");
}

int main(){
    int T; cin >> T; while (T--) solve();
    return 0;
}
