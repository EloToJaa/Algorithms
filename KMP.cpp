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

int Pi[NT];
void Kmp(string s) {
    int n = SZ(s);
    s = "#" + s;
    FOR(i, 2, n) {
        int pref = Pi[i - 1];
        while(pref > 0 and s[pref + 1] != s[i]) pref = Pi[pref];
        if(s[pref + 1] == s[i]) pref++;
        Pi[i] = pref;
    }
}