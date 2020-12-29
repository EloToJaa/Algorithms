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
typedef pair<ll, int> pli;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e6, NT = N + 2;
const ll INF = (ll)1e18 + 2;

ll path[2 * N], D[N];
vector<pii> V[N];
priority_queue<pli> Q;
int n, m;

void dijkstra(int v) {
    FOR(i, 1, n) D[i] = INF;
    D[v] = 0;
    Q.push({0, v});
    while(!Q.empty()) {
        v = Q.top().nd;
        ll dist = -Q.top().st;
        Q.pop();
        if(dist > D[v])
            continue;
        TRAV(x, V[v]) {
            auto [u, c] = x;
            if(D[v] + c < D[u]) {
                D[u] = D[v] + c;
                path[u] = v;
                Q.push({-D[u], u});
            }
        }
    }
}