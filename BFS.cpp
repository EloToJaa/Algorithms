#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e6, NT = N + 2;

vi V[NT];
bitset<NT> Vis;
queue<int> Q;
void bfs(int v) {
    Q.push(v);
    while(!Q.empty()) {
        v = Q.front();
        Q.pop();
        Vis[v] = true;
        TRAV(u, V[v]) {
            if(!Vis[u]) {
                Q.push(u);
            }
        } 
    }
}