#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
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
const int N = 1e6, NT = N + 2;

int P[NT], S[NT];
void kmp(string s, int n) {
    s = "#" + s;
    FOR(i, 2, n) {
        int pref = P[i - 1];
        while(pref > 0 && s[pref + 1] != s[i]) pref = P[pref];
        if(s[pref + 1] == s[i]) pref++;
        P[i] = pref;
    }

    FOR(i, 1, n) {
        if(P[i] == 0) S[i] = i;
        else S[i] = S[P[i]];
    }
}

ll solve(int n) {
    ll ans = 0;
    FOR(i, 1, n)
        if(S[i] <= i / 2)
            ans += (i - S[i]);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin>>n>>s;
    kmp(s, n);
    cout<<solve(n)<<"\n";
    return 0;
}