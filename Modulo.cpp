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

struct Modulo {
    const ll MOD = 1e9 + 7;
    ll val;
    ll Modulate(const ll &a) {
        if(a < MOD) return a;
        return a % MOD;
    }
    ll Pow(ll a, ll b) {
        if(b == 0) return 1;
        ll ans = Modulate(Pow(a, b / 2));
        ans = Modulate(ans * ans);
        if(b & 1) return Modulate(ans * a);
        return ans;
    }
    pll ExtGcd(ll a, ll b) {
        if(b == 0) return {1, 0};
        pll ans = ExtGcd(b, a % b);
        return { ans.second, ans.first - (a / b) * ans.second };
    }
    ll InverseMod(const ll &a) {
        ll b = ExtGcd(a, MOD).st;
        if(b < 0) b += MOD;
        return b;
    }
    void operator+=(const Modulo &x) {
        val += x.val;
        if(val >= MOD) val -= MOD;
    }
    void operator-=(const Modulo &x) {
        val -= x.val;
        if(val < 0) val += MOD;
    }
    void operator*=(const Modulo &x) {
        val *= x.val;
        val = Modulate(val);
    }
    void operator/=(const Modulo &x) {
        val *= InverseMod(x.val);
        val = Modulate(val);
    }
    void operator=(const Modulo &x) {
        val = Modulate(x.val);
    }
    void operator=(const ll &x) {
        val = Modulate(x);
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    return 0;
}