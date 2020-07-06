#include<bits/stdc++.h>
using namespace std; // ???
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 1e6 + 2;
const int LOG = 20; // log n
int anc[N][22], gle[N];
int n, m;

class Graf {
public:
    vector<int> V[N];
    void addEdge(int a, int b);
};
void Graf::addEdge(int a, int b) {
    V[a].pb(b);
    V[b].pb(a);
}

Graf G;

void dfs(int u, int p) { // u - wierzcholek wyjscia p - parent
    anc[u][0] = p;
    FOR(i, 1, LOG) {
        anc[u][i] = anc[ anc[u][i - 1] ][i - 1];
    }
    for(auto v: G.V[u]) {
        if(v != p) {
            gle[v] = gle[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int a, int b) {
    if(gle[b] < gle[a]) swap(a, b);

    FORD(k, 20, 0) {
        if(gle[ anc[b][k] ] >= gle[a]) b = anc[b][k];
    }

    if(a == b) return a;

    FORD(k, 20, 0) {
        if(anc[a][k] != anc[b][k]) {
            a = anc[a][k];
            b = anc[b][k];
        }
    }

    return anc[a][0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    int a,b;
    FOR(i, 1, m) {
        cin>>a>>b;
        G.addEdge(a,b);
    }
    dfs(1,1); // preprocessing
    cout<<lca(8,4)<<"\n";
    return 0;
}