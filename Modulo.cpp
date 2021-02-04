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
    ll MOD;
    Modulo(ll mod) {
        MOD = mod;
    }
    ll Moduluj(const ll &a) {
        if(a < MOD) return a;
        return a % MOD;
    }
    ll Power(ll a, ll b) {
        if(b == 0) return 1;
        ll ans = Power(a, b / 2);
        ans = Moduluj(ans * ans);
        if(b & 1) return Moduluj(ans * a);
        return ans;
    }
    ll Dodaj(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        if(a + b >= MOD) return a + b - MOD;
        else return a + b;
    }
    ll Odejmij(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        if(a - b < 0) return a - b + MOD;
        else return a - b;
    }
    ll Mnoz(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        return Moduluj(a * b);
    }
    ll Dziel(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        return Moduluj(a * Power(b, MOD - 2));
    }
} Mod(1e9 + 7);