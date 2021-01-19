#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(x) x.begin(), x.end()
#define TAB(x,n) (x)+1, (x)+((n)+1)
#define sz(x) (int)(x).size()
#define pb push_back
#define pf push_front
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int N = 2e3;

class Hash {
    vector<pll> H, pot;
    int n, m;
    string s;
    const int MOD = 1e9 + 7;
    ll mnoz(ll a, ll b) {
        return (a % MOD * (b % MOD)) % MOD;
    }
    ll dod(ll a, ll b) {
        return (a % MOD + b % MOD) % MOD;
    }
    ll ode(ll a, ll b) {
        return ((b % MOD - a % MOD + MOD) % MOD);
    }
    void build() {
        const pii P = {29, 31};
        const int S = 'a';
        H.resize(n + 2, {0, 0});
        pot.resize(m + 2, {0, 0});
        pot[0] = {1, 1};
        FOR(i, 1, m)
            pot[i] = {
                mnoz(pot[i - 1].st, P.st),
                mnoz(pot[i - 1].nd, P.nd)
            };
        FOR(i, 1, n)
            H[i] = {
                dod( H[i - 1].st, mnoz(pot[i].st, (s[i] - S + 1) ) ),
                dod( H[i - 1].nd, mnoz(pot[i].nd, (s[i] - S + 1) ) )
            };
    }

    public:
    void initialize(string input_string, int max_size = -1) {
        s = "#" + input_string;
        n = sz(s) - 1;
        if(max_size == -1) m = n;
        else m = max_size;
        build();
    }
    pll get_hash(int begin = 1, int end = -1) {
        if(end == -1) end = n;
        return {
            mnoz( ode(H[end].st, H[begin - 1].st), pot[m - end].st ),
            mnoz( ode(H[end].nd, H[begin - 1].nd), pot[m - end].nd )
        };
    }
    int size() {
        return n;
    }
};

vector<Hash> A;

bool check(int x) {
    map<pll, int> M;
    set<pll> S;
    int n = sz(A) - 2;
    FOR(j, 1, n) {
        // wrzucamy do seta wszystkie podslowa dlugosci x, unikamy powtarzajacych sie podslow
        S.clear();
        FOR(i, 1, sz(A[j]) - x + 1)
            S.insert(A[j].get_hash(i, i + x - 1));
        // przerzucamy te podslowa do mapy
        TRAV(a, S)
            M[a]++;
    }
    TRAV(a, M)
        if(a.nd == n) return true;
    return false;
}

int search_last(int l, int r) {
    while(l < r) {
        int mid = (l + r + 1) / 2;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, mx = 0;
    cin>>n;
    string s;
    vector<string> S;
    A.resize(n + 2);
    // wpisywanie danych wejsciowych
    FOR(i, 1, n) {
        cin>>s;
        mx = max(mx, sz(s));
        S.pb(s);
    }
    // tworzymy hashe dla kazdego slowa
    FOR(i, 1, n)
        A[i].initialize(S[i - 1], mx);
    
    cout<<search_last(0, mx)<<"\n";
    return 0;
}