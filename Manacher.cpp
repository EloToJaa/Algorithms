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

int P1[NT], P2[NT];

void Manacher(string s, int n) {
    int k, l = 0, r = -1;
    FOR(i, 0, n-1) {
        k = (i > r) ? 1: min(P1[l + r - i + 1], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        P1[i + 1] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    l = 0, r = -1;
    FOR(i, 0, n-1) {
        k = (i > r) ? 0: min(P2[l + r - i + 2], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])k++;
        P2[i + 1] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
    FOR(i, 1, n) {
        cout<<P1[i]<<" ";
    }
    cout<<"\n";
    FOR(i, 1, n) {
        cout<<P2[i]<<" ";
    }
    cout<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin>>n>>s;
    Manacher(s, n);   
    return 0;
}