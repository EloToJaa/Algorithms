#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define Nwd __gcd
#define pb push_back
#define st first
#define nd second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e6, NT = N + 2;

int Rep[NT], Ile[NT];
void Union(int a, int b) {
    a = Find(a); b = Find(b);
    if(Ile[a] > Ile[b]) swap(a, b);
    Rep[a] = b;
    Ile[b] += Ile[a];
}
int Find(int a) {
    if(Rep[a] != a) Rep[a] = Find(Rep[a]);
    return Rep[a];
}
void Init(int n) {
    FOR(i, 1, n) {
        Rep[i] = i;
        Ile[i] = 1;
    }
}