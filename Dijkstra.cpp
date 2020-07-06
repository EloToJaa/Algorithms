#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
const int N = 1e6 + 2;
const ll INF = 1e18 + 2;

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
        for(auto x: V[v]) {
            int u = x.st, c = x.nd;
            if(D[v] + c < D[u]) {
                D[u] = D[v] + c;
                path[u] = v;
                Q.push({-D[u], u});
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a, b, c;
    cin>>n>>m;
    FOR(i, 1, m) {
        cin>>a>>b>>c;
        V[a].pb({b, c});
        V[b].pb({a, c});
    }
    dijkstra(1);
    FOR(i, 1, n) cout<<D[i]<<" ";
    return 0;
}