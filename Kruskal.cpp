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
const int N = 1e6 + 2;

int rep[N], ile[N];
void init(int a, int b) {
    FOR(i, a, b) {
        rep[i] = i;
        ile[i] = 1;
    }
}
void Union(int a, int b) { // O(log n)
    if(ile[a] > ile[b]) swap(a, b);
    rep[a] = b;
    ile[b] += ile[a];
}
int Find(int a) { // O(n)
    if(rep[a] != a) rep[a] = Find(rep[a]);
    return rep[a];
}

struct Edge {
    int a,b,w; // a - poczatek, b - koniec, w - waga
};
vector<pii> V[N];
vector<Edge> wyn;
Edge t[N];
int tin = 0;

void addEdge(int a, int b, int w) {
    V[a].pb({b, w});
    V[b].pb({a, w});
    t[ ++tin ] = {a, b, w};
}

bool fun(Edge a, Edge b) {
    return a.w < b.w;
}

/* przykladowe dane
9 14
7 6 1
8 2 2
6 5 2
0 1 4
2 5 4
8 6 6
2 3 7
7 8 7
0 7 8
1 2 8
3 4 9
5 4 10
1 7 11
3 5 14
*/

void Kruskal(int n, int m) { // znajdz MST - minimalne drzewo rozpinajace, O(m log m)
    init(0, n - 1); // przygotuj Find and Union dla wierzcholkow, w tym przykladzie numeracja wierzcholkow jest od 0 do n - 1
    sort(t + 1, t + (m + 1), fun); // sort krawedzi po wagach
    int x,y;
    FOR(i,1,m) {
        x = Find(t[i].a);
        y = Find(t[i].b);
        if(x != y) {
            wyn.pb(t[i]); // dodajemy krawedz do wyniku
            Union(x, y);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // wprowadzanie grafu
    int n,m,a,b,c;
    cin>>n>>m;
    FOR(i,1,m) {
        cin>>a>>b>>c;
        addEdge(a, b, c);
    }
    Kruskal(n, m);
    for(auto e: wyn) cout<<e.a<<" -> "<<e.b<<" "<<e.w<<"\n";
    return 0;
}