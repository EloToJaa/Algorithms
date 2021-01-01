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

ll T[NTREE], A[NT];
int ntree = 1;

void build(int n) {
	while(ntree < n) ntree <<= 1;
    FOR(i, 1, n) T[i + ntree - 1] = A[i];
    FORD(v, ntree - 1, 1) T[v] = max(T[lc], T[rc]);
}

void update(int v, int val) {
    v += ntree - 1;
    T[v] = val;
    v /= 2;
    while(v > 0) {
        T[v] = max(T[lc], T[rc]);
        v >>= 1;
    }
}

ll query(int l, int r) {
    l += ntree - 1; r += ntree - 1;
    ll ans = T[l];
    if(r > l) ans = max(ans, T[r]);
    while(r - l > 1) {
        if(!(l&1)) ans = max(ans, T[l + 1]);
        if(r&1) ans = max(ans, T[r - 1]);
        l >>= 1; r >>= 1;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    return 0;
}