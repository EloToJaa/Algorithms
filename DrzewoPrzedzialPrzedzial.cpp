#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& (x): (T))
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
const int N = 3e5, NT = N + 2;
const int NTREE = 524288 * 2 + 2;

ll T[NTREE], lazy[NTREE], A[NT];

int ntree = 1;
void build(int n) {
	while(ntree < n) ntree <<= 1;
    FOR(i, 1, n) T[i + ntree - 1] = A[i];
    FORD(v, ntree - 1, 1) T[v] = max(T[lc], T[rc]);
}

void push(int v, ll len) {
    T[lc] += lazy[v] * len / 2;
    T[rc] += lazy[v] * len / 2;
    lazy[lc] += lazy[v];
    lazy[rc] += lazy[v];
    lazy[v] = 0;
}

ll query(int v, int tl, int tr, int l, int r) {
    if (l <= tl and tr <= r) return T[v];
    int tm = (tl + tr) / 2;
    push(v, tr-tl+1);
    ll a = 0, b = 0;
    if(l <= tm) a = query(lc, tl, tm, l, r);
    if(r > tm) b = query(rc, tm+1, tr, l, r);
    T[v] = T[lc] + T[rc] + lazy[v] * (tr-tl+1);
    return a + b;
}

void update(int v, int tl, int tr, int l, int r, ll val) {
    if (l <= tl and tr <= r) {
        T[v] += val * (tr-tl+1);
        lazy[v] += val;
        return;
    }
    int tm = (tl + tr) / 2;
    push(v, tr-tl+1);
    if(l <= tm) update(lc, tl, tm, l, r, val);
    if(r > tm) update(rc, tm + 1, tr, l, r, val);
    T[v] = T[lc] + T[rc] + lazy[v] * (tr-tl+1);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    return 0;
}   