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

typedef unsigned long long hash;
const hash B = 33;
const hash C = 5831;

const int MAXN = 12005;

hash pow[MAXN];
hash H[MAXN];

hash calc_hash(int a, int b) {
    return H[b] - H[a] * pow[b - a];
}

long long key[MAXN];
int sa[MAXN], rank[MAXN], *lcp=(int*)key;
struct Cmp { bool operator()(int i, int j) const { return key[i] < key[j]; } };

void build(const vector< int > &text) {
    int N = text.size();
    for (int i = 0; i < N; ++i) { sa[i] = i; key[i] = text[i]; }
    sort(sa, sa+N, Cmp());
    for (int k = 1; ; k *= 2) {
        for (int i = 0; i < N; ++i){
            rank[sa[i]] = i > 0 && key[sa[i-1]]==key[sa[i]] ? rank[sa[i-1]] : i;
        }
        if (k >= N) break;
        for (int i = 0; i < N; ++i){ 
            key[i] = rank[i] * (N + 1LL) + (i + k < N ? rank[i+k]+1 : 0);
        }
        sort(sa, sa+N, Cmp());
    }
//    for (int i = 0, k = 0; i < N; ++i) {
//        if (k > 0) k--;
//        if (rank[i] == N-1){ lcp[N-1] = -1; k = 0; continue; }
//        int j = sa[rank[i]+1];
//        while (text[i+k] == text[j+k]) k++;
//        lcp[rank[i]] = k;
//    }
}

// retorna el hash de la rotación ciclica más pequena de v
hash f(vector< int > &v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) v.push_back(v[i]);
    n *= 2; assert( n == v.size() );
    build(v);
    //printf("Before rotating: "); for (int i = 0; i < v.size(); ++i){ printf("%d", v[i]); if (i % 6 == 5) printf(" "); } puts("");
    for (int i = 0; i < v.size(); ++i) {
        if (sa[i] < n / 2) {
            v.resize(n / 2);
            n /= 2;
            rotate(v.begin(), v.begin() + sa[i], v.end());
            break;
        }    
    }
    //printf("Lexicographically smallest rotation is: "); for (int i = 0; i < v.size(); ++i){ printf("%d", v[i]); if (i % 6 == 5) printf(" "); } puts("");
    hash ans = C;
    for (int i = 0; i < v.size(); ++i) {
        ans = ans * B + (v[i] + 1);
    }
    return ans;
}

bool compare (const vector< int > &a, const vector< int > &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a[0] < b[0];
}

int main(){
    ios::sync_with_stdio(false);
    pow[0] = 1ULL;
    for (int i = 1; i < MAXN; ++i) pow[i] = pow[i - 1] * B;
    int run = 1;
    
    int n; while (cin >> n) {
        if (n == 0) break;
        
        map <hash, vector< int > > sets;
        
        for (int i = 0; i < n; ++i) {
            string s; cin >> s;
            vector< int > v;
            for (int k = 0; k < s.size(); ++k) {
                int value = -1;
                if (isupper(s[k])) value = s[k] - 'A';
                else if (islower(s[k])) value = s[k] - 'a' + 26;
                else if (isdigit(s[k])) value = s[k] - '0' + 2 * 26;
                else if (s[k] == '+') value = 62;
                else if (s[k] == '/') value = 63;
                assert(0 <= value and value <= 63);
                for (int p = 5; p >= 0; --p) {
                    v.push_back((value >> p) & 1);
                }
            }
            assert(v.size() == 6 * s.size());
            //D(s);for (int i = 0; i < v.size(); ++i){ printf("%d", v[i]); if (i % 6 == 5) printf(" "); } puts("");
            hash h = f(v);
            sets[h].push_back( i );
        }       
        
        vector< vector<int> > ans;
        foreach(p, sets) {
            ans.push_back(p->second);
            sort(ans.back().begin(), ans.back().end());
        }
        sort(ans.begin(), ans.end(), compare);
        printf("Case %d:\n", run++);
        for (int i = 0; i < ans.size(); ++i) {
            for (int j = 0; j < ans[i].size(); ++j) {
                if (j > 0) printf(" ");
                printf("%d", ans[i][j] + 1);
            }
            puts("");
        }
        
    }
    return 0;
}
