#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define TRAV(x,T) for(auto& (x): (T))
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
typedef vector<int> vi;
const int N = 1e3 + 2;

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
    int char_to_int(char a) {
        if(a == '#') return 1;
        return a - 'A' + 2;
    }
    void build() {
        const pii P = {29, 31};
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
                dod( H[i - 1].st, mnoz(pot[i].st, char_to_int(s[i]) ) ),
                dod( H[i - 1].nd, mnoz(pot[i].nd, char_to_int(s[i]) ) )
            };
    }
    void create_object(string input_string, int max_size) {
        s = "#" + input_string;
        n = sz(s) - 1;
        if(max_size == -1) m = n;
        else m = max_size;
        build();
    }

    public:
    Hash() {}
    Hash(string input_string) {
        create_object(input_string, -1);
    }
    Hash(string input_string, int max_size) {
        create_object(input_string, max_size);
    }
    void initialize(string input_string) {
        create_object(input_string, -1);
    }
    void initialize(string input_string, int max_size) {
        create_object(input_string, max_size);
    }
    pll get_hash(int begin = 1, int end = -1) {
        if(end == -1) end = n;
        return {
            mnoz( ode(H[end].st, H[begin - 1].st), pot[m - end].st ),
            mnoz( ode(H[end].nd, H[begin - 1].nd), pot[m - end].nd )
        };
    }
    char get_char(int index) {
        return s[index];
    }
    int size() {
        return n;
    }
} H;

int ilerownych(int a, int b) {
    int l = 0, r = min(sz(H) - a, sz(H) - b), mid;
    if(H.get_char(a) != H.get_char(b)) return 0;
    while(l < r) {
        mid = (l + r + 1) / 2;
        if(H.get_hash(a, a + mid) == H.get_hash(b, b + mid)) l = mid;
        else r = mid - 1;
    }
    return l + 1;
}

bool comp(int a, int b) { // compare suffixes
    int x = ilerownych(a, b);
    return H.get_char(a + x) < H.get_char(b + x); 
}

int SA[N];
void sa() {
    int n = sz(H);
    FOR(i, 1, n)
        SA[i] = i;
    sort(TAB(SA, n), comp);
    cout<<"SA:\n";
    FOR(i, 1, n) {
        cout<<SA[i]<<": ";
        FOR(j, SA[i], n) cout<<H.get_char(j); cout<<"\n";
    }
}

int LCP[N];
void lcp() {
    int n = sz(H);
    LCP[1] = -1;
    FOR(i, 2, n)
        LCP[i] = ilerownych(SA[i - 1], SA[i]);
    cout<<"LCP:\n"; FOR(i, 1, n) cout<<LCP[i]<<" "; cout<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    H.initialize(s + "#");
    sa();
    lcp();
    int sum = 0, n = sz(H) - 1;
    FOR(i, 3, n + 1)
        sum += LCP[i];
    cout<<n * (n + 1) / 2 - sum<<"\n";
    return 0;
}